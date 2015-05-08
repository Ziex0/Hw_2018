#include "ScriptPCH.h"

#define SPELL_HEALPOTION 28495
#define SPELL_STRENGHPOTION 28490
#define SPELL_ACID 54364
#define SPELL_FROSTBOLT 58535

class boss_nazaryan : public CreatureScript
{
public:
    boss_nazaryan() : CreatureScript("boss_nazaryan"){}
    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_nazaryanAI (pCreature);
    }
    struct boss_nazaryanAI : public ScriptedAI
    {
        InstanceScript* pInstance;
        boss_nazaryanAI(Creature *c) : ScriptedAI(c)
        {
            EnterEvadeMode();
            pInstance = c->GetInstanceScript();
        }
        bool elemental_summoned;
        uint32 next_proc;
        int32 pitsot;
        uint32 FB_Timer;
        Creature * elemental;
        void Reset()
        {
            elemental_summoned=false;
            next_proc=95;
            FB_Timer = 5;
            std::list<Creature*> elem=DoFindFriendlyMissingBuff(100.0f, 45112);
            for(std::list<Creature*>::iterator itr = elem.begin(); itr != elem.end(); ++itr)
                if((*itr)->GetEntry()==100001 && (*itr)->IsInWorld())
                {
                    (*itr)->RemoveFromWorld();
                    break;
                }
            elemental = NULL;
            me->SetHealth(me->GetMaxHealth());
        }
        void EnterCombat(Unit* pWho)
        {
            me->MonsterYell("I'll destroy you !!",0, pWho->GetGUID());
        }
        void UpdateAI(uint32 uiDiff)
        {
            if (!UpdateVictim())
                return;
            
            if((!elemental_summoned && next_proc<95) || (elemental && elemental->isDead()))
            {
                me->MonsterYell("Arise, my servant!",0, me->GetGUID());
                elemental = DoSpawnCreature(100001, 0, 0, 0, 0.0f, 5, 1000);
                elemental_summoned = true;
                elemental->AddThreat(me->GetVictim(), 1.0f);
            }
            if(int(me->GetHealth()*100/me->GetMaxHealth())==next_proc)
            {
                int random=rand()%10;
                switch(random)
                {
                    case 1:
                    {
                        me->MonsterYell("Yeah, right that, i need healing!",0, me->GetGUID());
                        me->CastCustomSpell(me, SPELL_HEALPOTION,0,0,0, false);
                        me->ModifyHealth(50000);
                        next_proc+=5;
                        break;
                    }
                    case 2:
                    {
                        if(me->GetAura(SPELL_STRENGHPOTION, 0))
                        {
                            me->MonsterYell("Yeah, right that, i need healing!",0, me->GetGUID());
                            me->CastCustomSpell(me, SPELL_HEALPOTION,0,0,0, false);
                            me->ModifyHealth(50000);
                                next_proc+=5;
                            break;
                        }
                        me->MonsterYell("Power, i feel it in my veins",0, me->GetGUID());
                        pitsot = 5000;
                        me->CastCustomSpell(me, SPELL_STRENGHPOTION,&pitsot, 0, 0, false);
                        me->UpdateAttackPowerAndDamage(false);
                        break;
                    }
                    default:
                    {
                        me->MonsterYell("Poison?! Dumn wrong label!",0, me->GetGUID());
                        int32 damage = 20000;
                        me->CastCustomSpell(me->GetVictim(), SPELL_ACID, &damage, 0, 0, false);
                    }
                }
                next_proc-=5;
            }
            DoMeleeAttackIfReady();
            if (me->GetDistance2d(me->GetHomePosition().GetPositionX(), me->GetHomePosition().GetPositionY()) > 50)
                EnterEvadeMode();
        }

        void EnterEvadeMode()
        {
            me->RemoveAllAuras();
            me->DeleteThreatList();
            me->CombatStop(true);
            me->LoadCreaturesAddon();

            if(me->isAlive())
                me->GetMotionMaster()->MoveTargetedHome(); //Q: should we avoid it? simply ScriptedAI::EnterEvadeMode

            me->SetLootRecipient(NULL);

            Reset();
        }

        void JustDied(Unit* Killer)
        {
            GameObject* HypnotoadDoor = pInstance->instance->GetGameObject( pInstance->GetData64(0));
            if(HypnotoadDoor)
                HypnotoadDoor->SetGoState(GO_STATE_ACTIVE);
            HypnotoadDoor = pInstance->instance->GetGameObject( pInstance->GetData64(1));
            if(HypnotoadDoor)
                HypnotoadDoor->SetGoState(GO_STATE_ACTIVE);
        }
    };
};

void AddSC_boss_nazaryan()
{
    new boss_nazaryan();
}