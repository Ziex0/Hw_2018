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
               LoginDatabase.PExecute("UPDATE Web_db.account_data Set dp = dp - '%u' WHERE id = '%u'", cost, player->GetSession()->GetAccountId());
               //LoginDatabase.PExecute("INSERT INTO Web_db.donation_purchases (account_id, character_name, donation_item_id, donation_item_amount) VALUES ('%u', '%s', '%u', '%u')", player->GetSession()->GetAccountId(), player->GetName(), item, count);
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
            //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Get a preview of the donor items", GOSSIP_SENDER_MAIN, 9998);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "|TInterface/ICONS/INV_Chest_Plate13:24|tHow much Donation points do i have?", GOSSIP_SENDER_MAIN, 19000);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "|TInterface/ICONS/Achievement_Leader_King_Varian_Wrynn:24|t|rSatria Donation Armor Token - 5 DP", GOSSIP_SENDER_MAIN, 4005);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "|TInterface/ICONS/Achievement_Leader_King_Varian_Wrynn:24|t|rDonor Weapons", GOSSIP_SENDER_MAIN, 2000);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "|TInterface/ICONS/Achievement_Leader_King_Varian_Wrynn:24|t|rDonor Rings/Trinkets/Amulets and Bags", GOSSIP_SENDER_MAIN, 3000);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "|TInterface/ICONS/Achievement_Leader_King_Varian_Wrynn:24|t|rDonor Shirts / Cloak / Tabard", GOSSIP_SENDER_MAIN, 300);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "|TInterface/ICONS/Achievement_Leader_King_Varian_Wrynn:24|t|rDual Wield - 10 DP", GOSSIP_SENDER_MAIN, 30000);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "|TInterface/ICONS/Achievement_Leader_King_Varian_Wrynn:24|t|rTitan_Grip - 20 DP", GOSSIP_SENDER_MAIN, 20000);
            //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "|cffFF0000|TInterface\\icons\\Achievement_Leader_Sylvanas:30|tSpecial Items", GOSSIP_SENDER_MAIN, 5000);
            //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "|cffFF0000|TInterface\\icons\\Achievement_Leader_Sylvanas:30|tSpecial Tokens", GOSSIP_SENDER_MAIN, 4000);
            //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "|cffFF0000|TInterface\\icons\\Achievement_Leader_Sylvanas:30|tDonor Tabard - 7 Dp", GOSSIP_SENDER_MAIN, 10000);
            //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "|cffFF0000|TInterface\\icons\\Achievement_Leader_Sylvanas:30|tDonor Cloak - 10 DP", GOSSIP_SENDER_MAIN, 11000);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "|TInterface/ICONS/Achievement_Leader_King_Varian_Wrynn:24|t|rDonor Set - 30 DP ( 8 Pieces )", GOSSIP_SENDER_MAIN, 12000);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "|TInterface/ICONS/Achievement_Leader_King_Varian_Wrynn:24|t|rUltimate Cross Weapon Skill", GOSSIP_SENDER_MAIN, 14000);
			//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "|cffFF0000|TInterface\\icons\\Achievement_Leader_Sylvanas:30|tDonor Royal Weapons", GOSSIP_SENDER_MAIN, 32000);
            //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Heaven Gems 5 DP - 3 Gems", GOSSIP_SENDER_MAIN, 5100);
            //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Portable Mailbox - 10 DP", GOSSIP_SENDER_MAIN, 5200);
            player->PlayerTalkClass->SendGossipMenu(90701, pCreature->GetGUID());

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
				case 5300:
					AddItem(player, pCreature,37298,1,10);
						break;
				case 5100:
					AddItem(player, pCreature,29765,3,5);
				break;
            case 300:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Donors Shirt - 6 DP", GOSSIP_SENDER_MAIN, 301);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Donors Tabard - 6 DP", GOSSIP_SENDER_MAIN, 302);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Donors Cloak - 6 DP", GOSSIP_SENDER_MAIN, 303);
                //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Donor Steel Shield - 7 DP", GOSSIP_SENDER_MAIN, 304);
				//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Donor Ultimate Speed Shirt ->>", GOSSIP_SENDER_MAIN, 310);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90701, pCreature->GetGUID());
                return true;
                break;
            case 301:
				player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Donors Shirt Paladin", 		GOSSIP_SENDER_MAIN, 70001);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Donors Shirt Warrior", 		GOSSIP_SENDER_MAIN, 70002);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Donors Shirt Death Knight", 	GOSSIP_SENDER_MAIN, 70003);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Donors Shirt Hunter", 		GOSSIP_SENDER_MAIN, 70004);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Donors Shirt Rogue", 		GOSSIP_SENDER_MAIN, 70005);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Donors Shirt Warlock", 		GOSSIP_SENDER_MAIN, 70006);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Donors Shirt Druid", 		GOSSIP_SENDER_MAIN, 70007);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Donors Shirt Mage", 			GOSSIP_SENDER_MAIN, 70008);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Donors Shirt Shaman", 		GOSSIP_SENDER_MAIN, 70009);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Donors Shirt Priest", 		GOSSIP_SENDER_MAIN, 70010);
				
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90701, pCreature->GetGUID());
                return true;
                break;
			
			case 70001:
                if(player->getClass() != CLASS_PALADIN) 
				{
				  char str[200];
				  sprintf(str,"Your not a paladin, so you cant buy this item!");
						player->MonsterWhisper(str,player->GetGUID(),true);
						player->PlayerTalkClass->SendCloseGossip();
				} else 
					{
						AddItem(player, pCreature,200224,1,6);
						player->PlayerTalkClass->SendCloseGossip();
					}
						break;
			case 70002:
                if(player->getClass() != CLASS_WARRIOR) 
				{
				  char str[200];
				  sprintf(str,"Your not a warrior, so you cant buy this item!");
						player->MonsterWhisper(str,player->GetGUID(),true);
						player->PlayerTalkClass->SendCloseGossip();
				} else 
					{
						AddItem(player, pCreature,200227,1,6);
						player->PlayerTalkClass->SendCloseGossip();
					}
						break;
			case 70003:
                if(player->getClass() != CLASS_DEATH_KNIGHT) 
				{
				  char str[200];
				  sprintf(str,"Your not a DK, so you cant buy this item!");
						player->MonsterWhisper(str,player->GetGUID(),true);
						player->PlayerTalkClass->SendCloseGossip();
				} else 
					{
						AddItem(player, pCreature,200223,1,6);
						player->PlayerTalkClass->SendCloseGossip();
					}
						break;
			case 70004:
                if(player->getClass() != CLASS_HUNTER) 
				{
				  char str[200];
				  sprintf(str,"Your not a hunter, so you cant buy this item!");
						player->MonsterWhisper(str,player->GetGUID(),true);
						player->PlayerTalkClass->SendCloseGossip();
				} else 
					{
						AddItem(player, pCreature,200222,1,6);
						player->PlayerTalkClass->SendCloseGossip();
					}
				break;
			case 70005:
                if(player->getClass() != CLASS_ROGUE) 
				{
				  char str[200];
				  sprintf(str,"Your not a rogue, so you cant buy this item!");
						player->MonsterWhisper(str,player->GetGUID(),true);
						player->PlayerTalkClass->SendCloseGossip();
				} else 
					{
						AddItem(player, pCreature,200221,1,6);
						player->PlayerTalkClass->SendCloseGossip();
					}
				break;
			case 70006:
                if(player->getClass() != CLASS_WARLOCK) 
				{
				  char str[200];
				  sprintf(str,"Your not a warlock, so you cant buy this item!");
						player->MonsterWhisper(str,player->GetGUID(),true);
						player->PlayerTalkClass->SendCloseGossip();
				} else 
					{
						AddItem(player, pCreature,200220,1,6);
						player->PlayerTalkClass->SendCloseGossip();
					}
				break;
			case 70007:
                if(player->getClass() != CLASS_DRUID) 
				{
				  char str[200];
				  sprintf(str,"Your not a Druid, so you cant buy this item!");
						player->MonsterWhisper(str,player->GetGUID(),true);
						player->PlayerTalkClass->SendCloseGossip();
				} else 
					{
						AddItem(player, pCreature,200219,1,6);
						player->PlayerTalkClass->SendCloseGossip();
					}
				break;
			case 70008:
                if(player->getClass() != CLASS_MAGE) 
				{
				  char str[200];
				  sprintf(str,"Your not a Mage, so you cant buy this item!");
						player->MonsterWhisper(str,player->GetGUID(),true);
						player->PlayerTalkClass->SendCloseGossip();
				} else 
					{
						AddItem(player, pCreature,200225,1,6);
						player->PlayerTalkClass->SendCloseGossip();
					}
				break;
			case 70009:
                if(player->getClass() != CLASS_SHAMAN) 
				{
				  char str[200];
				  sprintf(str,"Your not a Shaman, so you cant buy this item!");
						player->MonsterWhisper(str,player->GetGUID(),true);
						player->PlayerTalkClass->SendCloseGossip();
				} else 
					{
						AddItem(player, pCreature,200218,1,6);
						player->PlayerTalkClass->SendCloseGossip();
					}
				break;
			case 70010:
                if(player->getClass() != CLASS_PRIEST) 
				{
				  char str[200];
				  sprintf(str,"Your not a priest, so you cant buy this item!");
						player->MonsterWhisper(str,player->GetGUID(),true);
						player->PlayerTalkClass->SendCloseGossip();
				} else 
					{
						AddItem(player, pCreature,200226,1,6);
						player->PlayerTalkClass->SendCloseGossip();
					}
				break;
            
            case 302:
                AddItem(player, pCreature,200165,1,6);
                break;
            case 303:
                AddItem(player, pCreature,200166,1,6);
                break;
            case 304:
                AddItem(player, pCreature,100130,1,7);
                break;
			case 310:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Ultimate Shirt I - 5 Dp", GOSSIP_SENDER_MAIN, 311);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Ultimate Shirt II - 7 Dp", GOSSIP_SENDER_MAIN, 312);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Ultimate Shirt III - 13 Dp", GOSSIP_SENDER_MAIN, 313);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Ultimate Shirt IV - 20 Dp", GOSSIP_SENDER_MAIN, 314);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Ultimate Shirt V - 30 Dp", GOSSIP_SENDER_MAIN, 315);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90701, pCreature->GetGUID());
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
				
			
            case 1000:
                AddItem(player, pCreature, 0, 0, 0);
                break;
            case 2000:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "One-Handed Weapons", GOSSIP_SENDER_MAIN, 2001);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Two-Handed Weapons", GOSSIP_SENDER_MAIN, 2002);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Staves", GOSSIP_SENDER_MAIN, 2003);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Ranged", GOSSIP_SENDER_MAIN, 2004);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Off-Hand Weapons", GOSSIP_SENDER_MAIN, 2005);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(9000, pCreature->GetGUID());
                return true;
                break;
            case 2001:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Final Achievement One Hand Sword of Donation - 9 DP", GOSSIP_SENDER_MAIN, 2101);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Final Achievement One Hand Axe of Donation - 9 DP", GOSSIP_SENDER_MAIN, 2102);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Final Achievement One Hand Mace of Donation- 9 DP", GOSSIP_SENDER_MAIN, 2103);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Final Achievement Melee Dagger of Donation - 9 DP", GOSSIP_SENDER_MAIN, 2104);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Final Achievement Spell Dagger of Donation - 9 DP", GOSSIP_SENDER_MAIN, 2105);				
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90701, pCreature->GetGUID());
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
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Final Achievement Two Hand Sword of Donation - 15 DP", GOSSIP_SENDER_MAIN, 2201);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Final Achievement Two Hand Axe of Donation- 15 DP", GOSSIP_SENDER_MAIN, 2202);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Final Achievement Two Hand Mace of Donation - 15 DP", GOSSIP_SENDER_MAIN, 2203);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Final Achievement Polearm of Donation - 15 DP", GOSSIP_SENDER_MAIN, 2204);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90701, pCreature->GetGUID());
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
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Final Achievement Spell Staff of Donation- 15 DP", GOSSIP_SENDER_MAIN, 2301);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Final Achievement Feral Staff of Donation- 15 DP", GOSSIP_SENDER_MAIN, 2303);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90701, pCreature->GetGUID());
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
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Final Achievement Bow of Donation - 9 DP", GOSSIP_SENDER_MAIN, 2401);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Final Achievement Gun of Donation- 9 DP", GOSSIP_SENDER_MAIN, 2402);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Reaper Wand of Donators - 7 DP", GOSSIP_SENDER_MAIN, 2403);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90701, pCreature->GetGUID());
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
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Final Achievement Tank Shield of Donation - 7 DP", GOSSIP_SENDER_MAIN, 2501);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Final Achievement Spell Shield of Donation - 7 DP", GOSSIP_SENDER_MAIN, 2502);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90701, pCreature->GetGUID());
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
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Fallen Dragon Donor Melee Ring - 6 DP", GOSSIP_SENDER_MAIN, 3003);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Fallen Dragon Donor Caster Ring - 6 DP", GOSSIP_SENDER_MAIN, 3004);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Fallen Dragon Donor Melee Trinket - 6 DP", GOSSIP_SENDER_MAIN, 3005);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Fallen Dragon Donor Caster Trinket - 6 DP", GOSSIP_SENDER_MAIN, 3006);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Fallen Dragon Donor Melee Amulet - 6 DP", GOSSIP_SENDER_MAIN, 3007);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Fallen Dragon Donor Caster Amulet - 6 DP", GOSSIP_SENDER_MAIN, 3008);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Fallen Dragon Donor Bag - 5 DP", GOSSIP_SENDER_MAIN, 3009);
				//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Fallen Dragon Donor Caster Bag - 6 DP", GOSSIP_SENDER_MAIN, 3010);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90701, pCreature->GetGUID());
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
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Transmogrification Token - 1 DP", GOSSIP_SENDER_MAIN, 4001);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Re-Customize Token - 3 DP", GOSSIP_SENDER_MAIN, 14002);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Scroll of Dual Wield - 4 DP", GOSSIP_SENDER_MAIN, 4002);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Item Transfer/Exchange Token - 5 DP", GOSSIP_SENDER_MAIN, 4003);
                //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Scroll of Titan Grip's - 6 DP", GOSSIP_SENDER_MAIN, 4009);
				//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Cata / MoP Token - 5 DP", GOSSIP_SENDER_MAIN, 5040);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "VIP Rank - 55 DP", GOSSIP_SENDER_MAIN, 4004);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "VIP II Token - 75 DP", GOSSIP_SENDER_MAIN, 4006);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Upgrade to VIP II (This Work if you have VIP 1)- 311 DP", GOSSIP_SENDER_MAIN, 4007);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Signet of Berserking - 10 DP", GOSSIP_SENDER_MAIN, 14010);
                
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90701, pCreature->GetGUID());
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
            case 4005: //donation armor token
                AddItem(player, pCreature, 27,1,5);
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
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Royal Two Hand Sword - 32 Dp", GOSSIP_SENDER_MAIN, 52004);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Royal Two Hand Axe - 32 Dp", GOSSIP_SENDER_MAIN, 52005);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Royal Two Hand Mace - 32 Dp", GOSSIP_SENDER_MAIN, 52006);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Royal Two Hand Polearm - 32 Dp", GOSSIP_SENDER_MAIN, 52007);
								
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90701, pCreature->GetGUID());
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
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Royal One Hand Armageddon Staff - 21 Dp", GOSSIP_SENDER_MAIN, 52008);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Royal Two Hand Armageddon Staff - 32 Dp", GOSSIP_SENDER_MAIN, 52009);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90701, pCreature->GetGUID());
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
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Royal Bow - 17 Dp", GOSSIP_SENDER_MAIN, 52010);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Royal Wand - 17 Dp", GOSSIP_SENDER_MAIN, 52011);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Royal Steel Shield - 30 Dp", GOSSIP_SENDER_MAIN, 52015);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90701, pCreature->GetGUID());
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
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Donors Idol - 6 DP", GOSSIP_SENDER_MAIN, 5001);
                //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Donors Thrown - 15 DP", GOSSIP_SENDER_MAIN, 5002);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Donors Totem - 6 DP", GOSSIP_SENDER_MAIN, 5003);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Donors Sigil - 6 DP", GOSSIP_SENDER_MAIN, 5004);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Donors Libram - 6 DP", GOSSIP_SENDER_MAIN, 5005);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90701, pCreature->GetGUID());
                return true;
                break;
            case 5001:
                if(player->getClass() != CLASS_DRUID) {
			  char str[200];
			  sprintf(str,"Your not a Druid, so you cant buy this item!");
					player->MonsterWhisper(str,player->GetGUID(),true);
					player->PlayerTalkClass->SendCloseGossip();
					} else {
					AddItem(player, pCreature, 100107,1,6);
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
					AddItem(player, pCreature, 100103,1,6);
			  } 
					break;
				case 5004:
					if(player->getClass() != 6) {
			  char str[200];
			  sprintf(str,"Your not a Death Knight, so you cant buy this item!");
					player->MonsterWhisper(str,player->GetGUID(),true);
					player->PlayerTalkClass->SendCloseGossip();
					} else {
					AddItem(player, pCreature, 100104,1,6);
			  } 
					break;
				case 5005:
					if(player->getClass() != CLASS_PALADIN) {
			  char str[200];
			  sprintf(str,"Your not a Paladin, so you cant buy this item!");
					player->MonsterWhisper(str,player->GetGUID(),true);
					player->PlayerTalkClass->SendCloseGossip();
					} else {
					AddItem(player, pCreature, 100106,1,6);
			  } 
					break;
				case 5006:
					AddItem(player, pCreature, 4633,1,2);
					break;
			 case 10000: // tabard
			  switch(player->getClass())
			  {
			  case CLASS_WARRIOR:
					AddItem(player, pCreature, 100093,1,7);
			  break;
			  case CLASS_PALADIN:
					AddItem(player, pCreature, 100098,1,7);
				  break;
			  case CLASS_HUNTER:
					AddItem(player, pCreature, 100100,1,7);
				 break;
			  case CLASS_ROGUE:
					AddItem(player, pCreature, 100096,1,7);
				 break;
			  case CLASS_PRIEST:
					AddItem(player, pCreature, 100097,1,7);
			  break;
			  case CLASS_DEATH_KNIGHT:
					AddItem(player, pCreature, 100102,1,7);
					 break;
			  case CLASS_SHAMAN:
					AddItem(player, pCreature, 100095,1,7);
				  break;
			  case CLASS_MAGE:
					AddItem(player, pCreature, 100099,1,7);
			  break;
			  case CLASS_WARLOCK:
					AddItem(player, pCreature, 100094,1,7);
				  break;
			  case CLASS_DRUID:
					AddItem(player, pCreature, 100101,1,7);
					break;

			  default: break;
			  }
			  break;
			 case 11000: // donors cloak
			  switch(player->getClass())
			  {
			  case CLASS_WARRIOR:
					AddItem(player, pCreature, 100112,1,10);
			  break;
			  case CLASS_PALADIN:
					AddItem(player, pCreature, 100117,1,10);
				  break;
			  case CLASS_HUNTER:
					AddItem(player, pCreature, 100119,1,10);
				 break;
			  case CLASS_ROGUE:
					AddItem(player, pCreature, 100115,1,10);
				 break;
			  case CLASS_PRIEST:
					AddItem(player, pCreature, 100116,1,10);
			  break;
			  case CLASS_DEATH_KNIGHT:
					AddItem(player, pCreature, 100121,1,10);
					 break;
			  case CLASS_SHAMAN:
					AddItem(player, pCreature, 100114,1,10);
				  break;
			  case CLASS_MAGE:
					AddItem(player, pCreature, 100118,1,10);
			  break;
			  case CLASS_WARLOCK:
					AddItem(player, pCreature, 100113,1,10);
				  break;
			  case CLASS_DRUID:
					AddItem(player, pCreature, 100120,1,10);
					break;

			  default: break;
			  }
			  break;
			 case 12000: // donors set
			  switch(player->getClass())
			  {
			  case CLASS_WARRIOR:
					AddItem(player, pCreature, 320268,1,30);
				  break;
			  case CLASS_PALADIN:
					AddItem(player, pCreature, 320267,1,30);
				  break;
			  case CLASS_HUNTER:
					AddItem(player, pCreature, 320271,1,30);
				 break;
			  case CLASS_ROGUE:
					AddItem(player, pCreature, 320270,1,30);
				 break;
			  case CLASS_PRIEST:
					AddItem(player, pCreature, 320273,1,30);
				  break;
			  case CLASS_DEATH_KNIGHT:
					AddItem(player, pCreature, 320269,1,30);
					 break;
			  case CLASS_SHAMAN:
					AddItem(player, pCreature, 320275,1,30);
				  break;
			  case CLASS_MAGE:
					AddItem(player, pCreature, 320272,1,30);
				  break;
			  case CLASS_WARLOCK:
					AddItem(player, pCreature, 320274,1,30);
				  break;
			  case CLASS_DRUID:
					AddItem(player, pCreature, 320276,1,30);
				   break;

			  default: break;
			  }
			  break;
			  
			case 14000: // cross weapon skill
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Ultimate One Hand Sword Weapon Skill - 15 DP", GOSSIP_SENDER_MAIN, 14001);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Ultimate Two Hand Sword Weapon Skill - 30 DP", GOSSIP_SENDER_MAIN, 14909);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Ultimate One Hand Axe Weapon Skill - 15 DP", GOSSIP_SENDER_MAIN, 14003);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Ultimate Two Hand Axe Weapon Skill - 30 DP", GOSSIP_SENDER_MAIN, 14004);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Ultimate One Hand Mace Weapon Skill - 15 DP", GOSSIP_SENDER_MAIN, 14005);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Ultimate Two Hand Mace Weapon Skill - 30 DP", GOSSIP_SENDER_MAIN, 14006);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Ultimate Staff Weapon Skill - 30 DP ", GOSSIP_SENDER_MAIN, 14007);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Ultimate Polearm Hand Sword Weapon Skill - 30 DP", GOSSIP_SENDER_MAIN, 14008);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Ultimate Dagger Weapon Skill - 15 DP", GOSSIP_SENDER_MAIN, 14009);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Ultimate Bow Weapon Skill - 15 DP", GOSSIP_SENDER_MAIN, 14010);
				//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Ultimate Gun Hand Sword Weapon Skill - 15 DP", GOSSIP_SENDER_MAIN, 14011);
				//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Ultimate Wand Weapon Skill - 15 DP", GOSSIP_SENDER_MAIN, 14012);
			
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90702, pCreature->GetGUID());
                return true;
                break;
			
				case 14001:
				AddItem(player, pCreature, 340014,1,15);
				break;
				case 14909:
				AddItem(player, pCreature, 340015,1,30);
				break;
				case 14003:
				AddItem(player, pCreature, 340016,1,15);
				break;
				case 14004:
				AddItem(player, pCreature, 340017,1,30);
				break;
				case 14005:
				AddItem(player, pCreature, 340018,1,15);
				break;
				case 14006:
				AddItem(player, pCreature, 340019,1,30);
				break;
				case 14007:
				AddItem(player, pCreature, 340020,1,30);
				break;
				case 14008:
				AddItem(player, pCreature, 340021,1,30);
				break;
				case 14009:
				AddItem(player, pCreature, 340022,1,15);
				break;
				case 140010:
				AddItem(player, pCreature, 340023,1,15);
				break;
				case 140011:
				AddItem(player, pCreature, 130134,1,15);
				break;
				case 140012:
				AddItem(player, pCreature, 130134,1,15);
				break;
				
				case 20000:  //Titans grip
				AddItem(player, pCreature, 505505,1,20);
				break;
				case 30000:  //dual w
				AddItem(player, pCreature, 505506,1,5);
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
