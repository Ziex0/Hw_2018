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
#include <cstring>
#include "ObjectMgr.h"
#include "Language.h"
#include "Chat.h"


class npc_item_gambler : public CreatureScript
{
	public:
		npc_item_gambler() : CreatureScript("npc_item_gambler"){}
		
	bool OnGossipHello(Player* player, Creature* pCreature)
		{
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface/ICONS/Achievement_Leader_King_Varian_Wrynn:24|t|r I want Play Donor item Gamble -> ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF +2);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface/ICONS/Achievement_Leader_King_Varian_Wrynn:24|t|r I want points Only -> ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF +3);
			player->SEND_GOSSIP_MENU(85006, pCreature->GetGUID());
			return true;	
		}
		
	bool OnGossipSelect(Player* player, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
		if (player->isInCombat())
		{
			pCreature->MonsterWhisper("You are in combat !!", player->GetGUID());
			player->CLOSE_GOSSIP_MENU();
			return true;
		}

		player->PlayerTalkClass->ClearMenus();

		switch (uiAction)
		{
			
				case GOSSIP_ACTION_INFO_DEF +2:
					player->CLOSE_GOSSIP_MENU();
					if (player->HasItemCount(301, 1))
					{	
						player->DestroyItemCount(301, 1, true);
						ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(urand(1000101,1000188));
						ChatHandler(player->GetSession()).PSendSysMessage("Your Token %s % %s will be taken", itemTemplate->Name1.c_str());
						player->AddItem(urand(1000101,1000188), 1); //id dan jumlah yg didapat
						//const uint32 arrayNum[1]={300210}; // 4 dan 5 adalah item ID yg kurang % untuk didapatkan
						uint32 RandIndex = rand()%25; //jumlah % ID
						player->GetSession()->SendNotification("Success. you got new Unique Armor Item please Check your bag !!");					
					}
					else
					{
						player->GetSession()->SendNotification("Failed. Make sure you have the desired item");
						player->PlayerTalkClass->SendCloseGossip();
					}
					break;
				
				case GOSSIP_ACTION_INFO_DEF +3:
					player->CLOSE_GOSSIP_MENU();
					if (player->HasItemCount(301, 1))
					{
						player->DestroyItemCount(301, 1, true);
						ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(301);
						LoginDatabase.PExecute("Update sitez.accounts_more Set vp = vp + 20 WHERE id = '%u'", player->GetSession()->GetAccountId());
						//LoginDatabase.PExecute("INSERT INTO webdb.refund(account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
						player->GetSession()->SendNotification("Success, convert to 20 VP !!,Check your Account detail on website !!");
					}
					else
					{
						player->GetSession()->SendNotification("Failed. Make sure you have the desired item");
						player->PlayerTalkClass->SendCloseGossip();
					}
					break;
			}
			return true;
		}

};

void AddSC_npc_Fusionitemnew()
{
    new npc_item_gambler();
}
