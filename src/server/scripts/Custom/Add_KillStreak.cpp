#include "ScriptPCH.h"
#include "Language.h"

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
		char msg[500];
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
			case 1:
			sprintf(msg, "|cffFF0000%s|cffFFFF05 killed |cffFF0000%s|cffFFFF05 and is on a |cffFF0001|cffFFFF05 1st Streak !! ", pKiller->GetName(), pVictim->GetName());
			sWorld->SendWorldText(LANG_SYSTEMMESSAGE, msg);
			pKiller->ModifyHonorPoints(1);
			//pKiller->CastSpell(pKiller, 24378, true);
			break;
			
			case 10:
			sprintf(msg, "|cffFF0000%s|cffFFFF05 killed |cffFF0000%s|cffFFFF05 and is on a |cffFF00010|cffFFFF05 kill streak !! ", pKiller->GetName(), pVictim->GetName());
			sWorld->SendWorldText(LANG_SYSTEMMESSAGE, msg);
			pKiller->ModifyHonorPoints(10);
			//pKiller->CastSpell(pKiller, 24378, true);
			break;

			case 25:
			sprintf(msg, "|cffFF0000%s|cffFFFF05 killed |cffFF0000%s|cffFFFF05 and is on a |cffFF000025|cffFFFF05 kill streak!!", pKiller->GetName(), pVictim->GetName());
			sWorld->SendWorldText(LANG_SYSTEMMESSAGE, msg);
			pKiller->ModifyHonorPoints(25);
			//pKiller->CastSpell(pKiller, 24378, true);
			break;

			case 50:
			sprintf(msg, "|cffFF0000%s|cffFFFF05 killed |cffFF0000%s|cffFFFF05 and is on a |cffFF000050|cffFFFF05 kill streak!!", pKiller->GetName(), pVictim->GetName());
			sWorld->SendWorldText(LANG_SYSTEMMESSAGE, msg);
			pKiller->ModifyHonorPoints(50);
			//pKiller->CastSpell(pKiller, 24378, true);
			break;

			case 100:
			sprintf(msg, "|cffFF0000%s|cffFFFF05 killed |cffFF0000%s|cffFFFF05 and is on a |cffFF0000100|cffFFFF05 kill streak!!", pKiller->GetName(), pVictim->GetName());
			sWorld->SendWorldText(LANG_SYSTEMMESSAGE, msg);
			pKiller->ModifyHonorPoints(100);
			//pKiller->CastSpell(pKiller, 24378, true);
			break;

			case 250:
			sprintf(msg, "|cffFF0000%s|cffFFFF05 killed |cffFF0000%s|cffFFFF05 and is on a |cffFF0000250|cffFFFF05 kill streak!!", pKiller->GetName(), pVictim->GetName());
			sWorld->SendWorldText(LANG_SYSTEMMESSAGE, msg);
			pKiller->AddItem(23247, 25);
			KillingStreak[kGUID].KillStreak = 0;
			pKiller->ModifyHonorPoints(250);
			//pKiller->CastSpell(pKiller, 24378, true);
			break;
			
			}
	}
	
};

void AddSC_System_kill()
{
    new System_OnPvPKill();
}