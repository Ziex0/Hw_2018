/*
 *╔═╦═╦═╦╦╦══╦═╦╗─╔╦══╗
 *║╦╣║║║║║╠╗╗║╦╣╚╦╝║══╣
 *║╩╣║║║║║╠╩╝║╩╬╗║╔╬══║
 *╚═╩╩═╩╩═╩══╩═╝╚═╝╚══╝
 *            www.emudevs.com
*/
struct PlayerAbuse
{
    uint64 victimGUID;
    uint32 whenKilled;
};
 
std::map<uint64, PlayerAbuse> abuseList;
 
class kill_player_abuse : PlayerScript
{
public:
    kill_player_abuse() : PlayerScript("kill_player_abuse") { }
 
    void OnPVPKill(Player* killer, Player* victim)
    {
        if (killer->GetGUID() == victim->GetGUID())
            return;
 
        if (!abuseList.empty())
        {
            for (std::map<uint64, PlayerAbuse>::const_iterator itr = abuseList.begin(); itr != abuseList.end(); ++itr)
            {
                if (itr->first == killer->GetGUID() && itr->second.victimGUID == victim->GetGUID()) // Initial check
                {
                    if (GetMSTimeDiffToNow(itr->second.whenKilled) < 180000) // < 3 minutes 180000
                    {   // The player won't be able to kill the same player for another 3 minutes
                        ChatHandler(killer->GetSession()).PSendSysMessage("You cannot kill this player for another %u minute(s).", CalculateTimeInMinutes(GetMSTimeDiffToNow(itr->second.whenKilled)));
                        return;
                    }
                    else
                        abuseList.erase(killer->GetGUID());
                }
            }
        }
        // Adding the killer/victimGUID to the abuse list
        abuseList[killer->GetGUID()].victimGUID = victim->GetGUID();
        abuseList[killer->GetGUID()].whenKilled = getMSTime();
 
        /* You can add other code beyond this point */
    }
 
    uint32 CalculateTimeInMinutes(uint32 m_time)
    {
        uint32 howManyMinutes;
        if (m_time >= 180000) // 180000 = 3 minutes
            howManyMinutes = 3;
        else if (m_time < 180000-60000)
            howManyMinutes = 2;
        else if (m_time > 180000-60000)
            howManyMinutes = 1;
        return howManyMinutes;
    }
};
 
void AddSC_player_abuse()
{
    new kill_player_abuse();
}