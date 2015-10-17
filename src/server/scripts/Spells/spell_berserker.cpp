/*
 * Copyright (C) 2015 TheSatriaCore <http://www.TheSatria.Com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Scripts for spells with SPELLFAMILY_WARRIOR and SPELLFAMILY_GENERIC spells used by warrior players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_berserek_".
 */

#include "Player.h"
#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"

enum BerserkerSpells
{
    SPELL_BERSERKER_BLOODTHIRST                       = 23885,
    SPELL_BERSERKER_BLOODTHIRST_DAMAGE                = 23881,
    SPELL_BERSERKER_CHARGE                            = 34846,
    SPELL_BERSERKER_DAMAGE_SHIELD_DAMAGE              = 59653,
    SPELL_BERSERKER_DEEP_WOUNDS_RANK_1                = 12162,
    SPELL_BERSERKER_DEEP_WOUNDS_RANK_2                = 12850,
    SPELL_BERSERKER_DEEP_WOUNDS_RANK_3                = 12868,
    SPELL_BERSERKER_DEEP_WOUNDS_RANK_PERIODIC         = 12721,
    SPELL_BERSERKER_EXECUTE                           = 20647,
    SPELL_BERSERKER_GLYPH_OF_EXECUTION                = 58367,
    SPELL_BERSERKER_GLYPH_OF_VIGILANCE                = 63326,
    SPELL_BERSERKER_JUGGERNAUT_CRIT_BONUS_BUFF        = 65156,
    SPELL_BERSERKER_JUGGERNAUT_CRIT_BONUS_TALENT      = 64976,
    SPELL_BERSERKER_LAST_STAND_TRIGGERED              = 12976,
    SPELL_BERSERKER_SLAM                              = 50783,
    SPELL_BERSERKER_SWEEPING_STRIKES_EXTRA_ATTACK     = 26654,
    SPELL_BERSERKER_TAUNT                             = 53385,
    SPELL_BERSERKER_UNRELENTING_ASSAULT_RANK_1        = 46859,
    SPELL_BERSERKER_UNRELENTING_ASSAULT_RANK_2        = 46860,
    SPELL_BERSERKER_UNRELENTING_ASSAULT_TRIGGER_1     = 64849,
    SPELL_BERSERKER_UNRELENTING_ASSAULT_TRIGGER_2     = 64850,
    SPELL_BERSERKER_VIGILANCE_PROC                    = 50725,
    SPELL_BERSERKER_VIGILANCE_REDIRECT_THREAT         = 59665,
	SPELL_BERSERKER_150_RED					          = 27680,

    SPELL_PALADIN_BLESSING_OF_SANCTUARY             = 20911,
    SPELL_PALADIN_GREATER_BLESSING_OF_SANCTUARY     = 25899,
    SPELL_PRIEST_RENEWED_HOPE                       = 63944,
    SPELL_GEN_DAMAGE_REDUCTION_AURA                 = 68066,
};

enum WarriorSpellIcons
{
    WARRIOR_ICON_ID_SUDDEN_DEATH        = 1989,
};

// 23881 - Bloodthirst
class spell_berserek_bloodthirst : public SpellScriptLoader
{
    public:
        spell_berserek_bloodthirst() : SpellScriptLoader("spell_berserek_bloodthirst") { }

        class spell_berserek_bloodthirst_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_berserek_bloodthirst_SpellScript);

            void HandleDamage(SpellEffIndex /*effIndex*/)
            {
                int32 damage = GetEffectValue();
                ApplyPct(damage, GetCaster()->GetTotalAttackPowerValue(BASE_ATTACK));

                if (Unit* target = GetHitUnit())
                {
                    damage = GetCaster()->SpellDamageBonusDone(target, GetSpellInfo(), uint32(damage), SPELL_DIRECT_DAMAGE);
                    damage = target->SpellDamageBonusTaken(GetCaster(), GetSpellInfo(), uint32(damage), SPELL_DIRECT_DAMAGE);
                }
                SetHitDamage(damage);
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                int32 damage = GetEffectValue();
                GetCaster()->CastCustomSpell(GetCaster(), SPELL_BERSERKER_BLOODTHIRST, &damage, NULL, NULL, true, NULL);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_berserek_bloodthirst_SpellScript::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
                OnEffectHit += SpellEffectFn(spell_berserek_bloodthirst_SpellScript::HandleDummy, EFFECT_1, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_berserek_bloodthirst_SpellScript();
        }
};

// 23880 - Bloodthirst (Heal)
class spell_berserek_bloodthirst_heal : public SpellScriptLoader
{
    public:
        spell_berserek_bloodthirst_heal() : SpellScriptLoader("spell_berserek_bloodthirst_heal") { }

        class spell_berserek_bloodthirst_heal_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_berserek_bloodthirst_heal_SpellScript);

            void HandleHeal(SpellEffIndex /*effIndex*/)
            {
                if (SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(SPELL_BERSERKER_BLOODTHIRST_DAMAGE))
                    SetHitHeal(GetCaster()->CountPctFromMaxHealth(spellInfo->Effects[EFFECT_1].CalcValue(GetCaster())));
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_berserek_bloodthirst_heal_SpellScript::HandleHeal, EFFECT_0, SPELL_EFFECT_HEAL);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_berserek_bloodthirst_heal_SpellScript();
        }
};

// -100 - Charge
class spell_berserek_charge : public SpellScriptLoader
{
    public:
        spell_berserek_charge() : SpellScriptLoader("spell_berserek_charge") { }

        class spell_berserek_charge_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_berserek_charge_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_BERSERKER_JUGGERNAUT_CRIT_BONUS_TALENT) || !sSpellMgr->GetSpellInfo(SPELL_BERSERKER_JUGGERNAUT_CRIT_BONUS_BUFF) || !sSpellMgr->GetSpellInfo(SPELL_BERSERKER_CHARGE))
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                int32 chargeBasePoints0 = GetEffectValue();
                Unit* caster = GetCaster();
                caster->CastCustomSpell(caster, SPELL_BERSERKER_CHARGE, &chargeBasePoints0, NULL, NULL, true);

                // Juggernaut crit bonus
                if (caster->HasAura(SPELL_BERSERKER_JUGGERNAUT_CRIT_BONUS_TALENT))
                    caster->CastSpell(caster, SPELL_BERSERKER_JUGGERNAUT_CRIT_BONUS_BUFF, true);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_berserek_charge_SpellScript::HandleDummy, EFFECT_1, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_berserek_charge_SpellScript();
        }
};

// 12809 - Concussion Blow
class spell_berserek_concussion_blow : public SpellScriptLoader
{
    public:
        spell_berserek_concussion_blow() : SpellScriptLoader("spell_berserek_concussion_blow") { }

        class spell_berserek_concussion_blow_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_berserek_concussion_blow_SpellScript);

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                SetHitDamage(CalculatePct(GetCaster()->GetTotalAttackPowerValue(BASE_ATTACK), GetEffectValue()));
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_berserek_concussion_blow_SpellScript::HandleDummy, EFFECT_2, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_berserek_concussion_blow_SpellScript();
        }
};

// -58872 - Damage Shield
class spell_berserek_damage_shield : public SpellScriptLoader
{
    public:
        spell_berserek_damage_shield() : SpellScriptLoader("spell_berserek_damage_shield") { }

        class spell_berserek_damage_shield_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_berserek_damage_shield_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_BERSERKER_DAMAGE_SHIELD_DAMAGE))
                    return false;
                return true;
            }

            void OnProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
            {
                PreventDefaultAction();

                // % of amount blocked
                int32 damage = CalculatePct(int32(GetTarget()->GetShieldBlockValue()), aurEff->GetAmount());
                GetTarget()->CastCustomSpell(SPELL_BERSERKER_DAMAGE_SHIELD_DAMAGE, SPELLVALUE_BASE_POINT0, damage, eventInfo.GetProcTarget(), true, NULL, aurEff);
            }

            void Register()
            {
                OnEffectProc += AuraEffectProcFn(spell_berserek_damage_shield_AuraScript::OnProc, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_berserek_damage_shield_AuraScript();
        }
};

// -12162 - Deep Wounds
class spell_berserek_deep_wounds : public SpellScriptLoader
{
    public:
        spell_berserek_deep_wounds() : SpellScriptLoader("spell_berserek_deep_wounds") { }

        class spell_berserek_deep_wounds_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_berserek_deep_wounds_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_BERSERKER_DEEP_WOUNDS_RANK_1) || !sSpellMgr->GetSpellInfo(SPELL_BERSERKER_DEEP_WOUNDS_RANK_2) || !sSpellMgr->GetSpellInfo(SPELL_BERSERKER_DEEP_WOUNDS_RANK_3))
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                int32 damage = GetEffectValue();
                Unit* caster = GetCaster();
                if (Unit* target = GetHitUnit())
                {
                    // apply percent damage mods
                    damage = caster->SpellDamageBonusDone(target, GetSpellInfo(), damage, SPELL_DIRECT_DAMAGE);

                    ApplyPct(damage, 16 * sSpellMgr->GetSpellRank(GetSpellInfo()->Id));

                    damage = target->SpellDamageBonusTaken(caster, GetSpellInfo(), damage, SPELL_DIRECT_DAMAGE);

                    SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(SPELL_BERSERKER_DEEP_WOUNDS_RANK_PERIODIC);
                    uint32 ticks = spellInfo->GetDuration() / spellInfo->Effects[EFFECT_0].Amplitude;

                    // Add remaining ticks to damage done
                    if (AuraEffect const* aurEff = target->GetAuraEffect(SPELL_BERSERKER_DEEP_WOUNDS_RANK_PERIODIC, EFFECT_0, caster->GetGUID()))
                        damage += aurEff->GetAmount() * (ticks - aurEff->GetTickNumber());

                    damage /= ticks;

                    caster->CastCustomSpell(target, SPELL_BERSERKER_DEEP_WOUNDS_RANK_PERIODIC, &damage, NULL, NULL, true);
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_berserek_deep_wounds_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_berserek_deep_wounds_SpellScript();
        }
};

// -5308 - Execute
class spell_berserek_execute : public SpellScriptLoader
{
    public:
        spell_berserek_execute() : SpellScriptLoader("spell_berserek_execute") { }

        class spell_berserek_execute_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_berserek_execute_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_BERSERKER_EXECUTE) || !sSpellMgr->GetSpellInfo(SPELL_BERSERKER_GLYPH_OF_EXECUTION))
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex effIndex)
            {
                Unit* caster = GetCaster();
                if (Unit* target = GetHitUnit())
                {
                    SpellInfo const* spellInfo = GetSpellInfo();
                    int32 rageUsed = std::min<int32>(300 - spellInfo->CalcPowerCost(caster, SpellSchoolMask(spellInfo->SchoolMask)), caster->GetPower(POWER_RAGE));
                    int32 newRage = std::max<int32>(0, caster->GetPower(POWER_RAGE) - rageUsed);

                    // Sudden Death rage save
                    if (AuraEffect* aurEff = caster->GetAuraEffect(SPELL_AURA_PROC_TRIGGER_SPELL, SPELLFAMILY_GENERIC, WARRIOR_ICON_ID_SUDDEN_DEATH, EFFECT_0))
                    {
                        int32 ragesave = aurEff->GetSpellInfo()->Effects[EFFECT_1].CalcValue() * 10;
                        newRage = std::max(newRage, ragesave);
                    }

                    caster->SetPower(POWER_RAGE, uint32(newRage));
                    // Glyph of Execution bonus
                    if (AuraEffect* aurEff = caster->GetAuraEffect(SPELL_BERSERKER_GLYPH_OF_EXECUTION, EFFECT_0))
                        rageUsed += aurEff->GetAmount() * 10;


                    int32 bp = GetEffectValue() + int32(rageUsed * spellInfo->Effects[effIndex].DamageMultiplier + caster->GetTotalAttackPowerValue(BASE_ATTACK) * 0.2f);
                    caster->CastCustomSpell(target, SPELL_BERSERKER_EXECUTE, &bp, NULL, NULL, true, NULL, NULL, GetOriginalCaster()->GetGUID());
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_berserek_execute_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_berserek_execute_SpellScript();
        }
};

// 59725 - Improved Spell Reflection
class spell_berserek_improved_spell_reflection : public SpellScriptLoader
{
    public:
        spell_berserek_improved_spell_reflection() : SpellScriptLoader("spell_berserek_improved_spell_reflection") { }

        class spell_berserek_improved_spell_reflection_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_berserek_improved_spell_reflection_SpellScript);

            void FilterTargets(std::list<WorldObject*>& unitList)
            {
                if (GetCaster())
                    unitList.remove(GetCaster());
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_berserek_improved_spell_reflection_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_CASTER_AREA_PARTY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_berserek_improved_spell_reflection_SpellScript();
        }
};

// 5246 - Intimidating Shout
class spell_berserek_intimidating_shout : public SpellScriptLoader
{
    public:
        spell_berserek_intimidating_shout() : SpellScriptLoader("spell_berserek_intimidating_shout") { }

        class spell_berserek_intimidating_shout_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_berserek_intimidating_shout_SpellScript);

            void FilterTargets(std::list<WorldObject*>& unitList)
            {
                unitList.remove(GetExplTargetWorldObject());
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_berserek_intimidating_shout_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_SRC_AREA_ENEMY);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_berserek_intimidating_shout_SpellScript::FilterTargets, EFFECT_2, TARGET_UNIT_SRC_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_berserek_intimidating_shout_SpellScript();
        }
};

// 12975 - Last Stand
class spell_berserek_last_stand : public SpellScriptLoader
{
    public:
        spell_berserek_last_stand() : SpellScriptLoader("spell_berserek_last_stand") { }

        class spell_berserek_last_stand_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_berserek_last_stand_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_BERSERKER_LAST_STAND_TRIGGERED))
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (Unit* caster = GetCaster())
                {
                    int32 healthModSpellBasePoints0 = int32(caster->CountPctFromMaxHealth(30));
                    caster->CastCustomSpell(caster, SPELL_BERSERKER_LAST_STAND_TRIGGERED, &healthModSpellBasePoints0, NULL, NULL, true, NULL);
                }
            }

            void Register()
            {
                OnEffectHit += SpellEffectFn(spell_berserek_last_stand_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_berserek_last_stand_SpellScript();
        }
};

// 7384, 7887, 11584, 11585 - Overpower
class spell_berserek_overpower : public SpellScriptLoader
{
    public:
        spell_berserek_overpower() : SpellScriptLoader("spell_berserek_overpower") { }

        class spell_berserek_overpower_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_berserek_overpower_SpellScript);

            void HandleEffect(SpellEffIndex /*effIndex*/)
            {
                uint32 spellId = 0;
                if (GetCaster()->HasAura(SPELL_BERSERKER_UNRELENTING_ASSAULT_RANK_1))
                    spellId = SPELL_BERSERKER_UNRELENTING_ASSAULT_TRIGGER_1;
                else if (GetCaster()->HasAura(SPELL_BERSERKER_UNRELENTING_ASSAULT_RANK_2))
                    spellId = SPELL_BERSERKER_UNRELENTING_ASSAULT_TRIGGER_2;

                if (!spellId)
                    return;

                if (Player* target = GetHitPlayer())
                    if (target->HasUnitState(UNIT_STATE_CASTING))
                        target->CastSpell(target, spellId, true);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_berserek_overpower_SpellScript::HandleEffect, EFFECT_0, SPELL_EFFECT_ANY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_berserek_overpower_SpellScript();
        }
};

// -772 - Rend
class spell_berserek_rend : public SpellScriptLoader
{
    public:
        spell_berserek_rend() : SpellScriptLoader("spell_berserek_rend") { }

        class spell_berserek_rend_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_berserek_rend_AuraScript);

            void CalculateAmount(AuraEffect const* aurEff, int32& amount, bool& canBeRecalculated)
            {
                if (Unit* caster = GetCaster())
                {
                    canBeRecalculated = false;

                    // $0.2 * (($MWB + $mwb) / 2 + $AP / 14 * $MWS) bonus per tick
                    float ap = caster->GetTotalAttackPowerValue(BASE_ATTACK);
                    int32 mws = caster->GetAttackTime(BASE_ATTACK);
                    float mwbMin = caster->GetWeaponDamageRange(BASE_ATTACK, MINDAMAGE);
                    float mwbMax = caster->GetWeaponDamageRange(BASE_ATTACK, MAXDAMAGE);
                    float mwb = ((mwbMin + mwbMax) / 2 + ap * mws / 14000) * 0.2f;
                    amount += int32(caster->ApplyEffectModifiers(GetSpellInfo(), aurEff->GetEffIndex(), mwb));

                    // "If used while your target is above 75% health, Rend does 35% more damage."
                    // as for 3.1.3 only ranks above 9 (wrong tooltip?)
                    if (GetSpellInfo()->GetRank() >= 9)
                    {
                        if (GetUnitOwner()->HasAuraState(AURA_STATE_HEALTH_ABOVE_75_PERCENT, GetSpellInfo(), caster))
                            AddPct(amount, GetSpellInfo()->Effects[EFFECT_2].CalcValue(caster));
                    }
                }
            }

            void Register()
            {
                 DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_berserek_rend_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_berserek_rend_AuraScript();
        }
};

// 64380, 65941 - Shattering Throw
class spell_berserek_shattering_throw : public SpellScriptLoader
{
    public:
        spell_berserek_shattering_throw() : SpellScriptLoader("spell_berserek_shattering_throw") { }

        class spell_berserek_shattering_throw_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_berserek_shattering_throw_SpellScript);

            void HandleScript(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);

                // remove shields, will still display immune to damage part
                if (Unit* target = GetHitUnit())
                    target->RemoveAurasWithMechanic(1 << MECHANIC_IMMUNE_SHIELD, AURA_REMOVE_BY_ENEMY_SPELL);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_berserek_shattering_throw_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_berserek_shattering_throw_SpellScript();
        }
};

// -1464 - Slam
class spell_berserek_slam : public SpellScriptLoader
{
    public:
        spell_berserek_slam() : SpellScriptLoader("spell_berserek_slam") { }

        class spell_berserek_slam_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_berserek_slam_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_BERSERKER_SLAM))
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                int32 bp0 = GetEffectValue();
                if (GetHitUnit())
                    GetCaster()->CastCustomSpell(GetHitUnit(), SPELL_BERSERKER_SLAM, &bp0, NULL, NULL, true, 0);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_berserek_slam_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_berserek_slam_SpellScript();
        }
};

// 12328, 18765, 35429 - Sweeping Strikes
class spell_berserek_sweeping_strikes : public SpellScriptLoader
{
    public:
        spell_berserek_sweeping_strikes() : SpellScriptLoader("spell_berserek_sweeping_strikes") { }

        class spell_berserek_sweeping_strikes_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_berserek_sweeping_strikes_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_BERSERKER_SWEEPING_STRIKES_EXTRA_ATTACK))
                    return false;
                return true;
            }

            bool Load()
            {
                _procTarget = NULL;
                return true;
            }

            bool CheckProc(ProcEventInfo& eventInfo)
            {
                _procTarget = eventInfo.GetActor()->SelectNearbyTarget(eventInfo.GetProcTarget());
                return _procTarget;
            }

            void HandleProc(AuraEffect const* aurEff, ProcEventInfo& /*eventInfo*/)
            {
                PreventDefaultAction();
                GetTarget()->CastSpell(_procTarget, SPELL_BERSERKER_SWEEPING_STRIKES_EXTRA_ATTACK, true, NULL, aurEff);
            }

            void Register()
            {
                DoCheckProc += AuraCheckProcFn(spell_berserek_sweeping_strikes_AuraScript::CheckProc);
                OnEffectProc += AuraEffectProcFn(spell_berserek_sweeping_strikes_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
            }

        private:
            Unit* _procTarget;
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_berserek_sweeping_strikes_AuraScript();
        }
};

// 50720 - Vigilance
class spell_berserek_vigilance : public SpellScriptLoader
{
    public:
        spell_berserek_vigilance() : SpellScriptLoader("spell_berserek_vigilance") { }

        class spell_berserek_vigilance_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_berserek_vigilance_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_BERSERKER_GLYPH_OF_VIGILANCE))
                    return false;
                if (!sSpellMgr->GetSpellInfo(SPELL_BERSERKER_VIGILANCE_PROC))
                    return false;
                if (!sSpellMgr->GetSpellInfo(SPELL_BERSERKER_VIGILANCE_REDIRECT_THREAT))
                    return false;
                if (!sSpellMgr->GetSpellInfo(SPELL_GEN_DAMAGE_REDUCTION_AURA))
                    return false;
                return true;
            }

            bool Load()
            {
                _procTarget = NULL;
                return true;
            }

            void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                Unit* target = GetTarget();
                target->CastSpell(target, SPELL_GEN_DAMAGE_REDUCTION_AURA, true);

                if (Unit* caster = GetCaster())
                    target->CastSpell(caster, SPELL_BERSERKER_VIGILANCE_REDIRECT_THREAT, true);
            }

            void HandleAfterApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                //! WORKAROUND
                //! this glyph is a proc
                if (Unit* caster = GetCaster())
                {
                    if (AuraEffect const* glyph = caster->GetAuraEffect(SPELL_BERSERKER_GLYPH_OF_VIGILANCE, EFFECT_0))
                        GetTarget()->ModifyRedirectThreat(glyph->GetAmount());
                }
            }

            void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                Unit* target = GetTarget();
                if (target->HasAura(SPELL_GEN_DAMAGE_REDUCTION_AURA) &&
                    !(target->HasAura(SPELL_PALADIN_BLESSING_OF_SANCTUARY) ||
                    target->HasAura(SPELL_PALADIN_GREATER_BLESSING_OF_SANCTUARY) ||
                    target->HasAura(SPELL_PRIEST_RENEWED_HOPE)))
                {
                    target->RemoveAurasDueToSpell(SPELL_GEN_DAMAGE_REDUCTION_AURA);
                }

                target->ResetRedirectThreat();
            }

            bool CheckProc(ProcEventInfo& /*eventInfo*/)
            {
                _procTarget = GetCaster();
                return _procTarget;
            }

            void HandleProc(AuraEffect const* aurEff, ProcEventInfo& /*eventInfo*/)
            {
                PreventDefaultAction();
                GetTarget()->CastSpell(_procTarget, SPELL_BERSERKER_VIGILANCE_PROC, true, NULL, aurEff);
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_berserek_vigilance_AuraScript::HandleApply, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
                AfterEffectApply += AuraEffectApplyFn(spell_berserek_vigilance_AuraScript::HandleAfterApply, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
                OnEffectRemove += AuraEffectRemoveFn(spell_berserek_vigilance_AuraScript::HandleRemove, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
                DoCheckProc += AuraCheckProcFn(spell_berserek_vigilance_AuraScript::CheckProc);
                OnEffectProc += AuraEffectProcFn(spell_berserek_vigilance_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
            }

        private:
            Unit* _procTarget;
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_berserek_vigilance_AuraScript();
        }
};

// 50725 Vigilance
class spell_berserek_vigilance_trigger : public SpellScriptLoader
{
    public:
        spell_berserek_vigilance_trigger() : SpellScriptLoader("spell_berserek_vigilance_trigger") { }

        class spell_berserek_vigilance_trigger_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_berserek_vigilance_trigger_SpellScript);

            void HandleScript(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);

                // Remove Taunt cooldown
                if (Player* target = GetHitPlayer())
                    target->RemoveSpellCooldown(SPELL_BERSERKER_TAUNT, true);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_berserek_vigilance_trigger_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_berserek_vigilance_trigger_SpellScript();
        }
};

void AddSC_berserk_spell_scripts()
{
    new spell_berserek_bloodthirst();
    new spell_berserek_bloodthirst_heal();
    new spell_berserek_charge();
    new spell_berserek_concussion_blow();
    new spell_berserek_damage_shield();
    new spell_berserek_deep_wounds();
    new spell_berserek_execute();
    new spell_berserek_improved_spell_reflection();
    new spell_berserek_intimidating_shout();
    new spell_berserek_last_stand();
    new spell_berserek_overpower();
    new spell_berserek_rend();
    new spell_berserek_shattering_throw();
    new spell_berserek_slam();
    new spell_berserek_sweeping_strikes();
    new spell_berserek_vigilance();
    new spell_berserek_vigilance_trigger();
}
