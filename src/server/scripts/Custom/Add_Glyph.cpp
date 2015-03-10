/*
 * Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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

enum glyphs
{
        MAJOR_ZERO_GLYPH = 101,

        MAJOR_DRUID_GLYPH_OF_FRENZIED_REGENERATION = 161,
        // Glyph of Frenzied Regeneration: While Frenzied Regeneration is active, healing effects on you are $54810s1% more powerful.

        MAJOR_DRUID_GLYPH_OF_MAUL = 162,
        // Glyph of Maul: Your Maul ability now hits $s1 additional target.

        MAJOR_DRUID_GLYPH_OF_MANGLE = 164,
        // Glyph of Mangle: Increases the damage done by Mangle by $54813s1%.

        MAJOR_DRUID_GLYPH_OF_SHRED = 165,
        // Glyph of Shred: Each time you Shred, the duration of your Rip on the target is extended $54815s1 sec, up to a maximum of $54815s2 sec.

        MAJOR_DRUID_GLYPH_OF_RIP = 166,
        // Glyph of Rip: Increases the duration of your Rip ability by ${$m1/1000} sec.

        MAJOR_DRUID_GLYPH_OF_RAKE = 167,
        // Glyph of Rake: Your Rake ability prevents targets from fleeing.

        MAJOR_DRUID_GLYPH_OF_SWIFTMEND = 168,
        // Glyph of Swiftmend: Your Swiftmend ability no longer consumes a Rejuvenation or Regrowth effect from the target.

        MAJOR_DRUID_GLYPH_OF_INNERVATE = 169,
        // Glyph of Innervate: Innervate now grants the caster $54832s1% of $ghis:her; base mana pool over $54833d in addition to the normal effects of Innervate.

        MAJOR_DRUID_GLYPH_OF_REBIRTH = 170,
        // Glyph of Rebirth: Players resurrected by Rebirth are returned to life with $54733s2% health.

        MAJOR_DRUID_GLYPH_OF_REGROWTH = 171,
        // Glyph of Regrowth: Increases the healing of your Regrowth spell by $54743s1% if your Regrowth effect is still active on the target.

        MAJOR_DRUID_GLYPH_OF_REJUVENATION = 172,
        // Glyph of Rejuvenation: While your Rejuvenation targets are below 50% health, you will heal them for an additional $s1% health.

        MAJOR_DRUID_GLYPH_OF_HEALING_TOUCH = 173,
        // Glyph of Healing Touch: Decreases the cast time of Healing Touch by ${$m3/-1000}.1 sec, the mana cost by $s1%, and the amount healed by $s2%.

        MAJOR_DRUID_GLYPH_OF_LIFEBLOOM = 174,
        // Glyph of Lifebloom: Increases the duration of Lifebloom by ${$m1/1000} sec.

        MAJOR_DRUID_GLYPH_OF_STARFIRE = 175,
        // Glyph of Starfire: Your Starfire ability increases the duration of your Moonfire effect on the target by $54845s1 sec, up to a maximum of $54845s2 additional seconds.

        MAJOR_DRUID_GLYPH_OF_INSECT_SWARM = 176,
        // Glyph of Insect Swarm: Increases the damage of your Insect Swarm ability by $s2%, but it no longer affects your victim's chance to hit.

        MAJOR_DRUID_GLYPH_OF_HURRICANE = 177,
        // Glyph of Hurricane: Your Hurricane ability now also slows the movement speed of its victims by $s1%.

        MAJOR_DRUID_GLYPH_OF_STARFALL = 178,
        // Glyph of Starfall: Reduces the cooldown of Starfall by ${$54828m1/-1000} sec.

        MAJOR_DRUID_GLYPH_OF_WRATH = 179,
        // Glyph of Wrath: Reduces the pushback suffered from damaging attacks while casting your Wrath spell by $54756s1%.

        MAJOR_DRUID_GLYPH_OF_MOONFIRE = 180,
        // Glyph of Moonfire: Increases the periodic damage of your Moonfire ability by $s2%, but initial damage is decreased by $s1%.

        MAJOR_DRUID_GLYPH_OF_ENTANGLING_ROOTS = 181,
        // Glyph of Entangling Roots: Increases the damage your Entangling Roots victims can take before the Entangling Roots automatically breaks by $s1%.

        MAJOR_PALADIN_GLYPH_OF_JUDGEMENT = 183,
        // Glyph of Judgement: Your Judgements deal $54922s1% more damage.

        MAJOR_PALADIN_GLYPH_OF_SEAL_OF_COMMAND = 184,
        // Glyph of Seal of Command: You gain $68082s1% of your base mana each time you use a Judgement with Seal of Command active.

        MAJOR_PALADIN_GLYPH_OF_HAMMER_OF_JUSTICE = 185,
        // Glyph of Hammer of Justice: Increases your Hammer of Justice range by $54923s1 yards.

        MAJOR_PALADIN_GLYPH_OF_SPIRITUAL_ATTUNEMENT = 186,
        // Glyph of Spiritual Attunement: Increases the amount of mana gained from your Spiritual Attunement spell by an additional $54924s1%.

        MAJOR_PALADIN_GLYPH_OF_HAMMER_OF_WRATH = 187,
        // Glyph of Hammer of Wrath: Reduces the mana cost of Hammer of Wrath by ${$54926m1/-1}%.

        MAJOR_PALADIN_GLYPH_OF_CRUSADER_STRIKE = 188,
        // Glyph of Crusader Strike: Reduces the mana cost of your Crusader Strike ability by $54927s1%.

        MAJOR_PALADIN_GLYPH_OF_CONSECRATION = 189,
        // Glyph of Consecration: Increases the duration and cooldown of Consecration by ${$54928m1/1000} sec.

        MAJOR_PALADIN_GLYPH_OF_RIGHTEOUS_DEFENSE = 190,
        // Glyph of Righteous Defense: Increases the chance for your Righteous Defense and Hand of Reckoning abilities to work successfully by $54929s1% on each target.

        MAJOR_PALADIN_GLYPH_OF_AVENGERS_SHIELD = 191,
        // Glyph of Avenger's Shield: Your Avenger's Shield hits $54930s1 fewer targets, but for $54930s2% more damage.

        MAJOR_PALADIN_GLYPH_OF_TURN_EVIL = 192,
        // Glyph of Turn Evil: Reduces the casting time of your Turn Evil spell by $54931s1%, but increases the cooldown by ${$54931m2/1000} sec.

        MAJOR_PALADIN_GLYPH_OF_EXORCISM = 193,
        // Glyph of Exorcism: Increases damage done by Exorcism by $54934s1%.

        MAJOR_PALADIN_GLYPH_OF_CLEANSING = 194,
        // Glyph of Cleansing: Reduces the mana cost of your Cleanse and Purify spells by $54935s1%.

        MAJOR_PALADIN_GLYPH_OF_FLASH_OF_LIGHT = 195,
        // Glyph of Flash of Light: Your Flash of Light has an additional $54936s1% critical strike chance.

        MAJOR_PALADIN_GLYPH_OF_HOLY_LIGHT = 196,
        // Glyph of Holy Light: Your Holy Light grants $54937s1% of its heal amount to up to 5 friendly targets within $54968a1 yards of the initial target.

        MAJOR_PALADIN_GLYPH_OF_AVENGING_WRATH = 197,
        // Glyph of Avenging Wrath: Reduces the cooldown of your Hammer of Wrath spell by $54938s1% while Avenging Wrath is active.

        MAJOR_PALADIN_GLYPH_OF_DIVINITY = 198,
        // Glyph of Divinity: Your Lay on Hands grants twice as much mana as normal and also grants you as much mana as it grants your target.

        MAJOR_PALADIN_GLYPH_OF_SEAL_OF_WISDOM = 199,
        // Glyph of Seal of Wisdom: While Seal of Wisdom is active, the cost of your healing spells is reduced by $54940s1%.

        MAJOR_PALADIN_GLYPH_OF_SEAL_OF_LIGHT = 200,
        // Glyph of Seal of Light: While Seal of Light is active, the effect of your healing spells is increased by $54943s1%.

        MAJOR_SHAMAN_GLYPH_OF_WATER_MASTERY = 211,
        // Glyph of Water Mastery: Increases the passive mana regeneration of your Water Shield spell by $55436s1%.

        MAJOR_SHAMAN_GLYPH_OF_CHAIN_HEAL = 212,
        // Glyph of Chain Heal: Your Chain Heal heals 1 additional target.

        MAJOR_SHAMAN_GLYPH_OF_CHAIN_LIGHTNING = 213,
        // Glyph of Chain Lightning: Your Chain Lightning strikes 1 additional target.

        MAJOR_SHAMAN_GLYPH_OF_LAVA = 214,
        // Glyph of Lava: Your Lava Burst spell gains an additional $55454s1% of your spellpower.

        MAJOR_SHAMAN_GLYPH_OF_SHOCKING = 215,
        // Glyph of Shocking: Reduces the global cooldown triggered by your shock spells to $m2 sec.

        MAJOR_SHAMAN_GLYPH_OF_EARTHLIVING_WEAPON = 216,
        // Glyph of Earthliving Weapon: Increases the chance for your Earthliving weapon to trigger by $55439s1%.

        MAJOR_SHAMAN_GLYPH_OF_FIRE_ELEMENTAL_TOTEM = 217,
        // Glyph of Fire Elemental Totem: Reduces the cooldown of your Fire Elemental Totem by ${$55455m1/-60000} min.

        MAJOR_SHAMAN_GLYPH_OF_FIRE_NOVA = 218,
        // Glyph of Fire Nova: Reduces the cooldown of your Fire Nova spell by ${$55450m1/-1000} seconds.

        MAJOR_SHAMAN_GLYPH_OF_FLAME_SHOCK = 219,
        // Glyph of Flame Shock: Increases the critical strike damage bonus of your Flame Shock damage by $55447s1%.

        MAJOR_SHAMAN_GLYPH_OF_FLAMETONGUE_WEAPON = 220,
        // Glyph of Flametongue Weapon: Increases spell critical strike chance by $55451s1% while Flametongue Weapon is active.

        MAJOR_SHAMAN_GLYPH_OF_FROST_SHOCK = 221,
        // Glyph of Frost Shock: Increases the duration of your Frost Shock by ${$55443m1/1000} sec.

        MAJOR_SHAMAN_GLYPH_OF_HEALING_STREAM_TOTEM = 222,
        // Glyph of Healing Stream Totem: Your Healing Stream Totem heals for an additional $55456s1%.

        MAJOR_SHAMAN_GLYPH_OF_HEALING_WAVE = 223,
        // Glyph of Healing Wave: Your Healing Wave also heals you for $55440s1% of the healing effect when you heal someone else.

        MAJOR_SHAMAN_GLYPH_OF_LESSER_HEALING_WAVE = 224,
        // Glyph of Lesser Healing Wave: Your Lesser Healing Wave heals for $55438s1% more if the target is also affected by Earth Shield.

        MAJOR_SHAMAN_GLYPH_OF_LIGHTNING_SHIELD = 225,
        // Glyph of Lightning Shield: Increases the damage from Lightning Shield by $55448s1%.

        MAJOR_SHAMAN_GLYPH_OF_LIGHTNING_BOLT = 226,
        // Glyph of Lightning Bolt: Increases the damage dealt by Lightning Bolt by $55453s1%.

        MAJOR_SHAMAN_GLYPH_OF_STORMSTRIKE = 228,
        // Glyph of Stormstrike: Increases the Nature damage bonus from your Stormstrike ability by an additional $55446s1%.

        MAJOR_SHAMAN_GLYPH_OF_LAVA_LASH = 229,
        // Glyph of Lava Lash: Damage on your Lava Lash is increased by an additional $55444s1% if your weapon is enchanted with Flametongue.

        MAJOR_SHAMAN_GLYPH_OF_ELEMENTAL_MASTERY = 230,
        // Glyph of Elemental Mastery: Reduces the cooldown of your Elemental Mastery ability by ${$55452m1/-1000} sec.

        MAJOR_SHAMAN_GLYPH_OF_WINDFURY_WEAPON = 231,
        // Glyph of Windfury Weapon: Increases the chance per swing for Windfury Weapon to trigger by $55445s1%.

        MAJOR_PRIEST_GLYPH_OF_CIRCLE_OF_HEALING = 251,
        // Glyph of Circle of Healing: Your Circle of Healing spell heals 1 additional target.

        MAJOR_PRIEST_GLYPH_OF_DISPEL_MAGIC = 252,
        // Glyph of Dispel Magic: Your Dispel Magic spell also heals your target for $55677s1% of maximum health.

        MAJOR_PRIEST_GLYPH_OF_FADE = 253,
        // Glyph of Fade: Reduces the cooldown of your Fade spell by ${$55684m2/-1000} sec.

        MAJOR_PRIEST_GLYPH_OF_FEAR_WARD = 254,
        // Glyph of Fear Ward: Reduces cooldown and duration of Fear Ward by ${$55678m1/-1000} sec.

        MAJOR_PRIEST_GLYPH_OF_FLASH_HEAL = 255,
        // Glyph of Flash Heal: Reduces the mana cost of your Flash Heal by $55679s1%.

        MAJOR_PRIEST_GLYPH_OF_HOLY_NOVA = 256,
        // Glyph of Holy Nova: Increases the damage and healing of your Holy Nova spell by an additional $55683s1%.

        MAJOR_PRIEST_GLYPH_OF_INNER_FIRE = 257,
        // Glyph of Inner Fire: Increases the armor from your Inner Fire spell by $55686m1%.

        MAJOR_PRIEST_GLYPH_OF_LIGHTWELL = 258,
        // Glyph of Lightwell: Increases the amount healed by your Lightwell by $55673s1%

        MAJOR_PRIEST_GLYPH_OF_MASS_DISPEL = 259,
        // Glyph of Mass Dispel: Reduces the mana cost of Mass Dispel by $55691s1%.

        MAJOR_PRIEST_GLYPH_OF_MIND_CONTROL = 260,
        // Glyph of Mind Control: Reduces the chance targets will resist or break your Mind Control spell by an additional $55688s1%.

        MAJOR_PRIEST_GLYPH_OF_SHADOW_WORD_PAIN = 261,
        // Glyph of Shadow Word: Pain: The periodic damage ticks of your Shadow Word: Pain spell restore $s1% of your base mana.

        MAJOR_PRIEST_GLYPH_OF_POWER_WORD_SHIELD = 263,
        // Glyph of Power Word: Shield: Your Power Word: Shield also heals the target for $55672s1% of the absorption amount.

        MAJOR_PRIEST_GLYPH_OF_PRAYER_OF_HEALING = 264,
        // Glyph of Prayer of Healing: Your Prayer of Healing spell also heals an additional $55680s1% of its initial heal over 6 sec.

        MAJOR_PRIEST_GLYPH_OF_PSYCHIC_SCREAM = 265,
        // Glyph of Psychic Scream: Increases the duration of your Psychic Scream by ${$55676m1/1000} sec. and increases its cooldown by ${$55676m2/1000} sec.

        MAJOR_PRIEST_GLYPH_OF_RENEW = 266,
        // Glyph of Renew: Reduces the duration of your Renew by ${$55674m1/-1000} sec. but increases the amount healed each tick by $55674s2%.

        MAJOR_PRIEST_GLYPH_OF_SCOURGE_IMPRISONMENT = 267,
        // Glyph of Scourge Imprisonment: Reduces the cast time of your Shackle Undead by ${$55690m1/-1000}.1 sec.

        MAJOR_PRIEST_GLYPH_OF_SHADOW_WORD_DEATH = 268,
        // Glyph of Shadow Word: Death: Targets below $55682s1% health take an additional $55682s2% damage from your Shadow Word: Death spell.

        MAJOR_PRIEST_GLYPH_OF_MIND_FLAY = 269,
        // Glyph of Mind Flay: Increases the damage done by your Mind Flay spell by $55687s1% when your target is afflicted with Shadow Word: Pain.

        MAJOR_PRIEST_GLYPH_OF_SMITE = 270,
        // Glyph of Smite: Your Smite spell inflicts an additional $55692s1% damage against targets afflicted by Holy Fire.

        MAJOR_PRIEST_GLYPH_OF_SPIRIT_OF_REDEMPTION = 271,
        // Glyph of Spirit of Redemption: Increases the duration of Spirit of Redemption by ${$55685m2/1000} sec.

        MAJOR_WARLOCK_GLYPH_OF_INCINERATE = 272,
        // Glyph of Incinerate: Increases the damage done by Incinerate by $56242m1%.

        MAJOR_WARLOCK_GLYPH_OF_CONFLAGRATE = 273,
        // Glyph of Conflagrate: Your Conflagrate spell no longer consumes your Immolate or Shadowflame spell from the target.

        MAJOR_WARLOCK_GLYPH_OF_CORRUPTION = 274,
        // Glyph of Corruption: Your Corruption spell has a 4% chance to cause you to enter a Shadow Trance state after damaging the opponent.  The Shadow Trance state reduces the casting time of your next Shadow Bolt spell by $17941s1%.

        MAJOR_WARLOCK_GLYPH_OF_CURSE_OF_AGONY = 275,
        // Glyph of Curse of Agony: Increases the duration of your Curse of Agony by ${$56241m1/1000} sec.

        MAJOR_WARLOCK_GLYPH_OF_DEATH_COIL = 276,
        // Glyph of Death Coil: Increases the duration of your Death Coil by ${$56232m1/1000}.1 sec.

        MAJOR_WARLOCK_GLYPH_OF_FEAR = 277,
        // Glyph of Fear: Increases the damage your Fear target can take before the Fear effect is removed by $56244s1%.

        MAJOR_WARLOCK_GLYPH_OF_FELGUARD = 278,
        // Glyph of Felguard: Increases the Felguard's total attack power by $56246s1%.

        MAJOR_WARLOCK_GLYPH_OF_FELHUNTER = 279,
        // Glyph of Felhunter: When your Felhunter uses Devour Magic, you will also be healed for that amount.

        MAJOR_WARLOCK_GLYPH_OF_HEALTH_FUNNEL = 280,
        // Glyph of Health Funnel: Reduces the pushback suffered from damaging attacks while channeling your Health Funnel spell by $56238s1%.

        MAJOR_WARLOCK_GLYPH_OF_HEALTHSTONE = 281,
        // Glyph of Healthstone: You receive $56224s1% more healing from using a healthstone.

        MAJOR_WARLOCK_GLYPH_OF_HOWL_OF_TERROR = 282,
        // Glyph of Howl of Terror: Reduces the cooldown on your Howl of Terror spell by ${$56217m1/-1000} sec.

        MAJOR_WARLOCK_GLYPH_OF_IMMOLATE = 283,
        // Glyph of Immolate: Increases the periodic damage of your Immolate by $56228s2%.

        MAJOR_WARLOCK_GLYPH_OF_IMP = 284,
        // Glyph of Imp: Increases the damage done by your Imp's Firebolt spell by $56248s1%.

        MAJOR_WARLOCK_GLYPH_OF_SEARING_PAIN = 285,
        // Glyph of Searing Pain: Increases the critical strike bonus of your Searing Pain by $56226s1%.

        MAJOR_WARLOCK_GLYPH_OF_SHADOW_BOLT = 286,
        // Glyph of Shadow Bolt: Reduces the mana cost of your Shadow Bolt by $56240s1%.

        MAJOR_WARLOCK_GLYPH_OF_SHADOWBURN = 287,
        // Glyph of Shadowburn: Increases the critical strike chance of Shadowburn by $56229s1% when the target is below 35% health.

        MAJOR_WARLOCK_GLYPH_OF_SIPHON_LIFE = 288,
        // Glyph of Siphon Life: Increases the healing you receive from your Siphon Life talent by $56216s1%.

        MAJOR_WARLOCK_GLYPH_OF_SOULSTONE = 289,
        // Glyph of Soulstone: Increases the amount of health you gain from resurrecting via a Soulstone by $56231s1%.

        MAJOR_WARLOCK_GLYPH_OF_SUCCUBUS = 290,
        // Glyph of Succubus: Your Succubus's Seduction ability also removes all damage over time effects from the target.

        MAJOR_WARLOCK_GLYPH_OF_UNSTABLE_AFFLICTION = 291,
        // Glyph of Unstable Affliction: Decreases the casting time of your Unstable Affliction by ${$56233m1/-1000}.1 sec.

        MAJOR_WARLOCK_GLYPH_OF_VOIDWALKER = 292,
        // Glyph of Voidwalker: Increases your Voidwalker's total Stamina by $56247s1%.

        MAJOR_MAGE_GLYPH_OF_ARCANE_EXPLOSION = 311,
        // Glyph of Arcane Explosion: Reduces mana cost of Arcane Explosion by $56360s1%.

        MAJOR_MAGE_GLYPH_OF_ARCANE_MISSILES = 312,
        // Glyph of Arcane Missiles: Increases the critical strike damage bonus of Arcane Missiles by $56363s1%.

        MAJOR_MAGE_GLYPH_OF_ARCANE_POWER = 313,
        // Glyph of Arcane Power: Increases the duration of Arcane Power by ${$56381m1/1000} sec.

        MAJOR_MAGE_GLYPH_OF_BLINK = 314,
        // Glyph of Blink: Increases the distance you travel with the Blink spell by $56365s1 yards.

        MAJOR_MAGE_GLYPH_OF_EVOCATION = 315,
        // Glyph of Evocation: Your Evocation ability also causes you to regain ${$56380m1*4}% of your health over its duration.

        MAJOR_MAGE_GLYPH_OF_FIREBALL = 316,
        // Glyph of Fireball: Reduces the casting time of your Fireball spell by ${$56368m1/-1000}.2 sec, but removes the damage over time effect.

        MAJOR_MAGE_GLYPH_OF_FIRE_BLAST = 317,
        // Glyph of Fire Blast: Increases the critical strike chance of Fire Blast by $56369s1% when the target is stunned or incapacitated.

        MAJOR_MAGE_GLYPH_OF_FROST_NOVA = 318,
        // Glyph of Frost Nova: Your Frost Nova targets can take an additional $56376s1% damage before the Frost Nova effect automatically breaks.

        MAJOR_MAGE_GLYPH_OF_FROSTBOLT = 319,
        // Glyph of Frostbolt: Increases the damage dealt by Frostbolt by $56370s1%, but removes the slowing effect.

        MAJOR_MAGE_GLYPH_OF_ICE_ARMOR = 320,
        // Glyph of Ice Armor: Your Ice Armor and Frost Armor spells grant an additional $56384s1% armor and resistance.

        MAJOR_MAGE_GLYPH_OF_ICE_BLOCK = 321,
        // Glyph of Ice Block: Your Frost Nova cooldown is now reset every time you use Ice Block.

        MAJOR_MAGE_GLYPH_OF_ICE_LANCE = 322,
        // Glyph of Ice Lance: Your Ice Lance now causes $56377s1 times damage against frozen targets higher level than you instead of triple damage.

        MAJOR_MAGE_GLYPH_OF_ICY_VEINS = 323,
        // Glyph of Icy Veins: Your Icy Veins ability also removes all movement slowing and cast time slowing effects.

        MAJOR_MAGE_GLYPH_OF_SCORCH = 324,
        // Glyph of Scorch: Increases the damage of your Scorch spell by $56371s1%.

        MAJOR_MAGE_GLYPH_OF_INVISIBILITY = 325,
        // Glyph of Invisibility: Increases the duration of the Invisibility effect by $/1000;56366s1 sec.

        MAJOR_MAGE_GLYPH_OF_MAGE_ARMOR = 326,
        // Glyph of Mage Armor: Your Mage Armor spell grants an additional $56383s1% mana regeneration while casting.

        MAJOR_MAGE_GLYPH_OF_MANA_GEM = 327,
        // Glyph of Mana Gem: Increases the mana received from using a mana gem by $56367s1%.

        MAJOR_MAGE_GLYPH_OF_MOLTEN_ARMOR = 328,
        // Glyph of Molten Armor: Your Molten Armor grants an additional $56382s1% of your spirit as critical strike rating.

        MAJOR_MAGE_GLYPH_OF_POLYMORPH = 329,
        // Glyph of Polymorph: Your Polymorph spell also removes all damage over time effects from the target.

        MAJOR_MAGE_GLYPH_OF_REMOVE_CURSE = 330,
        // Glyph of Remove Curse: Your Remove Curse spell also makes the target immune to all curses for $60803d.

        MAJOR_MAGE_GLYPH_OF_WATER_ELEMENTAL = 331,
        // Glyph of Water Elemental: Reduces the cooldown of your Summon Water Elemental spell by ${$56373m1/-1000} sec.

        MAJOR_HUNTER_GLYPH_OF_AIMED_SHOT = 351,
        // Glyph of Aimed Shot: Reduces the cooldown of your Aimed Shot ability by ${$56824m1/-1000} sec.

        MAJOR_HUNTER_GLYPH_OF_ARCANE_SHOT = 352,
        // Glyph of Arcane Shot: Your Arcane Shot refunds $56841s1% of its mana cost if the target has one of your Stings active on it.

        MAJOR_HUNTER_GLYPH_OF_THE_BEAST = 353,
        // Glyph of the Beast: Increases the attack power bonus of Aspect of the Beast for you and your pet by an additional $56857s1%.

        MAJOR_HUNTER_GLYPH_OF_MENDING = 354,
        // Glyph of Mending: Increases the healing done by your Mend Pet ability by $56833s1%.

        MAJOR_HUNTER_GLYPH_OF_ASPECT_OF_THE_VIPER = 355,
        // Glyph of Aspect of the Viper: Increases the amount of mana gained from attacks while Aspect of the Viper is active by $56851s1%.

        MAJOR_HUNTER_GLYPH_OF_BESTIAL_WRATH = 356,
        // Glyph of Bestial Wrath: Decreases the cooldown of Bestial Wrath by ${$56830m1/-1000} sec.

        MAJOR_HUNTER_GLYPH_OF_DETERRENCE = 357,
        // Glyph of Deterrence: Decreases the cooldown of Deterrence by ${$56850m1/-1000} sec.

        MAJOR_HUNTER_GLYPH_OF_DISENGAGE = 358,
        // Glyph of Disengage: Decreases the cooldown of Disengage by ${$56844m1/-1000} sec.

        MAJOR_HUNTER_GLYPH_OF_FREEZING_TRAP = 359,
        // Glyph of Freezing Trap: When your Freezing Trap breaks, the victim's movement speed is reduced by $61394s1% for $61394d.

        MAJOR_HUNTER_GLYPH_OF_FROST_TRAP = 360,
        // Glyph of Frost Trap: Increases the radius of the effect from your Frost Trap by $56847s1 yards.

        MAJOR_HUNTER_GLYPH_OF_HUNTERS_MARK = 361,
        // Glyph of Hunter's Mark: Increases the attack power bonus of your Hunter's Mark by $56829s1%.

        MAJOR_HUNTER_GLYPH_OF_IMMOLATION_TRAP = 362,
        // Glyph of Immolation Trap: Decreases the duration of the effect from your Immolation Trap by 6 sec., but damage while active is increased by $56846s2%.

        MAJOR_HUNTER_GLYPH_OF_THE_HAWK = 363,
        // Glyph of the Hawk: Increases the haste bonus of the Improved Aspect of the Hawk effect by an additional $56856s1%.

        MAJOR_HUNTER_GLYPH_OF_MULTISHOT = 364,
        // Glyph of Multi-Shot: Decreases the cooldown of Multi-Shot by ${$56836m1/-1000} sec.

        MAJOR_HUNTER_GLYPH_OF_RAPID_FIRE = 365,
        // Glyph of Rapid Fire: Increases the haste from Rapid Fire by an additional $56828s1%.

        MAJOR_HUNTER_GLYPH_OF_SERPENT_STING = 366,
        // Glyph of Serpent Sting: Increases the duration of your Serpent Sting by ${$56832m1/1000} sec.

        MAJOR_HUNTER_GLYPH_OF_SNAKE_TRAP = 367,
        // Glyph of Snake Trap: Snakes from your Snake Trap take $56849s1% reduced damage from area of effect spells.

        MAJOR_HUNTER_GLYPH_OF_STEADY_SHOT = 368,
        // Glyph of Steady Shot: Increases the damage dealt by Steady Shot by $56826s1% when your target is afflicted with Serpent Sting.

        MAJOR_HUNTER_GLYPH_OF_TRUESHOT_AURA = 369,
        // Glyph of Trueshot Aura: While your Trueshot Aura is active, you have $56842s1% increased critical strike chance on your Aimed Shot.

        MAJOR_HUNTER_GLYPH_OF_VOLLEY = 370,
        // Glyph of Volley: Decreases the mana cost of Volley by $56838s1%.

        MAJOR_HUNTER_GLYPH_OF_WYVERN_STING = 371,
        // Glyph of Wyvern Sting: Decreases the cooldown of your Wyvern Sting by ${$m1/-1000} sec.

        MAJOR_ROGUE_GLYPH_OF_ADRENALINE_RUSH = 391,
        // Glyph of Adrenaline Rush: Increases the duration of Adrenaline Rush by ${$56808m1/1000} sec.

        MAJOR_ROGUE_GLYPH_OF_AMBUSH = 392,
        // Glyph of Ambush: Increases the range on Ambush by $56813s1 yards.

        MAJOR_ROGUE_GLYPH_OF_BACKSTAB = 393,
        // Glyph of Backstab: Your Backstab increases the duration of your Rupture effect on the target by $56800s1 sec, up to a maximum of $56800s2 additional sec.

        MAJOR_ROGUE_GLYPH_OF_BLADE_FLURRY = 394,
        // Glyph of Blade Flurry: Reduces the energy cost of Blade Flurry by $56818s1%.

        MAJOR_ROGUE_GLYPH_OF_CRIPPLING_POISON = 395,
        // Glyph of Crippling Poison: Increases the chance to inflict your target with Crippling Poison by an additional $56820s1%.

        MAJOR_ROGUE_GLYPH_OF_DEADLY_THROW = 396,
        // Glyph of Deadly Throw: Increases the slowing effect on Deadly Throw by $56806s1%.

        MAJOR_ROGUE_GLYPH_OF_EVASION = 397,
        // Glyph of Evasion: Increases the duration of Evasion by ${$56799m1/1000} sec.

        MAJOR_ROGUE_GLYPH_OF_EVISCERATE = 398,
        // Glyph of Eviscerate: Increases the critical strike chance of Eviscerate by $56802s1%.

        MAJOR_ROGUE_GLYPH_OF_EXPOSE_ARMOR = 399,
        // Glyph of Expose Armor: Increases the duration of Expose Armor by ${$56803m1/1000} sec.

        MAJOR_ROGUE_GLYPH_OF_FEINT = 400,
        // Glyph of Feint: Reduces the energy cost of Feint by $56804s1.

        MAJOR_ROGUE_GLYPH_OF_GARROTE = 401,
        // Glyph of Garrote: Reduces the duration of your Garrote ability by ${$56812m1/-1000} sec and increases the total damage it deals by 20%.

        MAJOR_ROGUE_GLYPH_OF_GHOSTLY_STRIKE = 402,
        // Glyph of Ghostly Strike: Increases the damage dealt by Ghostly Strike by $56814s2% and the duration of its effect by ${$56814m1/1000} sec, but increases its cooldown by ${$56814m3/1000} sec.

        MAJOR_ROGUE_GLYPH_OF_GOUGE = 403,
        // Glyph of Gouge: Reduces the energy cost of Gouge by $56809s1.

        MAJOR_ROGUE_GLYPH_OF_HEMORRHAGE = 404,
        // Glyph of Hemorrhage: Increases the damage bonus against targets afflicted by Hemorrhage by $56807s1%.

        MAJOR_ROGUE_GLYPH_OF_PREPARATION = 405,
        // Glyph of Preparation: Your Preparation ability also instantly resets the cooldown of Blade Flurry, Dismantle, and Kick.

        MAJOR_ROGUE_GLYPH_OF_RUPTURE = 406,
        // Glyph of Rupture: Increases the duration of Rupture by ${$56801m1/1000} sec.

        MAJOR_ROGUE_GLYPH_OF_SAP = 407,
        // Glyph of Sap: Increases the duration of Sap by ${$56798m1/1000} sec.

        MAJOR_ROGUE_GLYPH_OF_VIGOR = 408,
        // Glyph of Vigor: Vigor grants an additional $56805s1 maximum energy.

        MAJOR_ROGUE_GLYPH_OF_SINISTER_STRIKE = 409,
        // Glyph of Sinister Strike: Your Sinister Strike critical strikes have a $h% chance to add an additional combo point.

        MAJOR_ROGUE_GLYPH_OF_SLICE_AND_DICE = 410,
        // Glyph of Slice and Dice: Increases the duration of Slice and Dice by ${$56810m1/1000} sec.

        MAJOR_ROGUE_GLYPH_OF_SPRINT = 411,
        // Glyph of Sprint: Increases the movement speed of your Sprint ability by an additional $56811s1%.

        MAJOR_WARRIOR_GLYPH_OF_MORTAL_STRIKE = 489,
        // Glyph of Mortal Strike: Increases the damage of your Mortal Strike ability by $58368s2%.

        MAJOR_WARRIOR_GLYPH_OF_BLOODTHIRST = 490,
        // Glyph of Bloodthirst: Increases the healing you receive from your Bloodthirst ability by $58369s1%.

        MAJOR_WARRIOR_GLYPH_OF_RAPID_CHARGE = 491,
        // Glyph of Rapid Charge: Reduces the cooldown of your Charge ability by $58355s1%.

        MAJOR_WARRIOR_GLYPH_OF_CLEAVING = 492,
        // Glyph of Cleaving: Increases the number of targets your Cleave hits by 1.

        MAJOR_WARRIOR_GLYPH_OF_DEVASTATE = 493,
        // Glyph of Devastate: Your Devastate ability now applies two stacks of Sunder Armor.

        MAJOR_WARRIOR_GLYPH_OF_EXECUTION = 494,
        // Glyph of Execution: Your Execute ability deals damage as if you had $58367s1 additional rage.

        MAJOR_WARRIOR_GLYPH_OF_HAMSTRING = 495,
        // Glyph of Hamstring: Gives your Hamstring ability a $58372h% chance to immobilize the target for $58373d.

        MAJOR_WARRIOR_GLYPH_OF_HEROIC_STRIKE = 496,
        // Glyph of Heroic Strike: You gain ${$58357m1/10} rage when you critically strike with your Heroic Strike ability.

        MAJOR_WARRIOR_GLYPH_OF_INTERVENE = 497,
        // Glyph of Intervene: Increases the number attacks you intercept for your Intervene target by $58377s1.

        MAJOR_WARRIOR_GLYPH_OF_BARBARIC_INSULTS = 498,
        // Glyph of Barbaric Insults: Your Mocking Blow ability generates $58365s1% additional threat.

        MAJOR_WARRIOR_GLYPH_OF_OVERPOWER = 499,
        // Glyph of Overpower: Adds a $58386m1% chance to enable your Overpower when your attacks are parried.

        MAJOR_WARRIOR_GLYPH_OF_RENDING = 500,
        // Glyph of Rending: Increases the duration of your Rend ability by ${$58385m1/1000} sec.

        MAJOR_WARRIOR_GLYPH_OF_REVENGE = 501,
        // Glyph of Revenge: After using Revenge, your next Heroic Strike costs no rage.

        MAJOR_WARRIOR_GLYPH_OF_BLOCKING = 502,
        // Glyph of Blocking: Increases your block value by $58374s1% for $58374d after using your Shield Slam ability.

        MAJOR_WARRIOR_GLYPH_OF_LAST_STAND = 503,
        // Glyph of Last Stand: Reduces the cooldown of your Last Stand ability by ${$58376m1/-60000} min.

        MAJOR_WARRIOR_GLYPH_OF_SUNDER_ARMOR = 504,
        // Glyph of Sunder Armor: Your Sunder Armor ability affects a second nearby target.

        MAJOR_WARRIOR_GLYPH_OF_SWEEPING_STRIKES = 505,
        // Glyph of Sweeping Strikes: Reduces the rage cost of your Sweeping Strikes ability by $58384s1%.

        MAJOR_WARRIOR_GLYPH_OF_TAUNT = 506,
        // Glyph of Taunt: Increases the chance for your Taunt ability to succeed by $58353m1%.

        MAJOR_WARRIOR_GLYPH_OF_RESONATING_POWER = 507,
        // Glyph of Resonating Power: Reduces the rage cost of your Thunder Clap ability by ${$58356m1/-10}.

        MAJOR_WARRIOR_GLYPH_OF_VICTORY_RUSH = 508,
        // Glyph of Victory Rush: Your Victory Rush ability has a $58382s1% increased critical strike chance.

        MAJOR_WARRIOR_GLYPH_OF_WHIRLWIND = 509,
        // Glyph of Whirlwind: Reduces the cooldown of your Whirlwind by ${$58370m1/-1000} sec.

        MAJOR_DEATHKNIGHT_GLYPH_OF_DARK_COMMAND = 511,
        // Glyph of Dark Command: Increases the chance for your Dark Command ability to work successfully by $s1%.

        MAJOR_DEATHKNIGHT_GLYPH_OF_ANTIMAGIC_SHELL = 512,
        // Glyph of Anti-Magic Shell: Increases the duration of your Anti-Magic Shell by ${$58623m1/1000} sec.

        MAJOR_DEATHKNIGHT_GLYPH_OF_HEART_STRIKE = 513,
        // Glyph of Heart Strike: Your Heart Strike also reduces the movement speed of your target by $58617s1% for $58617d.

        MAJOR_DEATHKNIGHT_GLYPH_OF_BONE_SHIELD = 515,
        // Glyph of Bone Shield: Adds $58673s1 additional $Lcharge:charges; to your Bone Shield.

        MAJOR_DEATHKNIGHT_GLYPH_OF_CHAINS_OF_ICE = 516,
        // Glyph of Chains of Ice: Your Chains of Ice also causes $58621s1 Frost damage, increased by your attack power.

        MAJOR_DEATHKNIGHT_GLYPH_OF_DEATH_GRIP = 519,
        // Glyph of Death Grip: When you deal a killing blow that grants honor or experience, the cooldown of your Death Grip is refreshed.

        MAJOR_DEATHKNIGHT_GLYPH_OF_DEATH_AND_DECAY = 520,
        // Glyph of Death and Decay: Damage of your Death and Decay spell increased by $58629s1%.

        MAJOR_DEATHKNIGHT_GLYPH_OF_FROST_STRIKE = 521,
        // Glyph of Frost Strike: Reduces the cost of your Frost Strike by ${$58647m1/-10} Runic Power.

        MAJOR_DEATHKNIGHT_GLYPH_OF_ICEBOUND_FORTITUDE = 523,
        // Glyph of Icebound Fortitude: Your Icebound Fortitude now always grants at least $58625s1% damage reduction, regardless of your defense skill.

        MAJOR_DEATHKNIGHT_GLYPH_OF_ICY_TOUCH = 524,
        // Glyph of Icy Touch: Your Frost Fever disease deals $58631s1% additional damage.

        MAJOR_DEATHKNIGHT_GLYPH_OF_OBLITERATE = 525,
        // Glyph of Obliterate: Increases the damage of your Obliterate ability by $m3%.

        MAJOR_DEATHKNIGHT_GLYPH_OF_PLAGUE_STRIKE = 526,
        // Glyph of Plague Strike: Your Plague Strike does $s1% additional damage.

        MAJOR_DEATHKNIGHT_GLYPH_OF_THE_GHOUL = 527,
        // Glyph of the Ghoul: Your Ghoul receives an additional $58686s1% of your Strength and $58686s1% of your Stamina.

        MAJOR_DEATHKNIGHT_GLYPH_OF_RUNE_STRIKE = 528,
        // Glyph of Rune Strike: Increases the critical strike chance of your Rune Strike by $58669s2%.

        MAJOR_DEATHKNIGHT_GLYPH_OF_SCOURGE_STRIKE = 529,
        // Glyph of Scourge Strike: Your Scourge Strike increases the duration of your diseases on the target by $58642m1 sec, up to a maximum of $58642m2 additional seconds.

        MAJOR_DEATHKNIGHT_GLYPH_OF_STRANGULATE = 530,
        // Glyph of Strangulate: Reduces the cooldown of your Strangulate by ${$58618m1/-1000} sec.

        MAJOR_DEATHKNIGHT_GLYPH_OF_UNBREAKABLE_ARMOR = 531,
        // Glyph of Unbreakable Armor: Increases the total armor granted by Unbreakable Armor to $58635m2%.

        MAJOR_DEATHKNIGHT_GLYPH_OF_VAMPIRIC_BLOOD = 532,
        // Glyph of Vampiric Blood: Increases  the duration of your Vampiric Blood by ${$58676m1/1000} sec.

        MAJOR_DEATHKNIGHT_GLYPH_OF_RUNE_TAP = 556,
        // Glyph of Rune Tap: Your Rune Tap heals yourself for an additional 10% of the effect, and also heals your party for 10% of their maximum health.

        MAJOR_DEATHKNIGHT_GLYPH_OF_BLOOD_STRIKE = 557,
        // Glyph of Blood Strike: Your Blood Strike causes an additional 20% damage to snared targets.

        MAJOR_DEATHKNIGHT_GLYPH_OF_DEATH_STRIKE = 558,
        // Glyph of Death Strike: Increases your Death Strike's damage by $59336s1% for every $59336s1 runic power you currently have (up to a maximum of $59336s2%).  The runic power is not consumed by this effect.

        MAJOR_PALADIN_GLYPH_OF_HOLY_WRATH = 559,
        // Glyph of Holy Wrath: Reduces the cooldown of your Holy Wrath spell by ${$56420m1/-1000} sec.

        MAJOR_PALADIN_GLYPH_OF_SEAL_OF_RIGHTEOUSNESS = 560,
        // Glyph of Seal of Righteousness: Increases the damage done by Seal of Righteousness by $56414s1%.

        MAJOR_PALADIN_GLYPH_OF_SEAL_OF_VENGEANCE = 561,
        // Glyph of Seal of Vengeance: Your Seal of Vengeance or Seal of Corruption also grants $56416s1 expertise while active.

        MAJOR_MAGE_GLYPH_OF_FROSTFIRE = 591,
        // Glyph of Frostfire: Increases the initial damage dealt by Frostfire Bolt by $61205s1% and its critical strike chance by $61205s2%.

        MAJOR_DRUID_GLYPH_OF_FOCUS = 631,
        // Glyph of Focus: Increases the damage done by Starfall by $62080s2%, but decreases its radius by $62080s1%.

        MAJOR_MAGE_GLYPH_OF_ARCANE_BLAST = 651,
        // Glyph of Arcane Blast: Increases the damage from your Arcane Blast buff by $62210s1%.

        MAJOR_DRUID_GLYPH_OF_BERSERK = 671,
        // Glyph of Berserk: Increases the duration of Berserk by ${$62969m1/1000} sec.

        MAJOR_DRUID_GLYPH_OF_WILD_GROWTH = 672,
        // Glyph of Wild Growth: Wild Growth can affect $62970s1 additional target.

        MAJOR_DRUID_GLYPH_OF_NOURISH = 673,
        // Glyph of Nourish: Your Nourish heals an additional $62971s1% for each of your heal over time effects present on the target.

        MAJOR_DRUID_GLYPH_OF_SAVAGE_ROAR = 674,
        // Glyph of Savage Roar: Your Savage Roar ability grants an additional $63055s1% bonus damage done.

        MAJOR_DRUID_GLYPH_OF_MONSOON = 675,
        // Glyph of Monsoon: Reduces the cooldown of your Typhoon spell by ${$63056m1/-1000} sec.

        MAJOR_DRUID_GLYPH_OF_BARKSKIN = 676,
        // Glyph of Barkskin: Reduces the chance you'll be critically hit by melee attacks by $63057s1% while Barkskin is active.

        MAJOR_HUNTER_GLYPH_OF_CHIMERA_SHOT = 677,
        // Glyph of Chimera Shot: Reduces the cooldown of Chimera Shot by ${$63065m1/-1000} sec.

        MAJOR_HUNTER_GLYPH_OF_EXPLOSIVE_SHOT = 691,
        // Glyph of Explosive Shot: Increases the critical strike chance of Explosive Shot by $63066s1%.

        MAJOR_HUNTER_GLYPH_OF_KILL_SHOT = 692,
        // Glyph of Kill Shot: Reduces the cooldown of Kill Shot by ${$63067m1/-1000} sec.

        MAJOR_HUNTER_GLYPH_OF_EXPLOSIVE_TRAP = 693,
        // Glyph of Explosive Trap: The periodic damage from your Explosive Trap can now be critical strikes.

        MAJOR_HUNTER_GLYPH_OF_SCATTER_SHOT = 694,
        // Glyph of Scatter Shot: Increases the range of Scatter Shot by $63069s1 yards.

        MAJOR_HUNTER_GLYPH_OF_RAPTOR_STRIKE = 695,
        // Glyph of Raptor Strike: Reduces damage taken by $63087s1% for $63087d after using Raptor Strike.

        MAJOR_MAGE_GLYPH_OF_DEEP_FREEZE = 696,
        // Glyph of Deep Freeze: Increases the range of Deep Freeze by $63090s1 yards.

        MAJOR_MAGE_GLYPH_OF_LIVING_BOMB = 697,
        // Glyph of Living Bomb: The periodic damage from your Living Bomb can now be critical strikes.

        MAJOR_MAGE_GLYPH_OF_ARCANE_BARRAGE = 698,
        // Glyph of Arcane Barrage: Reduces the mana cost of Arcane Barrage by $63092s1%.

        MAJOR_MAGE_GLYPH_OF_MIRROR_IMAGE = 699,
        // Glyph of Mirror Image: Your Mirror Image spell now creates a 4th copy.

        MAJOR_MAGE_GLYPH_OF_ICE_BARRIER = 700,
        // Glyph of Ice Barrier: Increases the amount of damage absorbed by your Ice Barrier by $63095s1%.

        MAJOR_PALADIN_GLYPH_OF_BEACON_OF_LIGHT = 701,
        // Glyph of Beacon of Light: Increases the duration of Beacon of Light by ${$63218m1/1000} sec.

        MAJOR_PALADIN_GLYPH_OF_HAMMER_OF_THE_RIGHTEOUS = 702,
        // Glyph of Hammer of the Righteous: Your Hammer of the Righteous hits $63219s1 additional target.

        MAJOR_PALADIN_GLYPH_OF_DIVINE_STORM = 703,
        // Glyph of Divine Storm: Your Divine Storm now heals for an additional $63220s1% of the damage it causes.

        MAJOR_PALADIN_GLYPH_OF_SHIELD_OF_RIGHTEOUSNESS = 704,
        // Glyph of Shield of Righteousness: Reduces the mana cost of Shield of Righteousness by $63222s1%.

        MAJOR_PALADIN_GLYPH_OF_DIVINE_PLEA = 705,
        // Glyph of Divine Plea: While Divine Plea is active, you take $63223s1% reduced damage from all sources.

        MAJOR_PALADIN_GLYPH_OF_HOLY_SHOCK = 706,
        // Glyph of Holy Shock: Reduces the cooldown of Holy Shock by ${$63224m1/-1000} sec.

        MAJOR_PALADIN_GLYPH_OF_SALVATION = 707,
        // Glyph of Salvation: When you cast Hand of Salvation on yourself, it also reduces damage taken by $63225s1%.

        MAJOR_PRIEST_GLYPH_OF_DISPERSION = 708,
        // Glyph of Dispersion: Reduces the cooldown on Dispersion by ${$63229m1/-1000} sec.

        MAJOR_PRIEST_GLYPH_OF_GUARDIAN_SPIRIT = 709,
        // Glyph of Guardian Spirit: If your Guardian Spirit lasts its entire duration without being triggered, the cooldown is reset to ${$63231m1/60} min.

        MAJOR_PRIEST_GLYPH_OF_PENANCE = 710,
        // Glyph of Penance: Reduces the cooldown of Penance by ${$63235m1/-1000} sec.

        MAJOR_PRIEST_GLYPH_OF_MIND_SEAR = 711,
        // Glyph of Mind Sear: Increases the radius of effect on Mind Sear by $63237s1 yards.

        MAJOR_PRIEST_GLYPH_OF_HYMN_OF_HOPE = 712,
        // Glyph of Hymn of Hope: Your Hymn of Hope lasts an additional ${$m1/1000} sec.

        MAJOR_PRIEST_GLYPH_OF_PAIN_SUPPRESSION = 713,
        // Glyph of Pain Suppression: Allows Pain Suppression to be cast while stunned.

        MAJOR_ROGUE_GLYPH_OF_HUNGER_FOR_BLOOD = 714,
        // Glyph of Hunger For Blood: Increases the bonus damage from Hunger For Blood by $63249s1%.

        MAJOR_ROGUE_GLYPH_OF_KILLING_SPREE = 715,
        // Glyph of Killing Spree: Reduces the cooldown on Killing Spree by ${$63252m1/-1000} sec.

        MAJOR_ROGUE_GLYPH_OF_SHADOW_DANCE = 716,
        // Glyph of Shadow Dance: Increases the duration of Shadow Dance by ${$63253m1/1000} sec.

        MAJOR_ROGUE_GLYPH_OF_FAN_OF_KNIVES = 731,
        // Glyph of Fan of Knives: Increases the damage done by Fan of Knives by $63254s1%.

        MAJOR_ROGUE_GLYPH_OF_TRICKS_OF_THE_TRADE = 732,
        // Glyph of Tricks of the Trade: The bonus damage and threat redirection granted by your Tricks of the Trade ability lasts an additional ${$63256m1/1000} sec.

        MAJOR_ROGUE_GLYPH_OF_MUTILATE = 733,
        // Glyph of Mutilate: Reduces the cost of Mutilate by $63268s1 energy.

        MAJOR_ROGUE_GLYPH_OF_CLOAK_OF_SHADOWS = 734,
        // Glyph of Cloak of Shadows: While Cloak of Shadows is active, you take $63269s1% less physical damage.

        MAJOR_SHAMAN_GLYPH_OF_THUNDER = 735,
        // Glyph of Thunder: Reduces the cooldown on Thunderstorm by ${$63270m1/-1000} sec.

        MAJOR_SHAMAN_GLYPH_OF_FERAL_SPIRIT = 736,
        // Glyph of Feral Spirit: Your spirit wolves gain an additional $63271s1% of your attack power.

        MAJOR_SHAMAN_GLYPH_OF_RIPTIDE = 737,
        // Glyph of Riptide: Increases the duration of Riptide by ${$63273m1/1000} sec.

        MAJOR_SHAMAN_GLYPH_OF_EARTH_SHIELD = 751,
        // Glyph of Earth Shield: Increases the amount healed by your Earth Shield by $63279s1%.

        MAJOR_SHAMAN_GLYPH_OF_TOTEM_OF_WRATH = 752,
        // Glyph of Totem of Wrath: When you cast Totem of Wrath, you gain $63280s1% of the totem's bonus spell power for $63283d.

        MAJOR_SHAMAN_GLYPH_OF_HEX = 753,
        // Glyph of Hex: Increases the damage your Hex target can take before the Hex effect is removed by $63291s1%.

        MAJOR_SHAMAN_GLYPH_OF_STONECLAW_TOTEM = 754,
        // Glyph of Stoneclaw Totem: Your Stoneclaw Totem also places a damage absorb shield on you, equal to $63298s1 times the strength of the shield it places on your totems.

        MAJOR_WARLOCK_GLYPH_OF_HAUNT = 755,
        // Glyph of Haunt: The bonus damage granted by your Haunt spell is increased by an additional $63302s1%.

        MAJOR_WARLOCK_GLYPH_OF_METAMORPHOSIS = 756,
        // Glyph of Metamorphosis: Increases the duration of your Metamorphosis by ${$63303m1/1000} sec.

        MAJOR_WARLOCK_GLYPH_OF_CHAOS_BOLT = 757,
        // Glyph of Chaos Bolt: Reduces the cooldown on Chaos Bolt by ${$63304m1/-1000} sec.

        MAJOR_WARLOCK_GLYPH_OF_DEMONIC_CIRCLE = 758,
        // Glyph of Demonic Circle: Reduces the cooldown on Demonic Circle by ${$63309m1/-1000} sec.

        MAJOR_WARLOCK_GLYPH_OF_SHADOWFLAME = 759,
        // Glyph of Shadowflame: Your Shadowflame also applies a $63310s1% movement speed slow on its victims.

        MAJOR_WARLOCK_GLYPH_OF_LIFE_TAP = 760,
        // Glyph of Life Tap: When you use Life Tap or Dark Pact, you gain $63321s1% of your Spirit as spell power for $63321d.

        MAJOR_WARLOCK_GLYPH_OF_SOUL_LINK = 761,
        // Glyph of Soul Link: Increases the percentage of damage shared via your Soul Link by an additional $63312s1%.

        MAJOR_WARRIOR_GLYPH_OF_BLADESTORM = 762,
        // Glyph of Bladestorm: Reduces the cooldown on Bladestorm by ${$63324m1/-1000} sec.

        MAJOR_WARRIOR_GLYPH_OF_SHOCKWAVE = 763,
        // Glyph of Shockwave: Reduces the cooldown on Shockwave by ${$63325m1/-1000} sec.

        MAJOR_WARRIOR_GLYPH_OF_VIGILANCE = 764,
        // Glyph of Vigilance: Your Vigilance ability transfers an additional $63326s1% of your target's threat to you.

        MAJOR_WARRIOR_GLYPH_OF_ENRAGED_REGENERATION = 765,
        // Glyph of Enraged Regeneration: Your Enraged Regeneration ability heals for an additional ${$63327m1*10}% of your health over its duration.

        MAJOR_WARRIOR_GLYPH_OF_SPELL_REFLECTION = 766,
        // Glyph of Spell Reflection: Reduces the cooldown on Spell Reflection by ${$63328m1/-1000} sec.

        MAJOR_WARRIOR_GLYPH_OF_SHIELD_WALL = 767,
        // Glyph of Shield Wall: Reduces the cooldown on Shield Wall by ${$63329m1/-60000} min, but Shield Wall now only reduces damage taken by ${60-$63329m2}%.

        MAJOR_DEATHKNIGHT_GLYPH_OF_DANCING_RUNE_WEAPON = 768,
        // Glyph of Dancing Rune Weapon: Increases the duration of Dancing Rune Weapon by ${$63330m1/1000} sec.

        MAJOR_DEATHKNIGHT_GLYPH_OF_HUNGERING_COLD = 769,
        // Glyph of Hungering Cold: Reduces the cost of Hungering Cold by ${$63331m1/-10} runic power.

        MAJOR_DEATHKNIGHT_GLYPH_OF_UNHOLY_BLIGHT = 770,
        // Glyph of Unholy Blight: Increases the damage done by Unholy Blight by $63332s1%.

        MAJOR_DEATHKNIGHT_GLYPH_OF_DARK_DEATH = 771,
        // Glyph of Dark Death: Increases the damage or healing done by Death Coil by $63333s1%.

        MAJOR_DEATHKNIGHT_GLYPH_OF_DISEASE = 772,
        // Glyph of Disease: Your Pestilence ability now refreshes disease durations and secondary effects of diseases on your primary target back to their maximum duration.

        MAJOR_DEATHKNIGHT_GLYPH_OF_HOWLING_BLAST = 773,
        // Glyph of Howling Blast: Your Howling Blast ability now infects your targets with Frost Fever.

        MAJOR_ROGUE_GLYPH_OF_ENVENOM = 791,
        // Glyph of Envenom: Your Envenom ability no longer consumes Deadly Poison from your target.

        MAJOR_DRUID_GLYPH_OF_SURVIVAL_INSTINCTS = 811,
        // Glyph of Survival Instincts: Your Survival Instincts ability grants an additional $s1% of your maximum health.

        MAJOR_DRUID_GLYPH_OF_CLAW = 831,
        // Glyph of Claw: Reduces the energy cost of your Claw ability by $67598s1.

        MAJOR_MAGE_GLYPH_OF_ETERNAL_WATER = 871,
        // Glyph of Eternal Water: Your Summon Water Elemental now lasts indefinitely, but your Water Elemental can no longer cast Freeze.

        MAJOR_DRUID_GLYPH_OF_RAPID_REJUVENATION = 891,
        // Glyph of Rapid Rejuvenation: Your haste now reduces the time between the periodic healing ticks of your Rejuvenation spell.

        MAJOR_WARLOCK_GLYPH_OF_QUICK_DECAY = 911,
        // Glyph of Quick Decay: Your haste now reduces the time between periodic damage ticks of your Corruption spell.

        MINOR_DRUID_GLYPH_OF_AQUATIC_FORM = 431,
        // Glyph of Aquatic Form: Increases your swim speed by $57856s1% while in Aquatic Form.

        MINOR_DRUID_GLYPH_OF_CHALLENGING_ROAR = 432,
        // Glyph of Challenging Roar: Reduces the cooldown of your Challenging Roar ability by ${$57858m1/-1000} sec.

        MINOR_DRUID_GLYPH_OF_THE_WILD = 433,
        // Glyph of the Wild: Mana cost of your Mark of the Wild and Gift of the Wild spells reduced by $57855s1%.

        MINOR_DRUID_GLYPH_OF_UNBURDENED_REBIRTH = 434,
        // Glyph of Unburdened Rebirth: Your Rebirth spell no longer requires a reagent.

        MINOR_DRUID_GLYPH_OF_THORNS = 435,
        // Glyph of Thorns: Increases the duration of your Thorns ability by $57862s1 min when cast on yourself.

        MINOR_HUNTER_GLYPH_OF_REVIVE_PET = 439,
        // Glyph of Revive Pet: Reduces the pushback suffered from damaging attacks while casting Revive Pet by $57866s1%.

        MINOR_HUNTER_GLYPH_OF_MEND_PET = 440,
        // Glyph of Mend Pet: Your Mend Pet spell increases your pet's happiness slightly.

        MINOR_HUNTER_GLYPH_OF_FEIGN_DEATH = 441,
        // Glyph of Feign Death: Reduces the cooldown of your Feign Death spell by ${$57903m1/-1000} sec.

        MINOR_HUNTER_GLYPH_OF_SCARE_BEAST = 442,
        // Glyph of Scare Beast: Reduces the pushback suffered from damaging attacks while casting Scare Beast by $57902s1%.

        MINOR_HUNTER_GLYPH_OF_THE_PACK = 443,
        // Glyph of the Pack: Increases the range of your Aspect of the Pack ability by $57904s1 yards.

        MINOR_HUNTER_GLYPH_OF_POSSESSED_STRENGTH = 444,
        // Glyph of Possessed Strength: Increases the damage your pet inflicts while using Eyes of the Beast by $57900s1%.

        MINOR_MAGE_GLYPH_OF_ARCANE_INTELLECT = 445,
        // Glyph of Arcane Intellect: Reduces the mana cost of your Arcane Intellect and Arcane Brilliance spells by $57924s1%.

        MINOR_MAGE_GLYPH_OF_FIRE_WARD = 446,
        // Glyph of Fire Ward: You have an additional $57926s1% chance to reflect Fire spells while your Fire Ward is active.

        MINOR_MAGE_GLYPH_OF_FROST_WARD = 447,
        // Glyph of Frost Ward: You have an additional $57927s1% chance to reflect Frost spells while your Frost Ward is active.

        MINOR_MAGE_GLYPH_OF_FROST_ARMOR = 448,
        // Glyph of Frost Armor: Increases the duration of your Frost Armor and Ice Armor spells by ${$57928m1/60000} min.

        MINOR_MAGE_GLYPH_OF_THE_BEAR_CUB = 449,
        // Glyph of the Bear Cub: Your Polymorph: Sheep spell polymorphs the target into a polar bear cub instead.

        MINOR_MAGE_GLYPH_OF_THE_PENGUIN = 450,
        // Glyph of the Penguin: Your Polymorph: Sheep spell polymorphs the target into a penguin instead.

        MINOR_MAGE_GLYPH_OF_SLOW_FALL = 451,
        // Glyph of Slow Fall: Your Slow Fall spell no longer requires a reagent.

        MINOR_PALADIN_GLYPH_OF_BLESSING_OF_KINGS = 452,
        // Glyph of Blessing of Kings: Reduces the mana cost of your Blessing of Kings and Greater Blessing of Kings spells by $57937s1%.

        MINOR_PALADIN_GLYPH_OF_BLESSING_OF_MIGHT = 453,
        // Glyph of Blessing of Might: Increases the duration of your Blessing of Might spell by $57958s1 min when cast on yourself.

        MINOR_PALADIN_GLYPH_OF_BLESSING_OF_WISDOM = 454,
        // Glyph of Blessing of Wisdom: Increases the duration of your Blessing of Wisdom spell by $57979s1 min when cast on yourself.

        MINOR_PALADIN_GLYPH_OF_LAY_ON_HANDS = 455,
        // Glyph of Lay on Hands: Reduces the cooldown of your Lay on Hands spell by ${$57955m1/-60000} min.

        MINOR_PALADIN_GLYPH_OF_SENSE_UNDEAD = 456,
        // Glyph of Sense Undead: Damage against Undead increased by $57947s1% while your Sense Undead ability is active.

        MINOR_PALADIN_GLYPH_OF_THE_WISE = 457,
        // Glyph of the Wise: Reduces the mana cost of your Seal of Wisdom spell by $57954s1%.

        MINOR_PRIEST_GLYPH_OF_FADING = 458,
        // Glyph of Fading: Reduces the mana cost of your Fade spell by $57985s1%.

        MINOR_PRIEST_GLYPH_OF_LEVITATE = 459,
        // Glyph of Levitate: Your Levitate spell no longer requires a reagent.

        MINOR_PRIEST_GLYPH_OF_FORTITUDE = 460,
        // Glyph of Fortitude: Reduces the mana cost of your Power Word: Fortitude and Prayer of Fortitude spells by $58009s1%.

        MINOR_PRIEST_GLYPH_OF_SHACKLE_UNDEAD = 461,
        // Glyph of Shackle Undead: Increases the range of your Shackle Undead spell by $57986s1 yards.

        MINOR_PRIEST_GLYPH_OF_SHADOW_PROTECTION = 462,
        // Glyph of Shadow Protection: Increases the duration of your Shadow Protection and Prayer of Shadow Protection spells by ${$58015m1/60000} min.

        MINOR_PRIEST_GLYPH_OF_SHADOWFIEND = 463,
        // Glyph of Shadowfiend: Receive $58227s1% of your maximum mana if your Shadowfiend dies from damage.

        MINOR_ROGUE_GLYPH_OF_DISTRACT = 464,
        // Glyph of Distract: Increases the range of your Distract ability by $58032s1 yards.

        MINOR_ROGUE_GLYPH_OF_PICK_LOCK = 465,
        // Glyph of Pick Lock: Reduces the cast time of your Pick Lock ability by $58027s1%.

        MINOR_ROGUE_GLYPH_OF_PICK_POCKET = 466,
        // Glyph of Pick Pocket: Increases the range of your Pick Pocket ability by $58017s1 yards.

        MINOR_ROGUE_GLYPH_OF_SAFE_FALL = 467,
        // Glyph of Safe Fall: Increases the distance your Safe Fall ability allows you to fall without taking damage.

        MINOR_ROGUE_GLYPH_OF_BLURRED_SPEED = 468,
        // Glyph of Blurred Speed: Enables you to walk on water while your Sprint ability is active.

        MINOR_ROGUE_GLYPH_OF_VANISH = 469,
        // Glyph of Vanish: Increases your movement speed by $58038s1% while the Vanish effect is active.

        MINOR_SHAMAN_GLYPH_OF_ASTRAL_RECALL = 470,
        // Glyph of Astral Recall: Cooldown of your Astral Recall spell reduced by ${$58058m1/-60000}.1 min.

        MINOR_SHAMAN_GLYPH_OF_RENEWED_LIFE = 473,
        // Glyph of Renewed Life: Your Reincarnation spell no longer requires a reagent.

        MINOR_SHAMAN_GLYPH_OF_WATER_BREATHING = 474,
        // Glyph of Water Breathing: Your Water Breathing spell no longer requires a reagent.

        MINOR_SHAMAN_GLYPH_OF_WATER_SHIELD = 475,
        // Glyph of Water Shield: Increases the number of charges on your Water Shield spell by $58063s1.

        MINOR_SHAMAN_GLYPH_OF_WATER_WALKING = 476,
        // Glyph of Water Walking: Your Water Walking spell no longer requires a reagent.

        MINOR_WARLOCK_GLYPH_OF_UNENDING_BREATH = 477,
        // Glyph of Unending Breath: Increases the swim speed of targets affected by your Unending Breath spell by $58079s1%.

        MINOR_WARLOCK_GLYPH_OF_DRAIN_SOUL = 478,
        // Glyph of Drain Soul: Your Drain Soul ability occasionally creates an additional soul shard.

        MINOR_WARLOCK_GLYPH_OF_KILROGG = 479,
        // Glyph of Kilrogg: Increases the movement speed of your Eye of Kilrogg by $s1% and allows it to fly in areas where flying mounts are enabled.

        MINOR_WARLOCK_GLYPH_OF_ENSLAVE_DEMON = 481,
        // Glyph of Enslave Demon: Reduces the cast time of your Enslave Demon spell by $58107s1%.

        MINOR_WARLOCK_GLYPH_OF_SOULS = 482,
        // Glyph of Souls: Reduces the mana cost of your Ritual of Souls spell by $58094s1%.

        MINOR_WARRIOR_GLYPH_OF_BATTLE = 483,
        // Glyph of Battle: Increases the duration of your Battle Shout ability by ${$58095m1/60000} min.

        MINOR_WARRIOR_GLYPH_OF_BLOODRAGE = 484,
        // Glyph of Bloodrage: Reduces the health cost of your Bloodrage ability by $s1%.

        MINOR_WARRIOR_GLYPH_OF_CHARGE = 485,
        // Glyph of Charge: Increases the range of your Charge ability by $58097s1 yards.

        MINOR_WARRIOR_GLYPH_OF_MOCKING_BLOW = 486,
        // Glyph of Mocking Blow: Increases the damage of your Mocking Blow ability by $58099s1%.

        MINOR_WARRIOR_GLYPH_OF_THUNDER_CLAP = 487,
        // Glyph of Thunder Clap: Increases the radius of your Thunder Clap ability by $58098s1 yards.

        MINOR_WARRIOR_GLYPH_OF_ENDURING_VICTORY = 488,
        // Glyph of Enduring Victory: Increases the window of opportunity in which you can use Victory Rush by ${$58104m1/1000} sec.

        MINOR_DEATHKNIGHT_GLYPH_OF_BLOOD_TAP = 514,
        // Glyph of Blood Tap: Your Blood Tap no longer causes damage to you.

        MINOR_DEATHKNIGHT_GLYPH_OF_DEATHS_EMBRACE = 518,
        // Glyph of Death's Embrace: Your Death Coil refunds $s1 runic power when used to heal.

        MINOR_DEATHKNIGHT_GLYPH_OF_HORN_OF_WINTER = 522,
        // Glyph of Horn of Winter: Increases the duration of your Horn of Winter ability by ${$58680m1/60000} min.

        MINOR_DRUID_GLYPH_OF_DASH = 551,
        // Glyph of Dash: Reduces the cooldown of your Dash ability by $59219s1%.

        MINOR_SHAMAN_GLYPH_OF_GHOST_WOLF = 552,
        // Glyph of Ghost Wolf: Your Ghost Wolf form regenerates an additional $59289s1% of your maximum health every 5 sec.

        MINOR_DEATHKNIGHT_GLYPH_OF_PESTILENCE = 553,
        // Glyph of Pestilence: Increases the radius of your Pestilence effect by $59309s1 yards.

        MINOR_DEATHKNIGHT_GLYPH_OF_CORPSE_EXPLOSION = 554,
        // Glyph of Corpse Explosion: Increases the radius of effect on Corpse Explosion by $59307s1 yards.

        MINOR_DEATHKNIGHT_GLYPH_OF_RAISE_DEAD = 555,
        // Glyph of Raise Dead: Your Raise Dead spell no longer requires a reagent.

        MINOR_MAGE_GLYPH_OF_BLAST_WAVE = 611,
        // Glyph of Blast Wave: The mana cost of your Blast Wave spell is reduced by $62126s1%, but it no longer knocks enemies back.

        MINOR_SHAMAN_GLYPH_OF_THUNDERSTORM = 612,
        // Glyph of Thunderstorm: Increases the mana you receive from your Thunderstorm spell by $62132s1%, but it no longer knocks enemies back.

        MINOR_DRUID_GLYPH_OF_TYPHOON = 613,
        // Glyph of Typhoon: Reduces the cost of your Typhoon spell by $62135s1% and increases its radius by $62135s2 yards, but it no longer knocks enemies back.

        MINOR_WARRIOR_GLYPH_OF_COMMAND = 851
        // Glyph of Command: Increases the duration of your Commanding Shout ability by ${$68164m1/60000} min.
};

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "Player.h"
#include "ScriptPCH.h"
#include "cstring"

class npc_glyph_template : public CreatureScript
{
public:
    npc_glyph_template() : CreatureScript("npc_glyph_template") { }
        
       bool OnGossipHello(Player* player, Creature* creature) override
        {
            if (player->getClass() == CLASS_WARRIOR)
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "PvP / DPS (Arms)", GOSSIP_SENDER_MAIN, 6);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "PvP / DPS (Protection)", GOSSIP_SENDER_MAIN, 7);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "PvP / Tank (Protection)", GOSSIP_SENDER_MAIN, 8);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "PvE / DPS (Arms/Fury)", GOSSIP_SENDER_MAIN, 9);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "PvE / Tank (Protection)", GOSSIP_SENDER_MAIN, 10);
            }
            player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action) override
        {
            player->PlayerTalkClass->ClearMenus();
            switch (action)
            {
            case 6:
                player->CLOSE_GOSSIP_MENU();

                break;
            case 7:
                player->CLOSE_GOSSIP_MENU();

                break;
            case 8:
                player->CLOSE_GOSSIP_MENU();
                
                break;
            case 9:
                player->CLOSE_GOSSIP_MENU();

                break;
            case 10:
                player->CLOSE_GOSSIP_MENU();

                    //Glyph Slots

                    //Major
                    player->SetGlyph(0, MAJOR_WARRIOR_GLYPH_OF_LAST_STAND);
                    //Minor
                    player->SetGlyph(1, MINOR_WARRIOR_GLYPH_OF_BATTLE);
                    //Minor
                    player->SetGlyph(2, MINOR_WARRIOR_GLYPH_OF_THUNDER_CLAP);
                    //Major
                    player->SetGlyph(3, MAJOR_WARRIOR_GLYPH_OF_HAMSTRING);
                    //Minor
                    player->SetGlyph(4, MINOR_WARRIOR_GLYPH_OF_CHARGE);
                    //Major
                    player->SetGlyph(5, MAJOR_WARRIOR_GLYPH_OF_HAMSTRING);
                    player->SendTalentsInfoData(false);

                break;
            }
            return true;
        }
        
};

void AddSC_npc_glyph_template()
{
    new npc_glyph_template();
}