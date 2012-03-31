#include "Common.h"
#include "Database/DatabaseEnv.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#include "World.h"
#include "ObjectMgr.h"
#include "AuctionHouseMgr.h"
#include "AccountMgr.h"
#include "PlayerDump.h"
#include "SpellMgr.h"
#include "Player.h"
#include "Opcodes.h"
#include "GameObject.h"
#include "Chat.h"
#include "Log.h"
#include "Guild.h"
#include "ObjectAccessor.h"
#include "MapManager.h"
#include "Language.h"
#include "GridNotifiersImpl.h"
#include "CellImpl.h"
#include "Weather.h"
#include "PointMovementGenerator.h"
#include "TargetedMovementGenerator.h"
#include "SkillDiscovery.h"
#include "SkillExtraItems.h"
#include "SystemConfig.h"
#include "Config.h"
#include "Util.h"
#include "ItemEnchantmentMgr.h"
#include "BattlegroundMgr.h"
#include "InstanceSaveMgr.h"
//#include "InstanceData.h"
#include "CreatureEventAIMgr.h"
#include "DBCEnums.h"
#include "OutdoorPvPMgr.h"
#include "Group.h"
#include "BattlefieldMgr.h"

enum eEnums
{
    COUNT                        = 17,
    BAG_ID                        = 21841,


    FIELD_ID                    = 0,
    FIELD_ID_COMPTE,
    FIELD_NOM_PERSO,
    FIELD_ID_PCIBLE,
    FIELD_SERVEUR_ORIGINE,
    FIELD_LEVEL,
    FIELD_RACE,
    FIELD_CLASSE,

    FIELD_METIER1,
    FIELD_SKILL1,

    FIELD_METIER2,
    FIELD_SKILL2,

    FIELD_METIER3,
    FIELD_SKILL3,

    FIELD_METIER4,
    FIELD_SKILL4,

    FIELD_METIER5,
    FIELD_SKILL5,

    FIELD_SKILL_MOUNT,

    FIELD_ARMORY,
    FIELD_DATE,
    FIELD_ETAT_OUVERTURE,
    FIELD_ETAT_RECUP,
    FIELD_ID_JETON,
    FIELD_MONEY_AMOUNT
};

bool ChatHandler::HandleRecupCommand(const char* args)
{
	SQLTransaction trans = CharacterDatabase.BeginTransaction();

    if (sWorld->getBoolConfig(CONFIG_RECUP_ENABLE) != true)
    {
        SendSysMessage("Système de recupération desactivé");
        SetSentErrorMessage(true);
        return false;
    }


    Player* pPlayer = m_session->GetPlayer();            //Objet Player
    const char* pName = m_session->GetPlayerName();        //Nom du joueur
    uint64 pGUID = m_session->GetPlayer()->GetGUID();    //GUID du joueur
    uint32 pAccountID = m_session->GetAccountId();        //ID de l'account

    Item* tmp;

    QueryResult result = RecupDatabase.PQuery("SELECT * FROM %s WHERE id_compte = %u AND etat_recuperation=0 AND etat_ouverture=10 AND id_perso_cible = %u", sWorld->GetRecupTable(), pAccountID, pGUID);
    //On recherche les demandes avec le bon id compte, id joueur, et dans les récupes pas faites et acceptées

    if (!result || result->GetRowCount() == 0)
    {
        result = RecupDatabase.PQuery("SELECT * FROM %s WHERE id_compte = %u AND etat_recuperation=0 AND etat_ouverture=10 AND classe=6", sWorld->GetRecupTable(), pAccountID);
        
        if (!result || result->GetRowCount() == 0)
        {
            SendSysMessage(LANG_RECUP_NO_RESULT);
            //Pas de résultat, la demande n'est pas validée, ou est refusée.
            SetSentErrorMessage(true);
            return false;
        }
    }

    Field* fields = result->Fetch(); //On récupère les résultats

    uint8 rEtat = fields[FIELD_ETAT_OUVERTURE].GetUInt8();

    switch (rEtat)
    {
        case 1:
            SendSysMessage("Attente de validation");
            SetSentErrorMessage(true);
            return false;
            break;
        case 2:
            SendSysMessage("Attente de validation guilde");
            SetSentErrorMessage(true);
            return false;
            break;
        case 3:
            SendSysMessage("Doublons");
            SetSentErrorMessage(true);
            return false;
            break;
        case 4:
            SendSysMessage("Fake recup");
            SetSentErrorMessage(true);
            return false;
            break;
        case 5:
            SendSysMessage("Manque de screens");
            SetSentErrorMessage(true);
            return false;
            break;
        case 6:
            SendSysMessage("Serveur non Blizzlike");
            SetSentErrorMessage(true);
            return false;
            break;
        case 7:
            SendSysMessage("Récupération déjà effectuée");
            SetSentErrorMessage(true);
            return false;
            break;
        case 8:
            SendSysMessage("Demande supérieure a 1 mois");
            SetSentErrorMessage(true);
            return false;
            break;
        case 9:
            SendSysMessage("Pas le level 60 minimum");
            SetSentErrorMessage(true);
            return false;
            break;
        case 10:
            //Validée
            break;
        case 12:
            //Guilde Validée
            break;
        case 13:
            SendSysMessage("Recupération à partir d'Odyssée");
            SetSentErrorMessage(true);
            return false;
            break;
        case 14:
            SendSysMessage("Pas de lien armurerie");
            SetSentErrorMessage(true);
            return false;
            break;
    }

    uint32 rID = fields[FIELD_ID].GetUInt32();        //ID de la récupe
    uint8 rLvl = fields[FIELD_LEVEL].GetUInt8();    //Level à appliquer
    uint8 rRace = fields[FIELD_RACE].GetUInt8();    //Vérification race
    uint8 rClasse = fields[FIELD_CLASSE].GetUInt8();//Vérification classe
    uint8 rMountSk = fields[FIELD_SKILL_MOUNT].GetUInt8();
    uint32 rJetonId = fields[FIELD_ID_JETON].GetUInt32(); //On chope l'id jeton <:
    uint32 rMoneyAmount = fields[FIELD_MONEY_AMOUNT].GetUInt32();

    if (rRace != pPlayer->getRace())
    {
        SendSysMessage(LANG_RECUP_BAD_RACE);
        SetSentErrorMessage(true);
        return false;
    }

    if (rClasse != pPlayer->getClass())
    {
        SendSysMessage(LANG_RECUP_BAD_CLASS);
        SetSentErrorMessage(true);
        return false;
    }

    if (pPlayer->GetSelectedPlayer() != pPlayer)
    {
        //On vérifie la sélection pour éviter de récupérer sur quelqu'un d'autre
        SendSysMessage(LANG_RECUP_BAD_SELECT);
        SetSentErrorMessage(true);
        return false;
    }

    if (rLvl < 60 || rLvl > 80)
    {
        SendSysMessage(LANG_RECUP_BAD_LEVEL);
        SetSentErrorMessage(true);
        return false;
    }

    //pPlayer->SetLevel(rLvl);
    HandleCharacterLevel(pPlayer, pGUID, pPlayer->getLevel(), rLvl);

    MailDraft draft(GetTrinityString(LANG_MAIL_SUBJECT), GetTrinityString(LANG_MAIL_CONTENT));
    //11009 Titre, 11010 Texte

    uint32 skillid;
    uint32 skill;
    //Récupération des métiers
    pPlayer->resetSpells();
    for (int i = 0; i < 5; ++i)
    {
        skillid = fields[FIELD_METIER1 + 2*i].GetUInt32();
        skill = fields[FIELD_SKILL1 + 2*i].GetUInt32();
        //Droles de calculs, mais vérifiez, ça marche.
        if (skill <= 0 || skill > 450)
            continue;
        if (skill > 375 && skill <= 450)
            skill = 400;
        ChatHandler::HandleRecupLearnCommand(skillid);

        switch (skillid)
        {
            default:
                continue;
                break;
            case 51309: //Couture
                ChatHandler::HandleRecupSetSkillCommand(197, skill);
                break;
            case 51296: //Cuisine
                ChatHandler::HandleRecupSetSkillCommand(185, skill);
                break;
            case 50305: //Dépeuceur
                ChatHandler::HandleRecupSetSkillCommand(393, skill);
                break;
            case 51313: //Enchanteur
                ChatHandler::HandleRecupSetSkillCommand(333, skill);
                tmp = Item::CreateItem(22463, 1, pPlayer);
                tmp->SaveToDB(trans);
                draft.AddItem(tmp);
                break;
            case 51300: //Forge
                ChatHandler::HandleRecupSetSkillCommand(164, skill);
                break;
            case 50300: //Herboriste
                ChatHandler::HandleRecupSetSkillCommand(182, skill);
                break;
            case 51306: //Ingénieur
                ChatHandler::HandleRecupSetSkillCommand(202, skill);
                break;
            case 51311: //Joallier
                ChatHandler::HandleRecupSetSkillCommand(755, skill);
                break;
            case 50310: //Mineur
                ChatHandler::HandleRecupSetSkillCommand(186, skill);
                break;
            case 51294: //Pêche
                ChatHandler::HandleRecupSetSkillCommand(356, skill);
                break;
            case 45542: //Secourisme
                ChatHandler::HandleRecupSetSkillCommand(129, skill);
                break;
            case 51302: //Travail du cuir
                ChatHandler::HandleRecupSetSkillCommand(165, skill);
                break;
            case 51304: //Alcimiste
                ChatHandler::HandleRecupSetSkillCommand(171, skill);
                break;
            case 45363: //Calligraphie
                ChatHandler::HandleRecupSetSkillCommand(773, skill);
                break;
        }
    }

    switch(pPlayer->GetTeam()) //Montures
    {
        case ALLIANCE:
            ChatHandler::HandleRecupLearnCommand(32292);
            ChatHandler::HandleRecupLearnCommand(34091);
            break;
        case HORDE:
            ChatHandler::HandleRecupLearnCommand(34091);
            ChatHandler::HandleRecupLearnCommand(32246);
            break;
        default:
            SendSysMessage(LANG_RECUP_PROBLEM);
            break;
    }

    switch(pPlayer->getClass())
    {
        case CLASS_SHAMAN:
            ChatHandler::HandleRecupLearnCommand(196);
            ChatHandler::HandleRecupLearnCommand(1180);
            ChatHandler::HandleRecupLearnCommand(15590);
            ChatHandler::HandleRecupLearnCommand(197);
            ChatHandler::HandleRecupLearnCommand(196);
            ChatHandler::HandleRecupLearnCommand(199);
            ChatHandler::HandleRecupLearnCommand(3599);
            ChatHandler::HandleRecupLearnCommand(8071);
            ChatHandler::HandleRecupLearnCommand(5396);
            ChatHandler::HandleRecupLearnCommand(5394);
            break;
        case CLASS_WARRIOR:
            ChatHandler::HandleRecupLearnCommand(264);
            ChatHandler::HandleRecupLearnCommand(2567);
            ChatHandler::HandleRecupLearnCommand(15590);
            ChatHandler::HandleRecupLearnCommand(227);
            ChatHandler::HandleRecupLearnCommand(1180);
            ChatHandler::HandleRecupLearnCommand(266);
            ChatHandler::HandleRecupLearnCommand(197);
            ChatHandler::HandleRecupLearnCommand(199);
            ChatHandler::HandleRecupLearnCommand(5011);
            ChatHandler::HandleRecupLearnCommand(200);
            ChatHandler::HandleRecupLearnCommand(202);
            ChatHandler::HandleRecupLearnCommand(7386);
            ChatHandler::HandleRecupLearnCommand(71);
            ChatHandler::HandleRecupLearnCommand(355);
            ChatHandler::HandleRecupLearnCommand(20252);
            ChatHandler::HandleRecupLearnCommand(2458);
            break;
        case CLASS_PALADIN:
            ChatHandler::HandleRecupLearnCommand(196);
            ChatHandler::HandleRecupLearnCommand(197);
            ChatHandler::HandleRecupLearnCommand(200);
            ChatHandler::HandleRecupLearnCommand(202);
            ChatHandler::HandleRecupLearnCommand(201);
            ChatHandler::HandleRecupLearnCommand(7328);
            ChatHandler::HandleRecupLearnCommand(13819);
            ChatHandler::HandleRecupLearnCommand(34767);
            break;
        case CLASS_ROGUE:
            ChatHandler::HandleRecupLearnCommand(264);
            ChatHandler::HandleRecupLearnCommand(15590);
            ChatHandler::HandleRecupLearnCommand(266);
            ChatHandler::HandleRecupLearnCommand(198);
            ChatHandler::HandleRecupLearnCommand(5011);
            ChatHandler::HandleRecupLearnCommand(201);

            ChatHandler::HandleRecupLearnCommand(1804);
            ChatHandler::HandleRecupSetSkillCommand(633, 375);
            break;
        case CLASS_PRIEST:
            ChatHandler::HandleRecupLearnCommand(227);
            ChatHandler::HandleRecupLearnCommand(1180);
            break;
        case CLASS_DEATH_KNIGHT:
            ChatHandler::HandleRecupLearnCommand(199);
            ChatHandler::HandleRecupLearnCommand(198);
            ChatHandler::HandleRecupLearnCommand(50977);
            ChatHandler::HandleRecupLearnCommand(48778);
            ChatHandler::HandleRecupLearnCommand(53428);
            break;
        case CLASS_MAGE:
            ChatHandler::HandleRecupLearnCommand(1180);
            ChatHandler::HandleRecupLearnCommand(201);
            break;
        case CLASS_WARLOCK:
            ChatHandler::HandleRecupLearnCommand(201);
            ChatHandler::HandleRecupLearnCommand(227);
            ChatHandler::HandleRecupLearnCommand(688);
            ChatHandler::HandleRecupLearnCommand(697);
            ChatHandler::HandleRecupLearnCommand(712);
            ChatHandler::HandleRecupLearnCommand(691);
            ChatHandler::HandleRecupLearnCommand(1122);
            ChatHandler::HandleRecupLearnCommand(5784);
            ChatHandler::HandleRecupLearnCommand(23161);
            break;
        case CLASS_HUNTER:
            ChatHandler::HandleRecupLearnCommand(264);
            ChatHandler::HandleRecupLearnCommand(2567);
            ChatHandler::HandleRecupLearnCommand(15590);
            ChatHandler::HandleRecupLearnCommand(227);
            ChatHandler::HandleRecupLearnCommand(1180);
            ChatHandler::HandleRecupLearnCommand(197);
            ChatHandler::HandleRecupLearnCommand(201);
            ChatHandler::HandleRecupLearnCommand(5011);
            ChatHandler::HandleRecupLearnCommand(200);
            ChatHandler::HandleRecupLearnCommand(202);
            ChatHandler::HandleRecupLearnCommand(883);
            ChatHandler::HandleRecupLearnCommand(1515);
            ChatHandler::HandleRecupLearnCommand(6991);
            ChatHandler::HandleRecupLearnCommand(2641);
            ChatHandler::HandleRecupLearnCommand(982);
            ChatHandler::HandleRecupLearnCommand(136);
            ChatHandler::HandleRecupLearnCommand(23357);
            break;
        case CLASS_DRUID:
            ChatHandler::HandleRecupLearnCommand(15590);
            ChatHandler::HandleRecupLearnCommand(199);
            ChatHandler::HandleRecupLearnCommand(198);
            ChatHandler::HandleRecupLearnCommand(200);
            ChatHandler::HandleRecupLearnCommand(6795);
            ChatHandler::HandleRecupLearnCommand(8946);
            ChatHandler::HandleRecupLearnCommand(1066);
            ChatHandler::HandleRecupLearnCommand(9634);
            ChatHandler::HandleRecupLearnCommand(783);
            ChatHandler::HandleRecupLearnCommand(768);
            ChatHandler::HandleRecupLearnCommand(33943);
            ChatHandler::HandleRecupLearnCommand(40120);
            ChatHandler::HandleRecupLearnCommand(6807);
            ChatHandler::HandleRecupLearnCommand(18960);
            break;
        default:
            SendSysMessage(LANG_RECUP_PROBLEM);
            break;
    }

    switch (pPlayer->getRace())
    {
        case RACE_HUMAN:
            ChatHandler::HandleRecupLearnCommand(468);
            ChatHandler::HandleRecupLearnCommand(65640);
            break;
        case RACE_ORC:
            ChatHandler::HandleRecupAddItemCommand(5668);
            ChatHandler::HandleRecupAddItemCommand(18796);
            break;
        case RACE_DWARF:
            ChatHandler::HandleRecupLearnCommand(6898);
            ChatHandler::HandleRecupLearnCommand(23240);
            break;
        case RACE_NIGHTELF:
            ChatHandler::HandleRecupAddItemCommand(8631);
            ChatHandler::HandleRecupAddItemCommand(18766);
            break;
        case RACE_UNDEAD_PLAYER:
            ChatHandler::HandleRecupLearnCommand(65645);
            ChatHandler::HandleRecupLearnCommand(17464);
            break;
        case RACE_TAUREN:
            ChatHandler::HandleRecupLearnCommand(18990);
            ChatHandler::HandleRecupLearnCommand(23249);
            break;
        case RACE_GNOME:
            ChatHandler::HandleRecupLearnCommand(10969);
            ChatHandler::HandleRecupLearnCommand(23223);
            break;
        case RACE_TROLL:
            ChatHandler::HandleRecupAddItemCommand(8588);
            ChatHandler::HandleRecupAddItemCommand(18788);
            break;
        case RACE_BLOODELF:
            ChatHandler::HandleRecupLearnCommand(35020);
            ChatHandler::HandleRecupLearnCommand(33660);
            break;
        case RACE_DRAENEI:
            ChatHandler::HandleRecupLearnCommand(34406);
            ChatHandler::HandleRecupLearnCommand(47037);
            break;

        default:
            SendSysMessage(LANG_RECUP_PROBLEM);
            break;
    }    

    ChatHandler::HandleMaxSkillCommand("");

    ChatHandler::HandleRecupLearnCommand(762);
    ChatHandler::HandleRecupSetSkillCommand(762, rMountSk);
    switch (rMountSk)
    {
        default:
        case 0:
            ChatHandler::HandleRecupSetSkillCommand(762, 1);
            break;
        case 75:
            ChatHandler::HandleRecupLearnCommand(33388);
            break;
        case 150:
            ChatHandler::HandleRecupLearnCommand(33388);
            ChatHandler::HandleRecupLearnCommand(34091);
            break;
        case 225:
            ChatHandler::HandleRecupLearnCommand(33388);
            ChatHandler::HandleRecupLearnCommand(34091);
            ChatHandler::HandleRecupLearnCommand(33391);
            break;
        case 300:
            ChatHandler::HandleRecupLearnCommand(33388);
            ChatHandler::HandleRecupLearnCommand(34091);
            ChatHandler::HandleRecupLearnCommand(33391);
            ChatHandler::HandleRecupLearnCommand(34090);
            break;
    }
    ChatHandler::HandleRecupSetSkillCommand(762, rMountSk);

    if (sObjectMgr->GetItemPrototype(rJetonId))
    {
        tmp = Item::CreateItem(rJetonId, COUNT, pPlayer);
		tmp->SaveToDB(trans);
        draft.AddItem(tmp);
    }

    tmp = Item::CreateItem(BAG_ID, 1, pPlayer);
    tmp->SaveToDB(trans);
    draft.AddItem(tmp);

    tmp = Item::CreateItem(BAG_ID, 1, pPlayer);
    tmp->SaveToDB(trans);
    draft.AddItem(tmp);

    tmp = Item::CreateItem(BAG_ID, 1, pPlayer);
    tmp->SaveToDB(trans);
    draft.AddItem(tmp);

    tmp = Item::CreateItem(BAG_ID, 1, pPlayer);
	tmp->SaveToDB(trans);
    draft.AddItem(tmp);          //On crée 4 Sacs
     
    /*if (pPlayer->getLevel() == 80)
        draft.AddMoney(36000000);
    else
        draft.AddMoney(30000000);*/

    draft.AddMoney(rMoneyAmount);

    switch (pPlayer->getClass()) //A voir, il serait peut être judicieux de créer un nouveau mail pour les classes
    {
        case CLASS_SHAMAN:
            tmp = Item::CreateItem(5175, 1, pPlayer);
			tmp->SaveToDB(trans);
            draft.AddItem(tmp);
            tmp = Item::CreateItem(5176, 1, pPlayer);
            tmp->SaveToDB(trans);
            draft.AddItem(tmp);
            tmp = Item::CreateItem(5177, 1, pPlayer);
            tmp->SaveToDB(trans);
            draft.AddItem(tmp);
            tmp = Item::CreateItem(5178, 1, pPlayer);
            tmp->SaveToDB(trans);
            draft.AddItem(tmp);
            break;
        case CLASS_DEATH_KNIGHT:
            tmp = Item::CreateItem(32570, 1, pPlayer);
            tmp->SaveToDB(trans);
            draft.AddItem(tmp);
            tmp = Item::CreateItem(30903, 1, pPlayer);
            tmp->SaveToDB(trans);
            draft.AddItem(tmp);
            tmp = Item::CreateItem(28824, 1, pPlayer);
            tmp->SaveToDB(trans);
            draft.AddItem(tmp);
            tmp = Item::CreateItem(33215, 1, pPlayer);
            tmp->SaveToDB(trans);
            draft.AddItem(tmp);
            tmp = Item::CreateItem(32373, 1, pPlayer);
            tmp->SaveToDB(trans);
            draft.AddItem(tmp);
            break;
        default:
            break;
    }

    draft.SendMailTo(trans, MailReceiver(pPlayer), MailSender(MAIL_NORMAL, 3)); //On envoie le mail

    pPlayer->SaveToDB();    

    sLog->outSimple("Récupération d'ID %u [Joueur %u %s (IP : %s)] effectuée", rID, pGUID, pName, pPlayer->GetSession()->GetRemoteAddress().c_str());
    //On met dans le log la récupe 
    RecupDatabase.PExecute("UPDATE %s SET etat_recuperation = 1, etat_ouverture = 7 WHERE id = %u", sWorld->GetRecupTable(), rID);
    //Et on termine la récupération

    switch(pPlayer->GetTeam()) //Téléportation finale
    {
        GameTele const* tele;
        case ALLIANCE:
            tele = sObjectMgr->GetGameTele("allyzone");
            if (tele)
                pPlayer->TeleportTo(tele->mapId, tele->position_x, tele->position_y, tele->position_z, tele->orientation);
            pPlayer->PlayDirectSound(8455);
            break;
        case HORDE:
            tele = sObjectMgr->GetGameTele("hordezone");
            if (tele)
                pPlayer->TeleportTo(tele->mapId, tele->position_x, tele->position_y, tele->position_z, tele->orientation);
            pPlayer->PlayDirectSound(8454);
            break;
        default:
            SendSysMessage(LANG_RECUP_PROBLEM);
            pPlayer->PlayDirectSound(11803);
            break;
    }
	CharacterDatabase.CommitTransaction(trans);
    SendSysMessage(LANG_RECUP_FINISH);

    return true;
}

bool ChatHandler::HandleBumpCommand(const char *args)
{
    if (!*args)
        return false;

    float BumpSpeed = (float)atof((char*)args);

    if (BumpSpeed > 600.0f || BumpSpeed < 0.1f)
    {
        SendSysMessage(LANG_BAD_VALUE);
        SetSentErrorMessage(true);
        return false;
    }

    Player *pTarget = getSelectedPlayer();

    if (pTarget == NULL)
    {
        SendSysMessage(LANG_NO_CHAR_SELECTED);
        SetSentErrorMessage(true);
        return false;
    }

    if (HasLowerSecurity(pTarget, 0))
        return false;

    std::string chrNameLink = GetNameLink(pTarget);

    if(pTarget->isInFlight())
    {
        PSendSysMessage(LANG_CHAR_IN_FLIGHT,chrNameLink.c_str());
        SetSentErrorMessage(true);
        return false;
    }

    //pTarget->GetMotionMaster()->MoveKnockbackFrom(pTarget->GetPositionX(), pTarget->GetPositionY(), BumpSpeed, BumpSpeed);
    //pTarget->GetMotionMaster()->MoveJumpTo(pTarget->GetOrientation() + M_PI, BumpSpeed, BumpSpeed);

    WorldPacket data(SMSG_MOVE_KNOCK_BACK, 50);
    data.append(pTarget->GetPackGUID());
    data << getMSTime();
    data << float(cosf(pTarget->GetOrientation()+M_PI));
    data << float(sinf(pTarget->GetOrientation()+M_PI));
    data << float(BumpSpeed);
    data << float(-BumpSpeed);
    ((Player*)pTarget)->GetSession()->SendPacket(&data);

    return true;
}
/*
bool ChatHandler::HandleAchievementCompleteCommand(const char *args)
{
    if (!*args)
        return false;

    //uint32 AchievementId = (uint32)atol((char*)args);
    char* pParam1 = extractKeyFromLink((char*)args,"Hachievement");

    uint32 AchievementId = atoi(pParam1);

    if (!AchievementId)
        return false;

    Player *pTarget = getSelectedPlayer();

    if (pTarget == NULL)
    {
        SendSysMessage(LANG_NO_CHAR_SELECTED);
        SetSentErrorMessage(true);
        return false;
    }


    std::string chrNameLink = GetNameLink(pTarget);

    AchievementEntry const* AE = GetAchievementStore()->LookupEntry(AchievementId);

    if (!AE)
    {
        SendSysMessage("L'achievement existe pas. NOUB !");
        SetSentErrorMessage(true);
        return false;
    }

    pTarget->CompletedAchievement(AE);

    SendSysMessage("Haut-Fait ajoute");
    
    return true;
}

bool ChatHandler::HandleAchievementRemoveCommand(const char *args)
{
    if (!*args)
        return false;

    char* pParam1 = extractKeyFromLink((char*)args,"Hachievement");

    uint32 AchievementId = atoi(pParam1);

    if (!AchievementId)
        return false;


    Player *pTarget = getSelectedPlayer();

    if (pTarget == NULL)
    {
        SendSysMessage(LANG_NO_CHAR_SELECTED);
        SetSentErrorMessage(true);
        return false;
    }

    std::string chrNameLink = GetNameLink(pTarget);

    AchievementEntry const *AE = sAchievementStore.LookupEntry(AchievementId);

    if (!AE)
    {
        SendSysMessage("Le haut fait existe pas. NOUB !");
        SetSentErrorMessage(true);
        return false;
    }

    CharacterDatabase.PExecute("DELETE FROM character_achievement WHERE guid = %u AND achievement = %u", pTarget->GetGUIDLow(), AchievementId);

    AchievementReward const* reward = sAchievementMgr.GetAchievementReward(AE);

    if (CharTitlesEntry const* TEntry = sCharTitlesStore.LookupEntry(reward->titleId[pTarget->GetTeam() == ALLIANCE ? 0 : 1]))
        pTarget->SetTitle(TEntry, true);


    SendSysMessage("Haut-Fait supprimé");

    return true;
}*/

bool ChatHandler::HandleRecupLearnCommand(uint32 arg)
{
    Player* targetPlayer = m_session->GetPlayer();

    if(!arg || !sSpellStore.LookupEntry(arg))
        return false;

    SpellEntry const* spellInfo = sSpellStore.LookupEntry(arg);

    if (targetPlayer->HasSpell(arg))
        return false;

    targetPlayer->learnSpell(arg,false);

	uint32 first_spell = sSpellMgr->GetFirstSpellInChain(arg);
    if(GetTalentSpellCost(first_spell))
        targetPlayer->SendTalentsInfoData(false);

    return true;
}

bool ChatHandler::HandleRecupSetSkillCommand(uint32 skill, uint32 level)
{
    Player * target = m_session->GetPlayer();

    SkillLineEntry const* sl = sSkillLineStore.LookupEntry(skill);
    if (!sl)
    {
        return false;
    }

    if (!target->GetSkillValue(skill))
    {
        return false;
    }

    int32 max = target->GetPureMaxSkillValue(skill);

    if (level <= 0 || level > 450)
        level = 1;

    target->SetSkill(skill, target->GetSkillStep(skill), level, max);
    return true;
}

bool ChatHandler::HandleRecupAddItemCommand(uint32 itemId, int32 count)
{

    Player* pl = m_session->GetPlayer();
    Player* plTarget = pl;

    ItemPrototype const *pProto = sObjectMgr->GetItemPrototype(itemId);
    if(!pProto)
    {
        return false;
    }

    //Subtract
    if (count < 0)
    {
        plTarget->DestroyItemCount(itemId, -count, true, false);
        return true;
    }

    //Adding items
    uint32 noSpaceForCount = 0;

    // check space and find places
    ItemPosCountVec dest;
    uint8 msg = plTarget->CanStoreNewItem( NULL_BAG, NULL_SLOT, dest, itemId, count, &noSpaceForCount );
    if( msg != EQUIP_ERR_OK )                               // convert to possible store amount
        count -= noSpaceForCount;

    if( count == 0 || dest.empty())                         // can't add any
    {
        PSendSysMessage(LANG_ITEM_CANNOT_CREATE, itemId, noSpaceForCount );
        SetSentErrorMessage(true);
        return false;
    }

    Item* item = plTarget->StoreNewItem( dest, itemId, true, Item::GenerateItemRandomPropertyId(itemId));

    // remove binding (let GM give it to another player later)
    if(pl==plTarget)
        for (ItemPosCountVec::const_iterator itr = dest.begin(); itr != dest.end(); ++itr)
            if(Item* item1 = pl->GetItemByPos(itr->pos))
                item1->SetBinding( false );

    if(count > 0 && item)
    {
        pl->SendNewItem(item,count,false,true);
        if(pl!=plTarget)
            plTarget->SendNewItem(item,count,true,false);
    }

    if(noSpaceForCount > 0)
        PSendSysMessage(LANG_ITEM_CANNOT_CREATE, itemId, noSpaceForCount);

    return true;
}


bool ChatHandler::HandleTPJougCommand( const char *args )
{
    Battlefield* bf = sBattlefieldMgr->GetBattlefieldToZoneId(4197);

    if( !bf || (!bf->IsWarTime() && bf->GetTimer() > 15*60*1000 ) || (bf->IsWarTime() && bf->GetTimer() < 20*60*1000) )
    {
        SendSysMessage("Téléportation uniquement disponible à partir de 15 minutes avant la bataille ou 10 minutes après le commencement.");
        if(!bf->IsWarTime()) {
            uint32 timeBeforeWG = bf->GetTimer()/(60*1000);
            PSendSysMessage("Départ dans %u minutes", timeBeforeWG);
        }
        return false;
    }

    // Pour check bg commence, tenter un Player::GetBattleGround();
    // FIX( pascal ): Pas de moyens de vérifier si le Joug est commencé
    Player *player = m_session->GetPlayer();

    ASSERT( player );
    if( player->GetZoneId() == 4197 || player->getLevel() < 70 || player->isDead() || player->isInCombat( ) || player->GetMap()->IsBattlegroundOrArena()  )
    {
        SendSysMessage("Téléportation impossible");
        return false; // On ne TP pas dans tous les cas
    }

    switch( player->GetTeamId() )
    {
        case TEAM_ALLIANCE:
            if( bf && bf->getAlliancePlayersInWarCount() >= 120 )
            {
                SendSysMessage("Limite de joueurs atteinte");
                return false; // On ne TP pas dans tous les cas
            }
            player->TeleportTo( 571, 5088.51f, 2181.15f, 365.6f, 2.1984f );
            break;
        case TEAM_HORDE:
            if( bf && bf->getHordePlayersInWarCount() >= 120 )
            {
                SendSysMessage("Limite de joueurs atteinte");
                return false; // On ne TP pas dans tous les cas
            }
            player->TeleportTo( 571, 5020.86f, 3670.19f, 362.21f, 4.1148f );
            break;
    }
    return true;
}
