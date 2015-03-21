#include "ScriptPCH.h"
#include "Language.h"
#include "Chat.h"

class refundvendor : public CreatureScript
{
    public:
			refundvendor(): CreatureScript("refundvendor")
        {
        }
		
bool OnGossipHello(Player* pPlayer, Creature* pCreature)
        {
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Donor Weapons", GOSSIP_SENDER_MAIN, 2000);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Armor / Misc", GOSSIP_SENDER_MAIN, 3000);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Special Items", GOSSIP_SENDER_MAIN, 4000);
			
            pPlayer->PlayerTalkClass->SendGossipMenu(100000, pCreature->GetGUID());

            return true;
        }

        bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
        {
            pPlayer->PlayerTalkClass->ClearMenus();

            switch (uiAction)
            {
				
				case 2000://supreme  misc
                pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Sword - 5 Dp", GOSSIP_SENDER_MAIN, 2001);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Axe - 5 Dp", GOSSIP_SENDER_MAIN, 2002);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Melee Dagger - 5 Dp", GOSSIP_SENDER_MAIN, 2003);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Spell Dagger - 5 Dp", GOSSIP_SENDER_MAIN, 3004);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Bow  - 5 Dp", GOSSIP_SENDER_MAIN, 2005);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Gun  - 5 Dp", GOSSIP_SENDER_MAIN, 2006);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Wand  - 5 Dp", GOSSIP_SENDER_MAIN, 2007);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Dual Axe  - 5 Dp", GOSSIP_SENDER_MAIN, 2008);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Dual Sword  - 5 Dp", GOSSIP_SENDER_MAIN, 2009);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Dual Mace  - 5 Dp", GOSSIP_SENDER_MAIN, 2010);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Mace  - 5 Dp", GOSSIP_SENDER_MAIN, 2011);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Spell Staff  - 5 Dp", GOSSIP_SENDER_MAIN, 2012);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: Final Achievement Feral Staff  - 5 Dp", GOSSIP_SENDER_MAIN, 2013);
				
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Refund: [Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                pPlayer->PlayerTalkClass->SendGossipMenu(100000, pCreature->GetGUID());
                return true;
                break;
				
				
            case 2001:
                if(pPlayer->HasItemCount(130134, 1))
			{
			pPlayer->DestroyItemCount(130134, 1, true);
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(130134);			
			LoginDatabase.PQuery("Update web_db.account_data Set dp = dp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery("INSERT INTO web_db.refund (account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName(), itemTemplate->Name1.c_str());
			pPlayer->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Account in Site for detail !!");
			}else 
				{
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
				}
				break;
			
			
			
			
			
			
			
			
			}
		}
};

void AddSC_refundvendor()
{
    new refundvendor();
}
