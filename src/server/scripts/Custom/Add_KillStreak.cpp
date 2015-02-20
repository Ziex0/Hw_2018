/*
* Author: Ap Rose (Akamaran) Update by Zie
* Version: 1.0.1
* Contact: andra778@yahoo.com
*
* Build: Succeeded (2015)
* Rev: TrinityCore rev. d5d28057710e (3.3.5a - 12340)
* Copyright (C) 2008-2015 TrinityCore <http://www.trinitycore.org/>
*/

#include "ScriptPCH.h"
#include "Chat.h"

class System_OnKill : public PlayerScript
{
	public:
		System_OnKill() : PlayerScript("System_OnKill") {}

		void OnPVPKill(Player * Killer, Player * Victim)
		{
			uint64 KillerGUID = Killer->GetGUID();
			uint64 VictimGUID = Victim->GetGUID();
			std::ostringstream ss;
			struct KillStreak_Info{uint32 killstreak; uint64 lastkill;};
			static std::map<uint64, KillStreak_Info> KillStreakData;
			//Double Kill Check
			if (KillerGUID == VictimGUID || KillStreakData[KillerGUID].lastkill == VictimGUID) return;
			//Revenge Check
			if (KillerGUID == KillStreakData[VictimGUID].lastkill)
			{
				//Send Message (Revenge Earned)
				ChatHandler(Killer->GetSession()).PSendSysMessage("|cFF00FF00[CCR-PvP] You got revenge!");
				//Send Message (Revenged)
				ChatHandler(Victim->GetSession()).PSendSysMessage("|cFFFF0000[CCR-PvP] Your enemy got revenge!");
			}
			//Killstreak End
			if (KillStreakData[VictimGUID].killstreak > 9)
			{
				//Server Broadcast
				ss << "|cFF00FF00[CCR-PvP]|cFF81CF42[" << Killer->GetName() << "]|r has ended the streak of |cFF81CFCF[" << Victim->GetName() << "]|r and has earned 5 gold bounty!";
				sWorld->SendServerMessage(SERVER_MSG_STRING, ss.str().c_str());
				//Give Player Gold Reward (Bounty)
				Killer->SetMoney(Killer->GetMoney() + 50000);
				//Negative Check && 5 Gold Death Cost for Victim
				if ((Victim->GetMoney()) <50000){ Victim->SetMoney(0); }else{ Victim->SetMoney(Victim->GetMoney() - 50000); }
				//Send Notification
				Victim->GetSession()->SendAreaTriggerMessage("[CCR-PvP] Your killstreak has ended! (Cost 5G)");
				//Send Message (Killing Streak Ended)
				ChatHandler(Victim->GetSession()).PSendSysMessage("|cFFFF0000[CCR-PvP] Your killstreak has ended! (Cost 5G)");

			}
			//Update Information
			KillStreakData[KillerGUID].killstreak++; KillStreakData[KillerGUID].lastkill = VictimGUID;
			KillStreakData[VictimGUID].killstreak = 0; KillStreakData[VictimGUID].lastkill = 0;
			//Killstreak Check
			switch (KillStreakData[KillerGUID].killstreak)
			{
				case 5: case 10: case 20: case 30: case 40: case 50:
						//PvP Token
						Killer->AddItem(320284, 1);
						//Server Broadcast
						ss << "|cFFFF0000[CCR-PvP]|cFF81CF42[" << Killer->GetName() << "]|r has killed |cFF81CFCF[" << Victim->GetName() << "]|r and is at a " << (KillStreakData[KillerGUID].killstreak) << " man killstreak!";
						sWorld->SendServerMessage(SERVER_MSG_STRING, ss.str().c_str());
						//Give Player Gold Reward
						Killer->SetMoney(Killer->GetMoney() + (KillStreakData[KillerGUID].killstreak));
						//Send Notification
						ss << "|cFF00FF00[CCR-PvP] You are on a killing streak! You are awarded " << KillStreakData[KillerGUID].killstreak << " gold for your services!";
						Killer->GetSession()->SendAreaTriggerMessage(ss.str().c_str());
						//Send Message (Killing Streak)
						ChatHandler(Killer->GetSession()).PSendSysMessage(ss.str().c_str());
						//Negative Check && 50 Silver Death Cost for Victim
						if ((Victim->GetMoney()) <5000){ Victim->SetMoney(0); }else{ Victim->SetMoney(Victim->GetMoney() - 5000); }
						//Send Notification
						Victim->GetSession()->SendAreaTriggerMessage("|cFFFF0000[CCR-PvP] You died, 50 silver taken for medical costs.");
						//Send Message
						ChatHandler(Victim->GetSession()).PSendSysMessage("|cFFFF0000[CCR-PvP] You died, 50 silver taken for medical costs.");
				break;
					/* TODO :: Killstreak Auras
					 * Master Buff(Physical) - 35874
					 * Master Buff(Magical) - 35912
					 * Master Buff(Ranged) - 38734
					 */
				default :
						//Give Player Gold Reward (Default Reward)
						Killer->SetMoney(Killer->GetMoney() + 10000);
						Killer->GetSession()->SendAreaTriggerMessage("|cFF00FF00[CCR-PvP] You have killed enemy player! You are awarded 1 gold for your services!");
						//Send Message
						ChatHandler(Killer->GetSession()).PSendSysMessage("|cFF00FF00[CCR-PvP] You have killed enemy player! You are awarded 1 gold for your services!");
						//Negative Check && 50 Silver Death Cost for Victim
						if ((Victim->GetMoney()) <5000){ Victim->SetMoney(0); }else{ Victim->SetMoney(Victim->GetMoney() - 5000); }
						//Send Notification
						Victim->GetSession()->SendAreaTriggerMessage("|cFFFF0000[CCR-PvP] You have been killed, 50 silver taken for medical costs.");
						//Send Message
						ChatHandler(Victim->GetSession()).PSendSysMessage("|cFFFF0000[CCR-PvP] You have been killed, 50 silver taken for medical costs.");
				break;
			}
		}
};

void AddSC_PvP_System()
{
	new System_OnKill;
}