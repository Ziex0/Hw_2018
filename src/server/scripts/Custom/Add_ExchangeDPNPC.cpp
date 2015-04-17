#include "ScriptPCH.h"


class ExchangeDPNPC : public CreatureScript
{
    public: ExchangeDPNPC() : CreatureScript("ExchangeDPNPC") { }

	uint32 GetVP(Player* player) 
	 {
		uint32 points;

		QueryResult result = LoginDatabase.PQuery("SELECT vp FROM web_db.account_data WHERE id = '%u' AND vp >= '0'", player->GetSession()->GetAccountId());
        if (result)
        {
            do 
            {
				points = result->Fetch()->GetInt32();

			} while (result->NextRow());
		}
		else
			points = 0;

		 return points;
	 }

	 uint32 GetDP(Player* player) 
	 {
		uint32 points;

		QueryResult result = LoginDatabase.PQuery("SELECT dp FROM web_db.account_data WHERE id = '%u' AND dp >= '0'", player->GetSession()->GetAccountId());
        if (result)
        {
            do 
            {
				points = result->Fetch()->GetInt32();

			} while (result->NextRow());
		}
		else
			points = 0;

		 return points;
	 }

	 bool ExchangeToVP(Player* player, uint32 dp, uint32 vp)
	 {
		 if(GetDP(player) < dp)
			 return false;

		 LoginDatabase.PQuery("Update web_db.account_data Set dp = dp - '%u' WHERE id = '%u'", dp, player->GetSession()->GetAccountId());

		 LoginDatabase.PQuery("Update web_db.account_data Set vp = vp + '%u' WHERE id = '%u'", vp, player->GetSession()->GetAccountId());

		 return true;
	 }

	 bool ExchangeToDP(Player* player, uint32 vp, uint32 dp)
	 {
		 if(GetVP(player) < vp)
			 return false;

		 LoginDatabase.PQuery("Update web_db.account_data Set vp = vp - '%u' WHERE id = '%u'", vp, player->GetSession()->GetAccountId());

		 LoginDatabase.PQuery("Update web_db.account_data Set dp = dp + '%u' WHERE id = '%u'", dp, player->GetSession()->GetAccountId());

		 return true;
	 }

	bool OnGossipHello(Player* player, Creature* pCreature)
	{
		player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_CHAT, "* |cff00FF21 Exchange 100VP to 1DP",			GOSSIP_SENDER_MAIN, 1, "|cffFFFFFF Change 100VP to 1DP|r", 0, false);
		player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_CHAT, "* |cff00FF21 Exchange 200VP to 5DP *",			GOSSIP_SENDER_MAIN, 7, "|cffFFFFFF Change 200VP to 5DP|r", 0, false);
		player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_CHAT, "* |cff00FF21 Exchange 300VP to 10DP *",			GOSSIP_SENDER_MAIN, 6, "|cffFFFFFF Change 300VP to 10DP|r", 0, false);
		player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_CHAT, "* |cff00FF21 Exchange 400VP to 25DP *",			GOSSIP_SENDER_MAIN, 2, "|cffFFFFFF Change 400VP to 25DP|r", 0, false);
		player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_CHAT, "* |cffFFD800 Exchange 500VP to 30DP *",			GOSSIP_SENDER_MAIN, 3, "|cffFFFFFF Change 500VP to 30DP|r", 0, false);
		player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_CHAT, "* |cff0094FF Exchange 600VP to 35DP *",			GOSSIP_SENDER_MAIN, 4, "|cffFFFFFF Change 600VP to 35DP|r", 0, false);
		player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_CHAT, "* |cffFF0000 Exchange Massive 2200VP to 150DP *",	GOSSIP_SENDER_MAIN, 5, "|cffFFFFFF Change Massive 2200VP to 150DP|r", 0, false);
		player->PlayerTalkClass->SendGossipMenu(90701, pCreature->GetGUID());
        return true;
	}

	 void ReturnToMainMenu(Player* player, Creature* creature)
	 {
		player->PlayerTalkClass->ClearMenus();
	    OnGossipHello(player, creature);
	 }

	 char str[255];

	 bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
     {
		player->PlayerTalkClass->ClearMenus();

		switch (uiAction)
		{
			case 0:
				ReturnToMainMenu(player, creature);
				break;
			case 1:
				if(!ExchangeToDP(player, 100, 1))
					sprintf(str, "You dont have enough vote points");
				else
					sprintf(str, "You have changed 100vp to 1dp, congratulations");

				player->MonsterWhisper(str, player->GetGUID(), true);
				ReturnToMainMenu(player, creature);
				break;
			case 2:
				if(!ExchangeToDP(player, 400, 25))
					sprintf(str, "You dont have enough vote points");
				else
					sprintf(str, "You have changed 400VP to 25DP, congratulations");

				player->MonsterWhisper(str, player->GetGUID(), true);
				ReturnToMainMenu(player, creature);
				break;
			case 3:
				if(!ExchangeToDP(player, 500, 30))
					sprintf(str, "You dont have enough vote points");
				else
					sprintf(str, "You have changed 500VP to 30DP, congratulations");

				player->MonsterWhisper(str, player->GetGUID(), true);
				ReturnToMainMenu(player, creature);
				break;
			case 4:
				if(!ExchangeToDP(player, 600, 35))
					sprintf(str, "You dont have enough vote points");
				else
					sprintf(str, "You have changed 600VP to 35DP, congratulations");

				player->MonsterWhisper(str, player->GetGUID(), true);
				ReturnToMainMenu(player, creature);
				break;
			case 5:
				if(!ExchangeToDP(player, 2200, 150))
					sprintf(str, "You dont have enough vote points");
				else
					sprintf(str, "You have changed 2200VP to 150DP, congratulations Hero !!");

				player->MonsterWhisper(str, player->GetGUID(), true);
				ReturnToMainMenu(player, creature);
				break;
			case 6:
				if(!ExchangeToDP(player, 300, 10))
					sprintf(str, "You dont have enough vote points");
				else
					sprintf(str, "You have changed 300VP to 10DP, congratulations Hero !!");

				player->MonsterWhisper(str, player->GetGUID(), true);
				ReturnToMainMenu(player, creature);
				break;
			case 7:
				if(!ExchangeToDP(player, 200, 5))
					sprintf(str, "You dont have enough vote points");
				else
					sprintf(str, "You have changed 200VP to 5DP, congratulations Hero !!");

				player->MonsterWhisper(str, player->GetGUID(), true);
				ReturnToMainMenu(player, creature);
				break;
		}
		return true;
	 }
};

void AddSC_ExchangeDPNPC()
{
    new ExchangeDPNPC();
}