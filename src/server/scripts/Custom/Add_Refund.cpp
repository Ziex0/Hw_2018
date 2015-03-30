#include "ScriptPCH.h"
#include "Language.h"
#include "Chat.h"

class refundvendor : public CreatureScript
{
    public:
		refundvendor(): CreatureScript("refundvendor"){}
        
		
		bool OnGossipHello(Player* pPlayer, Creature* pCreature)
        {
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donor Weapons", GOSSIP_SENDER_MAIN, 2000);
            //pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Armor / Misc", GOSSIP_SENDER_MAIN, 3000);
            //pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Special Items", GOSSIP_SENDER_MAIN, 4000);
			
            pPlayer->PlayerTalkClass->SendGossipMenu(50000, pCreature->GetGUID());
			return true;

        }

        bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
        {
            pPlayer->PlayerTalkClass->ClearMenus();

            switch (uiAction)
            {	
				case 2000:
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Sword - 5 Dp", GOSSIP_SENDER_MAIN, 2001);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Axe - 5 Dp", GOSSIP_SENDER_MAIN, 2002);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Melee Dagger - 5 Dp", GOSSIP_SENDER_MAIN, 2003);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Spell Dagger - 5 Dp", GOSSIP_SENDER_MAIN, 2004);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Bow  - 5 Dp", GOSSIP_SENDER_MAIN, 2005);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Gun  - 5 Dp", GOSSIP_SENDER_MAIN, 2006);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Wand  - 5 Dp", GOSSIP_SENDER_MAIN, 2007);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Dual Axe  - 12 Dp", GOSSIP_SENDER_MAIN, 2008);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Dual Sword  - 12 Dp", GOSSIP_SENDER_MAIN, 2009);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Dual Mace  - 12 Dp", GOSSIP_SENDER_MAIN, 2010);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Mace  - 5 Dp", GOSSIP_SENDER_MAIN, 2011);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Spell Staff  - 12 Dp", GOSSIP_SENDER_MAIN, 2012);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Feral Staff  - 12 Dp", GOSSIP_SENDER_MAIN, 2013);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Polearm  - 12 Dp", GOSSIP_SENDER_MAIN, 2014);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Melee Tank Shield  - 6 Dp", GOSSIP_SENDER_MAIN, 2015);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Melee Tank Shield  - 6 Dp", GOSSIP_SENDER_MAIN, 2016);
				
				pPlayer->PlayerTalkClass->SendGossipMenu(50000, pCreature->GetGUID());
				break;

            case 2001:
                if(pPlayer->HasItemCount(200169, 1))
			{
			pPlayer->DestroyItemCount(200169, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(200169);			
			LoginDatabase.PQuery("Update web_db.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO web_db.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Account in Site for detail !!");
			}else 
				{
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
				}
				break;
				
			case 2002:
                if(pPlayer->HasItemCount(200170, 1))
			{
			pPlayer->DestroyItemCount(200170, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(200170);			
			LoginDatabase.PQuery("Update web_db.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO web_db.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Account in Site for detail !!");
			}else 
				{
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
				}
				break;
				
			case 2003:
                if(pPlayer->HasItemCount(200180, 1))
			{
			pPlayer->DestroyItemCount(200180, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(200180);			
			LoginDatabase.PQuery("Update web_db.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO web_db.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Account in Site for detail !!");
			}else 
				{
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
				}
				break;
			
			case 2004:
                if(pPlayer->HasItemCount(200228, 1))
			{
			pPlayer->DestroyItemCount(200228, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(200228);			
			LoginDatabase.PQuery("Update web_db.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO web_db.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Account in Site for detail !!");
			}else 
				{
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
				}
				break;
			
			case 2005: //bow
                if(pPlayer->HasItemCount(200172, 1))
			{
			pPlayer->DestroyItemCount(200172, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(200172);			
			LoginDatabase.PQuery("Update web_db.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO web_db.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Account in Site for detail !!");
			}else 
				{
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
				}
				break;
			
			case 2006://gun
                if(pPlayer->HasItemCount(200173, 1))
			{
			pPlayer->DestroyItemCount(200173, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(200173);			
			LoginDatabase.PQuery("Update web_db.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO web_db.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Account in Site for detail !!");
			}else 
				{
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
				}
				break;
				
			case 2007://wabd
                if(pPlayer->HasItemCount(200181, 1))
			{
			pPlayer->DestroyItemCount(200181, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(200181);			
			LoginDatabase.PQuery("Update web_db.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO web_db.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Account in Site for detail !!");
			}else 
				{
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
				}
				break;
				
			case 2008: //dual axe
                if(pPlayer->HasItemCount(200178, 1))
			{
			pPlayer->DestroyItemCount(200178, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(200178);			
			LoginDatabase.PQuery("Update web_db.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO web_db.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Account in Site for detail !!");
			}else 
				{
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
				}
				break;
				
			case 2009:  //dual sword
                if(pPlayer->HasItemCount(200176, 1))
			{
			pPlayer->DestroyItemCount(200176, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(200176);			
			LoginDatabase.PQuery("Update web_db.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO web_db.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Account in Site for detail !!");
			}else 
				{
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
				}
				break;
				
			case 2010://dual mace
                if(pPlayer->HasItemCount(200177, 1))
			{
			pPlayer->DestroyItemCount(200177, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(200177);			
			LoginDatabase.PQuery("Update web_db.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO web_db.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Account in Site for detail !!");
			}else 
				{
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
				}
				break;
				
			case 2011://mace
                if(pPlayer->HasItemCount(200171, 1))
			{
			pPlayer->DestroyItemCount(200171, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(200171);			
			LoginDatabase.PQuery("Update web_db.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO web_db.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Account in Site for detail !!");
			}else 
				{
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
				}
				break;
				
			case 2012://spell staff
                if(pPlayer->HasItemCount(200179, 1))
			{
			pPlayer->DestroyItemCount(200179, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(200179);			
			LoginDatabase.PQuery("Update web_db.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO web_db.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Account in Site for detail !!");
			}else 
				{
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
				}
				break;
				
			case 2013://feral staff
                if(pPlayer->HasItemCount(200229, 1))
			{
			pPlayer->DestroyItemCount(200229, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(200229);			
			LoginDatabase.PQuery("Update web_db.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO web_db.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Account in Site for detail !!");
			}else 
				{
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
				}
				break;
				
			case 2014://spell staff
                if(pPlayer->HasItemCount(200230, 1))
			{
			pPlayer->DestroyItemCount(200230, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(200230);			
			LoginDatabase.PQuery("Update web_db.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO web_db.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Account in Site for detail !!");
			}else 
				{
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
				}
				break;
				
			case 2015://spell staff
                if(pPlayer->HasItemCount(200167, 1))
			{
			pPlayer->DestroyItemCount(200167, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(200167);			
			LoginDatabase.PQuery("Update web_db.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO web_db.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Account in Site for detail !!");
			}else 
				{
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
				}
				break;
				
			case 2016://spell staff
                if(pPlayer->HasItemCount(200168, 1))
			{
			pPlayer->DestroyItemCount(200168, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(200168);			
			LoginDatabase.PQuery("Update web_db.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO web_db.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Account in Site for detail !!");
			}else 
				{
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
				}
			}

            return true;
     }
};

void AddSC_refundvendor()
{
    new refundvendor();
}
