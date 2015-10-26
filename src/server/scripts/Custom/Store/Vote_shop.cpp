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
               //LoginDatabase.PExecute("INSERT INTO purchases_vote (account_id, character_name, vote_item_id, vote_item_name, vote_item_amount, date) VALUES ('%u', '%s', '%u', '%s', '%u', DATE_FORMAT(date, '%s'))", player->GetSession()->GetAccountId(), player->GetName(), itemTemplate->Name1.c_str(), count, DateTime.c_str());
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
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "|cffFF0000|TInterface\\icons\\Achievement_Leader_Sylvanas:24|tVote Weapons", GOSSIP_SENDER_MAIN, 2000);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "|TInterface/ICONS/Achievement_Leader_King_Varian_Wrynn:24|t|rUltimate Cross Weapon Skill", GOSSIP_SENDER_MAIN, 14000);
			
			
            player->PlayerTalkClass->SendGossipMenu(90001, pCreature->GetGUID());

            return true;
        }

        bool OnGossipSelect(Player* player, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
        {
            player->PlayerTalkClass->ClearMenus();

            switch (uiAction)
            {            
				
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
				//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Vote Spell Dagger  - 40 VP", GOSSIP_SENDER_MAIN, 2105);				
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(90001, pCreature->GetGUID());
                return true;
                break;
            case 2101:
                AddItem(player, pCreature,55248,1,40);
                break;
			case 2102:
                AddItem(player, pCreature,55290,1,40);
                break;
			case 2103:
                AddItem(player, pCreature,51937,1,40);
                break;
			case 2104:
                AddItem(player, pCreature,33543,1,40);
                break;
			case 2105:
                AddItem(player, pCreature,200228,1,40);
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
                AddItem(player, pCreature,49706,1,55);
                break;
            case 2202:
                AddItem(player, pCreature,50415,1,55);
                break;
            case 2203:
                AddItem(player, pCreature,30179,1,55);
				break;
			case 2204:
                AddItem(player, pCreature,50178,1,55);
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
                AddItem(player, pCreature,32607,1,55);                
                break;
			
            case 2302:             
                AddItem(player, pCreature,51887,1,55);
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
                AddItem(player, pCreature,50776,1,33);
                break;
            case 2402:
                AddItem(player, pCreature,51834,1,33);
                break;
            case 2403:
                AddItem(player, pCreature,50033,1,33);
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
                AddItem(player, pCreature, 51455,1,30);
                break;
            case 2552:
                AddItem(player, pCreature, 51909,1,30);
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
				case 14010:
				AddItem(player, pCreature, 340023,1,215);
				break;
				case 14011:
				AddItem(player, pCreature, 340024,1,215);
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
