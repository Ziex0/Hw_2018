#include "ScriptPCH.h"

#define SONG 13473

class on_login : public PlayerScript
{
    public:
        on_login() : PlayerScript("on_login") {}

    void OnLogin(Player* player)
    {
            ChatHandler(player->GetSession()).PSendSysMessage("Welcome back online! Your character has been saved to the database, buffed and healed! Now remember to vote every 12 hours on www.unforgivenwow.com!");
	     player->GetSession()->SendNotification("WELCOME BACK ONLINE ");
	     player->GetSession()->SendNotification("! %s !", player->GetName());

	     //player->SetXpRate(1);	     

	     if (player->GetMap()->IsBattlegroundOrArena())
	     {
	     	  player->ResurrectPlayer(0.5f);
	         player->TeleportTo(0, 1610.99f, -5526.4f, 111.158f, 1.00078f);
	     }

	     /*QueryResult result = CharacterDatabase.PQuery("SELECT first_login FROM characters WHERE guid = '%u'", player->GetGUID());
 
	     Field* fields = result->Fetch();
	     uint8 flag = fields[0].GetUInt8();

            if (player->HasFlag)
            {
		  player->CastSpell(player, 11543, 1);
		  player->PlayDirectSound(11466, player);
		  CharacterDatabase.PExecute("UPDATE characters set first_login = 1 WHERE guid = '%u'", player->GetGUID());
            }*/
    }
};

void AddSC_on_login()
{
    new on_login();
}