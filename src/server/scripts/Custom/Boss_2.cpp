#include "ScriptPCH.h"

    enum Spells
    {
        SPELL_COUNTDOWN         = 99516,        // Phase One
        SPELL_MAGMA_RIFT        = 99840,        // Phase One
        SPELL_TOXIN_RAIN        = 99333,        // Phase One
        SPELL_HAND_OF_RAGNAROS  = 98237,        // Phase One
        SPELL_MAGMA_BEAT        = 98313,        //Phase One
        SPELL_BLADE_DANCE       = 105784,       //Phase Two
        SPELL_LIGHTNING_BOMB    = 109541,       // Phase Two
        SPELL_FEEDBACK          = 108934,       // Phase Two
        SPELL_SHOCKWAVE         = 108046,       // Phase Two
        SPELL_MENTAL_WITHRAWAL  = 104322,       // Phase Two
        SPELL_FINGER_OF_DEATH   = 31984, // Phase Three
    };
         
    enum Events
    {
        EVENT_NONE,
        EVENT_COUNTDOWN,
        EVENT_MAGMA_RIFT,
        EVENT_TOXIN_RAIN,
        EVENT_HAND_OF_RAGNAROS,
        EVENT_MAGMA_BEAT,
        EVENT_BLADE_DANCE,
        EVENT_LIGHTNING_BOMB,
        EVENT_FEEDBACK,
        EVENT_SHOCKWAVE,
        EVENT_MENTAL_WITHRAWAL,
        EVENT_FINGER_OF_DEATH,
        EVENT_CHECK
    };
         
    class boss_test_script : public CreatureScript
    {
    public:
        boss_test_script() : CreatureScript("boss_test_script") { }
         
        struct boss_test_scriptAI : public ScriptedAI
        {
            boss_test_scriptAI(Creature* creature) : ScriptedAI(creature) { }
         
            void Reset() override
            {
                events.Reset();
                phase = 1;
            }
     
            void EnterCombat(Unit* /* who */) override
            {
                events.ScheduleEvent(EVENT_COUNTDOWN, 30000);
                events.ScheduleEvent(EVENT_MAGMA_RIFT, 26000);
                events.ScheduleEvent(EVENT_TOXIN_RAIN, 22000);
                events.ScheduleEvent(EVENT_HAND_OF_RAGNAROS, 40000);
                events.ScheduleEvent(EVENT_MAGMA_BEAT, 18000);
                events.ScheduleEvent(EVENT_CHECK, 1500);
                me->MonsterYell("This is the beginning of the end!", LANG_UNIVERSAL, NULL);
            }
     
            void JustDied(Unit* /* victim */) override
            {
                me->MonsterYell("How did this happen ? That's impossible ....", LANG_UNIVERSAL, NULL);
            }
     
            void UpdateAI(uint32 diff) override
            {
                if (!UpdateVictim())
                    return;
     
                events.Update(diff);
     
                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_CHECK:
                            if (phase == 1 && me->GetHealthPct() <= 60)
                            {
                                me->MonsterYell("You can't defeat me !!", LANG_UNIVERSAL, NULL);
                                events.Reset();
                                events.ScheduleEvent(EVENT_BLADE_DANCE, 45000);
                                events.ScheduleEvent(EVENT_LIGHTNING_BOMB, 20000);
                                events.ScheduleEvent(EVENT_FEEDBACK, 75000);
                                events.ScheduleEvent(EVENT_SHOCKWAVE, 36000);
                                events.ScheduleEvent(EVENT_MENTAL_WITHRAWAL, 16000);
                                phase = 2;
                            }
         
                            if (phase == 2 && me->GetHealthPct() <= 15)
                            {
                                me->MonsterYell("It 's enough for me !", LANG_UNIVERSAL, NULL);
                                events.ScheduleEvent(EVENT_FINGER_OF_DEATH, 10000);
                                phase = 3;
                            }
                            events.ScheduleEvent(EVENT_CHECK, 1500);
                            break;
                        case EVENT_COUNTDOWN:
                            if (Unit *target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                                DoCast(target, SPELL_COUNTDOWN);
                            events.ScheduleEvent(EVENT_COUNTDOWN, 30000);
                            break;
                        case EVENT_MAGMA_RIFT:
                            if (Unit *target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                                DoCast(target, SPELL_MAGMA_RIFT);
                            events.ScheduleEvent(EVENT_MAGMA_RIFT, 26000);
                            break;
                        case EVENT_TOXIN_RAIN:
                            DoCastVictim(SPELL_TOXIN_RAIN);
                            events.ScheduleEvent(EVENT_TOXIN_RAIN, 22000);
                            break;
                        case EVENT_HAND_OF_RAGNAROS:
                            if (Unit *target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                                DoCast(target, SPELL_HAND_OF_RAGNAROS);
                            me->MonsterYell("Feel my Power", LANG_UNIVERSAL, NULL);
                            events.ScheduleEvent(EVENT_HAND_OF_RAGNAROS, 40000);
                            break;
                        case EVENT_MAGMA_BEAT:
                            DoCastVictim(SPELL_MAGMA_BEAT);
                            events.ScheduleEvent(EVENT_MAGMA_BEAT, 18000);
                            break;
                        case EVENT_BLADE_DANCE:
                            if (Unit *target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                                DoCast(target, SPELL_BLADE_DANCE);
                            me->MonsterYell("DIE!!!", LANG_UNIVERSAL, NULL);
                            events.ScheduleEvent(EVENT_BLADE_DANCE, 45000);
                            break;
                        case EVENT_LIGHTNING_BOMB:
                            if (Unit *target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                                DoCast(target, SPELL_LIGHTNING_BOMB);
                            events.ScheduleEvent(EVENT_LIGHTNING_BOMB, 20000);
                            break;
                        case EVENT_FEEDBACK:
                            DoCast(me, SPELL_FEEDBACK);
                            events.ScheduleEvent(EVENT_FEEDBACK, 75000);
                            break;
                        case EVENT_SHOCKWAVE:
                            if (Unit *target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                                DoCast(target, SPELL_SHOCKWAVE);
                            me->MonsterYell("Silence !!!", LANG_UNIVERSAL, NULL);
                            events.ScheduleEvent(EVENT_SHOCKWAVE, 36000);
                            break;
                        case EVENT_MENTAL_WITHRAWAL:
                            if (Unit *target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                                DoCast(target, SPELL_MENTAL_WITHRAWAL);
                            events.ScheduleEvent(EVENT_MENTAL_WITHRAWAL, 16000);
                            break;
                        case EVENT_FINGER_OF_DEATH:
                            if (Unit *target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                                DoCast(target, SPELL_FINGER_OF_DEATH);
                            events.ScheduleEvent(EVENT_FINGER_OF_DEATH, 10000);
                            break;
                    }
                }
                DoMeleeAttackIfReady();
            }
            private:
                EventMap events;
                uint8 phase;
        };
         
        CreatureAI* GetAI(Creature* creature) const override
        {
            return new boss_test_scriptAI(creature);
        }
    };
         
    void AddSC_boss_test_script()
    {
        new boss_test_script();
    }

