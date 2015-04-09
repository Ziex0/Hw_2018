#include "ScriptPCH.h"
#include <stdio.h>
#include <stdlib.h>
#include "../../game/CityConquest/CityConquestMgr.h"

struct city_conquest_genericAI : public ScriptedAI
{
    city_conquest_genericAI(Creature *c) : ScriptedAI(c)
	{
		sLog->outInfo(LOG_FILTER_SERVER_LOADING,"CQM: Generic creature loaded to world - %u", me->GetEntry());
		CityConquest.RegisterCreature(me, 0);
	}

    void Reset()
    {

    }

    void EnterCombat(Unit* pWho)
    {

    }

    void EnterEvadeMode()
    {
    }

    void UpdateAI(uint32 diff)
    {
        DoMeleeAttackIfReady();
    }
};

class city_conquest_generic : public CreatureScript
{
public:
    city_conquest_generic() : CreatureScript("city_conquest_generic") { }

	CreatureAI *GetAI(Creature *creature) const
    {
    return new city_conquest_genericAI (creature);
	}

};

void AddSC_city_conquest_generic()
{

    new city_conquest_generic;

}
