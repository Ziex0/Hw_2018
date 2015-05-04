#include "ScriptPCH.h"
#include "Language.h"
#include "Chat.h"

class premium_rate : public CreatureScript
{
    public:

        premium_rate()
            : CreatureScript("premium_rate")
        {
        }

        bool OnGossipHello(Player* pPlayer, Creature* pCreature)
        {
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface/ICONS/INV_Misc_Book_11:30:30:-18:0|t Set me to Permanent Premium", GOSSIP_SENDER_MAIN, 2000);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface/ICONS/INV_Misc_Book_11:30:30:-18:0|t Set me to 6 months Premium", GOSSIP_SENDER_MAIN, 3000);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface/ICONS/INV_Misc_Book_11:30:30:-18:0|t Set me to 3 Months Premium", GOSSIP_SENDER_MAIN, 4000);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface/ICONS/INV_Misc_Book_11:30:30:-18:0|t Set me to 1 Months Premium", GOSSIP_SENDER_MAIN, 5000);
			
            pPlayer->PlayerTalkClass->SendGossipMenu(85005, pCreature->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
        {
            pPlayer->PlayerTalkClass->ClearMenus();
			
            switch (uiAction)
            {
				
            case 2000:
                pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Activate Now", GOSSIP_SENDER_MAIN, 2001);
				pPlayer->PlayerTalkClass->SendGossipMenu(85005, pCreature->GetGUID());
                return true;
                break;
			case 3000:
                pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Activate Now", GOSSIP_SENDER_MAIN, 3001);
				pPlayer->PlayerTalkClass->SendGossipMenu(85005, pCreature->GetGUID());
                return true;
                break;
			case 4000:
                pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Activate Now", GOSSIP_SENDER_MAIN, 4001);
				pPlayer->PlayerTalkClass->SendGossipMenu(85005, pCreature->GetGUID());
                return true;
                break;
			case 5000:
                pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Activate Now", GOSSIP_SENDER_MAIN, 5001);
				pPlayer->PlayerTalkClass->SendGossipMenu(85005, pCreature->GetGUID());
                return true;
                break;

		case 2001:
			if(pPlayer->HasItemCount(320265, 1))
			{
			pPlayer->DestroyItemCount(320265, 1, true);
			LoginDatabase.PExecute("REPLACE INTO account_premium (`id`, `setdate`, `unsetdate`, `Premium_type`, `active`) VALUES ('%u', '%u', '0', '1', '1')", pPlayer->GetSession()->GetAccountId());			
			LoginDatabase.PExecute("REPLACE INTO account_access (`id`, `gmlevel`, `RealmID`) VALUES ('%u', '1', '1')", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PExecute("REPLACE INTO rbac_account_groups (accountId, groupId, RealmID) VALUES ('%u', '1', '1')", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PExecute("REPLACE INTO account_vip (`acc_id`, `viplevel`, `active`) VALUES ('%u', '1', '1')", pPlayer->GetSession()->GetAccountId());
			char str[200];
			sprintf(str,"Your now Permanent PREMIUM member, thank you for supporting our server! please close your Wow and Re-login");
                pPlayer->MonsterWhisper(str,pPlayer->GetGUID(),true);                
			} 
				else 
					{
					pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
					pPlayer->PlayerTalkClass->SendCloseGossip();
					}
			break;
					
		case 3001:
			if(pPlayer->HasItemCount(320265, 1))
			{
				uint32 start_date = 0;
				uint32 end_date = 0;
				
			pPlayer->DestroyItemCount(320265, 1, true);
			LoginDatabase.PExecute("REPLACE INTO account_premium (`id`, `setdate`, `unsetdate`, `Premium_type`, `active`) VALUES ('%u', '%u', '0', '1', '1')", pPlayer->GetSession()->GetAccountId());			
			LoginDatabase.PExecute("REPLACE INTO account_access (`id`, `gmlevel`, `RealmID`) VALUES ('%u', '1', '1')", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PExecute("REPLACE INTO rbac_account_groups (accountId, groupId, RealmID) VALUES ('%u', '1', '1')", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PQuery  ("INSERT INTO `account_vip` (acc_id, viplevel, start_date, end_date, active) VALUES (%u, %u, %u, %u, %u)", pPlayer->GetSession()-> GetAccountId());
			char str[200];
			sprintf(str,"You set Vip Level 1, valid 180 days. thank you for supporting our server! please close your Wow and Re-login");
                //pPlayer->MonsterWhisper(str,pPlayer->GetGUID(),true);                
			} 
			else 
					{
					pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
					pPlayer->PlayerTalkClass->SendCloseGossip();
					}break;
		  
				
	    
        }

            return true;
     }
};

void AddSC_premium_rate()
{
    new premium_rate();
}
