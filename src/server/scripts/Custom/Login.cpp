class player_login_announcer : public PlayerScript
{
public:
    player_login_announcer() : PlayerScript("player_login_announcer") { }
 
    void OnLogin(Player* player)
    {
        std::ostringstream ss;		
        switch (player->GetSession()->GetSecurity())
        {
            case SEC_PLAYER:
                ss << "[PLAYER] " << player->GetName() << " has logged in!";				
                break;
           
        }
        sWorld->SendGMText(LANG_SYSTEM_DEFAULT, ss.str().c_str());
    }
};
 
void AddSC_login_announcer()
{
    new player_login_announcer();
}