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

enum  defines
{
								// head,   shoulder,  chest,    legs,     hands,    foot,      wrist,   waist
	VOTE_ARMOR 					 = 300000 || 300001 || 300002 || 300003 || 300004 || 300005 || 300006 || 300007,
	VOTE_WEAPON					 = 200000 || 200001 || 200002 || 200003 || 200004 || 200005 || 200006 || 200007, 
								    // armor  vote
								  
	VOTE_TOKEN_GAMBLER			= 300,			    
	
	DONATE_ARMOR 					 = 300000 || 300001 || 300002 || 300003 || 300004 || 300005 || 300006 || 300007,
	DONATE_WEAPON					 = 200000 || 200001 || 200002 || 200003 || 200004 || 200005 || 200006 || 200007, 
								  							  
	DONATE_TOKEN_GAMBLER			= 301
};

class npc_item_gambler : public CreatureScript
{
	public:
		npc_item_gambler() : CreatureScript("npc_item_gambler"){}
		
		bool OnGossipHello(Player* player, Creature* pCreature)
		{
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface/ICONS/Achievement_Leader_King_Varian_Wrynn:24|t|r I want Play Gamble vote item -> ", GOSSIP_SENDER_MAIN, 5);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface/ICONS/Achievement_Leader_King_Varian_Wrynn:24|t|r I want Play Donor Gamble item -> ", GOSSIP_SENDER_MAIN, 6);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface/ICONS/Achievement_Leader_King_Varian_Wrynn:24|t|r I want points Only -> ", GOSSIP_SENDER_MAIN,7);
			player->SEND_GOSSIP_MENU(85006, pCreature->GetGUID());
			return true;
	
		}
		
		bool OnGossipSelect(Player* player, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
        {
            player->PlayerTalkClass->ClearMenus();
			
            switch (uiAction)
            {
			
			//vote
				case 5:
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT,  "|TInterface/ICONS/INV_Chest_Plate13:24|t|r Give my lucky Vote Armor", GOSSIP_SENDER_MAIN, 51);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT,   "|TInterface/ICONS/Thrown_1H_Harpoon_D_01Blue:24|t|r Give my lucky Vote Weapon ", GOSSIP_SENDER_MAIN, 52);
				break;
			//Donate 
				case 6:
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE,  "|TInterface/ICONS/INV_Chest_Plate13:24|t|r Give my lucky Donor Armor", GOSSIP_SENDER_MAIN,  61);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE,  "|TInterface/ICONS/Thrown_1H_Harpoon_D_01Blue:24|t|r Give my lucky DonorWeapon", GOSSIP_SENDER_MAIN,62);
				break;
				
				case 7:
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE,  "|TInterface/ICONS/INV_Chest_Plate13:24|t|r Dp -> 3", GOSSIP_SENDER_MAIN, 71);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE,  "|TInterface/ICONS/Thrown_1H_Harpoon_D_01Blue:24|t|r Vote -> 30", GOSSIP_SENDER_MAIN, 72);
				break;
				
				case 51:
					if(player->HasItemCount(player->HasItemCount(VOTE_TOKEN_GAMBLER, 1, true)))
					{
						ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(VOTE_ARMOR);
						player->DestroyItemCount(VOTE_TOKEN_GAMBLER, 1, true) ;
						ChatHandler(player->GetSession()).PSendSysMessage("Your Token %s % %s will be taken", itemTemplate->Name1.c_str());
						player->AddItem(urand(300200,300210), 1); //id dan jumlah yg didapat
						//const uint32 arrayNum[1]={300210}; // 4 dan 5 adalah item ID yg kurang % untuk didapatkan
						uint32 RandIndex = rand()%25; //jumlah % ID
						player->GetSession()->SendNotification("Success. you got new Unique Armor Item please Check your bag !!");
						player->PlayerTalkClass->SendCloseGossip();						
					}
					else
					{
						player->GetSession()->SendNotification("Failed. Make sure you have the desired item");
						player->PlayerTalkClass->SendCloseGossip();
					}
					break;
				
				case 52:
					if(player->HasItemCount(player->HasItemCount(VOTE_TOKEN_GAMBLER, 1, true)))
					{
						ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(VOTE_WEAPON);
						player->DestroyItemCount(VOTE_TOKEN_GAMBLER, 1, true) ;
						ChatHandler(player->GetSession()).PSendSysMessage("Your Token %s % %s will be taken", itemTemplate->Name1.c_str());
						player->AddItem(urand(300200,300210), 1); //id dan jumlah yg didapat
						//const uint32 arrayNum[1]={300210}; // 4 dan 5 adalah item ID yg kurang % untuk didapatkan
						uint32 RandIndex = rand()%25; //jumlah % ID
						player->GetSession()->SendNotification("Success. you got new Unique Item please Check your bag !!");
						player->PlayerTalkClass->SendCloseGossip();						
					}
					else
					{
						player->GetSession()->SendNotification("Failed. Make sure you have the desired item");
						player->PlayerTalkClass->SendCloseGossip();
					}
					break;
			
				case 61:
					if(player->HasItemCount(player->HasItemCount(DONATE_TOKEN_GAMBLER, 1, true)))
					{
						ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(DONATE_ARMOR);
						player->DestroyItemCount(DONATE_TOKEN_GAMBLER, 1, true) ;
						ChatHandler(player->GetSession()).PSendSysMessage("Your Token %s % %s will be taken", itemTemplate->Name1.c_str());
						player->AddItem(urand(300200,300210), 1); //id dan jumlah yg didapat
						//const uint32 arrayNum[1]={300210}; // 4 dan 5 adalah item ID yg kurang % untuk didapatkan
						uint32 RandIndex = rand()%25; //jumlah % ID
						player->GetSession()->SendNotification("Success. you got new Unique Armor Item please Check your bag !!");
						player->PlayerTalkClass->SendCloseGossip();						
					}
					else
					{
						player->GetSession()->SendNotification("Failed. Make sure you have the desired item");
						player->PlayerTalkClass->SendCloseGossip();
					}
					break;
				
				case 62:
					if(player->HasItemCount(player->HasItemCount(DONATE_TOKEN_GAMBLER, 1, true)))
					{
						ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(DONATE_WEAPON);
						player->DestroyItemCount(DONATE_TOKEN_GAMBLER, 1, true) ;
						ChatHandler(player->GetSession()).PSendSysMessage("Your Token %s % %s will be taken", itemTemplate->Name1.c_str());
						player->AddItem(urand(300200,300210), 1); //id dan jumlah yg didapat
						//const uint32 arrayNum[1]={300210}; // 4 dan 5 adalah item ID yg kurang % untuk didapatkan
						uint32 RandIndex = rand()%25; //jumlah % ID
						player->GetSession()->SendNotification("Success. you got new Unique Item please Check your bag !!");
						player->PlayerTalkClass->SendCloseGossip();						
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
