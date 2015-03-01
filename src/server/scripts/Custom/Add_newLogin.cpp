#include "ScriptPCH.h"

class on_login : public PlayerScript
{
    public:
        on_login() : PlayerScript("on_login") {}

    void OnLogin(Player* player)
    {
        ChatHandler(player->GetSession()).PSendSysMessage("Welcome back online! Your character has been saved to the database, buffed and healed! Now remember to vote every 12 hours on www.thesatria.com!");
	    player->GetSession()->SendNotification("WELCOME BACK ONLINE ");
	    
	 }
};

void AddSC_on_login()
{
    new on_login();
}