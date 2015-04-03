#include "ScriptPCH.h"
#include "Language.h"
#include "Chat.h"

class refundvendor : public CreatureScript
{
    public:
			refundvendor(): CreatureScript("refundvendor")
        {
        }
		
		bool OnGossipHello(Player * pPlayer, Creature* pCreature)
        {
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donor Weapons", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2000);
            //pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Rings/Trinkets/Amulets", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3000);
            //pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Armors", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 300);
 
			
            pPlayer->PlayerTalkClass->SendGossipMenu(85006, pCreature->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
        {
            pPlayer->PlayerTalkClass->ClearMenus();

            switch (uiAction)
            {
            case GOSSIP_ACTION_INFO_DEF +  2000:
                
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Sword - 5 Dp", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF +  2001);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Axe - 5 Dp", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF +   2002);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Melee Dagger - 5 Dp", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF +   2003);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Spell Dagger - 5 Dp", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF +   2004);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Bow  - 5 Dp", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF +   2005);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Gun  - 5 Dp", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF +   2006);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Wand  - 5 Dp", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF +   2007);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Dual Axe  - 12 Dp", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF +   2008);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Dual Sword  - 12 Dp", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF +   2009);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Dual Mace  - 12 Dp", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF +   2010);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Mace  - 5 Dp", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF +   2011);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Spell Staff  - 12 Dp", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF +   2012);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Feral Staff  - 12 Dp", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF +   2013);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Polearm  - 12 Dp", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF +   2014);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Melee Tank Shield  - 6 Dp", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF +   2015);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Melee Tank Shield  - 6 Dp", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF +   2016);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: [Main Menu]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9999);
                pPlayer->PlayerTalkClass->SendGossipMenu(85006, pCreature->GetGUID());

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
					
				
            case GOSSIP_ACTION_INFO_DEF +  300:
                pPlayer->PlayerTalkClass->ClearMenus();
                //pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Cloak of Triumph = 10 DP", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 301);
                //pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donaters Tabard = 15 DP", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 302);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donor Melee Bag = 6 DP", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 303);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donor Caster Bag = 6 DP", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 305);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donaters Steel Shield = 4 DP", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 304);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: [Main Menu]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9999);
                pPlayer->PlayerTalkClass->SendGossipMenu(85006, pCreature->GetGUID());
                return true;
                break;
				
            
            case GOSSIP_ACTION_INFO_DEF +  301:
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
            case GOSSIP_ACTION_INFO_DEF +  302:
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
            case GOSSIP_ACTION_INFO_DEF +  303:
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
   		  case GOSSIP_ACTION_INFO_DEF +  304:
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
                case GOSSIP_ACTION_INFO_DEF +  305:
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
		  
		  
        case GOSSIP_ACTION_INFO_DEF +  3000: // ringand trinket
                pPlayer->PlayerTalkClass->ClearMenus();                
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donor Melee Ring 6 DP", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3001);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donor Melee Trinket 6 DP", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3002);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donor Melee Amulet/Neck 6 DP", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3003);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donor Caster Ring 6 DP", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3004);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donor Caster Trinket 6 DP", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3005);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donor Caster Amulet/Neck 6 DP", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3006);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: [Main Menu]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9999);
                pPlayer->PlayerTalkClass->SendGossipMenu(85006, pCreature->GetGUID());
                return true;
                break;
				
            case GOSSIP_ACTION_INFO_DEF +  3001:
		  if(pPlayer->HasItemCount(100110, 1))
		  {
			pPlayer->DestroyItemCount(100110, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(100110);	
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 6 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
            case GOSSIP_ACTION_INFO_DEF +  3002:
		  if(pPlayer->HasItemCount(100109, 1))
		  {
			pPlayer->DestroyItemCount(100109, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(100109);	
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 6 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
            case GOSSIP_ACTION_INFO_DEF +  3003:
		  if(pPlayer->HasItemCount(100111, 1))
		  {
			pPlayer->DestroyItemCount(100111, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(100111);	
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 6 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
            case GOSSIP_ACTION_INFO_DEF +  3004:
		  if(pPlayer->HasItemCount(100131, 1))
		  {
			pPlayer->DestroyItemCount(100131, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(100131);	
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 6 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
            case GOSSIP_ACTION_INFO_DEF +  3005:
		  if(pPlayer->HasItemCount(100132, 1))
		  {
			pPlayer->DestroyItemCount(100132, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(100132);	
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 6 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
            case GOSSIP_ACTION_INFO_DEF +  3006:
		  if(pPlayer->HasItemCount(100133, 1))
		  {
			pPlayer->DestroyItemCount(100133, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(100133);	
			LoginDatabase.PQuery("Update fusion.account_data Set dp = dp + 6 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO fusion.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Dp for detail !!");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  } else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
 
            case GOSSIP_ACTION_INFO_DEF +  9999:
                pPlayer->PlayerTalkClass->ClearMenus();
                OnGossipHello(pPlayer, pCreature);
			break;
	     
            }

            return true;
		
	}
};

void AddSC_refundvendor()
{
    new refundvendor();
}