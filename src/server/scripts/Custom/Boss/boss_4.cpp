#include "ScriptPCH.h"
#include "Language.h"

enum Spells
{
    AHUNE= 45954,
    FLAME = 68970,
    METEOR = 45915,
	ARCANE = 34794, 
	CHILL_NOVA = 36148, 
	RUNIC_BARRIER = 62338, 
	OVERCHARGE = 37104, 
	ARCANE_SHOCK = 44319,
	SPELL_UNCONTROLLABLE_ENERGY = 59281, //Phase Spell 1
	SPELL_BELLOWING_ROAR = 36922, //Phase Spell 2
	SPELL_HUNGERING_COLD = 61058, //Phase Spell 3
	SPELL_NECROTIC_POISON = 46296, //Phase Spell 4
	SPELL_HEX = 16097, //Phase Spell 5
	SPELL_NINJA_COSTUME = 24710, //Phase Spell 6
	SPELL_BACKFIRE = 48558, //Phase Spell 7
};
     
class IceMan_boss : public CreatureScript
{
    public:
        IceMan_boss() : CreatureScript("IceMan_boss"){}
           
        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new IceMan_bossAI(pCreature);
        }
     
        struct IceMan_bossAI : public ScriptedAI
        {
           IceMan_bossAI(Creature *c) : ScriptedAI(c) {}
               
            uint32 Ahune_timer;
            uint32 Flame_timer;
            uint32 Meteor_timer;
			uint32 Arcane_timer;
			uint32 Chill_Nova_Timer;
			uint32 Runic_Barrier_Timer;
			uint32 Overcharge_Timer;
			uint32 Arcane_Shock_Timer;


            void Reset()
            {
                Ahune_timer = 4000;
                Flame_timer = 10000;
                Meteor_timer = 3500;
				Arcane_timer = 50000;
				Chill_Nova_Timer = 30000;
				Runic_Barrier_Timer = 40000;
				Overcharge_Timer = 8000;
				Arcane_Shock_Timer = 20000;
            }
      
            void JustDied(Unit * victim)
            {
                me->MonsterYell("I am Failed !",LANG_UNIVERSAL,NULL);
            }
     
            void KilledUnit(Unit * victim)
            {
                me->MonsterYell("You stil weaakkk ! hahahaha",LANG_UNIVERSAL,NULL);   
            }
     
            void EnterCombat(Unit * /*who*/)
            {
                me->MonsterYell("Not that easy to kill me !!",LANG_UNIVERSAL,NULL);
            }
               
            void UpdateAI(uint32 uiDiff)
            {
                if(!UpdateVictim())
                    return;

                
// SPELS USAGE...   :

// Ahune :
                    if(!UpdateVictim())
                    return;

                 if (Ahune_timer <= uiDiff)
                        {
                        DoCast(me->getVictim(), AHUNE); 
                        Ahune_timer = 2000; 
                    }
            else
                          Ahune_timer -= uiDiff;



// Flame Breath    :                       
            
            if (!UpdateVictim())
                    return;

                 if (Flame_timer <= uiDiff)
                        {
                        DoCast(me->getVictim(), FLAME); 
                        Flame_timer = 15000; 
                    }
            else
                          Flame_timer -= uiDiff;


// Meteor :                 
                 if(!UpdateVictim())
                    return;

                 if (Meteor_timer <= uiDiff)
                        {
                        DoCast(me->getVictim(), METEOR); 
                        Meteor_timer = 20000; 
                    }
            else
                          Meteor_timer -=uiDiff;

// Arcane :                 
                 if(!UpdateVictim())
                    return;

                 if (Arcane_timer <= uiDiff)
                        {
                        DoCast(me->getVictim(), ARCANE); 
                        Arcane_timer = 10000; 
                    }
            else
                          Arcane_timer -=uiDiff;
						  


						  

               DoMeleeAttackIfReady();
            }
        };
};
     
void AddSC_IceMan_boss()
{
    new IceMan_boss();
}