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
#include "Language.h"
#include "Chat.h"

class Vote_rewarder : public CreatureScript
{
	
    public:Vote_rewarder() : CreatureScript("Vote_rewarder") {}
		
		void RewardItem(Player* player, Creature* pCreature, int item , int count, int cost)
        {
            QueryResult result;
            result = CharacterDatabase.PQuery("SELECT vp FROM webdb.account_data WHERE id = '%u' AND vp >= '0'", player->GetSession()->GetAccountId());
            char str[200];
            if (!result) // check
            {
                sprintf(str,"Your have abused our systems and gotten a negative balance on your Vote Points. Your points are set to 0.");
				LoginDatabase.PQuery("UPDATE webdb.account_data set vp = 0 WHERE id = '%u'", player->GetSession()->GetAccountId());
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
                     sprintf(str,"You broke now,you must Vote more on www.Heavenwow.net!");
                     player->MonsterWhisper(str,player->GetGUID(),true);
                }
                else
                {
                    if (player->AddItem(item, count))
                    {
					std::string DateTime = "%Y-%m-%d %H:%M:%S";
					ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(item);
                    CharacterDatabase.PQuery("UPDATE webdb.account_data Set vp = vp - '%u' WHERE id = '%u'", cost, player->GetSession()->GetAccountId());
                    //LoginDatabase.PQuery("INSERT INTO webdb.vote_purchases (account_id, character_name, character_guid, vote_item_id, vote_item_name, vote_item_amount, date) VALUES ('%u', '%s', '%u', '%u', '%s', '%u', DATE_FORMAT(date, '%s'))", player->GetSession()->GetAccountId(), player->GetName(), player->GetGUIDLow(), item, itemTemplate->Name1.c_str(), count, DateTime.c_str());
                    sprintf(str,"Points are taken and your item is in your bag!");
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
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface/ICONS/INV_Misc_Gear_01:30|t How much Vote points do i have?", GOSSIP_SENDER_MAIN, 19000);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface\\icons\\Achievement_Leader_Sylvanas:24|tVote Weapons", GOSSIP_SENDER_MAIN, 2000);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface/ICONS/Achievement_Leader_King_Varian_Wrynn:24|t|rUltimate Cross Weapon Skill", GOSSIP_SENDER_MAIN, 14000);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface/ICONS/Achievement_Leader_King_Varian_Wrynn:24|t|rVote Misc Item", GOSSIP_SENDER_MAIN, 3000);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface/ICONS/Achievement_Leader_King_Varian_Wrynn:24|t|rVote Shirt ,Tabard and Cloak", GOSSIP_SENDER_MAIN, 4000);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|TInterface/ICONS/Achievement_Leader_King_Varian_Wrynn:24|t|rVoting Token, Coin etc", GOSSIP_SENDER_MAIN, 5000);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "|TInterface/ICONS/Achievement_Leader_King_Varian_Wrynn:24|t|rRelics", GOSSIP_SENDER_MAIN, 6666);
            player->PlayerTalkClass->SendGossipMenu(90001, pCreature->GetGUID());

            return true;			
		}

        bool OnGossipSelect(Player* player, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
        {
            player->PlayerTalkClass->ClearMenus();

            switch (uiAction)
            {  
				case 19000: //point check
				RewardItem(player, pCreature, 0, 0, 0);
				break;	
				
			case 5000:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Instant 255 Token - 35 VP", GOSSIP_SENDER_MAIN, 5001);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Customizer Token - 25 VP", GOSSIP_SENDER_MAIN, 5002);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Worgen Book - 10 VP", GOSSIP_SENDER_MAIN, 5003);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Vote Token for Armor - 30 VP", GOSSIP_SENDER_MAIN, 5004);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Full Vote Token for Armor - 190 VP", GOSSIP_SENDER_MAIN, 5005);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Na'wa Credit Coin ->", GOSSIP_SENDER_MAIN, 5006);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Molten Core Credit ->", GOSSIP_SENDER_MAIN, 5007);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Dual Wield - 250 VP", GOSSIP_SENDER_MAIN, 5008);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Titan Grip - 350 VP", GOSSIP_SENDER_MAIN, 5009);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Reforging Token - 10 VP", GOSSIP_SENDER_MAIN, 5010);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(9000, pCreature->GetGUID());
                return true;
                break;
			case 5001:
                RewardItem(player, pCreature,55559,1,35);
                break;
			case 5002:
                RewardItem(player, pCreature,31,1,25);
                break;
			case 5003:
                RewardItem(player, pCreature,23864,1,10);
                break;
			case 5004:
                RewardItem(player, pCreature,32572,1,30);
                break;
			case 5005:
                RewardItem(player, pCreature,66002,1,190);
                break;
			case 5006:// nawa
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "10 Na'wa Credit Coin - 10 Vp", GOSSIP_SENDER_MAIN, 5101);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "30 Na'wa Credit Coin - 30 VP", GOSSIP_SENDER_MAIN, 5102);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "50 Na'wa Credit Coin - 45 Vp", GOSSIP_SENDER_MAIN, 5103);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(9000, pCreature->GetGUID());
                return true;
                break;
			case 5101:
                RewardItem(player, pCreature,86100,10,10);
                break;
			case 5102:
                RewardItem(player, pCreature,86100,30,30);
                break;
			case 5103:
                RewardItem(player, pCreature,86100,50,45);
                break;
			case 5007:// moltencore
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "10 Molten Core Credit - 20 Vp", GOSSIP_SENDER_MAIN, 5701);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "30 Molten Core Credit - 60 VP", GOSSIP_SENDER_MAIN, 5702);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "50 Molten Core Credit - 90 Vp", GOSSIP_SENDER_MAIN, 5703);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(9000, pCreature->GetGUID());
                return true;
                break;
			case 5701:
                RewardItem(player, pCreature,86101,10,20);
                break;
			case 5702:
                RewardItem(player, pCreature,86101,30,60);
                break;
			case 5703:
                RewardItem(player, pCreature,86101,50,90);
                break;
			case 5008:
                RewardItem(player, pCreature, 90900, 1, 250);
                break;
			case 5009:
                RewardItem(player, pCreature, 90901, 1, 350);
                break;
			case 5010:
                RewardItem(player, pCreature,320281, 1, 10);
                break;	
			case 4000:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Firdaus Vote Shirt - 35 VP", GOSSIP_SENDER_MAIN, 4001);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Firdaus Vote Cloak - 35 VP", GOSSIP_SENDER_MAIN, 4002);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Firdaus Vote Caster Tabard - 30 VP", GOSSIP_SENDER_MAIN, 4003);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Firdaus Vote Melee Tabard - 30 VP", GOSSIP_SENDER_MAIN, 4004);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Firdaus Vote Range Tabard - 30 VP", GOSSIP_SENDER_MAIN, 4005);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(9000, pCreature->GetGUID());
                return true;
                break;
			case 4001:
                RewardItem(player, pCreature,85024,1,35);
                break;
			case 4002:
                RewardItem(player, pCreature,85022,1,35);
                break;
			case 4003:
                RewardItem(player, pCreature,90902,1,30);
                break;
			case 4004:
                RewardItem(player, pCreature,38314,1,30);
                break;
			case 4005:
                RewardItem(player, pCreature,90903,1,30);
                break;
				
			case 3000:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Firdaus Vote Melee Ring - 30 VP", GOSSIP_SENDER_MAIN, 3001);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Firdaus Vote Caster Ring - 30 VP", GOSSIP_SENDER_MAIN, 3002);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Firdaus Vote Range Ring - 30 VP", GOSSIP_SENDER_MAIN, 3003);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Firdaus Vote Melee Trinket - 30 VP", GOSSIP_SENDER_MAIN, 3004);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Firdaus Vote Caster Trinket - 30 VP", GOSSIP_SENDER_MAIN, 3005);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Firdaus Vote Range Trinket - 30 VP", GOSSIP_SENDER_MAIN, 3006);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Firdaus Vote Melee Amulet - 30 VP", GOSSIP_SENDER_MAIN, 3007);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Firdaus Vote Caster Amulet - 30 VP", GOSSIP_SENDER_MAIN, 3008);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Firdaus Vote Range Amulet - 30 VP", GOSSIP_SENDER_MAIN, 3009);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(9000, pCreature->GetGUID());
                return true;
                break;
			case 3001:
                RewardItem(player, pCreature,99080,1,30);
                break;
			case 3002:
                RewardItem(player, pCreature,99083,1,30);
                break;
			case 3003:
                RewardItem(player, pCreature,99086,1,30);
                break;
			case 3004:
                RewardItem(player, pCreature,99081,1,30);
                break;
			case 3005:
                RewardItem(player, pCreature,99085,1,30);
                break;
			case 3006:
                RewardItem(player, pCreature,99088,1,30);
                break;
			case 3007:
                RewardItem(player, pCreature,99082,1,30);
                break;
			case 3008:
                RewardItem(player, pCreature,99084,1,30);
                break;
			case 3009:
                RewardItem(player, pCreature,99087,1,30);
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
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Vote One Hand Sword - 40 VP", GOSSIP_SENDER_MAIN, 2101);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Vote One Hand Axe  - 40 VP", GOSSIP_SENDER_MAIN, 2102);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Vote One Hand Mace - 40 VP", GOSSIP_SENDER_MAIN, 2103);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Vote Dagger  - 40 VP", GOSSIP_SENDER_MAIN, 2104);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Vote Fist  - 40 VP", GOSSIP_SENDER_MAIN, 2105);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Vote Fist Offhand  - 40 VP", GOSSIP_SENDER_MAIN, 2106);
				//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Vote Spell Dagger  - 40 VP", GOSSIP_SENDER_MAIN, 2105);				
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90001, pCreature->GetGUID());
                return true;
                break;
            case 2101:
                RewardItem(player, pCreature,50248,1,40);
                break;
			case 2102:
                RewardItem(player, pCreature,50290,1,40);
                break;
			case 2103:
                RewardItem(player, pCreature,51937,1,40);
                break;
			case 2104:
                RewardItem(player, pCreature,33543,1,40);
                break;
			case 2105:
                RewardItem(player, pCreature,32189,1,40);
                break;
			case 2106:
                RewardItem(player, pCreature,32188,1,40);
                break;
				
            case 2002:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Vote Two Hand Sword - 55 VP", GOSSIP_SENDER_MAIN, 2201);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Vote Two Hand Axe - 55 VP", GOSSIP_SENDER_MAIN, 2202);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Vote Two Hand Mace - 55 VP", GOSSIP_SENDER_MAIN, 2203);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Vote Polearm  - 55 VP", GOSSIP_SENDER_MAIN, 2204);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90001, pCreature->GetGUID());
                return true;
                break;
            case 2201:
                RewardItem(player, pCreature,49706,1,55);
                break;
            case 2202:
                RewardItem(player, pCreature,50415,1,55);
                break;
            case 2203:
                RewardItem(player, pCreature,30179,1,55);
				break;
			case 2204:
                RewardItem(player, pCreature,50178,1,55);
				break;
            
                break;
            case 2003:
                player->PlayerTalkClass->ClearMenus();                
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Vote Caster Staff - 55 VP", GOSSIP_SENDER_MAIN, 2301);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Vote Feral Staff - 55 VP", GOSSIP_SENDER_MAIN, 2303);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90001, pCreature->GetGUID());
                return true;
                break;
            case 2301:                
                RewardItem(player, pCreature,32607,1,55);                
                break;
			
            case 2302:             
                RewardItem(player, pCreature,51887,1,55);
                break;
                
            case 2004:
                player->PlayerTalkClass->ClearMenus();                
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Vote Bow -33 VP", GOSSIP_SENDER_MAIN, 2401);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Vote Gun - 33 VP", GOSSIP_SENDER_MAIN, 2402);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Vote Wand  - 33 VP", GOSSIP_SENDER_MAIN, 2403);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90001, pCreature->GetGUID());
                return true;
                break;
            case 2401:
                RewardItem(player, pCreature,50776,1,33);
                break;
            case 2402:
                RewardItem(player, pCreature,51834,1,33);
                break;
            case 2403:
                RewardItem(player, pCreature,50033,1,33);
                break;
            case 2005:
                player->PlayerTalkClass->ClearMenus();                
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Vote Tank Shield - 30 VP", GOSSIP_SENDER_MAIN, 2551);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Vote Spell Shield  - 30 VP", GOSSIP_SENDER_MAIN, 2552);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90001, pCreature->GetGUID());
                return true;
                break;
            case 2551:
                RewardItem(player, pCreature, 51455,1,30);
                break;
            case 2552:
                RewardItem(player, pCreature, 51909,1,30);
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
				RewardItem(player, pCreature, 340014,1,215);
				break;
				case 14909:
				RewardItem(player, pCreature, 340015,1,430);
				break;
				case 14003:
				RewardItem(player, pCreature, 340016,1,215);
				break;
				case 14004:
				RewardItem(player, pCreature, 340017,1,430);
				break;
				case 14005:
				RewardItem(player, pCreature, 340018,1,215);
				break;
				case 14006:
				RewardItem(player, pCreature, 340019,1,430);
				break;
				case 14007:
				RewardItem(player, pCreature, 340020,1,430);
				break;
				case 14008:
				RewardItem(player, pCreature, 340021,1,430);
				break;
				case 14009:
				RewardItem(player, pCreature, 340022,1,215);
				break;
				case 14010:
				RewardItem(player, pCreature, 340023,1,215);
				break;
				case 14011:
				RewardItem(player, pCreature, 340024,1,215);
				break;
			
			case 6666:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Vote Idol - 35 VP", GOSSIP_SENDER_MAIN, 6001);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Vote Totem - 35 VP", GOSSIP_SENDER_MAIN, 6002);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Vote Sigil - 35 VP", GOSSIP_SENDER_MAIN, 6003);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Vote Libram - 35 VP", GOSSIP_SENDER_MAIN, 6004);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90701, pCreature->GetGUID());
                return true;
                break;
			
			case 6001:
                RewardItem(player, pCreature,99061,1,35);
                break;
            case 6002:
                RewardItem(player, pCreature,99062,1,35);
                break;
            case 6003:
                RewardItem(player, pCreature,99063,1,35);
				break;
			case 6004:
                RewardItem(player, pCreature,99060,1,35);
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
