/*
 * Copyright (C) 2008-2010 Trinity <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef _RECUPDATABASE_H
#define _RECUPDATABASE_H

#include "DatabaseWorkerPool.h"
#include "MySQLConnection.h"

enum RecupDatabaseStatements
{
  RECUP_GET_TOTO,
  MAX_RECUPDATABASE_STATEMENTS,
};

class RecupDatabaseConnection : public MySQLConnection
{
    public:
        //- Constructors for sync and async connections
        RecupDatabaseConnection(MySQLConnectionInfo& connInfo) : MySQLConnection(connInfo) {}
RecupDatabaseConnection(ACE_Activation_Queue* q, MySQLConnectionInfo& connInfo) : MySQLConnection(q, connInfo) {}

        //- Loads databasetype specific prepared statements
        bool Open()
        {
            if (!MySQLConnection::Open())
                return false;

            if (!m_reconnecting)
                m_stmts.resize(MAX_RECUPDATABASE_STATEMENTS);
            PREPARE_STATEMENT(RECUP_GET_TOTO, "SELECT * FROM accounts LIMIT 0, 1", CONNECTION_SYNCH)
            return true;
       }
};

typedef DatabaseWorkerPool<RecupDatabaseConnection> RecupDatabaseWorkerPool;

#endif
