#include "ScriptPCH.h"

class System_OnPvPKill : public PlayerScript
{
	public:
		System_OnPvPKill() : PlayerScript("System_OnPvPKill") {}

	struct SystemInfo
	{
		uint32 KillStreak;
		uint32 LastGUIDKill;
	};

static std::map<uint32, SystemInfo> KillingStreak;
	
void OnPvPKill(Player *pKiller, Player *pVictim)
	{
		uint32 kGUID; 
		uint32 vGUID;
		kGUID = pKiller->GetGUID();
		vGUID = pVictim->GetGUID();	
		if(kGUID == vGUID)
		{
			return;
		}
		if(KillingStreak[kGUID].LastGUIDKill == vGUID)
		{
			return;
		}
		
		KillingStreak[kGUID].KillStreak++;
		KillingStreak[vGUID].KillStreak = 0;
		KillingStreak[kGUID].LastGUIDKill = vGUID;
		KillingStreak[vGUID].LastGUIDKill = 0;
		
	switch(KillingStreak[kGUID].KillStreak)
		{
			char msg[200]; 
				{
					case 10:
					sprintf(msg, "[|cffFF8000PvP System]: %s killed %s and is on a 10 kill streak. ", pKiller->GetName(), pVictim->GetName());
						break;

					case 15:
					sprintf(msg, "[|cffFF8000PvP System]: %s killed %s and is on a 15 kill streak. ", pKiller->GetName(), pVictim->GetName());
						break;

					case 25:
					sprintf(msg, "[|cffFF8000PvP System]: %s killed %s and is on a 25 kill streak. ", pKiller->GetName(), pVictim->GetName());
						break;

					case 50:
					sprintf(msg, "[|cffFF8000PvP System]: Wow, %s killed %s is already on a 50 kill streak. ", pKiller->GetName(), pVictim->GetName());
						break;

					case 100:
					sprintf(msg, "[|cffFF8000PvP System]: Wow, %s killed %s is already on a 100 kill streak. ", pKiller->GetName(), pVictim->GetName());
						break;
					
					case 150:
					sprintf(msg, "[|cffFF8000PvP System]: Amazing! %s killed %s and is on a 150 kill streak. ", pKiller->GetName(), pVictim->GetName());
						break;
						
					case 200:
					sprintf(msg, "[|cffFF8000PvP System]: Amazing! %s killed %s and is on a 200 kill streak. ", pKiller->GetName(), pVictim->GetName());
						break;
						
					case 250:
					sprintf(msg, "[|cffFF8000PvP System]: Incredible! %s killed %s and is on a 250 kill streak!!! No One can STOP THIS TERROR?? ", pKiller->GetName(), pVictim->GetName());
						break;
				}
	
			sWorld->SendServerMessage(SERVER_MSG_STRING, msg, 0);
		}
	}
};

void AddSC_System_KillingStreak()
{
    new System_OnPvPKill();
}