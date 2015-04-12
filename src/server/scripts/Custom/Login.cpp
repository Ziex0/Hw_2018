#include "ScriptPCH.h"

#define CUSTOM_BLUE	 "|cff00479E"
#define CUSTOM_RED       "|cffFF0000"
#define CUSTOM_LIGHTRED  "|cffD63931"
#define CUSTOM_WHITE     "|cffffffff"

class announce_login : public PlayerScript
{
public:
	announce_login() : PlayerScript("announce_login") { }

	void OnPlayerLogin(Player* player, bool /*firstLogin*/)
	{
		char msg[500];
		if (player->GetTeam() == ALLIANCE)
		{
			sprintf(msg, "[%sATT|r]: %s%s|r has logged in !! [%sA|r]", CUSTOM_LIGHTRED, CUSTOM_WHITE, player->GetName().c_str(), CUSTOM_BLUE);
			sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
		}
		else{
			sprintf(msg, "[%sATT|r]: %s%s|r has logged in !! [%sH|r]", CUSTOM_LIGHTRED, CUSTOM_WHITE, player->GetName().c_str(), CUSTOM_RED);
			sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
		}
	}

	void OnPlayerLogout(Player* player)
	{
		char msg[500];
		if (player->GetTeam() == ALLIANCE)
		{
			sprintf(msg, "[%sATT|r]: %s%s|r has logged out ! [%sA|r]", CUSTOM_LIGHTRED, CUSTOM_WHITE, player->GetName().c_str(), CUSTOM_BLUE);
			sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
		}
		else{
			sprintf(msg, "[%sATT|r]: %s%s|r has logged out ! [%sH|r]", CUSTOM_LIGHTRED, CUSTOM_WHITE, player->GetName().c_str(), CUSTOM_RED);
			sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
		}
	}
};

void AddSC_announce_login()
{
	new announce_login();
}