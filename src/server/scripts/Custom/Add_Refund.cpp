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
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Rings/Trinkets/Amulets", GOSSIP_SENDER_MAIN, 3000);
			
			 pPlayer->PlayerTalkClass->SendGossipMenu(85006, pCreature->GetGUID());

            return true;
        }

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
        pPlayer->PlayerTalkClass->ClearMenus();

        switch (uiAction)
        {
			case 2000:
                pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: One-Handed Weapons", GOSSIP_SENDER_MAIN, 2001);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Two-Handed Weapons", GOSSIP_SENDER_MAIN, 2002);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Staves", GOSSIP_SENDER_MAIN, 2003);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Ranged", GOSSIP_SENDER_MAIN, 2004);
                //pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Off-Hand Weapons", GOSSIP_SENDER_MAIN, 2005);
                //pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Main-Hand Weapons", GOSSIP_SENDER_MAIN, 2006);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: [Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                pPlayer->PlayerTalkClass->SendGossipMenu(85006, pCreature->GetGUID());
                return true;
                break;
            case 2001:
                pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Sword - 5 Dp", GOSSIP_SENDER_MAIN,  2101);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Axe - 5 Dp", GOSSIP_SENDER_MAIN,   2102);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Melee Dagger - 5 Dp", GOSSIP_SENDER_MAIN,   2103);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Spell Dagger - 5 Dp", GOSSIP_SENDER_MAIN,   2104);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Mace  - 5 Dp", GOSSIP_SENDER_MAIN,   2111);
				
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: [Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                pPlayer->PlayerTalkClass->SendGossipMenu(85006, pCreature->GetGUID());
                return true;
                break;
            case  2101:
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
				
			case  2102:
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
				
			case  2303:
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
			
			case   2104:
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
			case  2011://mace
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
				
			//end one hannd
			case 2105:
		  if(pPlayer->HasItemCount(100088, 1))
		  {
			pPlayer->DestroyItemCount(100088, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(100088);	
			LoginDatabase.PQuery("Update web_db.account_data Set dp = dp + 8 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO web_db.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
			case 2106:
		  if(pPlayer->HasItemCount(100087, 1))
		  {
			pPlayer->DestroyItemCount(100087, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(100087);	
			LoginDatabase.PQuery("Update web_db.account_data Set dp = dp + 8 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO web_db.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
			case 2107:
		  if(pPlayer->HasItemCount(100082, 1))
		  {
			pPlayer->DestroyItemCount(100082, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(100082);	
			LoginDatabase.PQuery("Update web_db.account_data Set dp = dp + 8 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO web_db.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
			case 2108:
		  if(pPlayer->HasItemCount(100091, 1))
		  {
			pPlayer->DestroyItemCount(100091, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(100091);	
			LoginDatabase.PQuery("Update web_db.account_data Set dp = dp + 8 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO web_db.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
			case 2109:
		  if(pPlayer->HasItemCount(100090, 1))
		  {
			pPlayer->DestroyItemCount(100090, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(100090);	
			LoginDatabase.PQuery("Update web_db.account_data Set dp = dp + 8 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO web_db.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
case 2110:
		  if(pPlayer->HasItemCount(100089, 1))
		  {
			pPlayer->DestroyItemCount(100089, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(100089);	
			LoginDatabase.PQuery("Update web_db.account_data Set dp = dp + 8 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO web_db.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
				
            case 2002:
                pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Dual Axe  - 12 Dp", GOSSIP_SENDER_MAIN,   2208);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Dual Sword  - 12 Dp", GOSSIP_SENDER_MAIN,   2209);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Dual Mace  - 12 Dp", GOSSIP_SENDER_MAIN,   2210);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Polearm  - 12 Dp", GOSSIP_SENDER_MAIN,   2214);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: [Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                pPlayer->PlayerTalkClass->SendGossipMenu(85006, pCreature->GetGUID());
                return true;
                break;
            case  2208: //dual axe
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
				
			case  2209:  //dual sword
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
				
			case  2210://dual mace
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
			case  2214://polearm
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
				//end two hand
				
            case 2003:
                pPlayer->PlayerTalkClass->ClearMenus();                
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Spell Staff  - 12 Dp", GOSSIP_SENDER_MAIN,   2312);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Feral Staff  - 12 Dp", GOSSIP_SENDER_MAIN,   2313);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: [Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                pPlayer->PlayerTalkClass->SendGossipMenu(85006, pCreature->GetGUID());
                return true;
                break;
            case 2312://spell staff
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
				
			case 2313://feral staff
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
				//end staves
            case 2004:
                pPlayer->PlayerTalkClass->ClearMenus();                
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Bow  - 5 Dp", GOSSIP_SENDER_MAIN,   2005);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Gun  - 5 Dp", GOSSIP_SENDER_MAIN,   2006);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Wand  - 5 Dp", GOSSIP_SENDER_MAIN,  2007);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: [Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                pPlayer->PlayerTalkClass->SendGossipMenu(85006, pCreature->GetGUID());
                return true;
                break;
           case 2405: //bow
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
			
			case 2406://gun
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
				
			case 2407://wabd
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
				//end of range
			case 3000: // ringand trinket
                pPlayer->PlayerTalkClass->ClearMenus();                
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donor Melee Ring 3 DP", GOSSIP_SENDER_MAIN, 3001);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donor Melee Trinket 3 DP", GOSSIP_SENDER_MAIN, 3002);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donor Melee Amulet/Neck 3 DP", GOSSIP_SENDER_MAIN, 3003);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donor Caster Ring 3 DP", GOSSIP_SENDER_MAIN, 3004);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donor Caster Trinket 3 DP", GOSSIP_SENDER_MAIN, 3005);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donor Caster Amulet/Neck 3 DP", GOSSIP_SENDER_MAIN, 3006);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: [Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                pPlayer->PlayerTalkClass->SendGossipMenu(85006, pCreature->GetGUID());
                return true;
                break;
				
            case 3001:
		  if(pPlayer->HasItemCount(200161, 1))
		  {
			pPlayer->DestroyItemCount(200161, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(200161);	
			LoginDatabase.PQuery("Update web_db.account_data Set dp = dp + 3 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO web_db.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
            case 3002:
		  if(pPlayer->HasItemCount(200162, 1))
		  {
			pPlayer->DestroyItemCount(200162, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(200162);	
			LoginDatabase.PQuery("Update web_db.account_data Set dp = dp + 3 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO web_db.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
            case 3003:
		  if(pPlayer->HasItemCount(200163, 1))
		  {
			pPlayer->DestroyItemCount(200163, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(200163);	
			LoginDatabase.PQuery("Update web_db.account_data Set dp = dp + 3 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO web_db.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
            case 3004:
		  if(pPlayer->HasItemCount(200215, 1))
		  {
			pPlayer->DestroyItemCount(200215, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(200215);	
			LoginDatabase.PQuery("Update web_db.account_data Set dp = dp + 3 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO web_db.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
            case 3005:
		  if(pPlayer->HasItemCount(200216, 1))
		  {
			pPlayer->DestroyItemCount(200216, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(200216);	
			LoginDatabase.PQuery("Update web_db.account_data Set dp = dp + 3 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO web_db.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
            case 3006:
		  if(pPlayer->HasItemCount(100133, 1))
		  {
			pPlayer->DestroyItemCount(100133, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(100133);	
			LoginDatabase.PQuery("Update web_db.account_data Set dp = dp + 3 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO web_db.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  
		  return true;
		}			
					
    }
};

void AddSC_refundvendor()
{
    new refundvendor();
}