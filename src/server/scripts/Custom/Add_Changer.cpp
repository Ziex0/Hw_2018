#include "ScriptPCH.h"

enum  defines
{
	faction_token = 29, // Faction Change Token
	race_token = 30, // Race Change Token
	customize_token = 31, // Customize Change Token
};

class npc_changer : public CreatureScript
{
	public:
		npc_changer() : CreatureScript("npc_changer"){}

		bool OnGossipHello(Player * pPlayer, Creature * pCreature)
		{
						
			//pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Achievement_Boss_Valanar:24|t|r Change My Race ", GOSSIP_SENDER_MAIN, 0);
		    //pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Achievement_Boss_Valanar:24|t|r Change My Faction", GOSSIP_SENDER_MAIN, 1);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Achievement_Boss_Valanar:24|t|r Customize My Char", GOSSIP_SENDER_MAIN, 2);
			pPlayer->PlayerTalkClass->SendGossipMenu(9425, pCreature->GetGUID());
			return true;
		}

		bool OnGossipSelect(Player * Player, Creature * Creature, uint32 /*uiSender*/, uint32 uiAction)
		{
			if(!Player)
				return true;

			switch(uiAction)
			{
				case 0:
					if(Player->HasItemCount(race_token, 1))
					{
						Player->DestroyItemCount(race_token, 1, true, false);
						Player->SetAtLoginFlag(AT_LOGIN_CHANGE_RACE);
						Player->GetSession()->SendNotification("You need to re - login, to change your race!");
						Player->PlayerTalkClass->SendCloseGossip();
					}
					else
					{
						Player->GetSession()->SendNotification("You need at least one race change token!");
						Player->PlayerTalkClass->SendCloseGossip();
					}
					break;
				case 1:
					if(Player->HasItemCount(faction_token, 1))
					{
						Player->DestroyItemCount(faction_token, 1, true, false);
						Player->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);
						Player->GetSession()->SendNotification("You need to re - login, to change your faction!");
						Player->PlayerTalkClass->SendCloseGossip();
					}
					else
					{
						Player->GetSession()->SendNotification("You need at least one faction change token!");
						Player->PlayerTalkClass->SendCloseGossip();
					}
					break;
				case 2:
					if(Player->HasItemCount(customize_token, 1))
					{
						Player->DestroyItemCount(faction_token, 1, true, false);
						Player->SetAtLoginFlag(AT_LOGIN_CUSTOMIZE);
						Player->GetSession()->SendNotification("re - login to do your customizer!");
						Player->PlayerTalkClass->SendCloseGossip();
					}
					else
					{
						Player->GetSession()->SendNotification("You need at least one Customize change token!");
						Player->PlayerTalkClass->SendCloseGossip();
					}
					break;
			}
			return true;
		}

};

void AddSC_npc_changer()
{
	new npc_changer();
}