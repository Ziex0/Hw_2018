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
    public:

        donorrewarder()
            : CreatureScript("donorrewarder")
        {
        }

        void AddItem(Player* player, Creature* pCreature, int item , int count, int cost)
        {
            QueryResult result;
            result = CharacterDatabase.PQuery("SELECT dp FROM Web_db.account_data WHERE id = '%u' AND dp >= '0'", player->GetSession()->GetAccountId());
            char str[200];
            if (!result) // check
            {
                sprintf(str,"Your have abused our systems and gotten a negative balance on your Donation Points. Your points are set to 0.");
				LoginDatabase.PQuery("UPDATE Web_db.account_data set dp = 0 WHERE id = '%u'", player->GetSession()->GetAccountId());
                player->PlayerTalkClass->ClearMenus();
                OnGossipHello(player, pCreature);
                pCreature->MonsterSay(str, LANG_UNIVERSAL, player->GetGUID());
                return;
            }

            Field *fields = result->Fetch();
            uint32 points = fields[0].GetUInt32();
 
            if (item == 0)
            {
                sprintf(str,"You got %u Donation points!", points);
                player->MonsterWhisper(str,player->GetGUID(),true);
            }
            else
            {
                if (points <cost)
                {
                     sprintf(str,"You broke now,you must Donate on www.TheSatria.com!");
                     player->MonsterWhisper(str,player->GetGUID(),true);
                }
                else
                {
                    if (player->AddItem(item, count))
                    {
  			   std::string DateTime = "%Y-%m-%d %H:%M:%S";
			   ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(item);
               CharacterDatabase.PQuery("Update Web_db.account_data Set dp = dp - '%u' WHERE id = '%u'", cost, player->GetSession()->GetAccountId());
               //LoginDatabase.PQuery("INSERT INTO Web_db.donation_purchases (account_id, character_name, character_guid, donation_item_id, donation_item_name, donation_item_amount, date) VALUES ('%u', '%s', '%u', '%u', '%s', '%u', DATE_FORMAT(date, '%s'))", player->GetSession()->GetAccountId(), player->GetName(), player->GetGUIDLow(), item, itemTemplate->Name1.c_str(), count, DateTime.c_str());
               sprintf(str,"Your points are taken Thank you for your Support!!");
               player->MonsterWhisper(str,player->GetGUID(),true);
			   player->SaveToDB();
                    }
                    else
                    {
                        sprintf(str,"Item can't be given maybe or maybe and maybe your bag is full or you already got the item!");
                        player->MonsterWhisper(str,player->GetGUID(),true);
                    }

                }
            }
            player->PlayerTalkClass->ClearMenus();
            OnGossipHello(player, pCreature);
        }
		
    bool OnGossipHello(Player* player, Creature* pCreature)
        {
            //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Get a preview of the donor items", GOSSIP_SENDER_MAIN, 9998);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface/ICONS/Spell_Frost_ChillingBlast:35:35|tHow much Donation points do i have?", GOSSIP_SENDER_MAIN, 19000);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|cffFF0000|TInterface\\icons\\Achievement_Leader_Sylvanas:30|tDonor Weapons", GOSSIP_SENDER_MAIN, 2000);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|cffFF0000|TInterface\\icons\\Achievement_Leader_Sylvanas:30|tDonor Rings/Trinkets/Amulets and Bags", GOSSIP_SENDER_MAIN, 3000);
            //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|cffFF0000|TInterface\\icons\\Achievement_Leader_Sylvanas:30|tDonorArmors and Shirts", GOSSIP_SENDER_MAIN, 300);
			//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|cffFF0000|TInterface\\icons\\Achievement_Leader_Sylvanas:30|tDonorTitan_Grip (Paladin cant use ) - 10 DP (can't use for 2H Staff)", GOSSIP_SENDER_MAIN, 20000);
            //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|cffFF0000|TInterface\\icons\\Achievement_Leader_Sylvanas:30|tSpecial Items", GOSSIP_SENDER_MAIN, 5000);
            //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|cffFF0000|TInterface\\icons\\Achievement_Leader_Sylvanas:30|tSpecial Tokens", GOSSIP_SENDER_MAIN, 4000);
            //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|cffFF0000|TInterface\\icons\\Achievement_Leader_Sylvanas:30|tDonor Tabard - 7 Dp", GOSSIP_SENDER_MAIN, 10000);
            //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|cffFF0000|TInterface\\icons\\Achievement_Leader_Sylvanas:30|tDonor Cloak - 10 DP", GOSSIP_SENDER_MAIN, 11000);
            //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|cffFF0000|TInterface\\icons\\Achievement_Leader_Sylvanas:30|tDonor Set - 46 DP ( 8 Pieces )", GOSSIP_SENDER_MAIN, 12000);
			//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|cffFF0000|TInterface\\icons\\Achievement_Leader_Sylvanas:30|tRoyal Donor Set, 8 Coin - 62 DP", GOSSIP_SENDER_MAIN, 13000);
			//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|cffFF0000|TInterface\\icons\\Achievement_Leader_Sylvanas:30|tUltimate Misc Item", GOSSIP_SENDER_MAIN, 14000);
			//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|cffFF0000|TInterface\\icons\\Achievement_Leader_Sylvanas:30|tDonor Royal Weapons", GOSSIP_SENDER_MAIN, 32000);
			//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|cffFF0000|TInterface\\icons\\Achievement_Leader_Sylvanas:30|tCosmetic 50% Immune Stun Ring - 30 DP", GOSSIP_SENDER_MAIN, 9997);
			//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Cosmetic 50% Immune Stun Trinket - 30 DP", GOSSIP_SENDER_MAIN, 21070);
			//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Full Berserk Spell - 50 DP", GOSSIP_SENDER_MAIN, 22070);
            //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Invincible Offset - 35 DP", GOSSIP_SENDER_MAIN, 305);
            //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Emblem of Voting x2 - 1 DP", GOSSIP_SENDER_MAIN, 4005);
            //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Heaven Gems 5 DP - 3 Gems", GOSSIP_SENDER_MAIN, 5100);
            //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Portable Mailbox - 10 DP", GOSSIP_SENDER_MAIN, 5200);
            player->PlayerTalkClass->SendGossipMenu(90000, pCreature->GetGUID());

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
            case 300:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Donors Shirt - 6 DP", GOSSIP_SENDER_MAIN, 301);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Donors Tabard - 20 DP", GOSSIP_SENDER_MAIN, 302);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Donors Shirt - 6 DP", GOSSIP_SENDER_MAIN, 1303);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Donor Steel Shield - 7 DP", GOSSIP_SENDER_MAIN, 304);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Donor Ultimate Speed Shirt ->>", GOSSIP_SENDER_MAIN, 310);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90000, pCreature->GetGUID());
                return true;
                break;
            case 1303:
                if(player->getClass() != CLASS_HUNTER) {
				  char str[200];
				  sprintf(str,"Your not a Hunter, so you cant buy this item!");
						player->MonsterWhisper(str,player->GetGUID(),true);
						player->PlayerTalkClass->SendCloseGossip();
						} else {
						RewardItem(player, pCreature,7278,1,10);
						player->PlayerTalkClass->SendCloseGossip();
				  }
						break;
			case 12:
				RewardItem(player, pCreature,24368,1,20);
				break;
            case 301:
                AddItem(player, pCreature,100105,1,6);
                break;
            case 302:
                AddItem(player, pCreature,20131,1,20);
                break;
            case 303:
                AddItem(player, pCreature,20400,1,5);
                break;
            case 304:
                AddItem(player, pCreature,100130,1,7);
                break;
			case 310:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Ultimate Shirt I - 5 Dp", GOSSIP_SENDER_MAIN, 311);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Ultimate Shirt II - 7 Dp", GOSSIP_SENDER_MAIN, 312);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Ultimate Shirt III - 13 Dp", GOSSIP_SENDER_MAIN, 313);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Ultimate Shirt IV - 20 Dp", GOSSIP_SENDER_MAIN, 314);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Ultimate Shirt V - 30 Dp", GOSSIP_SENDER_MAIN, 315);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90000, pCreature->GetGUID());
                return true;
                break;
			case 311:
                AddItem(player, pCreature,100125,1,5);
                break;
			case 312:
                AddItem(player, pCreature,100126,1,7);
                break;
			case 313:
                AddItem(player, pCreature,100127,1,13);
                break;
			case 314:
                AddItem(player, pCreature,100128,1,20);
                break;
			case 315:
                AddItem(player, pCreature,100129,1,30);
                break;
				
			case 305: // invincible off set
			  switch(player->getClass())
			  {
			case CLASS_WARRIOR:
					RewardItem(player, pCreature, 66073,1,35);
			  break;
			case CLASS_PALADIN:
					RewardItem(player, pCreature, 66077,1,35);
				  break;
			case CLASS_HUNTER:
					RewardItem(player, pCreature, 66071,1,35);
				 break;
			case CLASS_ROGUE:
					RewardItem(player, pCreature, 66072,1,35);
				 break;
			case CLASS_PRIEST:
					RewardItem(player, pCreature, 66074,1,35);
			  break;
			case CLASS_DEATH_KNIGHT:
					RewardItem(player, pCreature, 66070,1,35);
					 break;
			case CLASS_SHAMAN:
					RewardItem(player, pCreature, 66078,1,35);
				  break;
			case CLASS_MAGE:
					RewardItem(player, pCreature, 66079,1,35);
			  break;
			case CLASS_WARLOCK:
					RewardItem(player, pCreature, 66076,1,35);
				  break;
			case CLASS_DRUID:
					RewardItem(player, pCreature, 66075,1,35);
					break;

			  default: break;
			  }
			  break;
            case 1000:
                AddItem(player, pCreature, 0, 0, 0);
                break;
            case 2000:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "One-Handed Weapons", GOSSIP_SENDER_MAIN, 2001);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Two-Handed Weapons", GOSSIP_SENDER_MAIN, 2002);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Staves", GOSSIP_SENDER_MAIN, 2003);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Ranged", GOSSIP_SENDER_MAIN, 2004);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Off-Hand Weapons", GOSSIP_SENDER_MAIN, 2005);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(9000, pCreature->GetGUID());
                return true;
                break;
            case 2001:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Final Achievement One Hand Sword of Donation - 9 DP", GOSSIP_SENDER_MAIN, 2101);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Final Achievement One Hand Axe of Donation - 9 DP", GOSSIP_SENDER_MAIN, 2102);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Final Achievement One Hand Mace of Donation- 9 DP", GOSSIP_SENDER_MAIN, 2103);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Final Achievement Melee Dagger of Donation - 9 DP", GOSSIP_SENDER_MAIN, 2104);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Final Achievement Spell Dagger of Donation - 9 DP", GOSSIP_SENDER_MAIN, 2105);				
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90000, pCreature->GetGUID());
                return true;
                break;
            case 2101:
                AddItem(player, pCreature,200169,1,9);
                break;
			case 2102:
                AddItem(player, pCreature,200170,1,9);
                break;
			case 2103:
                AddItem(player, pCreature,200171,1,9);
                break;
			case 2104:
                AddItem(player, pCreature,200180,1,9);
                break;
			case 2105:
                AddItem(player, pCreature,200228,1,9);
                break;
			
				
            case 2002:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Final Achievement Two Hand Sword of Donation - 15 DP", GOSSIP_SENDER_MAIN, 2201);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Final Achievement Two Hand Axe of Donation- 15 DP", GOSSIP_SENDER_MAIN, 2202);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Final Achievement Two Hand Mace of Donation - 15 DP", GOSSIP_SENDER_MAIN, 2203);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Final Achievement Polearm of Donation - 15 DP", GOSSIP_SENDER_MAIN, 2204);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90000, pCreature->GetGUID());
                return true;
                break;
            case 2201:
                AddItem(player, pCreature,200176,1,15);
                break;
            case 2202:
                AddItem(player, pCreature,200178,1,15);
                break;
            case 2203:
                AddItem(player, pCreature,200177,1,15);
				break;
			case 2204:
                AddItem(player, pCreature,200230,1,15);
				break;
            
                break;
            case 2003:
                player->PlayerTalkClass->ClearMenus();                
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Final Achievement Spell Staff of Donation- 15 DP", GOSSIP_SENDER_MAIN, 2301);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Final Achievement Feral Staff of Donation- 15 DP", GOSSIP_SENDER_MAIN, 2303);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90000, pCreature->GetGUID());
                return true;
                break;
            case 2301:
                if(player->getClass() == CLASS_PALADIN || player->getClass() == CLASS_ROGUE || player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_DEATH_KNIGHT || player->getClass() == CLASS_HUNTER) {
				  char str[200];
				  sprintf(str,"Your not a Caster, so you cant buy this item!");
                player->MonsterWhisper(str,player->GetGUID(),true);
                player->PlayerTalkClass->SendCloseGossip();
                } else {
                AddItem(player, pCreature,200179,1,15);
                player->PlayerTalkClass->SendCloseGossip();
						}
                break;
			
            case 2302:
                if(player->getClass() != CLASS_DRUID) {
				  char str[200];
				  sprintf(str,"Your not a Druid, so you cant buy this item!");
                player->MonsterWhisper(str,player->GetGUID(),true);
                player->PlayerTalkClass->SendCloseGossip();
                } else {
                AddItem(player, pCreature,200229,1,15);
                player->PlayerTalkClass->SendCloseGossip();
						}
                
            case 2004:
                player->PlayerTalkClass->ClearMenus();                
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Final Achievement Bow of Donation - 9 DP", GOSSIP_SENDER_MAIN, 2401);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Final Achievement Gun of Donation- 9 DP", GOSSIP_SENDER_MAIN, 2402);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Reaper Wand of Donators - 7 DP", GOSSIP_SENDER_MAIN, 2403);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90000, pCreature->GetGUID());
                return true;
                break;
            case 2401:
                AddItem(player, pCreature,34334,1,9);
                break;
            case 2402:
                AddItem(player, pCreature,200173,1,9);
                break;
            case 2403:
                if(player->getClass() == CLASS_PALADIN || player->getClass() == CLASS_ROGUE || player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_DEATH_KNIGHT || player->getClass() == CLASS_HUNTER) {
				char str[200];
				sprintf(str,"Your not a Caster, so you cant buy this item!");
                player->MonsterWhisper(str,player->GetGUID(),true);
                player->PlayerTalkClass->SendCloseGossip();
                } else {
                AddItem(player, pCreature,200181,1,7);
                player->PlayerTalkClass->SendCloseGossip();
		  }
                break;
            case 2005:
                player->PlayerTalkClass->ClearMenus();                
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Final Achievement Tank Shield of Donation - 7 DP", GOSSIP_SENDER_MAIN, 2501);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Final Achievement Spell Shield of Donation - 7 DP", GOSSIP_SENDER_MAIN, 2502);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90000, pCreature->GetGUID());
                return true;
                break;
            case 2501:
                AddItem(player, pCreature, 200167,1,7);
                break;
            case 2502:
                AddItem(player, pCreature, 200168,1,7);
                break;
				
            
            case 3000: // ring,amulet balal
                player->PlayerTalkClass->ClearMenus();                
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Fallen Dragon Donor Melee Ring - 6 DP", GOSSIP_SENDER_MAIN, 3003);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Fallen Dragon Donor Caster Ring - 6 DP", GOSSIP_SENDER_MAIN, 3004);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Fallen Dragon Donor Melee Trinket - 6 DP", GOSSIP_SENDER_MAIN, 3005);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Fallen Dragon Donor Caster Trinket - 6 DP", GOSSIP_SENDER_MAIN, 3006);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Fallen Dragon Donor Melee Amulet - 6 DP", GOSSIP_SENDER_MAIN, 3007);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Fallen Dragon Donor Caster Amulet - 6 DP", GOSSIP_SENDER_MAIN, 3008);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Fallen Dragon Donor Bag - 5 DP", GOSSIP_SENDER_MAIN, 3009);
				//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Fallen Dragon Donor Caster Bag - 6 DP", GOSSIP_SENDER_MAIN, 3010);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90000, pCreature->GetGUID());
                return true;
                break;
            
            case 3003:
                AddItem(player, pCreature, 200162,1,6);
                break;
            case 3004:
                AddItem(player, pCreature, 200216,1,6);
                break;
            case 3005:
                AddItem(player, pCreature, 200163,1,6);
                break;
			case 3006:
                AddItem(player, pCreature, 200217,1,6);
                break;
			case 3007:
                AddItem(player, pCreature, 200161,1,6);
                break;
			case 3008:
                AddItem(player, pCreature, 200215,1,6);
                break;
            case 3009:
                AddItem(player, pCreature, 210008,1,5);
                break;
			case 3010:
				AddItem(player, pCreature, 100134,1,6);
				break;
			
            case 4000:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Transmogrification Token - 1 DP", GOSSIP_SENDER_MAIN, 4001);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Re-Customize Token - 3 DP", GOSSIP_SENDER_MAIN, 14002);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Scroll of Dual Wield - 4 DP", GOSSIP_SENDER_MAIN, 4002);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Item Transfer/Exchange Token - 5 DP", GOSSIP_SENDER_MAIN, 4003);
                //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Scroll of Titan Grip's - 6 DP", GOSSIP_SENDER_MAIN, 4009);
				//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Cata / MoP Token - 5 DP", GOSSIP_SENDER_MAIN, 5040);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "VIP Rank - 55 DP", GOSSIP_SENDER_MAIN, 4004);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "VIP II Token - 75 DP", GOSSIP_SENDER_MAIN, 4006);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Upgrade to VIP II (This Work if you have VIP 1)- 311 DP", GOSSIP_SENDER_MAIN, 4007);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Signet of Berserking - 10 DP", GOSSIP_SENDER_MAIN, 14010);
                
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90000, pCreature->GetGUID());
                return true;
                break;
			case 4032:
				AddItem(player, pCreature, 985410,1,8);
				break;
			case 4031:
				AddItem(player, pCreature, 41596,1,7);
				break;
            case 5040:
                AddItem(player, pCreature, 11,1,5);
                break;
            case 4030:
                AddItem(player, pCreature, 9850100,2,1);
                break;
            case 4038:
                AddItem(player, pCreature, 29435,1,12);
                break;
            case 4029:
                AddItem(player, pCreature, 190,1,10);
                break;
            case 4028:
                AddItem(player, pCreature, 29436,1,10);
                break;
			case 14002:
				AddItem(player, pCreature, 98211,1,3);
				break;
			case 14010:
				AddItem(player, pCreature, 361805,1,10);
				break;
            case 4001:
                AddItem(player, pCreature, 361800,1,1);
                break;
            case 4002:
                AddItem(player, pCreature, 270002,1,4);
                break;
            case 4003:
                AddItem(player, pCreature, 361802,1,5);
                break;
            case 4004:
                AddItem(player, pCreature, 313370,1,55);
                break;
            case 4005:
                AddItem(player, pCreature, 40753,2,1);
                break;
            case 4006:
                AddItem(player, pCreature, 13,1,75);
                break;
            case 4007:
                AddItem(player, pCreature, 14,1,15);
                break;
            case 4008:
                AddItem(player, pCreature, 10,1,6);
                break;
            case 4010:
                AddItem(player, pCreature, 11,1,10);
                break;
				
		case 32000: //royal weapon
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "One-Handed Weapons", GOSSIP_SENDER_MAIN, 32001);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Two-Handed Weapons", GOSSIP_SENDER_MAIN, 32002);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Staves", GOSSIP_SENDER_MAIN, 32003);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Ranged & shields", GOSSIP_SENDER_MAIN, 32004);
                
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90000, pCreature->GetGUID());
                return true;
                break;
				
				case 32001:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Royal One Hand Sword - 21 Dp", GOSSIP_SENDER_MAIN, 52000);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Royal One Hand Axe - 21 Dp", GOSSIP_SENDER_MAIN, 52001);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Royal One Hand Mace - 21 Dp", GOSSIP_SENDER_MAIN, 52002);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Royal Dagger - 21 Dp", GOSSIP_SENDER_MAIN, 52003);
				
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90000, pCreature->GetGUID());
                break;
				
				case 52000:
                AddItem(player, pCreature, 34821,1,21);
                break;
				case 52001:
                AddItem(player, pCreature, 30699,1,21);
                break;
				case 52002:
                AddItem(player, pCreature, 42759,1,21);
                break;
				case 52003:
                AddItem(player, pCreature, 34045,1,21);
                break;
				
				case 32002:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Royal Two Hand Sword - 32 Dp", GOSSIP_SENDER_MAIN, 52004);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Royal Two Hand Axe - 32 Dp", GOSSIP_SENDER_MAIN, 52005);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Royal Two Hand Mace - 32 Dp", GOSSIP_SENDER_MAIN, 52006);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Royal Two Hand Polearm - 32 Dp", GOSSIP_SENDER_MAIN, 52007);
								
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90000, pCreature->GetGUID());
                break;
				
				case 52004:
                AddItem(player, pCreature, 40480,1,32);
                break;
				case 52005:
                AddItem(player, pCreature, 19199,1,32);
                break;
				case 52006:
                AddItem(player, pCreature, 35674,1,32);
                break;
				case 52007:
                AddItem(player, pCreature, 45884,1,32);
                break;
				
				case 32003:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Royal One Hand Armageddon Staff - 21 Dp", GOSSIP_SENDER_MAIN, 52008);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Royal Two Hand Armageddon Staff - 32 Dp", GOSSIP_SENDER_MAIN, 52009);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90000, pCreature->GetGUID());
                break;
				
				break;
				case 52008:
                AddItem(player, pCreature, 29432,1,21);
                break;
				case 52009:
                AddItem(player, pCreature, 29687,1,32);
                break;
				
				case 32004:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Royal Bow - 17 Dp", GOSSIP_SENDER_MAIN, 52010);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Royal Wand - 17 Dp", GOSSIP_SENDER_MAIN, 52011);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Royal Steel Shield - 30 Dp", GOSSIP_SENDER_MAIN, 52015);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90000, pCreature->GetGUID());
                break;
				
				break;
				case 52010:
                AddItem(player, pCreature, 47122,1,17);
                break;
				case 52011:
                AddItem(player, pCreature, 34144,1,17);
                break;
				case 52015:
                AddItem(player, pCreature, 100150,1,30);
                break;
				
            case 5000:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Donors Idol - 6 DP", GOSSIP_SENDER_MAIN, 5001);
                //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Donors Thrown - 15 DP", GOSSIP_SENDER_MAIN, 5002);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Donors Totem - 6 DP", GOSSIP_SENDER_MAIN, 5003);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Donors Sigil - 6 DP", GOSSIP_SENDER_MAIN, 5004);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Donors Libram - 6 DP", GOSSIP_SENDER_MAIN, 5005);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90000, pCreature->GetGUID());
                return true;
                break;
            case 5001:
                if(player->getClass() != CLASS_DRUID) {
			  char str[200];
			  sprintf(str,"Your not a Druid, so you cant buy this item!");
					player->MonsterWhisper(str,player->GetGUID(),true);
					player->PlayerTalkClass->SendCloseGossip();
					} else {
					RewardItem(player, pCreature, 100107,1,6);
			  } 
					break;
				case 5002:
					if(player->getClass() != CLASS_ROGUE) {
			  char str[200];
			  sprintf(str,"Your not a Rogue, so you cant buy this item!");
					player->MonsterWhisper(str,player->GetGUID(),true);
					player->PlayerTalkClass->SendCloseGossip();
					} else {
					RewardItem(player, pCreature, 30025,1,6);
			  } 
					break;
				case 5003:
					if(player->getClass() != CLASS_SHAMAN) {
			  char str[200];
			  sprintf(str,"Your not a Shaman, so you cant buy this item!");
					player->MonsterWhisper(str,player->GetGUID(),true);
					player->PlayerTalkClass->SendCloseGossip();
					} else {
					RewardItem(player, pCreature, 100103,1,6);
			  } 
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
			  switch(player->getClass())
			  {
			  case CLASS_WARRIOR:
					RewardItem(player, pCreature, 68,1,46);
			  break;
			  case CLASS_PALADIN:
					RewardItem(player, pCreature, 69,1,46);
				  break;
			  case CLASS_HUNTER:
					RewardItem(player, pCreature, 70,1,46);
				 break;
			  case CLASS_ROGUE:
					RewardItem(player, pCreature, 71,1,46);
				 break;
			  case CLASS_PRIEST:
					RewardItem(player, pCreature, 72,1,46);
				  break;
			  case CLASS_DEATH_KNIGHT:
					RewardItem(player, pCreature, 73,1,46);
					 break;
			  case CLASS_SHAMAN:
					RewardItem(player, pCreature, 74,1,46);
				  break;
			  case CLASS_MAGE:
					RewardItem(player, pCreature, 75,1,46);
			  break;
			  case CLASS_WARLOCK:
					RewardItem(player, pCreature, 76,1,46);
				  break;
			  case CLASS_DRUID:
					RewardItem(player, pCreature, 78,1,46);
					break;

			  default: break;
			  }
			  break;
			  
			  case 13000: // donors set
			  switch(player->getClass())
			  {
			  case CLASS_WARRIOR:
					RewardItem(player, pCreature, 7,8,62);
			  break;
			  case CLASS_PALADIN:
					RewardItem(player, pCreature, 7,8,62);
				  break;
			  case CLASS_HUNTER:
					RewardItem(player, pCreature, 7,8,62);
				 break;
			  case CLASS_ROGUE:
					RewardItem(player, pCreature, 7,8,62);
				 break;
			  case CLASS_PRIEST:
					RewardItem(player, pCreature, 7,8,62);
				  break;
			  case CLASS_DEATH_KNIGHT:
					RewardItem(player, pCreature, 7,8,62);
					 break;
			  case CLASS_SHAMAN:
					RewardItem(player, pCreature, 7,8,62);
				  break;
			  case CLASS_MAGE:
					RewardItem(player, pCreature, 7,8,62);
			  break;
			  case CLASS_WARLOCK:
					RewardItem(player, pCreature, 7,8,62);
				  break;
			  case CLASS_DRUID:
					RewardItem(player, pCreature, 7,8,62);
					break;

			  default: break;
			  }
			  break;
		  
			case 14000:
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Supreme Donor Melee Ring - 9 DP", GOSSIP_SENDER_MAIN, 14001);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Supreme Caster Ring - 9 DP", GOSSIP_SENDER_MAIN, 14909);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Supreme Melee Trinket - 9 DP", GOSSIP_SENDER_MAIN, 14003);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Supreme Caster Trinket - 9 DP", GOSSIP_SENDER_MAIN, 14004);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Supreme Melee Celestial Amulet - 9 DP", GOSSIP_SENDER_MAIN, 14005);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Supreme Caster Celestial Amulet - 9 DP", GOSSIP_SENDER_MAIN, 14006);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Supreme Melee Bag - 9 DP", GOSSIP_SENDER_MAIN, 14007);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Supreme Caster Bag - 9 DP", GOSSIP_SENDER_MAIN, 14008);
			
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90000, pCreature->GetGUID());
                return true;
                break;
			case 9997:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Are you sure you wish to buy Immune Ring misc' Item?", GOSSIP_SENDER_MAIN, 9997);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Yes.", GOSSIP_SENDER_MAIN, 9996);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "No.", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90000, pCreature->GetGUID());
                return true;
			case 21070:
				player->PlayerTalkClass->ClearMenus();
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Are you sure you wish to buy Immune Trinket misc' Item?", GOSSIP_SENDER_MAIN, 21070);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Yes.", GOSSIP_SENDER_MAIN, 99960);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "No.", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90000, pCreature->GetGUID());
                return true;
                break;
				case 14001:
				AddItem(player, pCreature, 130110,1,11);
				break;
				case 14909:
				AddItem(player, pCreature, 130131,1,11);
				break;
				case 14003:
				AddItem(player, pCreature, 130109,1,11);
				break;
				case 14004:
				AddItem(player, pCreature, 130132,1,11);
				break;
				case 14005:
				AddItem(player, pCreature, 130111,1,11);
				break;
				case 14006:
				AddItem(player, pCreature, 130133,1,11);
				break;
				case 14007:
				AddItem(player, pCreature, 130108,1,11);
				break;
				case 14008:
				AddItem(player, pCreature, 130134,1,11);
				break;
				case 20000:
				AddItem(player, pCreature, 10,1,10);
				break;
				
				case 22070:
				AddItem(player, pCreature, 22,1,50);
				break;
				
			case 9996:
                if(player->HasItemCount(56808, 1))
                {
                char str[200];
                sprintf(str,"You already have a Immune Ring, so you cant buy it!");
                player->MonsterWhisper(str,player->GetGUID(),true);
                player->PlayerTalkClass->SendCloseGossip();
                } else {
                AddItem(player, pCreature, 56808,1,30);
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
                AddItem(player, pCreature, 56809,1,30);
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
