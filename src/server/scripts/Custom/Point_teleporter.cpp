/////////////////////////////////////////////////////////////////////////////
//         			Developed by Zie For Thesatria.COm                     //
//                     Copyright (C) 2015 Zie                              //
//                          Thesatria.Com                                  //
/////////////////////////////////////////////////////////////////////////////

#include "ScriptPCH.h"
#include "Language.h"

class PointTele : public CreatureScript
{
public:
    PointTele() : CreatureScript("PointTele") { }
	
	struct universal_teleporterAI : public ScriptedAI
	{
		universal_teleporterAI(Creature *c) : ScriptedAI(c) {}

		void Reset()
		{
			me->RestoreFaction();
		}

		void EnterEvadeMode()
        {
            me->GetMotionMaster()->Clear();
            ScriptedAI::EnterEvadeMode();
        }
				void ReceiveEmote(Player *pPlayer, uint32 uiTextEmote)
		{
			if (pPlayer->isInCombat())
				{ pPlayer->GetSession()->SendAreaTriggerMessage("|cffff0000You are in combat!|r"); } 
				return;
		}
	};

	CreatureAI* GetAI(Creature* pCreature) const
    {
		return new universal_teleporterAI(pCreature);
    }

	void CreatureWhisperBasedOnBool(const char *text, Creature *pCreature, Player *pPlayer, bool value)
	{
		if (value)
			pCreature->MonsterWhisper(text, pPlayer->GetGUID());
	}
	
	void MainMenu(Player *pPlayer, Creature *pCreature)
	{	
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|cffFF0000|TInterface\\icons\\Achievement_Leader_Sylvanas:30|tIron Colossus ( World Boss)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 717);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|cffFF0000|TInterface\\icons\\Achievement_Leader_Sylvanas:30|tRaz the unforgiven ( World Boss)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 718);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|cffFF0000|TInterface\\icons\\Achievement_Leader_Sylvanas:30|tClyde the colossus ( World Boss)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 719);
	}
	
	bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
		MainMenu(pPlayer, pCreature);

        return true;
    }
	
	bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
		if (pPlayer->isInCombat())
		{
			pCreature->MonsterWhisper("You are in combat !!!!, wait until your combat is gone...ughhhhh .!!!", pPlayer->GetGUID());
			pPlayer->CLOSE_GOSSIP_MENU();

			return true;
		}

		pPlayer->PlayerTalkClass->ClearMenus();

		switch (uiAction)
		{
		
			//demonsoul
			case GOSSIP_ACTION_INFO_DEF + 717:
				if (pPlayer->HasItemCount( 320287, 1000, false ))
					{
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 8515.120117f, 792.216003f, 557.715027f, 1.537250f);
				pCreature->MonsterWhisper("Kill next Boss !!", pPlayer->GetGUID());
					}
				else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterWhisper("You need collect at last 500 Demon Soul to get teleport", pPlayer->GetGUID());
                    return false;
                }
                break;
			
			//golden
			case GOSSIP_ACTION_INFO_DEF + 718:
				if (pPlayer->HasItemCount( 320288, 500, false ))
					{
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1,-8628.698242f, 1973.565308f, 102.240532f , 0.356536f);
				pCreature->MonsterWhisper("Kill next Boss !!", pPlayer->GetGUID());
					}
				else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterWhisper("You need collect at last 500 Golden pearl to get teleport", pPlayer->GetGUID());
                    return false;
                }
                break;
				
			//golden
			case GOSSIP_ACTION_INFO_DEF + 719:
				if (pPlayer->HasItemCount( 320289, 500, false ))
					{
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(533, 3598.094727f, -4522.896484f ,200.513214f , 4.330854f);
				pCreature->MonsterWhisper("Kill next Boss !!", pPlayer->GetGUID());
					}
				else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterWhisper("You need collect at last 500 Black Diamond to get teleport", pPlayer->GetGUID());
                    return false;
                }
                break;
		}
			return true;
	}
};

void AddSc_PointTele()
{
	new PointTele();
}
	
	