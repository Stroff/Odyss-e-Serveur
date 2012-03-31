/*
 * Copyright (C) 2008-2010 TrinityCore <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Scripts for spells with SPELLFAMILY_ROGUE and SPELLFAMILY_GENERIC spells used by rogue players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_rog_".
 */
#include "ScriptPCH.h"
#include "SpellAuraEffects.h"
#include "SpellScript.h"

class spell_desespoir_SpellScript : public SpellScriptLoader
{
public:
    spell_desespoir_SpellScript() : SpellScriptLoader("spell_desespoir_SpellScript") { }
	
class spell_desespoir_SpellScriptS : public SpellScript
{
    void HandleDummy(SpellEffIndex effIndex)
    {
        if (Unit *unitTarget = GetHitUnit())
            if (unitTarget)
                if (unitTarget->HasAura(72396))
                    unitTarget->RemoveAurasDueToSpell(72395);

        if (Unit *unitTarget = GetHitUnit())
            if (unitTarget)
                if (unitTarget->HasAura(72397))
                {
                    unitTarget->RemoveAurasDueToSpell(72396);
                    unitTarget->RemoveAurasDueToSpell(72395);
                }

        if (Unit *unitTarget = GetHitUnit())
            if (unitTarget)
                if (unitTarget->HasAura(72391))
                    unitTarget->RemoveAurasDueToSpell(72390);

        if (Unit *unitTarget = GetHitUnit())
            if (unitTarget)
                if (unitTarget->HasAura(72393))
                {
                    unitTarget->RemoveAurasDueToSpell(72390);
                    unitTarget->RemoveAurasDueToSpell(72391);
                }
    }

    void Register()
    {
//OdyMERGE        OnEffect += SpellEffectFn(spell_desespoir_SpellScriptS::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

SpellScript *GetSpellScript()
{
    return new spell_desespoir_SpellScriptS();
}
};
void AddSC_odyssee_spell_scripts()
{
new spell_desespoir_SpellScript();
}
