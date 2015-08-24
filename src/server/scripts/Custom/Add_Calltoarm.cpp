#include "ScriptPCH.h"


bool WSGisActive;
bool ABisActive;
bool EOTSisActive;

	
class cta_npc : public CreatureScript
{
public:
	cta_npc() : CreatureScript("cta_npc") { }

	bool OnGossipHello(Player* player, Creature* creature)
	{
	GameEventMgr::GameEventDataMap const& events = sGameEventMgr->GetEventMap();
	GameEventMgr::ActiveEvents const& activeEvents = sGameEventMgr->GetActiveEventList();



	if(activeEvents.find(19) != activeEvents.end())
	{
		WSGisActive = true;
	}

	if(activeEvents.find(20) != activeEvents.end())
	{
		ABisActive = true;
	}

	if(activeEvents.find(21) != activeEvents.end())
	{
		EOTSisActive = true;
	}

	if(activeEvents.find(19) == activeEvents.end())
	{
		WSGisActive = false;
	}

	if(activeEvents.find(20) == activeEvents.end())
	{
		ABisActive = false;
	}
	if(activeEvents.find(21) == activeEvents.end())
	{
		EOTSisActive = false;
	}

		if(WSGisActive == false && ABisActive == false && EOTSisActive == false) {
		player->ADD_GOSSIP_ITEM(9, "|cff00ff00|TInterface\\icons\\Achievement_BG_winWSG:30|t|r Start Warsong Gulch Call to Arms [2500 Honor]", GOSSIP_SENDER_MAIN, 2);
		}
		else if(WSGisActive == true && ABisActive == false && EOTSisActive == false) {
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "WSG Call To Arms Is In Progress ...", GOSSIP_SENDER_MAIN, 5);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Stop Warsong Gulch Call To Arms [5000 Honor]", GOSSIP_SENDER_MAIN, 200);
		}
		if(ABisActive == false && WSGisActive == false && EOTSisActive == false) {
		player->ADD_GOSSIP_ITEM(9, "|cff00ff00|TInterface\\icons\\Achievement_BG_takeXflags_AB:30|t|r Start Arathi Basin Call To Arms [2500 Honor]", GOSSIP_SENDER_MAIN, 3);
		
		} 
		else if(ABisActive == true && WSGisActive == false && EOTSisActive == false) {
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Arathi Basin Call To Arms Is In Progress ...", GOSSIP_SENDER_MAIN, 6);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Stop Arathi Basin Call To Arms [5000 Honor]", GOSSIP_SENDER_MAIN, 300);
		}
		if(EOTSisActive == false && ABisActive == false && WSGisActive == false) {
		player->ADD_GOSSIP_ITEM(9, "|cff00ff00|TInterface\\icons\\Achievement_BG_winEOS:30|t|r Start Eye of the Storm Call To Arms [2500 Honor]", GOSSIP_SENDER_MAIN, 4);

		}
		else if(EOTSisActive == true && ABisActive == false && WSGisActive == false) {
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Eye of the Storm Call To Arms Is In Progress ...", GOSSIP_SENDER_MAIN, 7);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Stop Eye of the Storm Call To Arms [5000 Honor]", GOSSIP_SENDER_MAIN, 400);
		}
		if(EOTSisActive == true && ABisActive == true && WSGisActive == true) {
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Error: Please Contact a Gamemaster or Developer!", GOSSIP_SENDER_MAIN, 100);
		}
		player->PlayerTalkClass->SendGossipMenu(1, creature->GetGUID());
		return true;
	}


	bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
	{
		std::string alert = "";
		switch(action)
		{
		case 2:
			if(player->GetHonorPoints() >= 2500)
			{
				sGameEventMgr->StartEvent(19, true);
				player->SetHonorPoints(player->GetHonorPoints() - 2500);
				alert += player->GetName();
				alert += " has started Warsong Gulch - Call to Arms!";
				
			}
			else
				player->GetSession()->SendNotification("You do not have enough honor to start this Call to Arms!");
		break;
		
		case 3:
			if(player->GetHonorPoints() >= 2500)
			{
				sGameEventMgr->StartEvent(20, true);
				player->SetHonorPoints(player->GetHonorPoints() - 2500);
				alert += player->GetName();
				alert += " has started Arathi Basin - Call to Arms!";
				
			}
			else
				player->GetSession()->SendNotification("You do not have enough honor to start this Call to Arms!");
		break;

		case 4:
			if(player->GetHonorPoints() >= 2500)
			{
				sGameEventMgr->StartEvent(21, true);
				player->SetHonorPoints(player->GetHonorPoints() - 2500);
				alert += player->GetName();
				alert += " has started Eye of the Storm - Call to Arms!";
			}
			else
				player->GetSession()->SendNotification("You do not have enough honor to start this Call to Arms!");
		break;

		case 200:
			if(player->GetHonorPoints() >= 5000)
			{
				WSGisActive = false;
				sGameEventMgr->StopEvent(19, true);
				player->SetHonorPoints(player->GetHonorPoints() - 5000);
				alert += player->GetName();
				alert += " has ended Warsong Gulch - Call To Arms!";
			}
			else
				player->GetSession()->SendNotification("You do not have enough honor to end this Call to Arms!");
			break;

			case 300:
			if(player->GetHonorPoints() >= 5000)
			{
				ABisActive = false;
				sGameEventMgr->StopEvent(20, true);
				player->SetHonorPoints(player->GetHonorPoints() - 5000);
				alert += player->GetName();
				alert += " has ended Arathi Basin - Call To Arms!";
			}
			else
				player->GetSession()->SendNotification("You do not have enough honor to end this Call to Arms!");
			break;

			case 400:
			if(player->GetHonorPoints() >= 5000)
			{
				EOTSisActive = false;
				sGameEventMgr->StopEvent(21, true);
				player->SetHonorPoints(player->GetHonorPoints() - 5000);
				alert += player->GetName();
				alert += " has ended Eye of the Storm - Call To Arms!";
			}
			else
				player->GetSession()->SendNotification("You do not have enough honor to end this Call to Arms!");
			break;



		sWorld->SendServerMessage(SERVER_MSG_STRING, alert.c_str(), 0);
		}
		return true;
		
	}
};

void AddSC_cta_npc()
{
new cta_npc();
}