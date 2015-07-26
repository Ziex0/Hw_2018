/*
CREATE TABLE `vote_purchases` (
	`account_id` INT(10) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'Account Identifier',
	`character_name` VARCHAR(12) NOT NULL DEFAULT '' COLLATE 'utf8_general_ci',
	`character_guid` INT(10) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'Global Unique Identifier',
	`vote_item_id` INT(10) UNSIGNED NOT NULL DEFAULT '0',
	`vote_item_name` VARCHAR(60) NOT NULL DEFAULT '' COLLATE 'utf8_general_ci',
	`vote_item_amount` INT(10) UNSIGNED NOT NULL DEFAULT '1',
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

class Vote_rewarder : public CreatureScript
{
    public:

        Vote_rewarder()
            : CreatureScript("Vote_rewarder")
        {
        }

        void AddItem(Player* player, Creature* pCreature, int item , int count, int cost)
        {
            QueryResult result;
            result = CharacterDatabase.PQuery("SELECT vp FROM Web_db.account_data WHERE id = '%u' AND vp >= '0'", player->GetSession()->GetAccountId());
            char str[200];
            if (!result) // check
            {
                sprintf(str,"Your have abused our systems and gotten a negative balance on your Vote Points. Your points are set to 0.");
				LoginDatabase.PQuery("UPDATE Web_db.account_data set vp = 0 WHERE id = '%u'", player->GetSession()->GetAccountId());
                player->PlayerTalkClass->ClearMenus();
                OnGossipHello(player, pCreature);
                pCreature->MonsterSay(str, LANG_UNIVERSAL, player->GetGUID());
                return;
            }

            Field *fields = result->Fetch();
            uint32 points = fields[0].GetUInt32();
 
            if (item == 0)
            {
                sprintf(str,"You got %u Vote points!", points);
                player->MonsterWhisper(str,player->GetGUID(),true);
            }
            else
            {
                if (points <cost)
                {
                     sprintf(str,"You dont have Vote Points,you must Update your Voting on www.TheSatria.com!");
                     player->MonsterWhisper(str,player->GetGUID(),true);
                }
                else
                {
                    if (player->AddItem(item, count))
                    {
  			   std::string DateTime = "%Y-%m-%d %H:%M:%S";
			   ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(item);
               LoginDatabase.PExecute("UPDATE Web_db.account_data Set vp = vp - '%u' WHERE id = '%u'", cost, player->GetSession()->GetAccountId());
               //LoginDatabase.PExecute("INSERT INTO Web_db.vote_purchases (account_id, character_name, vote_item_id, vote_item_name, vote_item_amount, date) VALUES ('%u', '%s', '%u', '%s', '%u', DATE_FORMAT(date, '%s'))", player->GetSession()->GetAccountId(), player->GetName(), itemTemplate->Name1.c_str(), count, DateTime.c_str());
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
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface/ICONS/Spell_Frost_ChillingBlast:24|tHow much Vote points do I have?", GOSSIP_SENDER_MAIN, 19000);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|cffFF0000|TInterface\\icons\\Achievement_Leader_Sylvanas:24|tSatria Vote Armor Token - 35 VP", GOSSIP_SENDER_MAIN, 4005);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|cffFF0000|TInterface\\icons\\Achievement_Leader_Sylvanas:24|tSatria Vote Armor Token - 35 VP", GOSSIP_SENDER_MAIN, 4006);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|cffFF0000|TInterface\\icons\\Achievement_Leader_Sylvanas:24|tVote Weapons", GOSSIP_SENDER_MAIN, 2000);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|cffFF0000|TInterface\\icons\\Achievement_Leader_Sylvanas:24|tVote Rings/Trinkets/Amulets and Bags", GOSSIP_SENDER_MAIN, 3000);
            //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|cffFF0000|TInterface\\icons\\Achievement_Leader_Sylvanas:30|tDonorArmors and Shirts", GOSSIP_SENDER_MAIN, 300);
			//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|cffFF0000|TInterface\\icons\\Achievement_Leader_Sylvanas:30|tDonorTitan_Grip (Paladin cant use ) - 10 VP (can't use for 2H Staff)", GOSSIP_SENDER_MAIN, 20000);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|cffFF0000|TInterface\\icons\\Achievement_Leader_Sylvanas:24|tSpecial Items", GOSSIP_SENDER_MAIN, 5000);
            //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|cffFF0000|TInterface\\icons\\Achievement_Leader_Sylvanas:30|tSpecial Tokens", GOSSIP_SENDER_MAIN, 4000);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|cffFF0000|TInterface\\icons\\Achievement_Leader_Sylvanas:30|tDeath of Unholy Voting Tabard - 40 VP", GOSSIP_SENDER_MAIN, 10000);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|cffFF0000|TInterface\\icons\\Achievement_Leader_Sylvanas:30|tDeath of Unholy Voting Cloak - 40 VP", GOSSIP_SENDER_MAIN, 11000);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|cffFF0000|TInterface\\icons\\Achievement_Leader_Sylvanas:30|tDeath of Unholy Voting Shirt - 40 VP ", GOSSIP_SENDER_MAIN, 12000);
			//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|cffFF0000|TInterface\\icons\\Achievement_Leader_Sylvanas:30|tRoyal Donor Set, 8 Coin - 62 VP", GOSSIP_SENDER_MAIN, 13000);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|cffFF0000|TInterface\\icons\\Achievement_Leader_Sylvanas:24|tUltimate Cross Weapon Skill", GOSSIP_SENDER_MAIN, 14000);
			//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|cffFF0000|TInterface\\icons\\Achievement_Leader_Sylvanas:30|tDonor Royal Weapons", GOSSIP_SENDER_MAIN, 32000);
			//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|cffFF0000|TInterface\\icons\\Achievement_Leader_Sylvanas:30|tCosmetic 50% Immune Stun Ring - 30 VP", GOSSIP_SENDER_MAIN, 9997);

            player->PlayerTalkClass->SendGossipMenu(90001, pCreature->GetGUID());

            return true;
        }

        bool OnGossipSelect(Player* player, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
        {
            player->PlayerTalkClass->ClearMenus();

            switch (uiAction)
            {            
				case 5401:
					AddItem(player, pCreature,24,1,15);
						break;
				case 19000:
					AddItem(player, pCreature, 0, 0, 0);
						break;
				case 5402:
					AddItem(player, pCreature,25,1,15);
						break;
				case 5403:
					AddItem(player, pCreature,26,1,10);
						break;
				case 5200:
					AddItem(player, pCreature,40768,1,10);
						break;
				
				case 5100:
					AddItem(player, pCreature,29765,3,5);
				break;
            case 300:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Vote Shirt - 6 VP", GOSSIP_SENDER_MAIN, 301);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Vote Tabard - 20 VP", GOSSIP_SENDER_MAIN, 302);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Vote Shirt - 6 VP", GOSSIP_SENDER_MAIN, 1303);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Donor Steel Shield - 7 VP", GOSSIP_SENDER_MAIN, 304);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Donor Ultimate Speed Shirt ->>", GOSSIP_SENDER_MAIN, 310);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90001, pCreature->GetGUID());
                return true;
                break;
            case 1303:
                if(player->getClass() != CLASS_HUNTER) {
				  char str[200];
				  sprintf(str,"Your not a Hunter, so you cant buy this item!");
						player->MonsterWhisper(str,player->GetGUID(),true);
						player->PlayerTalkClass->SendCloseGossip();
						} else {
						AddItem(player, pCreature,7278,1,10);
						player->PlayerTalkClass->SendCloseGossip();
				  }
						break;
			case 12:
				AddItem(player, pCreature,24368,1,20);
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
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Ultimate Shirt I - 5 VP", GOSSIP_SENDER_MAIN, 311);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Ultimate Shirt II - 7 VP", GOSSIP_SENDER_MAIN, 312);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Ultimate Shirt III - 13 VP", GOSSIP_SENDER_MAIN, 313);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Ultimate Shirt IV - 20 VP", GOSSIP_SENDER_MAIN, 314);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Ultimate Shirt V - 30 VP", GOSSIP_SENDER_MAIN, 315);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90001, pCreature->GetGUID());
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
					AddItem(player, pCreature, 66073,1,35);
			  break;
			case CLASS_PALADIN:
					AddItem(player, pCreature, 66077,1,35);
				  break;
			case CLASS_HUNTER:
					AddItem(player, pCreature, 66071,1,35);
				 break;
			case CLASS_ROGUE:
					AddItem(player, pCreature, 66072,1,35);
				 break;
			case CLASS_PRIEST:
					AddItem(player, pCreature, 66074,1,35);
			  break;
			case CLASS_DEATH_KNIGHT:
					AddItem(player, pCreature, 66070,1,35);
					 break;
			case CLASS_SHAMAN:
					AddItem(player, pCreature, 66078,1,35);
				  break;
			case CLASS_MAGE:
					AddItem(player, pCreature, 66079,1,35);
			  break;
			case CLASS_WARLOCK:
					AddItem(player, pCreature, 66076,1,35);
				  break;
			case CLASS_DRUID:
					AddItem(player, pCreature, 66075,1,35);
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
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Vote One Hand Sword - 33 VP", GOSSIP_SENDER_MAIN, 2101);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Vote One Hand Axe  - 33 VP", GOSSIP_SENDER_MAIN, 2102);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Vote One Hand Mace - 33 VP", GOSSIP_SENDER_MAIN, 2103);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Vote Melee Dagger  - 33 VP", GOSSIP_SENDER_MAIN, 2104);
				//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Vote Spell Dagger  - 33 VP", GOSSIP_SENDER_MAIN, 2105);				
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90001, pCreature->GetGUID());
                return true;
                break;
            case 2101:
                AddItem(player, pCreature,200059,1,33);
                break;
			case 2102:
                AddItem(player, pCreature,200060,1,33);
                break;
			case 2103:
                AddItem(player, pCreature,200061,1,33);
                break;
			case 2104:
                AddItem(player, pCreature,200070,1,33);
                break;
			case 2105:
                AddItem(player, pCreature,200228,1,33);
                break;
			
				
            case 2002:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Vote Two Hand Sword - 50 VP", GOSSIP_SENDER_MAIN, 2201);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Vote Two Hand Axe - 50 VP", GOSSIP_SENDER_MAIN, 2202);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Vote Two Hand Mace - 50 VP", GOSSIP_SENDER_MAIN, 2203);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Vote Polearm  - 50 VP", GOSSIP_SENDER_MAIN, 2204);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90001, pCreature->GetGUID());
                return true;
                break;
            case 2201:
                AddItem(player, pCreature,200066,1,50);
                break;
            case 2202:
                AddItem(player, pCreature,200067,1,50);
                break;
            case 2203:
                AddItem(player, pCreature,200064,1,50);
				break;
			case 2204:
                AddItem(player, pCreature,200232,1,50);
				break;
            
                break;
            case 2003:
                player->PlayerTalkClass->ClearMenus();                
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Vote Spell Staff - 50 VP", GOSSIP_SENDER_MAIN, 2301);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Vote Feral Staff - 50 VP", GOSSIP_SENDER_MAIN, 2303);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90001, pCreature->GetGUID());
                return true;
                break;
            case 2301:
                if(player->getClass() == CLASS_PALADIN || player->getClass() == CLASS_ROGUE || player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_DEATH_KNIGHT || player->getClass() == CLASS_HUNTER) {
				  char str[200];
				  sprintf(str,"Your not a Caster, so you cant buy this item!");
                player->MonsterWhisper(str,player->GetGUID(),true);
                player->PlayerTalkClass->SendCloseGossip();
                } else {
                AddItem(player, pCreature,200069,1,50);
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
                AddItem(player, pCreature,200231,1,50);
                player->PlayerTalkClass->SendCloseGossip();
						}
                
            case 2004:
                player->PlayerTalkClass->ClearMenus();                
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Vote Bow -33 VP", GOSSIP_SENDER_MAIN, 2401);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Vote Gun - 33 VP", GOSSIP_SENDER_MAIN, 2402);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Vote Wand  - 7 VP", GOSSIP_SENDER_MAIN, 2403);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90001, pCreature->GetGUID());
                return true;
                break;
            case 2401:
                AddItem(player, pCreature,200062,1,25);
                break;
            case 2402:
                AddItem(player, pCreature,200063,1,25);
                break;
            case 2403:
                if(player->getClass() == CLASS_PALADIN || player->getClass() == CLASS_ROGUE || player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_DEATH_KNIGHT || player->getClass() == CLASS_HUNTER) {
				char str[200];
				sprintf(str,"Your not a Caster, so you cant buy this item!");
                player->MonsterWhisper(str,player->GetGUID(),true);
                player->PlayerTalkClass->SendCloseGossip();
                } else {
                AddItem(player, pCreature,200071,1,25);
                player->PlayerTalkClass->SendCloseGossip();
		  }
                break;
            case 2005:
                player->PlayerTalkClass->ClearMenus();                
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Vote Tank Shield - 25 VP", GOSSIP_SENDER_MAIN, 2501);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Vote Spell Shield  - 25 VP", GOSSIP_SENDER_MAIN, 2502);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90001, pCreature->GetGUID());
                return true;
                break;
            case 2501:
                AddItem(player, pCreature, 200057,1,25);
                break;
            case 2502:
                AddItem(player, pCreature, 200058,1,25);
                break;
				
            
            case 3000: // ring,amulet balal
                player->PlayerTalkClass->ClearMenus();                
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Death of Unholy Voting Melee Ring - 40 VP", GOSSIP_SENDER_MAIN, 3003);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Death of Unholy Voting Caster Ring - 40 VP", GOSSIP_SENDER_MAIN, 3004);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Death of Unholy Voting Melee Trinket - 40 VP", GOSSIP_SENDER_MAIN, 3005);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Death of Unholy Voting Caster Trinket - 40 VP", GOSSIP_SENDER_MAIN, 3006);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Death of Unholy Voting Melee Amulet - 40 VP", GOSSIP_SENDER_MAIN, 3007);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Death of Unholy Voting Caster Amulet - 40 VP", GOSSIP_SENDER_MAIN, 3008);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Voters Bag - 27 VP", GOSSIP_SENDER_MAIN, 3009);
				//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Fallen Dragon Donor Caster Bag - 6 VP", GOSSIP_SENDER_MAIN, 3010);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90001, pCreature->GetGUID());
                return true;
                break;
            
            case 3003:
                AddItem(player, pCreature, 200052,1,40);
                break;
            case 3004:
                AddItem(player, pCreature, 200213,1,40);
                break;
            case 3005:
                AddItem(player, pCreature, 200053,1,40);
                break;
			case 3006:
                AddItem(player, pCreature, 200214,1,40);
                break;
			case 3007:
                AddItem(player, pCreature, 200051,1,40);
                break;
			case 3008:
                AddItem(player, pCreature, 200212,1,40);
                break;
            case 3009:
                AddItem(player, pCreature, 210009,1,27);
                break;
			
            case 4000:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Transmogrification Token - 1 VP", GOSSIP_SENDER_MAIN, 4001);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Re-Customize Token - 3 VP", GOSSIP_SENDER_MAIN, 14002);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Scroll of Dual Wield - 4 VP", GOSSIP_SENDER_MAIN, 4002);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Item Transfer/Exchange Token - 5 VP", GOSSIP_SENDER_MAIN, 4003);
                //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Scroll of Titan Grip's - 6 VP", GOSSIP_SENDER_MAIN, 4009);
				//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Cata / MoP Token - 5 VP", GOSSIP_SENDER_MAIN, 5040);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "VIP Rank - 55 VP", GOSSIP_SENDER_MAIN, 4004);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Signet of Berserking - 10 VP", GOSSIP_SENDER_MAIN, 14010);
                
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90001, pCreature->GetGUID());
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
            case 4005://vote token armor
                AddItem(player, pCreature, 28,1,35);
                break;
            case 4006:// vote releaser
                AddItem(player, pCreature, 985467,1,60);
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
                player->PlayerTalkClass->SendGossipMenu(90001, pCreature->GetGUID());
                return true;
                break;
				
				case 32001:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Royal One Hand Sword - 21 VP", GOSSIP_SENDER_MAIN, 52000);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Royal One Hand Axe - 21 VP", GOSSIP_SENDER_MAIN, 52001);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Royal One Hand Mace - 21 VP", GOSSIP_SENDER_MAIN, 52002);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Royal Dagger - 21 VP", GOSSIP_SENDER_MAIN, 52003);
				
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90001, pCreature->GetGUID());
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
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Royal Two Hand Sword - 32 VP", GOSSIP_SENDER_MAIN, 52004);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Royal Two Hand Axe - 32 VP", GOSSIP_SENDER_MAIN, 52005);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Royal Two Hand Mace - 32 VP", GOSSIP_SENDER_MAIN, 52006);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Royal Two Hand Polearm - 32 VP", GOSSIP_SENDER_MAIN, 52007);
								
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90001, pCreature->GetGUID());
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
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Royal One Hand Armageddon Staff - 21 VP", GOSSIP_SENDER_MAIN, 52008);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Royal Two Hand Armageddon Staff - 32 VP", GOSSIP_SENDER_MAIN, 52009);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90001, pCreature->GetGUID());
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
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Royal Bow - 17 VP", GOSSIP_SENDER_MAIN, 52010);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Royal Wand - 17 VP", GOSSIP_SENDER_MAIN, 52011);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Royal Steel Shield - 30 VP", GOSSIP_SENDER_MAIN, 52015);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90001, pCreature->GetGUID());
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
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Vote Idol - 25 VP", GOSSIP_SENDER_MAIN, 5001);
                //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Vote Thrown - 15 VP", GOSSIP_SENDER_MAIN, 5002);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Vote Totem 25 VP", GOSSIP_SENDER_MAIN, 5003);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Vote Sigil -25 VP", GOSSIP_SENDER_MAIN, 5004);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Vote Libram - 25 VP", GOSSIP_SENDER_MAIN, 5005);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90001, pCreature->GetGUID());
                return true;
                break;
            case 5001:
                if(player->getClass() != CLASS_DRUID) {
			  char str[200];
			  sprintf(str,"Your not a Druid, so you cant buy this item!");
					player->MonsterWhisper(str,player->GetGUID(),true);
					player->PlayerTalkClass->SendCloseGossip();
					} else {
					AddItem(player, pCreature, 210005,1,25);
			  } 
					break;
				case 5002:
					if(player->getClass() != CLASS_ROGUE) {
			  char str[200];
			  sprintf(str,"Your not a Rogue, so you cant buy this item!");
					player->MonsterWhisper(str,player->GetGUID(),true);
					player->PlayerTalkClass->SendCloseGossip();
					} else {
					AddItem(player, pCreature, 30025,1,6);
			  } 
					break;
				case 5003:
					if(player->getClass() != CLASS_SHAMAN) {
			  char str[200];
			  sprintf(str,"Your not a Shaman, so you cant buy this item!");
					player->MonsterWhisper(str,player->GetGUID(),true);
					player->PlayerTalkClass->SendCloseGossip();
					} else {
					AddItem(player, pCreature, 210007,1,25);
			  } 
					break;
				case 5004:
					if(player->getClass() != 6) {
			  char str[200];
			  sprintf(str,"Your not a Death Knight, so you cant buy this item!");
					player->MonsterWhisper(str,player->GetGUID(),true);
					player->PlayerTalkClass->SendCloseGossip();
					} else {
					AddItem(player, pCreature, 210003,1,25);
			  } 
					break;
				case 5005:
					if(player->getClass() != CLASS_PALADIN) {
			  char str[200];
			  sprintf(str,"Your not a Paladin, so you cant buy this item!");
					player->MonsterWhisper(str,player->GetGUID(),true);
					player->PlayerTalkClass->SendCloseGossip();
					} else {
					AddItem(player, pCreature, 210000,1,25);
			  } 
					break;
				
			 case 10000: // tabard
			  switch(player->getClass())
			  {
			  case CLASS_WARRIOR:
					AddItem(player, pCreature, 200055,1,40);
			  break;
			  case CLASS_PALADIN:
					AddItem(player, pCreature, 200055,1,40);
				  break;
			  case CLASS_HUNTER:
					AddItem(player, pCreature, 200055,1,40);
				 break;
			  case CLASS_ROGUE:
					AddItem(player, pCreature, 200055,1,40);
				 break;
			  case CLASS_PRIEST:
					AddItem(player, pCreature, 2000055,1,40);
					break;
			  case CLASS_DEATH_KNIGHT:
					AddItem(player, pCreature, 200055,1,40);
					 break;
			  case CLASS_SHAMAN:
					AddItem(player, pCreature, 2000055,1,40);
				  break;
			  case CLASS_MAGE:
					AddItem(player, pCreature, 2000055,1,40);
					break;
			  case CLASS_WARLOCK:
					AddItem(player, pCreature, 2000055,1,40);
				  break;
			  case CLASS_DRUID:
					AddItem(player, pCreature, 200055,1,40);
					break;

			  default: break;
			  }
					break;
			  
			 case 11000: // Vote cloak
			  switch(player->getClass())
			  {
			  case CLASS_WARRIOR:
					AddItem(player, pCreature, 200056,1,40);
			  break;
			  case CLASS_PALADIN:
					AddItem(player, pCreature, 200056,1,40);
				  break;
			  case CLASS_HUNTER:
					AddItem(player, pCreature, 200056,1,40);
				 break;
			  case CLASS_ROGUE:
					AddItem(player, pCreature, 200056,1,40);
				 break;
			  case CLASS_PRIEST:
					AddItem(player, pCreature, 2000056,1,40);
					break;
			  case CLASS_DEATH_KNIGHT:
					AddItem(player, pCreature, 200056,1,40);
					 break;
			  case CLASS_SHAMAN:
					AddItem(player, pCreature, 2000056,1,40);
				  break;
			  case CLASS_MAGE:
					AddItem(player, pCreature, 2000056,1,40);
					break;
			  case CLASS_WARLOCK:
					AddItem(player, pCreature, 2000056,1,40);
				  break;
			  case CLASS_DRUID:
					AddItem(player, pCreature, 200056,1,40);
					break;

			  default: break;
			  }			  
						break;
			 case 12000: // Vote shirt
			  switch(player->getClass())
			  {
			  case CLASS_WARRIOR:
					AddItem(player, pCreature, 200054,1,40);
			  break;
			  case CLASS_PALADIN:
					AddItem(player, pCreature, 200054,1,40);
				  break;
			  case CLASS_HUNTER:
					AddItem(player, pCreature, 200054,1,40);
				 break;
			  case CLASS_ROGUE:
					AddItem(player, pCreature, 200054,1,40);
				 break;
			  case CLASS_PRIEST:
					AddItem(player, pCreature, 2000054,1,40);
					break;
			  case CLASS_DEATH_KNIGHT:
					AddItem(player, pCreature, 200054,1,40);
					 break;
			  case CLASS_SHAMAN:
					AddItem(player, pCreature, 2000054,1,40);
				  break;
			  case CLASS_MAGE:
					AddItem(player, pCreature, 2000054,1,40);
					break;
			  case CLASS_WARLOCK:
					AddItem(player, pCreature, 2000054,1,40);
				  break;
			  case CLASS_DRUID:
					AddItem(player, pCreature, 200054,1,40);
					break;

			  default: break;
			  }			  
						break;
			  
			  case 13000: // Vote set
			  switch(player->getClass())
			  {
			  case CLASS_WARRIOR:
					AddItem(player, pCreature, 7,8,62);
			  break;
			  case CLASS_PALADIN:
					AddItem(player, pCreature, 7,8,62);
				  break;
			  case CLASS_HUNTER:
					AddItem(player, pCreature, 7,8,62);
				 break;
			  case CLASS_ROGUE:
					AddItem(player, pCreature, 7,8,62);
				 break;
			  case CLASS_PRIEST:
					AddItem(player, pCreature, 7,8,62);
				  break;
			  case CLASS_DEATH_KNIGHT:
					AddItem(player, pCreature, 7,8,62);
					 break;
			  case CLASS_SHAMAN:
					AddItem(player, pCreature, 7,8,62);
				  break;
			  case CLASS_MAGE:
					AddItem(player, pCreature, 7,8,62);
			  break;
			  case CLASS_WARLOCK:
					AddItem(player, pCreature, 7,8,62);
				  break;
			  case CLASS_DRUID:
					AddItem(player, pCreature, 7,8,62);
					break;

			  default: break;
			  }
			  break;
		  
			case 14000: // cross weapon skill
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Ultimate One Hand Sword Weapon Skill - 215 VP", GOSSIP_SENDER_MAIN, 14001);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Ultimate Two Hand Sword Weapon Skill - 430 VP", GOSSIP_SENDER_MAIN, 14909);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Ultimate One Hand Axe Weapon Skill - 215 VP", GOSSIP_SENDER_MAIN, 14003);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Ultimate Two Hand Axe Weapon Skill - 430 VP", GOSSIP_SENDER_MAIN, 14004);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Ultimate One Hand Mace Weapon Skill - 215 VP", GOSSIP_SENDER_MAIN, 14005);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Ultimate Two Hand Mace Weapon Skill - 430 VP", GOSSIP_SENDER_MAIN, 14006);
				//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Ultimate Staff Weapon Skill - 430 VP ", GOSSIP_SENDER_MAIN, 14007);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Ultimate Polearm Hand Sword Weapon Skill - 430 VP", GOSSIP_SENDER_MAIN, 14008);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Ultimate Dagger Weapon Skill - 215 VP", GOSSIP_SENDER_MAIN, 14009);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Ultimate Bow Weapon Skill - 215 VP", GOSSIP_SENDER_MAIN, 14010);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Ultimate Shield Skill - 215 VP", GOSSIP_SENDER_MAIN, 14011);
				//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Ultimate Wand Weapon Skill - 15 VP", GOSSIP_SENDER_MAIN, 14012);
			
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90702, pCreature->GetGUID());
                return true;
                break;
			
				case 14001:
				AddItem(player, pCreature, 340014,1,215);
				break;
				case 14909:
				AddItem(player, pCreature, 340015,1,430);
				break;
				case 14003:
				AddItem(player, pCreature, 340016,1,215);
				break;
				case 14004:
				AddItem(player, pCreature, 340017,1,430);
				break;
				case 14005:
				AddItem(player, pCreature, 340018,1,215);
				break;
				case 14006:
				AddItem(player, pCreature, 340019,1,430);
				break;
				case 14007:
				AddItem(player, pCreature, 340020,1,430);
				break;
				case 14008:
				AddItem(player, pCreature, 340021,1,430);
				break;
				case 14009:
				AddItem(player, pCreature, 340022,1,215);
				break;
				case 140010:
				AddItem(player, pCreature, 340023,1,215);
				break;
				case 140011:
				AddItem(player, pCreature, 340024,1,215);
				break;
				case 140012:
				AddItem(player, pCreature, 1,1,215);
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

void AddSC_Vote_rewarder()
{
    new Vote_rewarder();
}
