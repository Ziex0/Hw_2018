/////////////////////////////////////////////////////////////////////////////
//        ____        __  __  __     ___                                   //
//       / __ )____ _/ /_/ /_/ /__  /   |  ________  ____  ____ ______     //
//      / __  / __ `/ __/ __/ / _ \/ /| | / ___/ _ \/ __ \/ __ `/ ___/     //
//     / /_/ / /_/ / /_/ /_/ /  __/ ___ |/ /  /  __/ / / / /_/ (__  )      //
//    /_____/\__,_/\__/\__/_/\___/_/  |_/_/   \___/_/ /_/\__,_/____/       //
//         Developed by Natureknight for BattleArenas.no-ip.org            //
//             Copyright (C) 2015 Natureknight/JessiqueBA                  //
//                      battlearenas.no-ip.org                             //
/////////////////////////////////////////////////////////////////////////////

#include "ScriptPCH.h"

// IMPORTANT: Write your definitions here:
static std::string website = "web_db";       // FusionCMS database name

// DONATION POINTS PRICES:
static uint32 oneMonthVipPrice = 7;               // VIP account price for 1 month (in donation points) (Default: 30 donate points)
static uint32 threeMonthsVipPrice = 17;            // VIP account price for 3 months (in donation points) (Default: 50 donate points)
static uint32 nineMonthsVipPrice = 28;            // VIP account price for 3 months (in donation points) (Default: 50 donate points)
static uint32 permaMonthsVipPrice = 40;


static uint32 purchaseDays;                   

class Donation_NPC_AT : public CreatureScript
{
public:
	Donation_NPC_AT() : CreatureScript("Donation_NPC_AT") {}

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

	bool OnGossipHello(Player * pPlayer, Creature * pCreature)
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

		// Purchase VIP Account for one month
		if (SelectDPoints(pPlayer) < oneMonthVipPrice)
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|TInterface/icons/Spell_Shadow_Shadowform:25|tPurchase |cffFF0000Premium|r Account for one month (|cff980000Locked|r / Information) 7 Dp", GOSSIP_SENDER_MAIN, 1);
		else if (SelectDPoints(pPlayer) >= oneMonthVipPrice)
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|TInterface/icons/Spell_Shadow_Shadowform:25|tPurchase |cffFF0000Premium|r Account for one month (|cff009900Unlocked|r / Click to use) 7 Dp", GOSSIP_SENDER_MAIN, 2);

		// Purchase VIP Account for three months
		if (SelectDPoints(pPlayer) < threeMonthsVipPrice)
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|TInterface/icons/Spell_Shadow_Shadowform:25|tPurchase |cffFF0000Premium|r Account for three months (|cff980000Locked|r / Information) 17 Dp", GOSSIP_SENDER_MAIN, 1);
		else if (SelectDPoints(pPlayer) >= threeMonthsVipPrice)
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|TInterface/icons/Spell_Shadow_Shadowform:25|tPurchase |cffFF0000Premium|r Account for three months (|cff009900Unlocked|r / Click to use) 17 Dp", GOSSIP_SENDER_MAIN, 3);
		
		// Purchase VIP Account for 9 months
		if (SelectDPoints(pPlayer) < nineMonthsVipPrice)
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|TInterface/icons/Spell_Shadow_Shadowform:25|tPurchase |cffFF0000Premium|r Account for nine months (|cff980000Locked|r / Information 28 Dp", GOSSIP_SENDER_MAIN, 1);
		else if (SelectDPoints(pPlayer) >= nineMonthsVipPrice)
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|TInterface/icons/Spell_Shadow_Shadowform:25|tPurchase |cffFF0000Premium|r Account for nine months (|cff009900Unlocked|r / Click to use) 28 Dp", GOSSIP_SENDER_MAIN, 4);
		
		// Purchase VIP Accountpermanent
		if (SelectDPoints(pPlayer) < permaMonthsVipPrice)
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|TInterface/icons/Spell_Shadow_Shadowform:25|tPurchase |cffFF0000Premium|r permanent (|cff980000Locked|r / Information)40 Dp", GOSSIP_SENDER_MAIN, 1);
		else if (SelectDPoints(pPlayer) >= permaMonthsVipPrice)
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|TInterface/icons/Spell_Shadow_Shadowform:25|tPurchase |cffFF0000Premium|r permanent (|cff009900Unlocked|r / Click to use) 40 Dp", GOSSIP_SENDER_MAIN, 5);


		
		// Show Donate and Voting Points when GossipHello
		points << "My Donation Points: " << SelectDPoints(pPlayer);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, points.str().c_str(), GOSSIP_SENDER_MAIN, 100);
		pPlayer->SEND_GOSSIP_MENU(60031, pCreature->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player * pPlayer, Creature * pCreature, uint32 sender, uint32 uiAction)
	{
		pPlayer->PlayerTalkClass->ClearMenus();

		if (sender != GOSSIP_SENDER_MAIN)
			return false;

		uint32 dp = SelectDPoints(pPlayer);

		switch(uiAction)
		{
			
			case 2:
                pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Activate Now", GOSSIP_SENDER_MAIN, 21);
				pPlayer->PlayerTalkClass->SendGossipMenu(85005, pCreature->GetGUID());
                return true;
                break;
			case 3:
                pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Activate Now", GOSSIP_SENDER_MAIN, 31);
				pPlayer->PlayerTalkClass->SendGossipMenu(85005, pCreature->GetGUID());
                return true;
                break;
			case 4:
                pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Activate Now", GOSSIP_SENDER_MAIN, 41);
				pPlayer->PlayerTalkClass->SendGossipMenu(85005, pCreature->GetGUID());
                return true;
                break;
			case 5:
                pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Activate Now", GOSSIP_SENDER_MAIN, 51);
				pPlayer->PlayerTalkClass->SendGossipMenu(85005, pCreature->GetGUID());
                return true;
                break;
				
		case 1: // Vip accounts - LOCKED
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "This |cffFF0000Premium|r rank same like |cffFF0000Premium|r permanent.. Custom Commands.. Free |cffFF0000Premium|r set.. |cffFF0000Premium|r use timer.. There you can choose how long you want be Premium rank on Server, or you can Get Permanent :)", GOSSIP_SENDER_MAIN, 1000);
			pPlayer->SEND_GOSSIP_MENU(60032, pCreature->GetGUID());
			break;

		case 21: // Vip account one month - unlocked
			if (pPlayer->GetSession()->GetSecurity() >= 1)
			{
				pPlayer->GetSession()->SendAreaTriggerMessage("You're already |cffFF0000Premium|r");
				pPlayer->CLOSE_GOSSIP_MENU();
			}
			else
			{
				uint32 purchaseTime = sWorld->GetGameTime() / DAY;
				purchaseDays = 30;

				LoginDatabase.PExecute("UPDATE %s.account_data SET dp = '%u' -%u WHERE id = '%u'", website.c_str(), dp, oneMonthVipPrice, pPlayer->GetSession()->GetAccountId());
				LoginDatabase.PExecute("DELETE FROM account_access WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
				LoginDatabase.PExecute("REPLACE INTO `account_access` (`id`, `gmlevel`, `RealmID`) VALUES ('%u', '1', '1')", pPlayer->GetSession()->GetAccountId());
				
				//LoginDatabase.PExecute("INSERT INTO web_db.vip_monthly_report (`account_id`, `char_use`, `RealmID`) VALUES ('%u', '%s', '1')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName());
				// Set the correct date timestamp and start the 1 month counter
				CharacterDatabase.PExecute("DELETE FROM `vip_conditions` WHERE `accountId` = '%u'", pPlayer->GetSession()->GetAccountId()); // Overwrite
				CharacterDatabase.PExecute("REPLACE INTO `vip_conditions` (`accountId`, `purchaseTime`) VALUES ('%u', '%u')", pPlayer->GetSession()->GetAccountId(), (purchaseTime + purchaseDays));

				pPlayer->GetSession()->SendAreaTriggerMessage("Successfully upgraded your account to |cffFF0000Premium|r for One month use. "
					"Close the game and login again for changes to take effect! Thanks for the support!");
				pPlayer->SaveToDB();
				pPlayer->CLOSE_GOSSIP_MENU();
			}
			break;

		case 31: // Vip account three months - unlocked
			if (pPlayer->GetSession()->GetSecurity() >= 1)
			{
				pPlayer->GetSession()->SendAreaTriggerMessage("You're already |cffFF0000Premium|r");
				pPlayer->CLOSE_GOSSIP_MENU();
			}
			else
			{
				uint32 purchaseTime = sWorld->GetGameTime() / DAY;
				purchaseDays = 90;

				LoginDatabase.PExecute("UPDATE %s.account_data SET dp = '%u' -%u WHERE id = '%u'", website.c_str(), dp, threeMonthsVipPrice, pPlayer->GetSession()->GetAccountId());
				LoginDatabase.PExecute("DELETE FROM account_access WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
				LoginDatabase.PExecute("REPLACE INTO `account_access` (`id`, `gmlevel`, `RealmID`) VALUES ('%u', '1', '1')", pPlayer->GetSession()->GetAccountId());
				
				// LoginDatabase.PExecute("INSERT INTO web_db.vip_monthly_report (`account_id`, `char_use`, `RealmID`) VALUES ('%u', '%s', '1')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName());
				// Set the correct date timestamp and start the 1 month counter
				CharacterDatabase.PExecute("DELETE FROM `vip_conditions` WHERE `accountId` = '%u'", pPlayer->GetSession()->GetAccountId()); // Overwrite
				CharacterDatabase.PExecute("REPLACE INTO `vip_conditions` (`accountId`, `purchaseTime`) VALUES ('%u', '%u')", pPlayer->GetSession()->GetAccountId(), (purchaseTime + purchaseDays));

				pPlayer->GetSession()->SendAreaTriggerMessage("Successfully upgraded your account to |cffFF0000Premium|r for Three months use. "
					"Close the game and login again for changes to take effect! Thanks for the support!");
				pPlayer->SaveToDB();
				pPlayer->CLOSE_GOSSIP_MENU();
			}
			break;
			
		case 41 : // Vip account three months - unlocked
			if (pPlayer->GetSession()->GetSecurity() >= 1)
			{
				pPlayer->GetSession()->SendAreaTriggerMessage("You're already |cffFF0000Premium|r");
				pPlayer->CLOSE_GOSSIP_MENU();
			}
			else
			{
				uint32 purchaseTime = sWorld->GetGameTime() / DAY;
				purchaseDays = 270;

				LoginDatabase.PExecute("UPDATE %s.account_data SET dp = '%u' -%u WHERE id = '%u'", website.c_str(), dp, nineMonthsVipPrice, pPlayer->GetSession()->GetAccountId());
				LoginDatabase.PExecute("DELETE FROM account_access WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
				LoginDatabase.PExecute("REPLACE INTO `account_access` (`id`, `gmlevel`, `RealmID`) VALUES ('%u', '1', '1')", pPlayer->GetSession()->GetAccountId());
				
				// Set the correct date timestamp and start the 1 month counter
				//LoginDatabase.PExecute("INSERT INTO web_db.vip_monthly_report (`account_id`, `char_use`, `RealmID`) VALUES ('%u', '%s', '1')", pPlayer->GetSession()->GetAccountId(), pPlayer->GetName());
				CharacterDatabase.PExecute("DELETE FROM `vip_conditions` WHERE `accountId` = '%u'", pPlayer->GetSession()->GetAccountId()); // Overwrite
				CharacterDatabase.PExecute("REPLACE INTO `vip_conditions` (`accountId`, `purchaseTime`) VALUES ('%u', '%u')", pPlayer->GetSession()->GetAccountId(), (purchaseTime + purchaseDays));

				pPlayer->GetSession()->SendAreaTriggerMessage("Successfully upgraded your account to |cffFF0000Premium|r for Nine months use. "
					"Close the game and login again for changes to take effect! Thanks for the support!");
				pPlayer->SaveToDB();
				pPlayer->CLOSE_GOSSIP_MENU();
			}
			break;
			
		case 51 : // Vip account three months - unlocked
			if (pPlayer->GetSession()->GetSecurity() >= 1)
			{
				pPlayer->GetSession()->SendAreaTriggerMessage("You're already |cffFF0000Premium|r");
				pPlayer->CLOSE_GOSSIP_MENU();
			}
			else
			{
				//uint32 purchaseTime = sWorld->GetGameTime() / DAY;
				//purchaseDays = 270;

				LoginDatabase.PExecute("UPDATE %s.account_data SET dp = '%u' -%u WHERE id = '%u'", website.c_str(), dp, permaMonthsVipPrice, pPlayer->GetSession()->GetAccountId());
				LoginDatabase.PExecute("DELETE FROM account_access WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
				LoginDatabase.PExecute("REPLACE INTO `account_access` (`id`, `gmlevel`, `RealmID`) VALUES ('%u', '1', '1')", pPlayer->GetSession()->GetAccountId());
				
				// Set the correct date timestamp and start the 1 month counter
				CharacterDatabase.PExecute("DELETE FROM `vip_conditions` WHERE `accountId` = '%u'", pPlayer->GetSession()->GetAccountId()); // Overwrite
				LoginDatabase.PExecute("REPLACE INTO account_premium (`id`, `setdate`, `unsetdate`, `Premium_type`, `active`) VALUES ('%u', '%u', '%u', '1', '1')", pPlayer->GetSession()->GetAccountId());
				//CharacterDatabase.PExecute("REPLACE INTO `vip_conditions` (`accountId`, `purchaseTime`) VALUES ('%u', '%u')", pPlayer->GetSession()->GetAccountId(), (purchaseTime + purchaseDays));

				pPlayer->GetSession()->SendAreaTriggerMessage("Successfully upgraded your account to |cffFF0000Premium|r Permanent. "
					"Close the game and login again for changes to take effect! Thanks for the support!");
				pPlayer->SaveToDB();
				pPlayer->CLOSE_GOSSIP_MENU();
			}
			break;

		case 999: // Not enought points
			pPlayer->GetSession()->SendAreaTriggerMessage("Not dont have enought points.Donate more on Www.TheSatria.Com");
			OnGossipHello(pPlayer, pCreature);
			break;

		case 1000: // Back to main menu
			OnGossipHello(pPlayer, pCreature);
			break;
		}
		return true;
	}
};


class Conditions : public WorldScript
{
public:
	Conditions() : WorldScript("Conditions") {}

	uint32 checkTimer;

	void CheckConditions(Player* player)
	{
		if (player->GetSession()->GetSecurity() != 1)
			return;

		QueryResult select = CharacterDatabase.PQuery("SELECT purchaseTime FROM vip_conditions WHERE accountId = '%u'", player->GetSession()->GetAccountId());
		if (!select)
		{
			// Just in case
			sLog->outError(LOG_FILTER_GENERAL,"NOTE: Automatic VIP accounts script just removed the VIP rights for player %s (accountId: '%u'). There are no "
				"records in the vip_conditions table for this player any more, so the changes will take effect once the player logout.", 
				player->GetName(), player->GetSession()->GetAccountId());
			return;
		}

		Field* fields = select->Fetch();
		uint32 purchaseTimestamp = fields[0].GetUInt32();
		uint32 currentDay = sWorld->GetGameTime() / DAY;
		std::string expireMessage = "Your VIP rights for one month just expired, so your account is not VIP anymore, and "
			"changes will take effect on the next login. Feel free to purchase VIP rights for an additional month. Thanks for the support!";

		if (currentDay > purchaseTimestamp)
		{
			player->GetSession()->SendAreaTriggerMessage(expireMessage.c_str());
			ChatHandler(player->GetSession()).PSendSysMessage(expireMessage.c_str());

			// Delete DB entries also
			LoginDatabase.PExecute("DELETE FROM account_access WHERE id = '%u'", player->GetSession()->GetAccountId());
			CharacterDatabase.PExecute("DELETE FROM vip_conditions WHERE accountId = '%u'", player->GetSession()->GetAccountId());
		}
	}

	void OnStartup()
	{
		// Start timer 10 minutes after server initialize
		checkTimer = 30 * IN_MILLISECONDS * MINUTE;
	}

	void OnUpdate(uint32 diff)
	{
		if (checkTimer <= diff)
		{
			SessionMap players = sWorld->GetAllSessions();
			for (SessionMap::iterator itr = players.begin(); itr != players.end(); ++itr)
				if (Player* vipPlayer = itr->second->GetPlayer())
					CheckConditions(vipPlayer);

			// Check expired VIPs on every 10 minutes
			checkTimer = 10 * IN_MILLISECONDS * MINUTE;
		} else { 
			checkTimer -= diff;
		}
	}
};

void AddSC_Donation_NPC()
{
	new Donation_NPC_AT();
	new Conditions();
}
