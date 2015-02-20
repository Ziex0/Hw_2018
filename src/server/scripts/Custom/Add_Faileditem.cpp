/*
 * Copyright (C) 2015 TheSatriaCore <http://www.TheSatria.Con/>
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
 

#include "ScriptPCH.h"

enum  defines
{
	FAIL_ITEM_1 = 1,
	FAIL_ITEM_2 = 1,
	FAIL_ITEM_3 = 1

};

class npc_failed_item : public CreatureScript
{
	public:
		npc_failed_item() : CreatureScript("npc_failed_item"){}
		
		bool OnGossipHello(Player * pPlayer, Creature * pCreature)
		
		{
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Achievement_Dungeon_Icecrown_Frostmourne:24|t|r I want refund wrong Lighting Fusion ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Achievement_Dungeon_Icecrown_Frostmourne:24|t|r I want refund wrong Poison Fusion ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Achievement_Dungeon_Icecrown_Frostmourne:24|t|r I want refund wrong Fire Fusion ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Achievement_Dungeon_Icecrown_Frostmourne:24|t|r I want refund wrong Nature Fusion ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Achievement_Dungeon_Icecrown_Frostmourne:24|t|r I want refund wrong Extremis fusion ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Achievement_Dungeon_Icecrown_Frostmourne:24|t|r I want refund wrong iron Knights Fusion ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
			pPlayer->SEND_GOSSIP_MENU(907, pCreature->GetGUID());
			return true;
		}
	
	bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
		{
			pPlayer->PlayerTalkClass->ClearMenus();

			switch (uiAction)
			{
			
			case GOSSIP_ACTION_INFO_DEF + 1:	
			
			
				break;
			
			
			}
			return true;
		}

};

void AddSC_npc_failed_item()
{
    new npc_failed_item();
}