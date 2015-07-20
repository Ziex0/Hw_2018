#include "ScriptPCH.h"
#include "Language.h"
#include "Chat.h"

// IMPORTANT: Write your definitions here:
static std::string website = "web_db";       // FusionCMS database name

// DONATION POINTS PRICES:
static uint32 oneMonthVipPrice = 11;               // VIP account price for 1 month (in donation points) (Default: 30 donate points)
static uint32 threeMonthsVipPrice = 21;            // VIP account price for 3 months (in donation points) (Default: 50 donate points)
static uint32 nineMonthsVipPrice = 33;            // VIP account price for 3 months (in donation points) (Default: 50 donate points)
static uint32 permaMonthsVipPrice = 45;


static uint32 purchaseDays;   

class premium_rate : public CreatureScript
{
    public:

        premium_rate()
            : CreatureScript("premium_rate")
        {
        }
		
		uint32 SelectDPoints(Player* pPlayer)
	{
		QueryResult select = LoginDatabase.PQuery("SELECT dp FROM %s.account_data WHERE id = '%u'", website.c_str(), pPlayer->GetSession()->GetAccountId());
		if (!select) // Just in case, but should not happen
		{
			pPlayer->CLOSE_GOSSIP_MENU();
			return 0;
		}

		Field* fields = select->Fetch();
		uint32 dp = fields[0].GetUInt32();

		return dp;
		
	}

        bool OnGossipHello(Player* pPlayer, Creature* pCreature)
        {
			std::stringstream points;

		// Prevent exploiting the FusionCMS donate points
		if (pPlayer->GetSession()->GetSecurity() < 3 && SelectDPoints(pPlayer) > 200)
		{
			pPlayer->GetSession()->SendAreaTriggerMessage("You have large amount of Donation points: %u. This is probably a website related problem, please "
				"immediately contact the administrator via ticket about this issue.", SelectDPoints(pPlayer));
			pPlayer->CLOSE_GOSSIP_MENU();
			return false;
		}
		
            //pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface/ICONS/INV_Misc_Book_11:30:30:-18:0|tPremium Permanent Rank 1", GOSSIP_SENDER_MAIN, 2000);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface/ICONS/INV_Misc_Book_11:30:30:-18:0|tSet me to premium Rank 2 for 1 month", GOSSIP_SENDER_MAIN, 6000);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface/ICONS/INV_Misc_Book_11:30:30:-18:0|tSet me to premium Rank 2 for 3 month", GOSSIP_SENDER_MAIN, 7000);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface/ICONS/INV_Misc_Book_11:30:30:-18:0|tSet me to premium Rank 2 for 9 month", GOSSIP_SENDER_MAIN, 8000);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface/ICONS/INV_Misc_Book_11:30:30:-18:0|tSet me to premium Rank 2 Permanent", GOSSIP_SENDER_MAIN, 9000);
			
			// Show Donate and Voting Points when GossipHello
				points << "My Donation Points: " << SelectDPoints(pPlayer);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, points.str().c_str(), GOSSIP_SENDER_MAIN, 100);
				pPlayer->SEND_GOSSIP_MENU(60031, pCreature->GetGUID());
				return true;
        }

        bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
        {
            pPlayer->PlayerTalkClass->ClearMenus();
			
			uint32 dp = SelectDPoints(pPlayer);
			
            switch (uiAction)
            {
				
            case 2000:
                pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Activate Now", GOSSIP_SENDER_MAIN, 2001);
				pPlayer->PlayerTalkClass->SendGossipMenu(85005, pCreature->GetGUID());
                return true;
                break;
			
			case 6000:
                pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Upgrade Now", GOSSIP_SENDER_MAIN, 6001);
				pPlayer->PlayerTalkClass->SendGossipMenu(60031, pCreature->GetGUID());
                return true;
                break;

		case 2001:
			pPlayer->CLOSE_GOSSIP_MENU();
			if(pPlayer->HasItemCount(320265, 1))
			{
			pPlayer->DestroyItemCount(320265, 1, true);
			LoginDatabase.PExecute("REPLACE INTO account_premium (`id`, `setdate`, `unsetdate`, `Premium_type`, `active`) VALUES ('%u', '%u', '0', '1', '1')", pPlayer->GetSession()->GetAccountId());			
			LoginDatabase.PExecute("REPLACE INTO account_access (`id`, `gmlevel`, `RealmID`) VALUES ('%u', '1', '1')", pPlayer->GetSession()->GetAccountId());
			//LoginDatabase.PExecute("REPLACE INTO account_vip (`acc_id`, `viplevel`, `active`) VALUES ('%u', '1', '1')", pPlayer->GetSession()->GetAccountId());
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
		
		case 6001:
			pPlayer->CLOSE_GOSSIP_MENU();
			if(pPlayer->HasItemCount(320264, 1))
			{
				pPlayer->DestroyItemCount(320264, 1, true);
				uint32 purchaseTime = sWorld->GetGameTime() / DAY;
				purchaseDays = 30;

				//LoginDatabase.PExecute("UPDATE %s.account_data SET dp = '%u' -%u WHERE id = '%u'", website.c_str(), dp, oneMonthVipPrice, pPlayer->GetSession()->GetAccountId());
				LoginDatabase.PExecute("DELETE FROM account_access WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
				LoginDatabase.PExecute("REPLACE INTO `account_access` (`id`, `gmlevel`, `RealmID`) VALUES ('%u', '2', '1')", pPlayer->GetSession()->GetAccountId());
				// Set the correct date timestamp and start the 1 month counter
				CharacterDatabase.PExecute("DELETE FROM `vip_conditions` WHERE `accountId` = '%u'", pPlayer->GetSession()->GetAccountId()); // Overwrite
				CharacterDatabase.PExecute("REPLACE INTO `vip_conditions` (`accountId`, `purchaseTime`) VALUES ('%u', '%u')", pPlayer->GetSession()->GetAccountId(), (purchaseTime + purchaseDays));

				pPlayer->GetSession()->SendAreaTriggerMessage("Successfully upgraded your account to |cffFF0000Premium|r for One month use. "
					"Close the game and login again for changes to take effect! Thanks for the support!");
				pPlayer->SaveToDB();
				pPlayer->CLOSE_GOSSIP_MENU();           
			} 
				else 
					{
					pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
					pPlayer->PlayerTalkClass->SendCloseGossip();
					}
			break;				
	    
		}

            return true;
     }
};

void AddSC_premium_rate()
{
    new premium_rate();
}
