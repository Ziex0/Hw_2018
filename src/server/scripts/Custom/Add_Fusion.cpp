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
								// head,   shoulder,  chest,    legs,     hands,    foot,      wrist,   waist
	LIGHTING_ITEM_ARMOR1 		= 300000 || 300001 || 300002 || 300003 || 300004 || 300005 || 300006 || 300007,
	LIGHTING_ITEM_ARMOR2		= 200000 || 200001 || 200002 || 200003 || 200004 || 200005 || 200006 || 200007 
								  || 200008|| 200009|| 200010|| 200011|| 200012|| 200013|| 200014|| 200015|| 200016 
								  || 200017|| 200018|| 200007|| 200019|| 200020|| 200021|| 200022|| 200023|| 200024 
								  || 200025|| 200026|| 200027|| 200028|| 200029|| 200029|| 200029|| 200029|| 200029 
								  || 200030|| 200031|| 200032|| 200033|| 200034|| 200035|| 200036|| 200037|| 200038
								  || 200031|| 200032|| 200033|| 200034|| 200035|| 200036|| 200037|| 200038|| 200039
								  || 200040|| 200041|| 200042|| 200043|| 200044|| 200045|| 200046|| 200047|| 200048
								  || 200049|| 200050,  // armor  vote
								  
							      //sword    axe       staff     mace      2sword    2axe     2mace     dagger
	LIGHTING_ITEM_WEAPON1		= 300009 || 300010 || 300011 || 300012 || 300013 || 300014 || 300015 || 300016,
	LIGHTING_ITEM_WEAPON2		= 200059|| 200060|| 200061|| 200062|| 200063|| 200064|| 200065|| 200066|| 200067|| 200068
								  || 200069|| 200070, // weapon vote
								  
								// boots     wrist    waist
	LIGHTING_ITEM_MISC1			= 300004 || 300001 || 300002,
	LIGHTING_ITEM_MISC2			= 200072|| 200073|| 200074|| 200075|| 200076|| 200077|| 200078|| 200079|| 200080
								 || 200081|| 200082, // misc from vote
	
	LIGHTING_FUSI_TOKEN			= 300100,
	
	//POISON ITEM
	POISON_ITEM_ARMOR1			= 300006,
	POISON_ITEM_ARMOR12			= 300007,
	POISON_ITEM_WEAPON1			= 300008,
	POISON_ITEM_WEAPON2			= 300009,
	POISON_ITEM_MISC1			= 300010,
	POISON_ITEM_MISC2			= 300011,
	
	POISON_FUSI_TOKEN			= 300101,
	
	//fire item
	FIRE_ITEM_ARMOR1			= 300012,
	FIRE_ITEM_ARMOR12			= 300013,
	FIRE_ITEM_WEAPON1			= 300014,
	FIRE_ITEM_WEAPON2			= 300015,
	FIRE_ITEM_MISC1				= 300016,
	FIRE_ITEM_MISC2				= 300017,
	
	FIRE_FUSI_TOKEN				= 300102,
	
	//NATURE ITEM
	NATURE_ITEM_ARMOR1			= 300024,
	NATURE_ITEM_ARMOR12			= 300019,
	NATURE_ITEM_WEAPON1			= 300020,
	NATURE_ITEM_WEAPON2			= 300021,
	NATURE_ITEM_MISC1			= 300022,
	NATURE_ITEM_MISC2			= 300023,
	
	NATURE_FUSI_TOKEN			= 300103,
	
	//EXTREMIS
	EXTREMIS_ITEM_ARMOR1		= 300023,
	EXTREMIS_ITEM_ARMOR12		= 300024,
	EXTREMIS_ITEM_WEAPON1		= 300025,
	EXTREMIS_ITEM_WEAPON2		= 300026,
	EXTREMIS_ITEM_MISC1			= 300027,
	EXTREMIS_ITEM_MISC2			= 300028,
	
	EXTREMIS_FUSI_TOKEN			= 300104, // JUST FROM VOTE
	
	//IRON KNIGHTS
	IRON_KNIGHTS_ITEM_ARMOR1		= 300029,
	IRON_KNIGHTS_ITEM_ARMOR12		= 300030,
	IRON_KNIGHTS_ITEM_WEAPON1		= 300031,
	IRON_KNIGHTS_ITEM_WEAPON2		= 300032,
	IRON_KNIGHTS_ITEM_MISC1			= 300033,
	IRON_KNIGHTS_ITEM_MISC2			= 300034,
	
	IRON_KNIGHTS_FUSI_TOKEN			= 300105, // JUST FROM DONATE
	
};

class npc_Fusion : public CreatureScript
{
	public:
		npc_Fusion() : CreatureScript("npc_Fusion"){}
		
		bool OnGossipHello(Player* Player, Creature* pCreature)
		{
			Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT,  "|TInterface/ICONS/Achievement_Leader_King_Varian_Wrynn:24|t|r I want Lighting Fusion ", GOSSIP_SENDER_MAIN, 1);
			Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT,  "|TInterface/ICONS/Achievement_Leader_King_Varian_Wrynn:24|t|r I want Poison Fusion ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
			Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT,  "|TInterface/ICONS/Achievement_Leader_King_Varian_Wrynn:24|t|r I want Fire Fusion ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
			Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT,  "|TInterface/ICONS/Achievement_Leader_King_Varian_Wrynn:24|t|r I want Nature Fusion ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
			Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT,  "|TInterface/ICONS/Achievement_Leader_King_Varian_Wrynn:24|t|r I want Extremis fusion ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
			Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT,  "|TInterface/ICONS/Achievement_Leader_King_Varian_Wrynn:24|t|r I want iron Knights Fusion ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
			Player->SEND_GOSSIP_MENU(85006, pCreature->GetGUID());
			return true;
		}
		
		bool OnGossipSelect(Player * Player, Creature * Creature, uint32 /*uiSender*/, uint32 uiAction)
		{
			if(!Player)
				return true;

			switch(uiAction)
			{
			
				case 1:		
				Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE,  "|TInterface/ICONS/INV_Chest_Plate13:24|t|r I want Lighting Fusion Armor  ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
				//Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Lighting Armor Fusion", GOSSIP_SENDER_MAIN, 11, "Are you sure you want to fusion this item name?", 0, true);
				Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT,  "|TInterface/ICONS/Thrown_1H_Harpoon_D_01Blue:24|t|r I want Lighting Fusion Weapon  ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
				Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT,  "|TInterface/ICONS/INV_Misc_Gear_01:24|t|r I want Lighting Fusion Misc item ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13);
				break;
			
				case 2:
				Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT,  "|TInterface/ICONS/INV_Chest_Plate13:24|t|r I want Poison Armor Fusion", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 21);
				Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT,   "|TInterface/ICONS/Thrown_1H_Harpoon_D_01Blue:24|t|r I want Poison Weapon Fusion ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 22);
				Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT,  "|TInterface/ICONS/INV_Misc_Gear_01:24|t|r I want Poison Armor Fusion ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 23);
				break;
					
				case 3:	
				Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT,  "|TInterface/ICONS/INV_Chest_Plate13:24|t|r I want Fire Armor Fusion", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 31);
				Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT,   "|TInterface/ICONS/Thrown_1H_Harpoon_D_01Blue:24|t|r I want Fire Weapon Fusion ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 32);
				Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT,  "|TInterface/ICONS/INV_Misc_Gear_01:24|t|r I want Fire Armor Fusion ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 33);
				break;
				
				case 4:			
				Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT,  "|TInterface/ICONS/INV_Chest_Plate13:24|t|r I want Nature Armor Fusion", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 41);
				Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT,   "|TInterface/ICONS/Thrown_1H_Harpoon_D_01Blue:24|t|r I want Nature Weapon Fusion ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 42);
				Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT,  "|TInterface/ICONS/INV_Misc_Gear_01:24|t|r I want Nature Armor Fusion ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 43);
				break;
			//vote
				case 5:
				Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT,  "|TInterface/ICONS/INV_Chest_Plate13:24|t|r I want Extremis Armor Fusion", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 51);
				Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT,   "|TInterface/ICONS/Thrown_1H_Harpoon_D_01Blue:24|t|r I want Extremis Weapon Fusion ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 52);
				Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT,  "|TInterface/ICONS/INV_Misc_Gear_01:24|t|r I want Extremis Armor Fusion ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 53);
				break;
			//Donate 
				case 6:
				Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE,  "|TInterface/ICONS/INV_Chest_Plate13:24|t|r I want Iron Knights Armor Fusion", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 61);
				Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE,  "|TInterface/ICONS/Thrown_1H_Harpoon_D_01Blue:24|t|r I want Knights Weapon Fusion ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 62);
				Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE,  "|TInterface/ICONS/INV_Misc_Gear_01:24|t|r I want Knights Armor Fusion ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 63);
				break;
				
				
				case GOSSIP_ACTION_INFO_DEF + 11:
					if(Player->HasItemCount(LIGHTING_ITEM_ARMOR1, 1, true) && (Player->HasItemCount(LIGHTING_ITEM_ARMOR2, 1, true)) && (Player->HasItemCount(LIGHTING_FUSI_TOKEN, 1, true)))
					{
						ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(LIGHTING_ITEM_ARMOR1);
						Player->DestroyItemCount(LIGHTING_ITEM_ARMOR1, 1, true) ; Player->DestroyItemCount(LIGHTING_ITEM_ARMOR2,1, true) ; Player->DestroyItemCount(LIGHTING_FUSI_TOKEN, 1, true);						
						ChatHandler(Player->GetSession()).PSendSysMessage("Your item %s % %s will be taken", itemTemplate->Name1.c_str());
						Player->AddItem(urand(300200,300210), 1); //id dan jumlah yg didapat
						const uint32 arrayNum[1]={300210}; // 4 dan 5 adalah item ID yg kurang % untuk didapatkan
						uint32 RandIndex = rand()%2; //jumlah % ID
						Player->GetSession()->SendNotification("Success. you got new Unique Item please Check your bag !!");
						Player->PlayerTalkClass->SendCloseGossip();						
					}
					else
					{
						Player->GetSession()->SendNotification("Failed. Make sure you have the desired item");
						Player->PlayerTalkClass->SendCloseGossip();
					}
					break;
				case GOSSIP_ACTION_INFO_DEF + 12:
					if(Player->HasItemCount(LIGHTING_ITEM_WEAPON1, 1, true) && (Player->HasItemCount(LIGHTING_ITEM_WEAPON2, 1, true)) && (Player->HasItemCount(LIGHTING_FUSI_TOKEN, 1, true)))
					{
						ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(LIGHTING_ITEM_WEAPON1);
						Player->DestroyItemCount(LIGHTING_ITEM_WEAPON1, 1, true);Player->DestroyItemCount(LIGHTING_ITEM_WEAPON2,1, true);Player->DestroyItemCount(LIGHTING_FUSI_TOKEN, 1, true);						
						ChatHandler(Player->GetSession()).PSendSysMessage("Your item %s % %s will be taken", itemTemplate->Name1.c_str());
						Player->AddItem(urand(1,100), 1); //id dan jumlah yg didapat
						const uint32 arrayNum[1]={4}; // 4 dan 5 adalah item ID yg kurang % untuk didapatkan
						uint32 RandIndex = rand()%2; //jumlah % ID
						Player->GetSession()->SendNotification("Success. you got new Unique Item please Check your bag !!");
						Player->PlayerTalkClass->SendCloseGossip();						
					}
					else
					{
						Player->GetSession()->SendNotification("Failed. Make sure you have the desired item");
						Player->PlayerTalkClass->SendCloseGossip();
					}
					break;
				case GOSSIP_ACTION_INFO_DEF + 13:
					if(Player->HasItemCount(LIGHTING_ITEM_MISC1, 1, true) && (Player->HasItemCount(LIGHTING_ITEM_MISC2, 1, true)) && (Player->HasItemCount(LIGHTING_FUSI_TOKEN, 1, true)))
					{
						Player->DestroyItemCount(LIGHTING_ITEM_MISC1, 1, true);Player->DestroyItemCount(LIGHTING_ITEM_MISC2,1, true);Player->DestroyItemCount(LIGHTING_FUSI_TOKEN, 1, true);						
						Player->AddItem(urand(1,100), 1); //id dan jumlah yg didapat
						const uint32 arrayNum[1]={4}; // 4 dan 5 adalah item ID yg kurang % untuk didapatkan
						uint32 RandIndex = rand()%2; //jumlah % ID
						Player->GetSession()->SendNotification("Success. you got new Unique Item please Check your bag !!");
						Player->PlayerTalkClass->SendCloseGossip();						
					}
					else
					{
						Player->GetSession()->SendNotification("Failed. Make sure you have the desired item");
						Player->PlayerTalkClass->SendCloseGossip();
					}
					break;
				

			}
			return true;
		}

};

void AddSC_npc_Fusion()
{
    new npc_Fusion();
}
