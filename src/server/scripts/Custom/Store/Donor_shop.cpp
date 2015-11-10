/*
CREATE TABLE `donation_purchases` (
	`account_id` INT(10) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'Account Identifier',
	`character_name` VARCHAR(12) NOT NULL DEFAULT '' COLLATE 'utf8_general_ci',
	`character_guid` INT(10) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'Global Unique Identifier',
	`donation_item_id` INT(10) UNSIGNED NOT NULL DEFAULT '0',
	`donation_item_name` VARCHAR(60) NOT NULL DEFAULT '' COLLATE 'utf8_general_ci',
	`donation_item_amount` INT(10) UNSIGNED NOT NULL DEFAULT '1',
	`date` TIMESTAMP NOT NULL DEFAULT '0000-00-00 00:00:00'
)
COMMENT='Write here a comment if this has been refunded or not.'
COLLATE='latin1_swedish_ci'
ENGINE=MyISAM
;
*/

#include "ScriptPCH.h"
#include <cstring>
#include "ObjectMgr.h"
#include "Language.h"
#include "Chat.h"

class donorrewarder : public CreatureScript
{
    public:donorrewarder() : CreatureScript("donorrewarder") {}
        
		uint32 SelectDPoints(Player* pPlayer)
			{
				QueryResult select = LoginDatabase.PQuery("SELECT dp FROM web_db.account_data WHERE id = '%u'",  pPlayer->GetSession()->GetAccountId());
				if (!select) // Just in case, but should not happen
				{
					pPlayer->CLOSE_GOSSIP_MENU();
					return 0;
				}

				Field* fields = select->Fetch();
				uint32 dp = fields[0].GetUInt32();

				return dp;
			}		
        void RewardItem(Player* player, Creature* pCreature, int item , int count, int cost)
        {
			char str[200];             
            if (player->AddItem(item, count))
            {
  			std::string DateTime = "%Y-%m-%d %H:%M:%S";
			ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(item);
			CharacterDatabase.PQuery("Update web_db.account_data Set dp = dp - '%u' WHERE id = '%u'", cost, player->GetSession()->GetAccountId());
            //LoginDatabase.PQuery("INSERT INTO donation_purchases (account_id, character_name, character_guid, donation_item_id, donation_item_name, donation_item_amount, date) VALUES ('%u', '%s', '%u', '%u', '%s', '%u', DATE_FORMAT(date, '%s'))", player->GetSession()->GetAccountId(), player->GetName(), player->GetGUIDLow(), item, itemTemplate->Name1.c_str(), count, DateTime.c_str());
            sprintf(str,"Your points are taken and your item is given!!!");
            player->MonsterWhisper(str,player->GetGUID(),true);
			player->SaveToDB();
            }
                    else
                    {
                        sprintf(str,"Item can't be given maybe your bag is full or you already got the item!");
                        player->MonsterWhisper(str,player->GetGUID(),true);
                    }           

            player->PlayerTalkClass->ClearMenus();
            OnGossipHello(player, pCreature);
        }
		
    bool OnGossipHello(Player* player, Creature* pCreature)
        {			

		// Prevent exploiting the FusionCMS donate points
				std::stringstream points;				
				if (player->GetSession()->GetSecurity() >= 0 && SelectDPoints(player) < 5 )
				{
					player->GetSession()->SendAreaTriggerMessage("SHOP LOCKED!!,You cant see item on Donor shop until your points are enought or at last you got 5 DP on your account", SelectDPoints(player));
					player->CLOSE_GOSSIP_MENU();
					return false;
				}
			else
			{
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "|TInterface/ICONS/Achievement_Leader_King_Varian_Wrynn:24|t|rDonation Token ,Coin", GOSSIP_SENDER_MAIN, 4000);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "|TInterface/ICONS/Achievement_Leader_King_Varian_Wrynn:24|t|rSupreme Donor Weapons", GOSSIP_SENDER_MAIN, 2000);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "|TInterface/ICONS/Achievement_Leader_King_Varian_Wrynn:24|t|rDonor Rings/Trinkets/Amulets and Bags", GOSSIP_SENDER_MAIN, 3000);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "|TInterface/ICONS/Achievement_Leader_King_Varian_Wrynn:24|t|rSpecial Items", GOSSIP_SENDER_MAIN, 5000);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "|TInterface/ICONS/Achievement_Leader_King_Varian_Wrynn:24|t|rRelics", GOSSIP_SENDER_MAIN, 6666);
				//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "|cffFF0000|TInterface\\icons\\Achievement_Leader_Sylvanas:30|tDonor Tabard - 7 Dp", GOSSIP_SENDER_MAIN, 10000);
				//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "|cffFF0000|TInterface\\icons\\Achievement_Leader_Sylvanas:30|tDonor Cloak - 10 DP", GOSSIP_SENDER_MAIN, 11000);
				//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "|TInterface/ICONS/Achievement_Leader_King_Varian_Wrynn:24|t|rDonor Set - 23 DP ( 8 Pieces )", GOSSIP_SENDER_MAIN, 12000);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "|TInterface/ICONS/Achievement_Leader_King_Varian_Wrynn:24|t|rUltimate Cross Weapon Skill", GOSSIP_SENDER_MAIN, 14000);
				//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "|cffFF0000|TInterface\\icons\\Achievement_Leader_Sylvanas:30|tDonor Royal Weapons", GOSSIP_SENDER_MAIN, 32000);
				//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Heaven Gems 5 DP - 3 Gems", GOSSIP_SENDER_MAIN, 5100);
				//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Portable Mailbox - 10 DP", GOSSIP_SENDER_MAIN, 5200);
				player->PlayerTalkClass->SendGossipMenu(90701, pCreature->GetGUID());

			}
			
			// Show Donate and Voting Points when GossipHello
				points << "|cffFF0000|TInterface/ICONS/ABILITY_DRUID_DEMORALIZINGROAR:24|tMy Donation Points: " << SelectDPoints(player);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, points.str().c_str(), GOSSIP_SENDER_MAIN, 100);
				player->SEND_GOSSIP_MENU(60031, pCreature->GetGUID());
				return true;
		}

        bool OnGossipSelect(Player* player, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
        {
            player->PlayerTalkClass->ClearMenus();
			
            switch (uiAction)
            {            
				case 5401:
					RewardItem(player, pCreature,24,1,15);
						break;
				case 19000:
					RewardItem(player, pCreature, 0, 0, 0);
						break;
				case 5402:
					RewardItem(player, pCreature,25,1,15);
						break;
				case 5403:
					RewardItem(player, pCreature,26,1,10);
						break;
				case 5200:
					RewardItem(player, pCreature,40768,1,10);
						break;
				case 5300:
					RewardItem(player, pCreature,37298,1,10);
						break;
				case 5100:
					RewardItem(player, pCreature,29765,3,5);
				break;
				
			case 4000:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Donor Coin - 7 DP", GOSSIP_SENDER_MAIN, 4001);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Heaven Soul Token - 11 DP", GOSSIP_SENDER_MAIN, 4012);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Heaven Soul Token Full - 70 DP", GOSSIP_SENDER_MAIN, 4002);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Premium Rank I - 20 DP", GOSSIP_SENDER_MAIN, 4003);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Premium Rank II - 40 DP", GOSSIP_SENDER_MAIN, 4004);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Premium Rank III - 60 DP", GOSSIP_SENDER_MAIN, 4005);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Master Buff Magic - 14 DP", GOSSIP_SENDER_MAIN, 4006);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Master Buff Range - 14 DP", GOSSIP_SENDER_MAIN, 4007);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Master Buff Melee - 14 DP", GOSSIP_SENDER_MAIN, 4008);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Transfer Token - 50 DP", GOSSIP_SENDER_MAIN, 4009);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Dual Wield - 10 DP", GOSSIP_SENDER_MAIN, 4010);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Titan Grip - 20 DP", GOSSIP_SENDER_MAIN, 4011);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90701, pCreature->GetGUID());
                return true;
                break;
			case 4012:
                RewardItem(player, pCreature, 30242,1,11);
                break;
			case 4001:
                RewardItem(player, pCreature, 31102,1,7);
                break;
			case 4002:
                RewardItem(player, pCreature, 30250,1,70);
                break;
			case 4003:
                RewardItem(player, pCreature, 745450,1,20);
                break;
			case 4004:
                RewardItem(player, pCreature, 745451,1,40);
                break;
			case 4005:
                RewardItem(player, pCreature, 22484,1,60);
                break;			
            case 4006:
                RewardItem(player, pCreature, 82000, 1, 14);
                break;	
            case 4007:
                RewardItem(player, pCreature, 82001, 1, 14);
                break;
			case 4008:
                RewardItem(player, pCreature, 82002, 1, 14);
                break;
			case 4009:
                RewardItem(player, pCreature, 66001, 1, 50);
                break;	
			case 4010:
                RewardItem(player, pCreature, 90900, 1, 10);
                break;
			case 4011:
                RewardItem(player, pCreature, 90901, 1, 20);
                break;
				
            case 1000:
                RewardItem(player, pCreature, 0, 0, 0);
                break;
				
				//donor weapon
            case 2000:
				player->PlayerTalkClass->ClearMenus();
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "One-Handed Weapons", GOSSIP_SENDER_MAIN, 2001);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Two-Handed Weapons", GOSSIP_SENDER_MAIN, 2002);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Staves", GOSSIP_SENDER_MAIN, 2003);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Ranged", GOSSIP_SENDER_MAIN, 2004);
				//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Off-Hand Weapons/ Shield", GOSSIP_SENDER_MAIN, 2005);
				//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Main-Hand Weapons", GOSSIP_SENDER_MAIN, 2006);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
				player->PlayerTalkClass->SendGossipMenu(85006, pCreature->GetGUID());
				return true;
				break;
				
			case 2001:
				player->PlayerTalkClass->ClearMenus();
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Supreme Melee Sword - 7 Dp", GOSSIP_SENDER_MAIN, 2101);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Supreme Spell Sword - 7 Dp", GOSSIP_SENDER_MAIN, 2106);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Supreme Axe - 7 Dp", GOSSIP_SENDER_MAIN, 2102);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Supreme Melee Dagger - 7 Dp", GOSSIP_SENDER_MAIN, 2103);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Supreme Spell Dagger - 7 Dp", GOSSIP_SENDER_MAIN, 2104);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Supreme Mace  - 7 Dp", GOSSIP_SENDER_MAIN, 2105);

				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
				player->PlayerTalkClass->SendGossipMenu(85006, pCreature->GetGUID());
				return true;
				break;
				
				case 2101:
					player->CLOSE_GOSSIP_MENU();
					RewardItem(player, pCreature, 30733, 1,7);
					break;
					
				case 2106:
					player->CLOSE_GOSSIP_MENU();
					RewardItem(player, pCreature,26624, 1,7);		
					break;

				case 2102:
					player->CLOSE_GOSSIP_MENU();
					RewardItem(player, pCreature,51516, 1,7);
					break;

				case 2103: //Melee Dagger
					player->CLOSE_GOSSIP_MENU();
					RewardItem(player, pCreature,43598, 1,7);
					break;

				case  2104: //Spell Dagger
					player->CLOSE_GOSSIP_MENU();
					RewardItem(player, pCreature,26624, 1,7);
					break;
				case 2105://mace
					player->CLOSE_GOSSIP_MENU();
					RewardItem(player, pCreature,19019, 1,7);
					break;
					//end one hannd

				case 2002:
					player->PlayerTalkClass->ClearMenus();
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Supreme Dual Axe  - 11 Dp", GOSSIP_SENDER_MAIN, 2208);
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Supreme Dual Sword  - 11 Dp", GOSSIP_SENDER_MAIN, 2209);
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Supreme Dual Mace  - 11 Dp", GOSSIP_SENDER_MAIN, 2210);
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Supreme Polearm  - 11 Dp", GOSSIP_SENDER_MAIN, 2214);
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
					player->PlayerTalkClass->SendGossipMenu(85006, pCreature->GetGUID());
					return true;
					break;
			
					case 2208: //dual axe
						player->CLOSE_GOSSIP_MENU();
						RewardItem(player, pCreature,50709, 1,11 );
						break;

					case 2209:  //dual sword
						player->CLOSE_GOSSIP_MENU();
						RewardItem(player, pCreature,52062, 1,11 );
						break;

					case 2210://dual mace
					player->CLOSE_GOSSIP_MENU();
						RewardItem(player, pCreature,50756, 1,11 );
						break;
					case 2214://polearm
					player->CLOSE_GOSSIP_MENU();
						RewardItem(player, pCreature,18869, 1,11 );
						break;
			//end two hand

		case 2003:
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Supreme Spell Staff  - 11 Dp", GOSSIP_SENDER_MAIN, 2312);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Supreme Feral Staff  - 11 Dp", GOSSIP_SENDER_MAIN, 2313);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
			player->PlayerTalkClass->SendGossipMenu(85006, pCreature->GetGUID());
			return true;
			break;
		case 2312://spell staff
		player->CLOSE_GOSSIP_MENU();
			RewardItem(player, pCreature,54806, 1,11 );
			break;

		case 2313://feral staff
		player->CLOSE_GOSSIP_MENU();
			RewardItem(player, pCreature,35514, 1,11 );
			break;
			//end staves
			
		case 2004:
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Supreme Bow  - 7 Dp", GOSSIP_SENDER_MAIN, 2405);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Supreme Gun  - 7 Dp", GOSSIP_SENDER_MAIN, 2406);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Supreme Wand  - 7 Dp", GOSSIP_SENDER_MAIN, 2407);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
			player->PlayerTalkClass->SendGossipMenu(85006, pCreature->GetGUID());
			return true;
			break;
		case 2405: //bow
		player->CLOSE_GOSSIP_MENU();
			RewardItem(player, pCreature,34529, 1,7);
			break;

		case 2406://gun
		player->CLOSE_GOSSIP_MENU();
			RewardItem(player, pCreature, 2552, 1, 7);
			break;

		case 2407://wand
		player->CLOSE_GOSSIP_MENU();
			RewardItem(player, pCreature, 51532, 1,7 );
			break;
			//end of range
			
		case 2005: // shield
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Supreme Tank Shield 4 DP", GOSSIP_SENDER_MAIN, 2501);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Supreme Spell Shield 4 DP", GOSSIP_SENDER_MAIN, 2502);
			player->PlayerTalkClass->SendGossipMenu(85006, pCreature->GetGUID());
			return true;
			break;
			
		case 2501:// tank shield
			player->CLOSE_GOSSIP_MENU();
			if (player->HasItemCount(50729, 1))
			{
				player->DestroyItemCount(50729, 1, true);
				ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(50729);
				LoginDatabase.PExecute("Update web_db.account_data Set dp = dp + 6 WHERE id = '%u'", player->GetSession()->GetAccountId());
				//LoginDatabase.PExecute("INSERT INTO db_world.refund(account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", player->GetSession()->GetAccountId(), player->GetName(), itemTemplate->Name1.c_str());
				player->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Account in Site for detail !!");
			}
			else
			{
				player->GetSession()->SendNotification("Failed. Make sure you have the desired item");
				player->PlayerTalkClass->SendCloseGossip();
			}
			break;
		case 2502: //spel shield
			player->CLOSE_GOSSIP_MENU();
			if (player->HasItemCount(44223, 1))
			{
				player->DestroyItemCount(44223, 1, true);
				ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(44223);
				LoginDatabase.PExecute("Update web_db.account_data Set dp = dp + 6 WHERE id = '%u'", player->GetSession()->GetAccountId());
				//LoginDatabase.PExecute("INSERT INTO db_world.refund(account_id, character_name, donation_item_name) VALUES ('%u', '%s', '%s')", player->GetSession()->GetAccountId(), player->GetName(), itemTemplate->Name1.c_str());
				player->GetSession()->SendNotification("Success. Your donor item has been removed and your points has been refunded.Check your Account in Site for detail !!");
			}
			else
			{
				player->GetSession()->SendNotification("Failed. Make sure you have the desired item");
				player->PlayerTalkClass->SendCloseGossip();
			}
			break;
			
			case 6666:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Supreme Relic - 5 DP ->", GOSSIP_SENDER_MAIN, 6000);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Heaven God Relic - 5 DP ->", GOSSIP_SENDER_MAIN, 7000);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90701, pCreature->GetGUID());
                return true;
                break;
				
			case 6000:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Supreme Idol - 5 DP", GOSSIP_SENDER_MAIN, 6001);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Supreme Totem - 5 DP", GOSSIP_SENDER_MAIN, 6002);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Supreme Sigil - 5 DP", GOSSIP_SENDER_MAIN, 6003);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Supreme Libram - 5 DP", GOSSIP_SENDER_MAIN, 6004);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90701, pCreature->GetGUID());
                return true;
                break;
			
			case 6001:
                RewardItem(player, pCreature,200004,1,5);
                break;
            case 6002:
                RewardItem(player, pCreature,200007,1,5);
                break;
            case 6003:
                RewardItem(player, pCreature,200006,1,5);
				break;
			case 6004:
                RewardItem(player, pCreature,200005,1,5);
				break;		
			
			case 7000:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Heaven God Idol - 8 DP", GOSSIP_SENDER_MAIN, 7001);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Heaven God Totem - 8 DP", GOSSIP_SENDER_MAIN, 7002);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Heaven God Sigil - 8 DP", GOSSIP_SENDER_MAIN, 7003);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Heaven God Libram - 8 DP", GOSSIP_SENDER_MAIN, 7004);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90701, pCreature->GetGUID());
                return true;
                break;
			
			case 7001:
                RewardItem(player, pCreature,310004,1,8);
                break;
            case 7002:
                RewardItem(player, pCreature,310007,1,8);
                break;
            case 7003:
                RewardItem(player, pCreature,310006,1,8);
				break;
			case 7004:
                RewardItem(player, pCreature,310005,1,8);
				break;
            
            case 3000: // ring,amulet balal
                player->PlayerTalkClass->ClearMenus();                
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Supreme Donor Melee Ring - 5 DP", GOSSIP_SENDER_MAIN, 3003);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Supreme Donor Caster Ring - 5 DP", GOSSIP_SENDER_MAIN, 3004);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Supreme Donor Melee Trinket - 5 DP", GOSSIP_SENDER_MAIN, 3005);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Supreme Donor Caster Trinket - 5 DP", GOSSIP_SENDER_MAIN, 3006);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Supreme Donor Melee Amulet - 5 DP", GOSSIP_SENDER_MAIN, 3007);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Supreme Donor Caster Amulet - 5 DP", GOSSIP_SENDER_MAIN, 3008);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Supreme Donor Range Ring - 5 DP", GOSSIP_SENDER_MAIN, 3011);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Supreme Donor Range Trinket - 5 DP", GOSSIP_SENDER_MAIN, 3012);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Supreme Donor Range Amulet - 5 DP", GOSSIP_SENDER_MAIN, 3013);
				//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Supreme Donor Bag - 5 DP", GOSSIP_SENDER_MAIN, 3009);
				//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Supreme Donor Caster Bag - 6 DP", GOSSIP_SENDER_MAIN, 3010);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90701, pCreature->GetGUID());
                return true;
                break;
            
            case 3003:
                RewardItem(player, pCreature, 200011,1,5);
                break;
            case 3004:
                RewardItem(player, pCreature, 200019,1,5);
                break;
            case 3005:
                RewardItem(player, pCreature, 200012,1,5);
                break;
			case 3006:
                RewardItem(player, pCreature, 200018,1,5);
                break;
			case 3007:
                RewardItem(player, pCreature, 200003,1,5);
                break;
			case 3008:
                RewardItem(player, pCreature, 200017,1,5);
                break;
            case 3009:
                RewardItem(player, pCreature, 210008,1,5);
                break;
			case 3010:
				RewardItem(player, pCreature, 100134,1,5);
				break;
			case 3011:
				RewardItem(player, pCreature, 200013,1,5);
				break;
			case 3012:
				RewardItem(player, pCreature, 200014,1,5);
				break;
			case 3013:
				RewardItem(player, pCreature, 200015,1,5);
				break;
			
			
		case 32000: //royal weapon
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "One-Handed Weapons", GOSSIP_SENDER_MAIN, 32001);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Two-Handed Weapons", GOSSIP_SENDER_MAIN, 32002);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Staves", GOSSIP_SENDER_MAIN, 32003);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Ranged & shields", GOSSIP_SENDER_MAIN, 32004);
                
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90701, pCreature->GetGUID());
                return true;
                break;
				
				case 32001:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Royal One Hand Sword - 21 Dp", GOSSIP_SENDER_MAIN, 52000);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Royal One Hand Axe - 21 Dp", GOSSIP_SENDER_MAIN, 52001);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Royal One Hand Mace - 21 Dp", GOSSIP_SENDER_MAIN, 52002);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Royal Dagger - 21 Dp", GOSSIP_SENDER_MAIN, 52003);
				
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90701, pCreature->GetGUID());
                break;
				
				case 52000:
                RewardItem(player, pCreature, 34821,1,21);
                break;
				case 52001:
                RewardItem(player, pCreature, 30699,1,21);
                break;
				case 52002:
                RewardItem(player, pCreature, 42759,1,21);
                break;
				case 52003:
                RewardItem(player, pCreature, 34045,1,21);
                break;
				
				case 32002:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Royal Two Hand Sword - 32 Dp", GOSSIP_SENDER_MAIN, 52004);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Royal Two Hand Axe - 32 Dp", GOSSIP_SENDER_MAIN, 52005);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Royal Two Hand Mace - 32 Dp", GOSSIP_SENDER_MAIN, 52006);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Royal Two Hand Polearm - 32 Dp", GOSSIP_SENDER_MAIN, 52007);
								
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90701, pCreature->GetGUID());
                break;
				
				case 52004:
                RewardItem(player, pCreature, 40480,1,32);
                break;
				case 52005:
                RewardItem(player, pCreature, 19199,1,32);
                break;
				case 52006:
                RewardItem(player, pCreature, 35674,1,32);
                break;
				case 52007:
                RewardItem(player, pCreature, 45884,1,32);
                break;
				
				case 32003:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Royal One Hand Armageddon Staff - 21 Dp", GOSSIP_SENDER_MAIN, 52008);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Royal Two Hand Armageddon Staff - 32 Dp", GOSSIP_SENDER_MAIN, 52009);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90701, pCreature->GetGUID());
                break;
				
				break;
				case 52008:
                RewardItem(player, pCreature, 29432,1,21);
                break;
				case 52009:
                RewardItem(player, pCreature, 29687,1,32);
                break;
				
				case 32004:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Royal Bow - 17 Dp", GOSSIP_SENDER_MAIN, 52010);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Royal Wand - 17 Dp", GOSSIP_SENDER_MAIN, 52011);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Royal Steel Shield - 30 Dp", GOSSIP_SENDER_MAIN, 52015);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90701, pCreature->GetGUID());
                break;
				
				break;
				case 52010:
                RewardItem(player, pCreature, 47122,1,17);
                break;
				case 52011:
                RewardItem(player, pCreature, 34144,1,17);
                break;
				case 52015:
                RewardItem(player, pCreature, 100150,1,30);
                break;
				
            case 5000:
                player->PlayerTalkClass->ClearMenus();
                //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Characters item Transfer Token - 6 DP", GOSSIP_SENDER_MAIN, 5001);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Custom Mount Token - 3 DP", GOSSIP_SENDER_MAIN, 5002);
                //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Instance Booster - 3 DP", GOSSIP_SENDER_MAIN, 5003);
                //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Donors Sigil - 6 DP", GOSSIP_SENDER_MAIN, 5004);
                //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Donors Libram - 6 DP", GOSSIP_SENDER_MAIN, 5005);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90701, pCreature->GetGUID());
                return true;
                break;
            case 5001:
                RewardItem(player, pCreature, 340007,1,6);
                break;
			case 5002:
				RewardItem(player, pCreature, 340009,1,3);
                break;
			case 5003:
				RewardItem(player, pCreature, 985468,1,3);
                break;
			case 5004:
					if(player->getClass() != 6) {
			  char str[200];
			  sprintf(str,"Your not a Death Knight, so you cant buy this item!");
					player->MonsterWhisper(str,player->GetGUID(),true);
					player->PlayerTalkClass->SendCloseGossip();
					} else {
					RewardItem(player, pCreature, 100104,1,6);
			  } 
					break;
				case 5005:
					if(player->getClass() != CLASS_PALADIN) {
			  char str[200];
			  sprintf(str,"Your not a Paladin, so you cant buy this item!");
					player->MonsterWhisper(str,player->GetGUID(),true);
					player->PlayerTalkClass->SendCloseGossip();
					} else {
					RewardItem(player, pCreature, 100106,1,6);
			  } 
					break;
				case 5006:
					RewardItem(player, pCreature, 4633,1,2);
					break;
			 case 10000: // tabard
			  switch(player->getClass())
			  {
			  case CLASS_WARRIOR:
					RewardItem(player, pCreature, 100093,1,7);
			  break;
			  case CLASS_PALADIN:
					RewardItem(player, pCreature, 100098,1,7);
				  break;
			  case CLASS_HUNTER:
					RewardItem(player, pCreature, 100100,1,7);
				 break;
			  case CLASS_ROGUE:
					RewardItem(player, pCreature, 100096,1,7);
				 break;
			  case CLASS_PRIEST:
					RewardItem(player, pCreature, 100097,1,7);
			  break;
			  case CLASS_DEATH_KNIGHT:
					RewardItem(player, pCreature, 100102,1,7);
					 break;
			  case CLASS_SHAMAN:
					RewardItem(player, pCreature, 100095,1,7);
				  break;
			  case CLASS_MAGE:
					RewardItem(player, pCreature, 100099,1,7);
			  break;
			  case CLASS_WARLOCK:
					RewardItem(player, pCreature, 100094,1,7);
				  break;
			  case CLASS_DRUID:
					RewardItem(player, pCreature, 100101,1,7);
					break;

			  default: break;
			  }
			  break;
			 case 11000: // donors cloak
			  switch(player->getClass())
			  {
			  case CLASS_WARRIOR:
					RewardItem(player, pCreature, 100112,1,10);
			  break;
			  case CLASS_PALADIN:
					RewardItem(player, pCreature, 100117,1,10);
				  break;
			  case CLASS_HUNTER:
					RewardItem(player, pCreature, 100119,1,10);
				 break;
			  case CLASS_ROGUE:
					RewardItem(player, pCreature, 100115,1,10);
				 break;
			  case CLASS_PRIEST:
					RewardItem(player, pCreature, 100116,1,10);
			  break;
			  case CLASS_DEATH_KNIGHT:
					RewardItem(player, pCreature, 100121,1,10);
					 break;
			  case CLASS_SHAMAN:
					RewardItem(player, pCreature, 100114,1,10);
				  break;
			  case CLASS_MAGE:
					RewardItem(player, pCreature, 100118,1,10);
			  break;
			  case CLASS_WARLOCK:
					RewardItem(player, pCreature, 100113,1,10);
				  break;
			  case CLASS_DRUID:
					RewardItem(player, pCreature, 100120,1,10);
					break;

			  default: break;
			  }
			  break;
			  
			case 12000: // donors set
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Druid Melee Set", GOSSIP_SENDER_MAIN, 12001);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Druid Caster Set", GOSSIP_SENDER_MAIN, 12002);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Shaman Melee Set", GOSSIP_SENDER_MAIN, 12003);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Shaman Caster Set", GOSSIP_SENDER_MAIN, 12004);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Shaman Paladin Set", GOSSIP_SENDER_MAIN, 12005);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Shaman Warrior Set", GOSSIP_SENDER_MAIN, 12006);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Shaman Death Knight Set", GOSSIP_SENDER_MAIN, 12007);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Shaman Hunter Set", GOSSIP_SENDER_MAIN, 12008);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Shaman Rogue Set", GOSSIP_SENDER_MAIN, 12009);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Shaman Priest Set", GOSSIP_SENDER_MAIN, 12010);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Shaman Mage Set", GOSSIP_SENDER_MAIN, 12011);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Shaman Warlock Set", GOSSIP_SENDER_MAIN, 12012);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90702, pCreature->GetGUID());
                return true;
                break;
				
				case 12001:
							RewardItem(player, pCreature, 320276,1,23);
						   break;
				case 12002:
							RewardItem(player, pCreature, 320293,1,23);
						   break;
				case 12003:
							RewardItem(player, pCreature, 320275,1,23);
							break;
				case 12004:
							RewardItem(player, pCreature, 320294,1,23);
							break;
										  
					  case 12006:
							RewardItem(player, pCreature, 320268,1,23);
							break;
					  case 12005:
							RewardItem(player, pCreature, 320267,1,23);
							break;
					  case 12008:
							RewardItem(player, pCreature, 320271,1,23);
							break;
					  case 12009:
							RewardItem(player, pCreature, 320270,1,23);
							break;
					  case 12010:
							RewardItem(player, pCreature, 320273,1,23);
							break;
					  case 12007:
							RewardItem(player, pCreature, 320269,1,23);
							break;
					  case 12011:
							RewardItem(player, pCreature, 320272,1,23);
						  break;
					  case 12012:
							RewardItem(player, pCreature, 320274,1,23);
						  break;
			  
			case 14000: // cross weapon skill
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Ultimate One Hand Sword Weapon Skill - 10 DP", GOSSIP_SENDER_MAIN, 14001);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Ultimate Two Hand Sword Weapon Skill - 14 DP", GOSSIP_SENDER_MAIN, 14909);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Ultimate One Hand Axe Weapon Skill - 10 DP", GOSSIP_SENDER_MAIN, 14003);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Ultimate Two Hand Axe Weapon Skill - 14 DP", GOSSIP_SENDER_MAIN, 14004);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Ultimate One Hand Mace Weapon Skill - 10 DP", GOSSIP_SENDER_MAIN, 14005);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Ultimate Two Hand Mace Weapon Skill - 14 DP", GOSSIP_SENDER_MAIN, 14006);
				//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Ultimate Staff Weapon Skill - 30 DP ", GOSSIP_SENDER_MAIN, 14007);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Ultimate Polearm Hand Sword Weapon Skill - 14 DP", GOSSIP_SENDER_MAIN, 14008);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Ultimate Dagger Weapon Skill - 10 DP", GOSSIP_SENDER_MAIN, 14009);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Ultimate Bow Weapon Skill - 10 DP", GOSSIP_SENDER_MAIN, 14020);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Ultimate Shield Skill - 10 DP", GOSSIP_SENDER_MAIN, 14011);
				//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Ultimate Wand Weapon Skill - 15 DP", GOSSIP_SENDER_MAIN, 14012);
			
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90702, pCreature->GetGUID());
                return true;
                break;
			
				case 14001:
				RewardItem(player, pCreature, 340014,1,10);
				break;
				case 14909:
				RewardItem(player, pCreature, 340015,1,14);
				break;
				case 14003:
				RewardItem(player, pCreature, 340016,1,10);
				break;
				case 14004:
				RewardItem(player, pCreature, 340017,1,14);
				break;
				case 14005:
				RewardItem(player, pCreature, 340018,1,10);
				break;
				case 14006:
				RewardItem(player, pCreature, 340019,1,14);
				break;
				case 14007:
				RewardItem(player, pCreature, 340020,1,14);
				break;
				case 14008:
				RewardItem(player, pCreature, 340021,1,14);
				break;
				case 14009:
				RewardItem(player, pCreature, 340022,1,10);
				break;
				case 14020:
				RewardItem(player, pCreature, 340023,1,10);
				break;
				case 14011: //shield
				RewardItem(player, pCreature, 340024,1,10);
				break;				
				
			case 9996:
                if(player->HasItemCount(56808, 1))
                {
                char str[200];
                sprintf(str,"You already have a Immune Ring, so you cant buy it!");
                player->MonsterWhisper(str,player->GetGUID(),true);
                player->PlayerTalkClass->SendCloseGossip();
                } else {
                RewardItem(player, pCreature, 56808,1,30);
                player->PlayerTalkClass->SendCloseGossip();
                }
                break;
			case 99960:
                if(player->HasItemCount(56809, 1))
                {
                char str[200];
                sprintf(str,"You already have a Immune Trinket, so you cant buy it!");
                player->MonsterWhisper(str,player->GetGUID(),true);
                player->PlayerTalkClass->SendCloseGossip();
                } else {
                RewardItem(player, pCreature, 56809,1,30);
                player->PlayerTalkClass->SendCloseGossip();
                }
                break;
            case 9998:
                player->GetSession()->SendListInventory(pCreature->GetGUID());
                break;
            case 9999:
                player->PlayerTalkClass->ClearMenus();
                OnGossipHello(player, pCreature);
                break;
            }


            return true;
        }

};

void AddSC_donorrewarder()
{
    new donorrewarder();
}
