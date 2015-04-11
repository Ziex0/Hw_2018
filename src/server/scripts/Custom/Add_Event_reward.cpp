#include "ScriptPCH.h"

const uint32 EVENT_TOKEN = 340005;

class Event_Vendor : public CreatureScript
{
	public:
		Event_Vendor() : CreatureScript("Events"){}

		bool OnGossipHello(Player * pPlayer, Creature * pCreature)
		{
			pPlayer->ADD_GOSSIP_ITEM(7, "I would like to view the titles.", GOSSIP_SENDER_MAIN, 0);
			//pPlayer->ADD_GOSSIP_ITEM(7, "Tata :D", GOSSIP_SENDER_MAIN, 1);
			pPlayer->PlayerTalkClass->SendGossipMenu(900, pCreature->GetGUID());
			return true;
		}

		bool OnGossipSelect(Player * pPlayer, Creature * pCreature, uint32 sender, uint32 uiAction)
		{
			pPlayer->PlayerTalkClass->ClearMenus();
			std::string name;
			switch(uiAction)
			{
				case 0:
					name = pPlayer->GetName();
					pPlayer->ADD_GOSSIP_ITEM(10, "Each Title costs 1 event token", GOSSIP_SENDER_MAIN, 8888);
					pPlayer->ADD_GOSSIP_ITEM(4, name + " Hand of A'dal", GOSSIP_SENDER_MAIN, 64);
					pPlayer->ADD_GOSSIP_ITEM(4, name + " the Seeker", GOSSIP_SENDER_MAIN, 81);
					pPlayer->ADD_GOSSIP_ITEM(4, name + " of the Ten Storms", GOSSIP_SENDER_MAIN, 86);
					pPlayer->ADD_GOSSIP_ITEM(4, name + " of the Emerald Dream", GOSSIP_SENDER_MAIN, 87);
					pPlayer->ADD_GOSSIP_ITEM(4, name + " of Khaz Modan", GOSSIP_SENDER_MAIN, 112);
					pPlayer->ADD_GOSSIP_ITEM(4, name + " the Lion Hearted", GOSSIP_SENDER_MAIN, 114);
					pPlayer->ADD_GOSSIP_ITEM(4, name + " the Forsaken", GOSSIP_SENDER_MAIN, 119);
					pPlayer->ADD_GOSSIP_ITEM(4, name + " the Magic Seeker", GOSSIP_SENDER_MAIN, 120);
					pPlayer->ADD_GOSSIP_ITEM(4, name + " of the Nightfall", GOSSIP_SENDER_MAIN, 140);
					pPlayer->ADD_GOSSIP_ITEM(4, name + " the Immortal", GOSSIP_SENDER_MAIN, 141);
					pPlayer->ADD_GOSSIP_ITEM(4, name + " the Undying", GOSSIP_SENDER_MAIN, 142);       
					pPlayer->ADD_GOSSIP_ITEM(4, name + " the Insane", GOSSIP_SENDER_MAIN, 145);      
					pPlayer->ADD_GOSSIP_ITEM(4, name + " the Astral Walker", GOSSIP_SENDER_MAIN, 165);
					pPlayer->ADD_GOSSIP_ITEM(4, name + " Herald of the Titans", GOSSIP_SENDER_MAIN, 166);       
					pPlayer->ADD_GOSSIP_ITEM(4, "Flame Keeper " + name, GOSSIP_SENDER_MAIN, 76);                          
					pPlayer->ADD_GOSSIP_ITEM(4, "Stalker " + name, GOSSIP_SENDER_MAIN, 91);            
					pPlayer->ADD_GOSSIP_ITEM(4, "Assassin " + name, GOSSIP_SENDER_MAIN, 95);
					pPlayer->ADD_GOSSIP_ITEM(4, "Merrymaker " + name, GOSSIP_SENDER_MAIN, 134);
					pPlayer->ADD_GOSSIP_ITEM(4, "Bloodsail Admiral " + name, GOSSIP_SENDER_MAIN, 144);
					pPlayer->ADD_GOSSIP_ITEM(4, "Starcaller " + name, GOSSIP_SENDER_MAIN, 164);
					pPlayer->PlayerTalkClass->SendGossipMenu(20000, pCreature->GetGUID());
					break;
				case 1:
					pPlayer->GetSession()->SendListInventory(pCreature->GetGUID());
					break;
				case 8888:
					OnGossipSelect(pPlayer, pCreature, GOSSIP_SENDER_MAIN, 0);
					break;
				default:
					if(pPlayer->HasItemCount(EVENT_TOKEN, 1))
					{
						CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(uiAction);
						if(!titleInfo)
							return false;
						pPlayer->SetTitle(titleInfo, false);
						pCreature->MonsterWhisper("Enjoy your new title!", pPlayer->GetGUID());
						pPlayer->DestroyItemCount(EVENT_TOKEN, 20, true);
						pPlayer->PlayerTalkClass->SendCloseGossip();
					}
					break;
			}
			return true;
		}
};

void AddSC_Event_Vendor()
{
	new Event_Vendor();
}