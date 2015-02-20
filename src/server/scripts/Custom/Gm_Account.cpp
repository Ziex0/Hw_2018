#include "ScriptPCH.h"
#include "Language.h"
#include "Chat.h"

class gm_active : public CreatureScript
{
    public:

        gm_active()
            : CreatureScript("gm_active")
        {
        }

        bool OnGossipHello(Player* pPlayer, Creature* pCreature)
        {
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface/ICONS/INV_Misc_Book_11:30:30:-18:0|t Trial Gm", GOSSIP_SENDER_MAIN, 2000);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface/ICONS/INV_Misc_Book_11:30:30:-18:0|t Gm", GOSSIP_SENDER_MAIN, 3000);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface/ICONS/INV_Misc_Book_11:30:30:-18:0|t Head Gm", GOSSIP_SENDER_MAIN, 4000);
			
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
			

			case 2001:
				if(pPlayer->HasItemCount(320278, 1))
		{
			pPlayer->DestroyItemCount(320278, 1, true);
			LoginDatabase.PExecute("REPLACE INTO account_access (`id`, `gmlevel`, `RealmID`) VALUES ('%u', '2', '1')", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PExecute("REPLACE INTO rbac_account_groups (accountId, groupId, RealmID) VALUES ('%u', '1', '1')", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PExecute("REPLACE INTO rbac_account_groups (accountId, groupId, RealmID) VALUES ('%u', '2', '1')", pPlayer->GetSession()->GetAccountId());
			char str[200];
			sprintf(str,"You are now Activated! please close your Wow and Re-login");
                pPlayer->MonsterWhisper(str,pPlayer->GetGUID(),true);
                
		} else 
		  {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
		  
			case 3001:
				if(pPlayer->HasItemCount(320279, 1))
		{
			pPlayer->DestroyItemCount(320279, 1, true);
			LoginDatabase.PExecute("REPLACE INTO account_access (`id`, `gmlevel`, `RealmID`) VALUES ('%u', '3', '1')", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PExecute("REPLACE INTO rbac_account_groups (accountId, groupId, RealmID) VALUES ('%u', '1', '1')", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PExecute("REPLACE INTO rbac_account_groups (accountId, groupId, RealmID) VALUES ('%u', '2', '1')", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PExecute("REPLACE INTO rbac_account_groups (accountId, groupId, RealmID) VALUES ('%u', '3', '1')", pPlayer->GetSession()->GetAccountId());
			char str[200];
			sprintf(str,"You are now Activated! please close your Wow and Re-login");
                pPlayer->MonsterWhisper(str,pPlayer->GetGUID(),true);
                
		} else 
		  {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
			
		case 4001:
				if(pPlayer->HasItemCount(320280, 1))
		{
			pPlayer->DestroyItemCount(320280, 1, true);
			LoginDatabase.PExecute("REPLACE INTO account_access (`id`, `gmlevel`, `RealmID`) VALUES ('%u', '4', '1')", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PExecute("REPLACE INTO rbac_account_groups (accountId, groupId, RealmID) VALUES ('%u', '1', '1')", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PExecute("REPLACE INTO rbac_account_groups (accountId, groupId, RealmID) VALUES ('%u', '2', '1')", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PExecute("REPLACE INTO rbac_account_groups (accountId, groupId, RealmID) VALUES ('%u', '3', '1')", pPlayer->GetSession()->GetAccountId());
			LoginDatabase.PExecute("REPLACE INTO rbac_account_groups (accountId, groupId, RealmID) VALUES ('%u', '4', '1')", pPlayer->GetSession()->GetAccountId());
			char str[200];
			sprintf(str,"You are now Activated! please close your Wow and Re-login");
                pPlayer->MonsterWhisper(str,pPlayer->GetGUID(),true);
                
		} else 
		  {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;
	    
        }

            return true;
     }
};

void AddSC_gm_active()
{
    new gm_active();
}
