#include "ScriptPCH.h"
#include <cstring>
#include "ObjectMgr.h"


class vip_set : public CreatureScript
{
    public:

        vip_set()
            : CreatureScript("vip_set"){}
        
        void RewardItem(Player* player, Creature* pCreature, int item , int count, int cost)
        {
                char str[200];

                if (!player->HasItemCount(37711, cost, true))
                {
                     sprintf(str,"You don't have enough points for this item, you must donate on www.Satria.com!");
                     player->MonsterWhisper(str,player->GetGUID(),true);
                }
                else
                {
                    if (player->AddItem(item, count))
                    {
  			   std::string DateTime = "%Y-%m-%d %H:%M:%S";
				ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(item);
                player->DestroyItemCount(37711, cost, true);
                LoginDatabase.PQuery("INSERT INTO web_db.donation_purchases (account_id, character_name, character_guid, donation_item_id, donation_item_name, donation_item_amount, date) VALUES ('%u', '%s', '%u', '%u', '%s', '%u', DATE_FORMAT(date, '%s'))", player->GetSession()->GetAccountId(), player->GetName(), player->GetGUIDLow(), item, itemTemplate->Name1.c_str(), count, DateTime.c_str());
                sprintf(str,"Your points are taken and your item is given!!!");
                player->MonsterWhisper(str,player->GetGUID(),true);
				player->SaveToDB();
                    }
                    else
                    {
                        sprintf(str,"Item can't be given maybe your bag is full or you already got the item!");
                        player->MonsterWhisper(str,player->GetGUID(),true);
                    }

                }

            player->PlayerTalkClass->ClearMenus();
            OnGossipHello(player, pCreature);
        }
		
		bool OnGossipHello(Player* player, Creature* pCreature)
        {
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "VIP + VIP Warrior Set", GOSSIP_SENDER_MAIN, 1000);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "VIP + VIP Paladin Set", GOSSIP_SENDER_MAIN, 2000);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "VIP + VIP Death Knight Set", GOSSIP_SENDER_MAIN, 3000);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "VIP + VIP Hunter Set", GOSSIP_SENDER_MAIN, 4000);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "VIP + VIP Druid Set", GOSSIP_SENDER_MAIN, 5000);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "VIP + VIP Warlock Set", GOSSIP_SENDER_MAIN, 6000);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "VIP + VIP Priest Set", GOSSIP_SENDER_MAIN, 7000);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "VIP + VIP Rogue Set", GOSSIP_SENDER_MAIN, 8000);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "VIP + VIP Shaman Set", GOSSIP_SENDER_MAIN, 9000);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "VIP + VIP Mage Set", GOSSIP_SENDER_MAIN, 10000);
			
			player->PlayerTalkClass->SendGossipMenu(900000, pCreature->GetGUID());

            return true;
        }
		
		bool OnGossipSelect(Player* player, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
        {
            player->PlayerTalkClass->ClearMenus();

            switch (uiAction)
            {
			case 1000:
                RewardItem(player, pCreature,600001, 1, 40);
                break;
				
			case 2000:
                RewardItem(player, pCreature,600000, 1, 40);
                break;
			case 3000:
                RewardItem(player, pCreature,600002, 1, 40);
                break;
			case 4000:
                RewardItem(player, pCreature,600004, 1, 40);
                break;
			case 5000:
                RewardItem(player, pCreature,600010, 1, 40);
                break;
			case 6000:
                RewardItem(player, pCreature,600008, 1, 40);
                break;
			case 7000:
                RewardItem(player, pCreature,600007, 1, 40);
                break;
			case 8000:
                RewardItem(player, pCreature,600003, 1, 40);
                break;
			case 9000:
                RewardItem(player, pCreature,600009, 1, 40);
                break;
			case 10000:
                RewardItem(player, pCreature,600005, 1, 40);
                break;
			
			
			}
			
			 return true;
        }

};

void AddSC_vip_set()
{
    new vip_set();
}
