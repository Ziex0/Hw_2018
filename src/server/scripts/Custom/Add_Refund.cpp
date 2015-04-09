#include "ScriptPCH.h"
#include "Language.h"
#include "Chat.h"

class refundvendor : public CreatureScript
{
    public:

        refundvendor()
            : CreatureScript("refundvendor")
        {
        }
		
bool OnGossipHello(Player* pPlayer, Creature* pCreature)
        {
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donor Weapons", GOSSIP_SENDER_MAIN, 2000);
            /*pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Rings/Trinkets/Amulets", GOSSIP_SENDER_MAIN, 3000);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Armors", GOSSIP_SENDER_MAIN, 300);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Special Items", GOSSIP_SENDER_MAIN, 5000);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donor Shirts", GOSSIP_SENDER_MAIN, 10000);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donor Cloak = 10 DP", GOSSIP_SENDER_MAIN, 11000);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donor Tabard = 7 DP", GOSSIP_SENDER_MAIN, 14000);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donation set", GOSSIP_SENDER_MAIN, 13000);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: |cffFF7423 ROYAL Weapon ->", GOSSIP_SENDER_MAIN, 15000);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: |cffFF7423 ROYAL Gear Set ->", GOSSIP_SENDER_MAIN, 16000);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: |cffFF7423 Supreme Misc Item ->", GOSSIP_SENDER_MAIN, 17000);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: |cffFF7423 Supreme Bag ->", GOSSIP_SENDER_MAIN, 18000);*/

            pPlayer->PlayerTalkClass->SendGossipMenu(85006, pCreature->GetGUID());

            return true;
        }

        bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
        {
            pPlayer->PlayerTalkClass->ClearMenus();

            switch (uiAction)
            {
            case 13000:
                pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donor Set - 45 Dp", GOSSIP_SENDER_MAIN, 13001);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: [Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                pPlayer->PlayerTalkClass->SendGossipMenu(85006, pCreature->GetGUID());
                return true;
                break;
				
		case 18000://supreme bag
                pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Supreme Melee Bag - 11Dp", GOSSIP_SENDER_MAIN, 18001);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Supreme Caster Bag - 11Dp", GOSSIP_SENDER_MAIN, 18002);
                
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: [Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                pPlayer->PlayerTalkClass->SendGossipMenu(85006, pCreature->GetGUID());
                return true;
                break;	
				
				case 18001:
			if(pPlayer->HasItemCount(130108, 1))
			{
			pPlayer->DestroyItemCount(130108, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(130108);			
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			}
			else 
				{
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
				}
				break;
   		  case 18002:
			if(pPlayer->HasItemCount(130134, 1))
			{
			pPlayer->DestroyItemCount(130134, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(130134);			
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			}else 
				{
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
				}
				break;
				
		case 17000://supreme  misc
                pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Supreme Melee Ring - 11Dp", GOSSIP_SENDER_MAIN, 17001);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Supreme Melee Trinket - 11Dp", GOSSIP_SENDER_MAIN, 17002);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Supreme Melee Amulet - 11Dp", GOSSIP_SENDER_MAIN, 17003);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Supreme Caster Ring - 11Dp", GOSSIP_SENDER_MAIN, 17004);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Supreme Caster Trinket - 11Dp", GOSSIP_SENDER_MAIN, 17005);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Supreme Caster Amulet - 11Dp", GOSSIP_SENDER_MAIN, 17006);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: [Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                pPlayer->PlayerTalkClass->SendGossipMenu(85006, pCreature->GetGUID());
                return true;
                break;
				case 17001:
			if(pPlayer->HasItemCount(130110, 1))
			{
			pPlayer->DestroyItemCount(130110, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(130110);			
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			}
			else 
				{
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
				}
				break;
   		  case 17002:
			if(pPlayer->HasItemCount(130109, 1))
			{
			pPlayer->DestroyItemCount(130109, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(130109);			
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			}else 
				{
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
				}
				break;
				case 17003:
			if(pPlayer->HasItemCount(130111, 1))
			{
			pPlayer->DestroyItemCount(130111, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(130111);			
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			}else 
				{
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
				}
				break;
				case 17004:
			if(pPlayer->HasItemCount(130131, 1))
			{
			pPlayer->DestroyItemCount(130131, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(130131);			
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			}else 
				{
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
				}
				break;
				case 17005:
			if(pPlayer->HasItemCount(130132, 1))
			{
			pPlayer->DestroyItemCount(130132, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(130132);			
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			}else 
				{
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
				}
				break;
				case 17006:
			if(pPlayer->HasItemCount(130133, 1))
			{
			pPlayer->DestroyItemCount(130133, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(130133);			
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			}else 
				{
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
				}
				break;
				
		case 15000:
                pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: One-Handed Weapons", GOSSIP_SENDER_MAIN, 15001);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Two-Handed Weapons", GOSSIP_SENDER_MAIN, 15002);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Staves", GOSSIP_SENDER_MAIN, 15003);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Ranged", GOSSIP_SENDER_MAIN, 15004);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: [Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                pPlayer->PlayerTalkClass->SendGossipMenu(85006, pCreature->GetGUID());
                return true;
                break;
				
				case 15001:
                pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Royal One Hand Axe - 21 DP", GOSSIP_SENDER_MAIN, 15101);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Royal One Hand Sword - 21 DP", GOSSIP_SENDER_MAIN, 15102);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Royal One Hand Mace - 21 DP", GOSSIP_SENDER_MAIN, 15103);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Royal Dagger - 21 DP", GOSSIP_SENDER_MAIN, 15104);
                				
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: [Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                pPlayer->PlayerTalkClass->SendGossipMenu(85006, pCreature->GetGUID());
                return true;
                break;
				
				case 15101:
			if(pPlayer->HasItemCount(30699, 1))
			{
			pPlayer->DestroyItemCount(30699, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(30699);			
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 21 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
		
			} 
		  else 
		  {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case 15102:
			if(pPlayer->HasItemCount(34821, 1))
			{
			pPlayer->DestroyItemCount(34821, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(34821);			
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 21 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
		
			} 
		  else 
		  {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case 15103:
			if(pPlayer->HasItemCount(42759, 1))
			{
			pPlayer->DestroyItemCount(42759,1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(42759);			
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 21 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
		
			} 
		  else 
		  {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case 15104:
			if(pPlayer->HasItemCount(34045, 1))
			{
			pPlayer->DestroyItemCount(34045,1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(34045);			
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 21 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
		
			} 
		  else 
		  {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  
		  case 15002:
                pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Royal Two Hand Axe - 32 DP", GOSSIP_SENDER_MAIN, 15201);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Royal Two Hand Sword - 32 DP", GOSSIP_SENDER_MAIN, 15202);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Royal Two Hand Mace - 32 DP", GOSSIP_SENDER_MAIN, 15203);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Royal Two Hand Polearm - 32 DP", GOSSIP_SENDER_MAIN, 15204);
                				
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: [Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                pPlayer->PlayerTalkClass->SendGossipMenu(85006, pCreature->GetGUID());
                return true;
                break;
				
				case 15201:
			if(pPlayer->HasItemCount(19199, 1))
			{
			pPlayer->DestroyItemCount(19199, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(19199);			
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 32 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
		
			} 
		  else 
		  {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case 15202:
			if(pPlayer->HasItemCount(40480, 1))
			{
			pPlayer->DestroyItemCount(40480, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(40480);			
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 32 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
		
			} 
		  else 
		  {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case 15203:
			if(pPlayer->HasItemCount(35674, 1))
			{
			pPlayer->DestroyItemCount(35674, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(35674);			
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 32 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
		
			} 
		  else 
		  {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case 15204:
			if(pPlayer->HasItemCount(45884, 1))
			{
			pPlayer->DestroyItemCount(45884, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(45884);			
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 32 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
		
			} 
		  else 
		  {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  
		  case 15003:
                pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Royal One Hand Armageddon Staff - 21 DP", GOSSIP_SENDER_MAIN, 15301);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Royal Two Hand Armageddon Staff - 32 DP", GOSSIP_SENDER_MAIN, 15302);
                				
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: [Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                pPlayer->PlayerTalkClass->SendGossipMenu(85006, pCreature->GetGUID());
                return true;
                break;
				case 15301:
			if(pPlayer->HasItemCount(29432, 1))
			{
			pPlayer->DestroyItemCount(29432, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(29432);			
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 21 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
		
			} 
		  else 
		  {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
				case 15302:
			if(pPlayer->HasItemCount(29687, 1))
			{
			pPlayer->DestroyItemCount(29687, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(29687);			
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 32 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
		
			} 
		  else 
		  {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  
		  case 15004:
                pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Royal Pain Bow - 21 DP", GOSSIP_SENDER_MAIN, 15401);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Royal Pain Wand - 21 DP", GOSSIP_SENDER_MAIN, 15402);
                				
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: [Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                pPlayer->PlayerTalkClass->SendGossipMenu(85006, pCreature->GetGUID());
                return true;
                break;
				case 15401:
			if(pPlayer->HasItemCount(47122, 1))
			{
			pPlayer->DestroyItemCount(47122, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(47122);			
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 17 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
		
			} 
		  else
		  
		  {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case 15402:
			if(pPlayer->HasItemCount(34144, 1))
			{
			pPlayer->DestroyItemCount(34144, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(34144);			
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 17 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
		
			} 
		  else 
		  {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
				
	     case 13001: // donors set
		  switch(pPlayer->getClass())
		  {
		  case CLASS_WARRIOR:
		  if(pPlayer->HasItemCount(100079, 1) && pPlayer->HasItemCount(100072, 1) && pPlayer->HasItemCount(100073, 1) && pPlayer->HasItemCount(100074, 1) && pPlayer->HasItemCount(100075, 1) && pPlayer->HasItemCount(100076, 1) && pPlayer->HasItemCount(100077, 1) && pPlayer->HasItemCount(100078, 1))
		  {
			pPlayer->DestroyItemCount(100079, 1, true);
			pPlayer->DestroyItemCount(100072, 1, true);
			pPlayer->DestroyItemCount(100073, 1, true);
			pPlayer->DestroyItemCount(100074, 1, true);
			pPlayer->DestroyItemCount(100075, 1, true);
			pPlayer->DestroyItemCount(100076, 1, true);
			pPlayer->DestroyItemCount(100077, 1, true);
			pPlayer->DestroyItemCount(100078, 1, true);
			
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 45 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case CLASS_PALADIN:
		  if(pPlayer->HasItemCount(100038, 1) && pPlayer->HasItemCount(100032, 1) && pPlayer->HasItemCount(100033, 1) && pPlayer->HasItemCount(100034, 1) && pPlayer->HasItemCount(100035, 1) && pPlayer->HasItemCount(100036, 1) && pPlayer->HasItemCount(100037, 1) && pPlayer->HasItemCount(100039, 1))
		  {
			pPlayer->DestroyItemCount(100032, 1, true);
			pPlayer->DestroyItemCount(100033, 1, true);
			pPlayer->DestroyItemCount(100034, 1, true);
			pPlayer->DestroyItemCount(100035, 1, true);
			pPlayer->DestroyItemCount(100036, 1, true);
			pPlayer->DestroyItemCount(100037, 1, true);
			pPlayer->DestroyItemCount(100038, 1, true);
			pPlayer->DestroyItemCount(100039, 1, true);
			
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 45 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case CLASS_HUNTER:
		  if(pPlayer->HasItemCount(100016, 1) && pPlayer->HasItemCount(100017, 1) && pPlayer->HasItemCount(100018, 1) && pPlayer->HasItemCount(100019, 1) && pPlayer->HasItemCount(100020, 1) && pPlayer->HasItemCount(100021, 1) && pPlayer->HasItemCount(100022, 1) && pPlayer->HasItemCount(100023, 1))
		  {
			pPlayer->DestroyItemCount(100016, 1, true);
			pPlayer->DestroyItemCount(100017, 1, true);
			pPlayer->DestroyItemCount(100018, 1, true);
			pPlayer->DestroyItemCount(100019, 1, true);
			pPlayer->DestroyItemCount(100020, 1, true);
			pPlayer->DestroyItemCount(100021, 1, true);
			pPlayer->DestroyItemCount(100022, 1, true);
			pPlayer->DestroyItemCount(100023, 1, true);
			
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 45 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case CLASS_ROGUE:
		  if(pPlayer->HasItemCount(100048, 1) && pPlayer->HasItemCount(100049, 1) && pPlayer->HasItemCount(100050, 1) && pPlayer->HasItemCount(100051, 1) && pPlayer->HasItemCount(100052, 1) && pPlayer->HasItemCount(100053, 1) && pPlayer->HasItemCount(100054, 1) && pPlayer->HasItemCount(100055, 1))
		  {
			pPlayer->DestroyItemCount(100048, 1, true);
			pPlayer->DestroyItemCount(100049, 1, true);
			pPlayer->DestroyItemCount(100050, 1, true);
			pPlayer->DestroyItemCount(100051, 1, true);
			pPlayer->DestroyItemCount(100052, 1, true);
			pPlayer->DestroyItemCount(100053, 1, true);
			pPlayer->DestroyItemCount(100054, 1, true);
			pPlayer->DestroyItemCount(100055, 1, true);
			
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 45 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
	 	  case CLASS_PRIEST:
		  if(pPlayer->HasItemCount(100040, 1) && pPlayer->HasItemCount(100041, 1) && pPlayer->HasItemCount(100042, 1) && pPlayer->HasItemCount(100043, 1) && pPlayer->HasItemCount(100044, 1) && pPlayer->HasItemCount(100045, 1) && pPlayer->HasItemCount(100046, 1) && pPlayer->HasItemCount(100047, 1))
		  {
			pPlayer->DestroyItemCount(100040, 1, true);
			pPlayer->DestroyItemCount(100041, 1, true);
			pPlayer->DestroyItemCount(100042, 1, true);
			pPlayer->DestroyItemCount(100043, 1, true);
			pPlayer->DestroyItemCount(100044, 1, true);
			pPlayer->DestroyItemCount(100045, 1, true);
			pPlayer->DestroyItemCount(100046, 1, true);
			pPlayer->DestroyItemCount(100047, 1, true);
			
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 45 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case CLASS_DEATH_KNIGHT:
		  if(pPlayer->HasItemCount(100000, 1) && pPlayer->HasItemCount(100001, 1) && pPlayer->HasItemCount(100002, 1) && pPlayer->HasItemCount(100003, 1) && pPlayer->HasItemCount(100004, 1) && pPlayer->HasItemCount(100005, 1) && pPlayer->HasItemCount(100006, 1) && pPlayer->HasItemCount(100007, 1))
		  {
			pPlayer->DestroyItemCount(100000, 1, true);
			pPlayer->DestroyItemCount(100001, 1, true);
			pPlayer->DestroyItemCount(100002, 1, true);
			pPlayer->DestroyItemCount(100003, 1, true);
			pPlayer->DestroyItemCount(100004, 1, true);
			pPlayer->DestroyItemCount(100005, 1, true);
			pPlayer->DestroyItemCount(100006, 1, true);
			pPlayer->DestroyItemCount(100007, 1, true);
			
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 45 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case CLASS_SHAMAN:
		  if(pPlayer->HasItemCount(100056, 1) && pPlayer->HasItemCount(100057, 1) && pPlayer->HasItemCount(100058, 1) && pPlayer->HasItemCount(100059, 1) && pPlayer->HasItemCount(100060, 1) && pPlayer->HasItemCount(100061, 1) && pPlayer->HasItemCount(100062, 1) && pPlayer->HasItemCount(100063, 1))
		  {
			pPlayer->DestroyItemCount(100056, 1, true);
			pPlayer->DestroyItemCount(100057, 1, true);
			pPlayer->DestroyItemCount(100058, 1, true);
			pPlayer->DestroyItemCount(100059, 1, true);
			pPlayer->DestroyItemCount(100060, 1, true);
			pPlayer->DestroyItemCount(100061, 1, true);
			pPlayer->DestroyItemCount(100062, 1, true);
			pPlayer->DestroyItemCount(100063, 1, true);
			
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 45 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case CLASS_MAGE:
		  if(pPlayer->HasItemCount(100024, 1) && pPlayer->HasItemCount(100025, 1) && pPlayer->HasItemCount(100026, 1) && pPlayer->HasItemCount(100027, 1) && pPlayer->HasItemCount(100028, 1) && pPlayer->HasItemCount(100029, 1) && pPlayer->HasItemCount(100030, 1) && pPlayer->HasItemCount(100031, 1))
		  {
			pPlayer->DestroyItemCount(100024, 1, true);
			pPlayer->DestroyItemCount(100025, 1, true);
			pPlayer->DestroyItemCount(100026, 1, true);
			pPlayer->DestroyItemCount(100027, 1, true);
			pPlayer->DestroyItemCount(100028, 1, true);
			pPlayer->DestroyItemCount(100029, 1, true);
			pPlayer->DestroyItemCount(100030, 1, true);
			pPlayer->DestroyItemCount(100031, 1, true);
			
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 45 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case CLASS_WARLOCK:
		  if(pPlayer->HasItemCount(100064, 1) && pPlayer->HasItemCount(100065, 1) && pPlayer->HasItemCount(100066, 1) && pPlayer->HasItemCount(100067, 1) && pPlayer->HasItemCount(100068, 1) && pPlayer->HasItemCount(100069, 1) && pPlayer->HasItemCount(100070, 1) && pPlayer->HasItemCount(100071, 1))
		  {
			pPlayer->DestroyItemCount(100064, 1, true);
			pPlayer->DestroyItemCount(100065, 1, true);
			pPlayer->DestroyItemCount(100066, 1, true);
			pPlayer->DestroyItemCount(100067, 1, true);
			pPlayer->DestroyItemCount(100068, 1, true);
			pPlayer->DestroyItemCount(100069, 1, true);
			pPlayer->DestroyItemCount(100070, 1, true);
			pPlayer->DestroyItemCount(100071, 1, true);
			
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 45 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case CLASS_DRUID:
		  if(pPlayer->HasItemCount(100008, 1) && pPlayer->HasItemCount(100009, 1) && pPlayer->HasItemCount(100010, 1) && pPlayer->HasItemCount(100011, 1) && pPlayer->HasItemCount(100012, 1) && pPlayer->HasItemCount(100013, 1) && pPlayer->HasItemCount(100014, 1) && pPlayer->HasItemCount(100015, 1))
		  {
			pPlayer->DestroyItemCount(100008, 1, true);
			pPlayer->DestroyItemCount(100009, 1, true);
			pPlayer->DestroyItemCount(100010, 1, true);
			pPlayer->DestroyItemCount(100011, 1, true);
			pPlayer->DestroyItemCount(100012, 1, true);
			pPlayer->DestroyItemCount(100013, 1, true);
			pPlayer->DestroyItemCount(100014, 1, true);
			pPlayer->DestroyItemCount(100015, 1, true);
			

			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 45 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;

		  default: break;
		  }
		  break;

	     case 16000:
                pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donor Set - 62 Dp", GOSSIP_SENDER_MAIN, 16001);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: [Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                pPlayer->PlayerTalkClass->SendGossipMenu(85006, pCreature->GetGUID());
                return true;
                break;
		 
		 case 16001: // Royal donors set
		  switch(pPlayer->getClass())
		  {
		  case CLASS_WARRIOR:
		  if(pPlayer->HasItemCount(130079, 1) && pPlayer->HasItemCount(130072, 1) && pPlayer->HasItemCount(130073, 1) && pPlayer->HasItemCount(130074, 1) && pPlayer->HasItemCount(130075, 1) && pPlayer->HasItemCount(130076, 1) && pPlayer->HasItemCount(130077, 1) && pPlayer->HasItemCount(130078, 1))
		  {
			pPlayer->DestroyItemCount(130079, 1, true);
			pPlayer->DestroyItemCount(130072, 1, true);
			pPlayer->DestroyItemCount(130073, 1, true);
			pPlayer->DestroyItemCount(130074, 1, true);
			pPlayer->DestroyItemCount(130075, 1, true);
			pPlayer->DestroyItemCount(130076, 1, true);
			pPlayer->DestroyItemCount(130077, 1, true);
			pPlayer->DestroyItemCount(130078, 1, true);
			
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 62 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case CLASS_PALADIN:
		  if(pPlayer->HasItemCount(130038, 1) && pPlayer->HasItemCount(130032, 1) && pPlayer->HasItemCount(130033, 1) && pPlayer->HasItemCount(130034, 1) && pPlayer->HasItemCount(130035, 1) && pPlayer->HasItemCount(130036, 1) && pPlayer->HasItemCount(130037, 1) && pPlayer->HasItemCount(130039, 1))
		  {
			pPlayer->DestroyItemCount(130032, 1, true);
			pPlayer->DestroyItemCount(130033, 1, true);
			pPlayer->DestroyItemCount(130034, 1, true);
			pPlayer->DestroyItemCount(130035, 1, true);
			pPlayer->DestroyItemCount(130036, 1, true);
			pPlayer->DestroyItemCount(130037, 1, true);
			pPlayer->DestroyItemCount(130038, 1, true);
			pPlayer->DestroyItemCount(130039, 1, true);
			
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 62 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case CLASS_HUNTER:
		  if(pPlayer->HasItemCount(130016, 1) && pPlayer->HasItemCount(130017, 1) && pPlayer->HasItemCount(130018, 1) && pPlayer->HasItemCount(130019, 1) && pPlayer->HasItemCount(130020, 1) && pPlayer->HasItemCount(130021, 1) && pPlayer->HasItemCount(130022, 1) && pPlayer->HasItemCount(130023, 1))
		  {
			pPlayer->DestroyItemCount(130016, 1, true);
			pPlayer->DestroyItemCount(130017, 1, true);
			pPlayer->DestroyItemCount(130018, 1, true);
			pPlayer->DestroyItemCount(130019, 1, true);
			pPlayer->DestroyItemCount(130020, 1, true);
			pPlayer->DestroyItemCount(130021, 1, true);
			pPlayer->DestroyItemCount(130022, 1, true);
			pPlayer->DestroyItemCount(130023, 1, true);
			
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 62 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case CLASS_ROGUE:
		  if(pPlayer->HasItemCount(130048, 1) && pPlayer->HasItemCount(130049, 1) && pPlayer->HasItemCount(130050, 1) && pPlayer->HasItemCount(130051, 1) && pPlayer->HasItemCount(130052, 1) && pPlayer->HasItemCount(130053, 1) && pPlayer->HasItemCount(130054, 1) && pPlayer->HasItemCount(130055, 1))
		  {
			pPlayer->DestroyItemCount(130048, 1, true);
			pPlayer->DestroyItemCount(130049, 1, true);
			pPlayer->DestroyItemCount(130050, 1, true);
			pPlayer->DestroyItemCount(130051, 1, true);
			pPlayer->DestroyItemCount(130052, 1, true);
			pPlayer->DestroyItemCount(130053, 1, true);
			pPlayer->DestroyItemCount(130054, 1, true);
			pPlayer->DestroyItemCount(130055, 1, true);
			
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 62 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
	 	  case CLASS_PRIEST:
		  if(pPlayer->HasItemCount(130040, 1) && pPlayer->HasItemCount(130041, 1) && pPlayer->HasItemCount(130042, 1) && pPlayer->HasItemCount(130043, 1) && pPlayer->HasItemCount(130044, 1) && pPlayer->HasItemCount(130045, 1) && pPlayer->HasItemCount(130046, 1) && pPlayer->HasItemCount(130047, 1))
		  {
			pPlayer->DestroyItemCount(130040, 1, true);
			pPlayer->DestroyItemCount(130041, 1, true);
			pPlayer->DestroyItemCount(130042, 1, true);
			pPlayer->DestroyItemCount(130043, 1, true);
			pPlayer->DestroyItemCount(130044, 1, true);
			pPlayer->DestroyItemCount(130045, 1, true);
			pPlayer->DestroyItemCount(130046, 1, true);
			pPlayer->DestroyItemCount(130047, 1, true);
			
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 62 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case CLASS_DEATH_KNIGHT:
		  if(pPlayer->HasItemCount(130000, 1) && pPlayer->HasItemCount(130001, 1) && pPlayer->HasItemCount(130002, 1) && pPlayer->HasItemCount(130003, 1) && pPlayer->HasItemCount(130004, 1) && pPlayer->HasItemCount(130005, 1) && pPlayer->HasItemCount(130006, 1) && pPlayer->HasItemCount(130007, 1))
		  {
			pPlayer->DestroyItemCount(130000, 1, true);
			pPlayer->DestroyItemCount(130001, 1, true);
			pPlayer->DestroyItemCount(130002, 1, true);
			pPlayer->DestroyItemCount(130003, 1, true);
			pPlayer->DestroyItemCount(130004, 1, true);
			pPlayer->DestroyItemCount(130005, 1, true);
			pPlayer->DestroyItemCount(130006, 1, true);
			pPlayer->DestroyItemCount(130007, 1, true);
			
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 62 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case CLASS_SHAMAN:
		  if(pPlayer->HasItemCount(130056, 1) && pPlayer->HasItemCount(130057, 1) && pPlayer->HasItemCount(130058, 1) && pPlayer->HasItemCount(130059, 1) && pPlayer->HasItemCount(130060, 1) && pPlayer->HasItemCount(130061, 1) && pPlayer->HasItemCount(130062, 1) && pPlayer->HasItemCount(130063, 1))
		  {
			pPlayer->DestroyItemCount(130056, 1, true);
			pPlayer->DestroyItemCount(130057, 1, true);
			pPlayer->DestroyItemCount(130058, 1, true);
			pPlayer->DestroyItemCount(130059, 1, true);
			pPlayer->DestroyItemCount(130060, 1, true);
			pPlayer->DestroyItemCount(130061, 1, true);
			pPlayer->DestroyItemCount(130062, 1, true);
			pPlayer->DestroyItemCount(130063, 1, true);
			
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 62 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case CLASS_MAGE:
		  if(pPlayer->HasItemCount(130024, 1) && pPlayer->HasItemCount(130025, 1) && pPlayer->HasItemCount(130026, 1) && pPlayer->HasItemCount(130027, 1) && pPlayer->HasItemCount(130028, 1) && pPlayer->HasItemCount(130029, 1) && pPlayer->HasItemCount(130030, 1) && pPlayer->HasItemCount(130031, 1))
		  {
			pPlayer->DestroyItemCount(130024, 1, true);
			pPlayer->DestroyItemCount(130025, 1, true);
			pPlayer->DestroyItemCount(130026, 1, true);
			pPlayer->DestroyItemCount(130027, 1, true);
			pPlayer->DestroyItemCount(130028, 1, true);
			pPlayer->DestroyItemCount(130029, 1, true);
			pPlayer->DestroyItemCount(130030, 1, true);
			pPlayer->DestroyItemCount(130031, 1, true);
			
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 62 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case CLASS_WARLOCK:
		  if(pPlayer->HasItemCount(130064, 1) && pPlayer->HasItemCount(130065, 1) && pPlayer->HasItemCount(130066, 1) && pPlayer->HasItemCount(130067, 1) && pPlayer->HasItemCount(130068, 1) && pPlayer->HasItemCount(130069, 1) && pPlayer->HasItemCount(130070, 1) && pPlayer->HasItemCount(130071, 1))
		  {
			pPlayer->DestroyItemCount(130064, 1, true);
			pPlayer->DestroyItemCount(130065, 1, true);
			pPlayer->DestroyItemCount(130066, 1, true);
			pPlayer->DestroyItemCount(130067, 1, true);
			pPlayer->DestroyItemCount(130068, 1, true);
			pPlayer->DestroyItemCount(130069, 1, true);
			pPlayer->DestroyItemCount(130070, 1, true);
			pPlayer->DestroyItemCount(130071, 1, true);
			
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 62 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case CLASS_DRUID:
		  if(pPlayer->HasItemCount(130008, 1) && pPlayer->HasItemCount(130009, 1) && pPlayer->HasItemCount(130010, 1) && pPlayer->HasItemCount(130011, 1) && pPlayer->HasItemCount(130012, 1) && pPlayer->HasItemCount(130013, 1) && pPlayer->HasItemCount(130014, 1) && pPlayer->HasItemCount(130015, 1))
		  {
			pPlayer->DestroyItemCount(130008, 1, true);
			pPlayer->DestroyItemCount(130009, 1, true);
			pPlayer->DestroyItemCount(130010, 1, true);
			pPlayer->DestroyItemCount(130011, 1, true);
			pPlayer->DestroyItemCount(130012, 1, true);
			pPlayer->DestroyItemCount(130013, 1, true);
			pPlayer->DestroyItemCount(130014, 1, true);
			pPlayer->DestroyItemCount(130015, 1, true);
			

			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 62 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  default: break;
		  }
		  break;
		  
            case 300:
                pPlayer->PlayerTalkClass->ClearMenus();
                //pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Cloak of Triumph = 10 DP", GOSSIP_SENDER_MAIN, 301);
                //pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donaters Tabard = 15 DP", GOSSIP_SENDER_MAIN, 302);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donor Melee Bag = 6 DP", GOSSIP_SENDER_MAIN, 303);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donor Caster Bag = 6 DP", GOSSIP_SENDER_MAIN, 305);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donaters Steel Shield = 4 DP", GOSSIP_SENDER_MAIN, 304);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: [Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                pPlayer->PlayerTalkClass->SendGossipMenu(85006, pCreature->GetGUID());
                return true;
                break;
            case 1303:
		if(pPlayer->HasItemCount(7278, 1))
		{
			pPlayer->DestroyItemCount(7278, 1, true);
			
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 3 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
            case 301:
		if(pPlayer->HasItemCount(21394, 1))
		{
			pPlayer->DestroyItemCount(21394, 1, true);
			
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
            case 302:
		  if(pPlayer->HasItemCount(20131, 1))
		  {
			pPlayer->DestroyItemCount(20131, 1, true);
			
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 15 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
            case 303:
		  if(pPlayer->HasItemCount(100108, 1))
		  {
			pPlayer->DestroyItemCount(100108, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(100108);
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 4 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
   		  case 304:
		  if(pPlayer->HasItemCount(100130, 1))
		  {
			pPlayer->DestroyItemCount(100130, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(100130);
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 4 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
                case 305:
		  if(pPlayer->HasItemCount(100134, 1))
		  {
			pPlayer->DestroyItemCount(100134, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(100134);
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 4 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  
            case 2000:
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Sword - 5 Dp", GOSSIP_SENDER_MAIN,  2001);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Axe - 5 Dp", GOSSIP_SENDER_MAIN,   2002);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Melee Dagger - 5 Dp", GOSSIP_SENDER_MAIN,   2003);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Spell Dagger - 5 Dp", GOSSIP_SENDER_MAIN,   2004);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Bow  - 5 Dp", GOSSIP_SENDER_MAIN,   2005);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Gun  - 5 Dp", GOSSIP_SENDER_MAIN,   2006);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Wand  - 5 Dp", GOSSIP_SENDER_MAIN,   2007);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Dual Axe  - 12 Dp", GOSSIP_SENDER_MAIN,   2008);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Dual Sword  - 12 Dp", GOSSIP_SENDER_MAIN,   2009);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Dual Mace  - 12 Dp", GOSSIP_SENDER_MAIN,   2010);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Mace  - 5 Dp", GOSSIP_SENDER_MAIN,   2011);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Spell Staff  - 12 Dp", GOSSIP_SENDER_MAIN,   2012);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Feral Staff  - 12 Dp", GOSSIP_SENDER_MAIN,   2013);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Polearm  - 12 Dp", GOSSIP_SENDER_MAIN,   2014);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Melee Tank Shield  - 6 Dp", GOSSIP_SENDER_MAIN,   2015);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Melee Tank Shield  - 6 Dp", GOSSIP_SENDER_MAIN,   2016);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: [Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                pPlayer->PlayerTalkClass->SendGossipMenu(85006, pCreature->GetGUID());
                return true;
                break;
				
        case GOSSIP_ACTION_INFO_DEF +  2001:
                if(pPlayer->HasItemCount(200169, 1))
			{
			pPlayer->DestroyItemCount(200169, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(200169);			
			LoginDatabase.PQuery("Update web_db.account_data Set dp = dp + 5 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO web_db.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Account in Site for detail !!");
			}else 
				{
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
				}
				break;
				
			case GOSSIP_ACTION_INFO_DEF +  2002:
                if(pPlayer->HasItemCount(200170, 1))
			{
			pPlayer->DestroyItemCount(200170, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(200170);			
			LoginDatabase.PQuery("Update web_db.account_data Set dp = dp + 5 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO web_db.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Account in Site for detail !!");
			}else 
				{
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
				}
				break;
				
			case GOSSIP_ACTION_INFO_DEF +  2003:
                if(pPlayer->HasItemCount(200180, 1))
			{
			pPlayer->DestroyItemCount(200180, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(200180);			
			LoginDatabase.PQuery("Update web_db.account_data Set dp = dp + 5 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO web_db.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Account in Site for detail !!");
			}else 
				{
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
				}
				break;
			
			case GOSSIP_ACTION_INFO_DEF +   2004:
                if(pPlayer->HasItemCount(200228, 1))
			{
			pPlayer->DestroyItemCount(200228, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(200228);			
			LoginDatabase.PQuery("Update web_db.account_data Set dp = dp + 5 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO web_db.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Account in Site for detail !!");
			}else 
				{
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
				}
				break;
			
			case GOSSIP_ACTION_INFO_DEF +   2005: //bow
                if(pPlayer->HasItemCount(200172, 1))
			{
			pPlayer->DestroyItemCount(200172, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(200172);			
			LoginDatabase.PQuery("Update web_db.account_data Set dp = dp + 5 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO web_db.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Account in Site for detail !!");
			}else 
				{
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
				}
				break;
			
			case GOSSIP_ACTION_INFO_DEF +   2006://gun
                if(pPlayer->HasItemCount(200173, 1))
			{
			pPlayer->DestroyItemCount(200173, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(200173);			
			LoginDatabase.PQuery("Update web_db.account_data Set dp = dp + 5 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO web_db.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Account in Site for detail !!");
			}else 
				{
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
				}
				break;
				
			case GOSSIP_ACTION_INFO_DEF +   2007://wabd
                if(pPlayer->HasItemCount(200181, 1))
			{
			pPlayer->DestroyItemCount(200181, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(200181);			
			LoginDatabase.PQuery("Update web_db.account_data Set dp = dp + 5 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO web_db.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Account in Site for detail !!");
			}else 
				{
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
				}
				break;
				
			case GOSSIP_ACTION_INFO_DEF +   2008: //dual axe
                if(pPlayer->HasItemCount(200178, 1))
			{
			pPlayer->DestroyItemCount(200178, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(200178);			
			LoginDatabase.PQuery("Update web_db.account_data Set dp = dp + 12 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO web_db.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Account in Site for detail !!");
			}else 
				{
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
				}
				break;
				
			case GOSSIP_ACTION_INFO_DEF +   2009:  //dual sword
                if(pPlayer->HasItemCount(200176, 1))
			{
			pPlayer->DestroyItemCount(200176, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(200176);			
			LoginDatabase.PQuery("Update web_db.account_data Set dp = dp + 12 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO web_db.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Account in Site for detail !!");
			}else 
				{
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
				}
				break;
				
			case GOSSIP_ACTION_INFO_DEF +   2010://dual mace
                if(pPlayer->HasItemCount(200177, 1))
			{
			pPlayer->DestroyItemCount(200177, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(200177);			
			LoginDatabase.PQuery("Update web_db.account_data Set dp = dp + 12 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO web_db.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Account in Site for detail !!");
			}else 
				{
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
				}
				break;
				
			case GOSSIP_ACTION_INFO_DEF +   2011://mace
                if(pPlayer->HasItemCount(200171, 1))
			{
			pPlayer->DestroyItemCount(200171, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(200171);			
			LoginDatabase.PQuery("Update web_db.account_data Set dp = dp + 5 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO web_db.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Account in Site for detail !!");
			}else 
				{
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
				}
				break;
				
			case GOSSIP_ACTION_INFO_DEF +   2012://spell staff
                if(pPlayer->HasItemCount(200179, 1))
			{
			pPlayer->DestroyItemCount(200179, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(200179);			
			LoginDatabase.PQuery("Update web_db.account_data Set dp = dp + 12 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO web_db.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Account in Site for detail !!");
			}else 
				{
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
				}
				break;
				
			case GOSSIP_ACTION_INFO_DEF +   2013://feral staff
                if(pPlayer->HasItemCount(200229, 1))
			{
			pPlayer->DestroyItemCount(200229, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(200229);			
			LoginDatabase.PQuery("Update web_db.account_data Set dp = dp + 12 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO web_db.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Account in Site for detail !!");
			}else 
				{
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
				}
				break;
				
			case GOSSIP_ACTION_INFO_DEF +   2014://polearm
                if(pPlayer->HasItemCount(200230, 1))
			{
			pPlayer->DestroyItemCount(200230, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(200230);			
			LoginDatabase.PQuery("Update web_db.account_data Set dp = dp + 12 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO web_db.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Account in Site for detail !!");
			}else 
				{
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
				}
				break;
				
			case GOSSIP_ACTION_INFO_DEF +   2015://spell staff
                if(pPlayer->HasItemCount(200167, 1))
			{
			pPlayer->DestroyItemCount(200167, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(200167);			
			LoginDatabase.PQuery("Update web_db.account_data Set dp = dp + 6 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO web_db.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Account in Site for detail !!");
			}else 
				{
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
				}
				break;
				
			case GOSSIP_ACTION_INFO_DEF +   2016://spell staff
                if(pPlayer->HasItemCount(200168, 1))
			{
			pPlayer->DestroyItemCount(200168, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(200168);			
			LoginDatabase.PQuery("Update web_db.account_data Set dp = dp + 6 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO web_db.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Account in Site for detail !!");
			}else 
				{
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
				}
			break;

            case 5000:
                pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donaters Idol = 6 DP", GOSSIP_SENDER_MAIN, 5001);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donaters Totem = 6 DP", GOSSIP_SENDER_MAIN, 5002);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donaters Sigil = 6 DP", GOSSIP_SENDER_MAIN, 5003);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donaters Libram = 6 DP", GOSSIP_SENDER_MAIN, 5004);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: [Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                pPlayer->PlayerTalkClass->SendGossipMenu(85006, pCreature->GetGUID());
                return true;
                break;
            case 5001:
		  if(pPlayer->HasItemCount(100107, 1))
		  {
			pPlayer->DestroyItemCount(100107, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(100107);	
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 6 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pCreature->MonsterWhisper("Success. Your donor item has been removed and your points has been refunded.", LANG_UNIVERSAL, pPlayer->GetGUID());
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
            case 5002:
		  if(pPlayer->HasItemCount(100103, 1))
		  {
			pPlayer->DestroyItemCount(100103, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(100103);	
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 6 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pCreature->MonsterWhisper("Success. Your donor item has been removed and your points has been refunded.", LANG_UNIVERSAL, pPlayer->GetGUID());
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
            case 5003:
		  if(pPlayer->HasItemCount(100104, 1))
		  {
			pPlayer->DestroyItemCount(100104, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(100104);	
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 6 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pCreature->MonsterWhisper("Success. Your donor item has been removed and your points has been refunded.", LANG_UNIVERSAL, pPlayer->GetGUID());
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
            case 5004:
		  if(pPlayer->HasItemCount(100106, 1))
		  {
			pPlayer->DestroyItemCount(100106, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(100106);	
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 6 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pCreature->MonsterWhisper("Success. Your donor item has been removed and your points has been refunded.", LANG_UNIVERSAL, pPlayer->GetGUID());
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
            
	     case 10000://shirt
				pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donaters Shirt - 6 Dp ", GOSSIP_SENDER_MAIN, 10001);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Ultimate Shirt I - 5 Dp", GOSSIP_SENDER_MAIN, 10002);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Ultimate Shirt II - 7 Dp", GOSSIP_SENDER_MAIN, 10003);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Ultimate Shirt III - 13 Dp", GOSSIP_SENDER_MAIN, 10004);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Ultimate Shirt IV - 20 Dp", GOSSIP_SENDER_MAIN, 10005);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Ultimate Shirt V - 30 Dp", GOSSIP_SENDER_MAIN, 10006);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                pPlayer->PlayerTalkClass->SendGossipMenu(85006, pCreature->GetGUID());
                return true;
                break;
				
		
		case 10001:	
		  if(pPlayer->HasItemCount(100105, 1))
			{
			pPlayer->DestroyItemCount(100105, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(100105);	
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 6 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;case 10002:	
		  if(pPlayer->HasItemCount(100125, 1))
			{
			pPlayer->DestroyItemCount(100125, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(100125);	
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 5 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case 10003:	
		  if(pPlayer->HasItemCount(100126, 1))
			{
			pPlayer->DestroyItemCount(100126, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(100126);	
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 6 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case 10004:	
		  if(pPlayer->HasItemCount(100127, 1))
			{
			pPlayer->DestroyItemCount(100127, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(100127);	
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 13 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case 10005:	
		  if(pPlayer->HasItemCount(100128, 1))
			{
			pPlayer->DestroyItemCount(100128, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(100128);	
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 20 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case 10006:	
		  if(pPlayer->HasItemCount(100129, 1))
			{
			pPlayer->DestroyItemCount(100129, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(100129);	
			LoginDatabase.PQuery("Update Fusion.account_data Set dp = dp + 30 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  
	     case 11000: // donors cloak
		  switch(pPlayer->getClass())
		  {
		  case CLASS_WARRIOR:
		  if(pPlayer->HasItemCount(100112, 1))
		  {
			pPlayer->DestroyItemCount(100112, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(100112);	
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pCreature->MonsterWhisper("Success. Your donor item has been removed and your points has been refunded.", LANG_UNIVERSAL, pPlayer->GetGUID());
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case CLASS_PALADIN:
		  if(pPlayer->HasItemCount(100117, 1))
		  {
			pPlayer->DestroyItemCount(100117, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(100117);	
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pCreature->MonsterWhisper("Success. Your donor item has been removed and your points has been refunded.", LANG_UNIVERSAL, pPlayer->GetGUID());
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case CLASS_HUNTER:
		  if(pPlayer->HasItemCount(100119, 1))
		  {
			pPlayer->DestroyItemCount(100119, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(100119);	
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pCreature->MonsterWhisper("Success. Your donor item has been removed and your points has been refunded.", LANG_UNIVERSAL, pPlayer->GetGUID());
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case CLASS_ROGUE:
		  if(pPlayer->HasItemCount(100115, 1))
		  {
			pPlayer->DestroyItemCount(100115, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(100115);	
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pCreature->MonsterWhisper("Success. Your donor item has been removed and your points has been refunded.", LANG_UNIVERSAL, pPlayer->GetGUID());
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
	 	  case CLASS_PRIEST:
		  if(pPlayer->HasItemCount(100116, 1))
		  {
			pPlayer->DestroyItemCount(100116, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(100116);	
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pCreature->MonsterWhisper("Success. Your donor item has been removed and your points has been refunded.", LANG_UNIVERSAL, pPlayer->GetGUID());
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case CLASS_DEATH_KNIGHT:
		  if(pPlayer->HasItemCount(100121, 1))
		  {
			pPlayer->DestroyItemCount(100121, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(100121);	
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pCreature->MonsterWhisper("Success. Your donor item has been removed and your points has been refunded.", LANG_UNIVERSAL, pPlayer->GetGUID());
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case CLASS_SHAMAN:
		  if(pPlayer->HasItemCount(100114, 1))
		  {
			pPlayer->DestroyItemCount(100114, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(100114);	
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pCreature->MonsterWhisper("Success. Your donor item has been removed and your points has been refunded.", LANG_UNIVERSAL, pPlayer->GetGUID());
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case CLASS_MAGE:
		  if(pPlayer->HasItemCount(100118, 1))
		  {
			pPlayer->DestroyItemCount(100118, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(100118);	
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pCreature->MonsterWhisper("Success. Your donor item has been removed and your points has been refunded.", LANG_UNIVERSAL, pPlayer->GetGUID());
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case CLASS_WARLOCK:
		  if(pPlayer->HasItemCount(100113, 1))
		  {
			pPlayer->DestroyItemCount(100113, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(100113);	
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pCreature->MonsterWhisper("Success. Your donor item has been removed and your points has been refunded.", LANG_UNIVERSAL, pPlayer->GetGUID());
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case CLASS_DRUID:
		  if(pPlayer->HasItemCount(100120, 1))
		  {
			pPlayer->DestroyItemCount(100120, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(100120);	
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pCreature->MonsterWhisper("Success. Your donor item has been removed and your points has been refunded.", LANG_UNIVERSAL, pPlayer->GetGUID());
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;

		  default: break;
		  }
		  break;
		  
		  case 14000: // donors tabard
		  switch(pPlayer->getClass())
		  {
		  case CLASS_WARRIOR:
		  if(pPlayer->HasItemCount(100093, 1))
		  {
			pPlayer->DestroyItemCount(100093, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(100093);	
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 7 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pCreature->MonsterWhisper("Success. Your donor item has been removed and your points has been refunded.", LANG_UNIVERSAL, pPlayer->GetGUID());
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case CLASS_PALADIN:
		  if(pPlayer->HasItemCount(100098, 1))
		  {
			pPlayer->DestroyItemCount(100098, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(100098);	
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 7 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pCreature->MonsterWhisper("Success. Your donor item has been removed and your points has been refunded.", LANG_UNIVERSAL, pPlayer->GetGUID());
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case CLASS_HUNTER:
		  if(pPlayer->HasItemCount(100100, 1))
		  {
			pPlayer->DestroyItemCount(100100, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(100100);	
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 7 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pCreature->MonsterWhisper("Success. Your donor item has been removed and your points has been refunded.", LANG_UNIVERSAL, pPlayer->GetGUID());
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case CLASS_ROGUE:
		  if(pPlayer->HasItemCount(100096, 1))
		  {
			pPlayer->DestroyItemCount(100096, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(100096);	
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 7 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pCreature->MonsterWhisper("Success. Your donor item has been removed and your points has been refunded.", LANG_UNIVERSAL, pPlayer->GetGUID());
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
	 	  case CLASS_PRIEST:
		  if(pPlayer->HasItemCount(100097, 1))
		  {
			pPlayer->DestroyItemCount(100097, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(100097);	
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 7 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pCreature->MonsterWhisper("Success. Your donor item has been removed and your points has been refunded.", LANG_UNIVERSAL, pPlayer->GetGUID());
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case CLASS_DEATH_KNIGHT:
		  if(pPlayer->HasItemCount(100102, 1))
		  {
			pPlayer->DestroyItemCount(100102, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(100102);	
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 7 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pCreature->MonsterWhisper("Success. Your donor item has been removed and your points has been refunded.", LANG_UNIVERSAL, pPlayer->GetGUID());
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case CLASS_SHAMAN:
		  if(pPlayer->HasItemCount(100095, 1))
		  {
			pPlayer->DestroyItemCount(100095, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(100095);	
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 7 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pCreature->MonsterWhisper("Success. Your donor item has been removed and your points has been refunded.", LANG_UNIVERSAL, pPlayer->GetGUID());
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case CLASS_MAGE:
		  if(pPlayer->HasItemCount(100099, 1))
		  {
			pPlayer->DestroyItemCount(100099, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(100099);	
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 7 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pCreature->MonsterWhisper("Success. Your donor item has been removed and your points has been refunded.", LANG_UNIVERSAL, pPlayer->GetGUID());
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case CLASS_WARLOCK:
		  if(pPlayer->HasItemCount(100094, 1))
		  {
			pPlayer->DestroyItemCount(100094, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(100094);	
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 7 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pCreature->MonsterWhisper("Success. Your donor item has been removed and your points has been refunded.", LANG_UNIVERSAL, pPlayer->GetGUID());
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case CLASS_DRUID:
		  if(pPlayer->HasItemCount(100101, 1))
		  {
			pPlayer->DestroyItemCount(100101, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(100101);	
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 7 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pCreature->MonsterWhisper("Success. Your donor item has been removed and your points has been refunded.", LANG_UNIVERSAL, pPlayer->GetGUID());
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;

		  default: break;
		  }
		  break;
		  
	     case 12000: // donors set
		  switch(pPlayer->getClass())
		  {
		  case CLASS_WARRIOR:
		  if(pPlayer->HasItemCount(65015, 1) && pPlayer->HasItemCount(65016, 1) && pPlayer->HasItemCount(65017, 1) && pPlayer->HasItemCount(65018, 1) && pPlayer->HasItemCount(65019, 1))
		  {
			pPlayer->DestroyItemCount(65015, 1, true);
			pPlayer->DestroyItemCount(65016, 1, true);
			pPlayer->DestroyItemCount(65017, 1, true);
			pPlayer->DestroyItemCount(65018, 1, true);
			pPlayer->DestroyItemCount(65019, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 75 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			pCreature->MonsterWhisper("Success. Your donor item has been removed and your points has been refunded.", LANG_UNIVERSAL, pPlayer->GetGUID());
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case CLASS_PALADIN:
		  if(pPlayer->HasItemCount(65035, 1) && pPlayer->HasItemCount(65036, 1) && pPlayer->HasItemCount(65037, 1) && pPlayer->HasItemCount(65038, 1) && pPlayer->HasItemCount(65039, 1))
		  {
			pPlayer->DestroyItemCount(65035, 1, true);
			pPlayer->DestroyItemCount(65036, 1, true);
			pPlayer->DestroyItemCount(65037, 1, true);
			pPlayer->DestroyItemCount(65038, 1, true);
			pPlayer->DestroyItemCount(65039, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 75 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			pCreature->MonsterWhisper("Success. Your donor item has been removed and your points has been refunded.", LANG_UNIVERSAL, pPlayer->GetGUID());
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case CLASS_HUNTER:
		  if(pPlayer->HasItemCount(65005, 1) && pPlayer->HasItemCount(65006, 1) && pPlayer->HasItemCount(65007, 1) && pPlayer->HasItemCount(65008, 1) && pPlayer->HasItemCount(65009, 1))
		  {
			pPlayer->DestroyItemCount(65005, 1, true);
			pPlayer->DestroyItemCount(65006, 1, true);
			pPlayer->DestroyItemCount(65007, 1, true);
			pPlayer->DestroyItemCount(65008, 1, true);
			pPlayer->DestroyItemCount(65009, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 75 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			pCreature->MonsterWhisper("Success. Your donor item has been removed and your points has been refunded.", LANG_UNIVERSAL, pPlayer->GetGUID());
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case CLASS_ROGUE:
		  if(pPlayer->HasItemCount(65010, 1) && pPlayer->HasItemCount(65011, 1) && pPlayer->HasItemCount(65012, 1) && pPlayer->HasItemCount(65013, 1) && pPlayer->HasItemCount(65014, 1))
		  {
			pPlayer->DestroyItemCount(65010, 1, true);
			pPlayer->DestroyItemCount(65011, 1, true);
			pPlayer->DestroyItemCount(65012, 1, true);
			pPlayer->DestroyItemCount(65013, 1, true);
			pPlayer->DestroyItemCount(65014, 1, true);
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 75 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			pCreature->MonsterWhisper("Success. Your donor item has been removed and your points has been refunded.", LANG_UNIVERSAL, pPlayer->GetGUID());
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
	 	  case CLASS_PRIEST:
		  if(pPlayer->HasItemCount(65020, 1) && pPlayer->HasItemCount(65021, 1) && pPlayer->HasItemCount(65022, 1) && pPlayer->HasItemCount(65023, 1) && pPlayer->HasItemCount(65024, 1))
		  {
			pPlayer->DestroyItemCount(65020, 1, true);
			pPlayer->DestroyItemCount(65021, 1, true);
			pPlayer->DestroyItemCount(65022, 1, true);
			pPlayer->DestroyItemCount(65023, 1, true);
			pPlayer->DestroyItemCount(65024, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 75 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			pCreature->MonsterWhisper("Success. Your donor item has been removed and your points has been refunded.", LANG_UNIVERSAL, pPlayer->GetGUID());
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case CLASS_DEATH_KNIGHT:
		  if(pPlayer->HasItemCount(65000, 1) && pPlayer->HasItemCount(65001, 1) && pPlayer->HasItemCount(65002, 1) && pPlayer->HasItemCount(65003, 1) && pPlayer->HasItemCount(65004, 1))
		  {
			pPlayer->DestroyItemCount(65000, 1, true);
			pPlayer->DestroyItemCount(65001, 1, true);
			pPlayer->DestroyItemCount(65002, 1, true);
			pPlayer->DestroyItemCount(65003, 1, true);
			pPlayer->DestroyItemCount(65004, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 75 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			pCreature->MonsterWhisper("Success. Your donor item has been removed and your points has been refunded.", LANG_UNIVERSAL, pPlayer->GetGUID());
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case CLASS_SHAMAN:
		  if(pPlayer->HasItemCount(65040, 1) && pPlayer->HasItemCount(65041, 1) && pPlayer->HasItemCount(65042, 1) && pPlayer->HasItemCount(65043, 1) && pPlayer->HasItemCount(65044, 1))
		  {
			pPlayer->DestroyItemCount(65040, 1, true);
			pPlayer->DestroyItemCount(65041, 1, true);
			pPlayer->DestroyItemCount(65042, 1, true);
			pPlayer->DestroyItemCount(65043, 1, true);
			pPlayer->DestroyItemCount(65044, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 75 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			pCreature->MonsterWhisper("Success. Your donor item has been removed and your points has been refunded.", LANG_UNIVERSAL, pPlayer->GetGUID());
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case CLASS_MAGE:
		  if(pPlayer->HasItemCount(65045, 1) && pPlayer->HasItemCount(65046, 1) && pPlayer->HasItemCount(65047, 1) && pPlayer->HasItemCount(65048, 1) && pPlayer->HasItemCount(65049, 1))
		  {
			pPlayer->DestroyItemCount(65045, 1, true);
			pPlayer->DestroyItemCount(65046, 1, true);
			pPlayer->DestroyItemCount(65047, 1, true);
			pPlayer->DestroyItemCount(65048, 1, true);
			pPlayer->DestroyItemCount(65049, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 75 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			pCreature->MonsterWhisper("Success. Your donor item has been removed and your points has been refunded.", LANG_UNIVERSAL, pPlayer->GetGUID());
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case CLASS_WARLOCK:
		  if(pPlayer->HasItemCount(65030, 1) && pPlayer->HasItemCount(65031, 1) && pPlayer->HasItemCount(65032, 1) && pPlayer->HasItemCount(65033, 1) && pPlayer->HasItemCount(65034, 1))
		  {
			pPlayer->DestroyItemCount(65030, 1, true);
			pPlayer->DestroyItemCount(65031, 1, true);
			pPlayer->DestroyItemCount(65032, 1, true);
			pPlayer->DestroyItemCount(65033, 1, true);
			pPlayer->DestroyItemCount(65034, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 75 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			pCreature->MonsterWhisper("Success. Your donor item has been removed and your points has been refunded.", LANG_UNIVERSAL, pPlayer->GetGUID());
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  case CLASS_DRUID:
		  if(pPlayer->HasItemCount(65025, 1) && pPlayer->HasItemCount(65026, 1) && pPlayer->HasItemCount(65027, 1) && pPlayer->HasItemCount(65028, 1) && pPlayer->HasItemCount(65029, 1))
		  {
			pPlayer->DestroyItemCount(65025, 1, true);
			pPlayer->DestroyItemCount(65026, 1, true);
			pPlayer->DestroyItemCount(65027, 1, true);
			pPlayer->DestroyItemCount(65028, 1, true);
			pPlayer->DestroyItemCount(65029, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 75 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			pCreature->MonsterWhisper("Success. Your donor item has been removed and your points has been refunded.", LANG_UNIVERSAL, pPlayer->GetGUID());
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;

		  default: break;
		  }
		  break;
	     case 9997:
                pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Are you sure you wish to sell your frostmourne?", GOSSIP_SENDER_MAIN, 9997);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Yes.", GOSSIP_SENDER_MAIN, 9996);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: No.", GOSSIP_SENDER_MAIN, 9999);
                pPlayer->PlayerTalkClass->SendGossipMenu(85006, pCreature->GetGUID());
                return true;
                break;
            case 9999:
                pPlayer->PlayerTalkClass->ClearMenus();
                OnGossipHello(pPlayer, pCreature);
                break;
	     case 9996:
		  if(pPlayer->HasItemCount(27769, 1))
		  {
			pPlayer->DestroyItemCount(27769, 1, true);
			
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 35 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			pCreature->MonsterWhisper("Success. Your donor item has been removed and your points has been refunded.", LANG_UNIVERSAL, pPlayer->GetGUID());
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
            }

            return true;
     }
};

void AddSC_refundvendor()
{
    new refundvendor();
}
