// Made By Sinistah/ToxicDev
 
enum config
{
    TOKEN = 320284, // Entry Id Of The Item Defined Here
    AMMOUNT = 1,    // Ammount Of The TOKEN's Given
    AREAIDONE = 1741, // Area Id For Location One
    AREAIDTWO = 3855, // Area Id For Location Two
	AREAIDTHREE = 3701
};  
 
class itemonkill : public PlayerScript
{
public: 
    itemonkill() : PlayerScript("itemonkill") { }
 
    void OnPVPKill(Player * killer, Player * victim)
    {
        if ((killer->GetAreaId() == AREAIDONE || killer->GetAreaId() == AREAIDTWO || killer->GetAreaId() == AREAIDTHREE) && killer->GetGUID() != victim->GetGUID())
        {
            if (killer->GetSession()->GetRemoteAddress() == victim->GetSession()->GetRemoteAddress())
                killer->GetSession()->SendNotification("[PvP System] Your Victim Has Same Ip Adress As You! No Reward Was Given.");
            else if (victim->HasAura(2479))
                killer->GetSession()->SendNotification("[PvP System] Your Victim Had Honorless Target Aura! No Reward Was Given");
            else
            {
                killer->GetSession()->SendNotification("[PvP System] You Were Rewarded For Killing %s!", victim->GetName());    
                killer->AddItem(TOKEN, AMMOUNT);
            }
        }
    }
};
 
void AddSC_itemonkill()
{
    new itemonkill;
}