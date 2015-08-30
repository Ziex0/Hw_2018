/*
 *╔═╦═╦═╦╦╦══╦═╦╗─╔╦══╗ 
 *║╦╣║║║║║╠╗╗║╦╣╚╦╝║══╣
 *║╩╣║║║║║╠╩╝║╩╬╗║╔╬══║
 *╚═╩╩═╩╩═╩══╩═╝╚═╝╚══╝
 *           (http://emudevs.com)
 GameObject: (Burning Tree;191160)
 GameObject: (Burning Blaze;190570) - Deals Damage if near
 NPC DisplayID: 24905
*/
enum SpellIds
{
/*     NAME                       SPELLID    CAST-TIME     DAMAGE   */
    SPELL_FIREBALL               = 70282, //  3 sec       6198-7202
    SPELL_FIRE_SPIT              = 66796, //  1 sec       5088-5912
    SPELL_BLAST_NOVA             = 74392, //  2 sec       5688-7312
};

enum EventIds
{
    EVENT_NONE,
    EVENT_FIREBALL,
    EVENT_FIRE_SPIT,
    EVENT_BLAST_NOVA,
    EVENT_SPAWN_FIRE,
    EVENT_SPAWN_FIRE_CLEANUP
};

class npc_battle : public CreatureScript
{
public:
    npc_battle() : CreatureScript("npc_battle") { }

    struct npc_battleAI : public ScriptedAI
    {
        npc_battleAI(Creature* creature) : ScriptedAI(creature) { }

        void Reset()
        {
            events.Reset();
            events.ScheduleEvent(EVENT_FIREBALL, urand(6000, 11000));
            events.ScheduleEvent(EVENT_FIRE_SPIT, urand(2000, 9000));
            events.ScheduleEvent(EVENT_BLAST_NOVA, urand(10000, 19000));
            events.ScheduleEvent(EVENT_SPAWN_FIRE, urand(30000, 38000));
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                    case EVENT_FIREBALL:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                            DoCast(target, SPELL_FIREBALL);
                        events.ScheduleEvent(EVENT_FIREBALL, urand(6000, 11000));
                        break;
                    case EVENT_FIRE_SPIT:
                        DoCast(me->getVictim(), SPELL_FIRE_SPIT, true);
                        events.ScheduleEvent(EVENT_FIRE_SPIT, urand(2000, 9000));
                        break;
                    case EVENT_BLAST_NOVA:
                        DoCast(SPELL_BLAST_NOVA);
                        events.ScheduleEvent(EVENT_BLAST_NOVA, urand(10000, 19000));
                        break;
                    case EVENT_SPAWN_FIRE:
                        me->MonsterYell("COME to MEEE !!!", LANG_UNIVERSAL, 0);
                        events.ScheduleEvent(EVENT_SPAWN_FIRE, urand(30000, 38000));
                        events.ScheduleEvent(EVENT_SPAWN_FIRE_CLEANUP, 15000);
                        SpawnFire();
                        break;
                    case EVENT_SPAWN_FIRE_CLEANUP:
                        ClearFire();
                        break;
                }
            }
            DoMeleeAttackIfReady();
        }

        void SpawnFire()
        {
            float x, y, z;
            gameObjectTree = NULL;
            gameObjectFire = NULL;
            gameObjectFire2 = NULL;
            gameObjectFire3 = NULL;
            gameObjectFire4 = NULL;
            // Getting Position
            me->GetPosition(x, y, z);
            // Start Spawning
            gameObjectTree = me->SummonGameObject(191160, x, y, z, 0, 0, 0, 0, 0, 0);
            gameObjectTreeFire = me->SummonGameObject(190570, gameObjectTree->GetPositionX(), gameObjectTree->GetPositionY(), gameObjectTree->GetPositionZ(), 0, 0, 0, 0, 0, 0);
            gameObjectFire = me->SummonGameObject(190570, x, y + 10, z, 0, 0, 0, 0, 0, 0);
            gameObjectFire2 = me->SummonGameObject(190570, x, y -10, z, 0, 0, 0, 0, 0, 0);
            gameObjectFire3 = me->SummonGameObject(190570, x + 10, y, z, 0, 0, 0, 0, 0, 0);
            gameObjectFire4 = me->SummonGameObject(190570, x - 10, y, z, 0, 0, 0, 0, 0, 0);
        }

        void ClearFire()
        {
            if (gameObjectTree && gameObjectTreeFire && gameObjectFire && gameObjectFire2 && gameObjectFire3 && gameObjectFire4)
            {
                gameObjectTree->Delete();
                gameObjectTreeFire->Delete();
                gameObjectFire->Delete();
                gameObjectFire2->Delete();
                gameObjectFire3->Delete();
                gameObjectFire4->Delete();
            }
        }

        void JustDied(Unit* /* victim */)
        {
            events.Reset();
            ClearFire();
        }
    private:
        EventMap events;
        GameObject* gameObjectTree;
        GameObject* gameObjectTreeFire;
        GameObject* gameObjectFire;
        GameObject* gameObjectFire2;
        GameObject* gameObjectFire3;
        GameObject* gameObjectFire4;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_battleAI(creature);
    }
};

void AddSC_mini_fight()
{
    new npc_battle;
}