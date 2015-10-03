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
		player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_CHAT, "* |cff00ff00|TInterface\\icons\\spell_holy_fanaticism:30|t|r Exchange 1000 PVP Donation Coin to 1 DP ", GOSSIP_SENDER_MAIN, 1, "|cffFFFFFF Change 200VP to 1DP|r", 0, false);
		player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_CHAT, "* |cff00ff00|TInterface\\icons\\spell_holy_fanaticism:30|t|r Exchange 2000 PVP Donation Coin to 4 DP ", GOSSIP_SENDER_MAIN, 2, "|cffFFFFFF Change 500VP to 5DP|r", 0, false);
		player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_CHAT, "* |cff00ff00|TInterface\\icons\\spell_holy_fanaticism:30|t|r Exchange 3000 PVP Donation Coin to 8 DP ", GOSSIP_SENDER_MAIN, 3, "|cffFFFFFF Change 800VP to 10DP|r", 0, false);
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
				if(!ExchangeToDP(player, 1000, 1))
					sprintf(str, "You dont have enough PVP Donation Coin");
				else
					sprintf(str, "You have changed 1000 to 2 DP, congratulations");

				player->MonsterWhisper(str, player->GetGUID(), true);
				ReturnToMainMenu(player, creature);
				break;
			case 2:
				if(!ExchangeToDP(player, 2000, 4))
					sprintf(str, "You dont have PVP Donation Coin");
				else
					sprintf(str, "You have changed 2000 PVP Donation Coin to 4 DP, congratulations");

				player->MonsterWhisper(str, player->GetGUID(), true);
				ReturnToMainMenu(player, creature);
				break;
			case 3:
				if(!ExchangeToDP(player, 3000, 8))
					sprintf(str, "You dont have enough PVP Donation Coin");
				else
					sprintf(str, "You have changed 3000 PVP Donation Coin to 8 DP, congratulations");

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