/*
 * Copyright (C) 2015 TheSatriaCore <http://www.TheSatria.Con/>
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */
 
#include "ScriptPCH.h"
#include "Language.h"

enum eTexts
{
	TEXT_ON_DANCE = -1700004,
	TEXT_ON_SALUTE = -1700005,
	TEXT_ON_SPIT = -1700006,
	TEXT_ON_LAUGH = -1700007,
	TEXT_ON_BYE = -1700008
};

enum eRidingSkills
{
	RIDING_APPRENTICE = 33388,
	RIDING_JOURNEYMAN = 33391,
	RIDING_EXPERT = 34090,
	RIDING_ARTISAN = 34091,
	COLD_WEATHER_FLYING = 54197
};

enum eEmblems
{
	EMBLEM_OF_FROST = 49426,
	EMBLEM_OF_TRIUMPH = 47241,
	EMBLEM_OF_VALOR = 40753,
	EMBLEM_OF_CONQUEST = 45624,
	EMBLEM_OF_HEROISM = 40752
};

class universal_teleporter : public CreatureScript
{
public:
	universal_teleporter()
		: CreatureScript("universal_teleporter")
	{
	}

	struct universal_teleporterAI : public ScriptedAI
	{
		universal_teleporterAI(Creature *c) : ScriptedAI(c)
		{
		}

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

	uint32 PlayerMaxLevel() const
	{
		return sWorld->getIntConfig(CONFIG_MAX_PLAYER_LEVEL);
	}

	void MainMenu(Player *pPlayer, Creature *pCreature)
	{
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Thrown_1H_Harpoon_D_01Blue:24|t Mall Non PVP", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8910);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/INV_Misc_Coin_03:24|t Home Cities ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/INV_Misc_Coin_03:24|t Neutral Cities ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 21);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Achievement_Arena_2v2_7:24|t Arenas ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 28);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Achievement_Arena_2v2_7:24|t Dungeons ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 32);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Achievement_Arena_2v2_7:24|t Raids ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 79);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/INV_Misc_Gear_01:24|t Zones ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 106);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Achievement_FeatsOfStrength_Gladiator_10:24|t Quest Location ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 310);
		//pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Achievement_Leader_King_Varian_Wrynn:24|t Fusion Item Drop Zone ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3810);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/INV_Misc_Coin_03:24|t I want free Mounts ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 177);
		//pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[|cff00FFFFEvent Zone]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 810);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/INV_Misc_Gear_01:24|t Leveling Zone", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8000);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/INV_Misc_Gear_01:24|t Farming Zone", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9000);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/INV_Misc_Gear_01:24|t Custom Boss Zone ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 710);
		//pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "--|cffFF0000Advance Summon Boss Area--", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9710);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/INV_Misc_Gear_01:24|t |cffFF00DEChill Area--", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1110);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "|TInterface/ICONS/INV_Chest_Plate13:24|t Professions ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 196);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "|TInterface/ICONS/INV_Chest_Plate13:24|t Learn Spells ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 460);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "|TInterface/ICONS/INV_Chest_Plate13:24|t Player Tools ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 450);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/INV_Chest_Plate13:24|t Combat Clear", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3526);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "|TInterface/ICONS/INV_Chest_Plate13:24|t Buffs Me UP", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2500);
		//pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "|TInterface/ICONS/INV_Chest_Plate13:30|t Learn me Pet Tame Beast Skill--", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 50000);
		pPlayer->SEND_GOSSIP_MENU(907, pCreature->GetGUID());
	}

	bool PlayerReachedMoneyCap(const Player *plr) const
	{
		return plr->GetMoney() == MAX_MONEY_AMOUNT;
	}

	bool PlayerReachedHonorCap(Player *plr) const
	{
		int32 maxHonor = sWorld->getIntConfig(CONFIG_MAX_HONOR_POINTS);
		return plr->GetHonorPoints() == (uint32)maxHonor;
	}

	bool PlayerReachedArenaCap(Player *plr) const
	{
		int32 maxArena = sWorld->getIntConfig(CONFIG_MAX_ARENA_POINTS);
		return plr->GetArenaPoints() == (uint32)maxArena;
	}

	bool PlayerHasItemOrSpell(const Player *plr, uint32 itemId, uint32 spellId) const
	{
		return plr->HasItemCount(itemId, 1, true) || plr->HasSpell(spellId);
	}

	bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
		MainMenu(pPlayer, pCreature);

        return true;
    }

	std::string GetEmblemName(eEmblems emblem) const
	{
		switch (emblem)
		{
		case EMBLEM_OF_FROST:
			return "emblem of frost";
		case EMBLEM_OF_TRIUMPH:
			return "emblem of triumph";
		case EMBLEM_OF_VALOR:
			return "emblem of valor";
		case EMBLEM_OF_CONQUEST:
			return "emblem of conquest";
		case EMBLEM_OF_HEROISM:
			return "emblem of heroism";
		default:
			return "error";
		}
	}

	bool PlayerAlreadyHasTwoProfessions(const Player *pPlayer) const
	{
		uint32 skillCount = 0;

		if (pPlayer->HasSkill(SKILL_MINING))
			skillCount++;
		if (pPlayer->HasSkill(SKILL_SKINNING))
			skillCount++;
		if (pPlayer->HasSkill(SKILL_HERBALISM))
			skillCount++;

		if (skillCount >= 2)
			return true;

		for (uint32 i = 1; i < sSkillLineStore.GetNumRows(); ++i)
		{
			SkillLineEntry const *SkillInfo = sSkillLineStore.LookupEntry(i);
			if (!SkillInfo)
				continue;

			if (SkillInfo->categoryId == SKILL_CATEGORY_SECONDARY)
				continue;

			if ((SkillInfo->categoryId != SKILL_CATEGORY_PROFESSION) || !SkillInfo->canLink)
				continue;

			const uint32 skillID = SkillInfo->id;
			if (pPlayer->HasSkill(skillID))
				skillCount++;

			if (skillCount >= 2)
				return true;
		}

		return false;
	}

	bool LearnAllRecipesInProfession(Player *pPlayer, SkillType skill)
                {
                        ChatHandler handler(pPlayer->GetSession());
                        char* skill_name;

                        SkillLineEntry const *SkillInfo = sSkillLineStore.LookupEntry(skill);
						skill_name = SkillInfo->name[handler.GetSessionDbcLocale()];

                        if (!SkillInfo)
                        {
                        sLog->outError(LOG_FILTER_SERVER_LOADING, "Profession NPC: received non-valid skill ID (LearnAllRecipesInProfession)");
                        }       

                        LearnSkillRecipesHelper(pPlayer, SkillInfo->id);

                        pPlayer->SetSkill(SkillInfo->id, pPlayer->GetSkillStep(SkillInfo->id), 450, 450);
                        handler.PSendSysMessage(LANG_COMMAND_LEARN_ALL_RECIPES, skill_name);
                
                        return false;
	}
	// See "static void HandleLearnSkillRecipesHelper(Player* player,uint32 skill_id)" from cs_learn.cpp 
	void LearnSkillRecipesHelper(Player *player, uint32 skill_id)
	{
		uint32 classmask = player->getClassMask();

        for (uint32 j = 0; j < sSkillLineAbilityStore.GetNumRows(); ++j)
        {
            SkillLineAbilityEntry const *skillLine = sSkillLineAbilityStore.LookupEntry(j);
            if (!skillLine)
                continue;

            // wrong skill
            if (skillLine->skillId != skill_id)
                continue;

            // not high rank
            if (skillLine->forward_spellid)
                continue;

            // skip racial skills
            if (skillLine->racemask != 0)
                continue;

            // skip wrong class skills
            if (skillLine->classmask && (skillLine->classmask & classmask) == 0)
                continue;

            SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(skillLine->spellId);
            if (!spellInfo || !SpellMgr::IsSpellValid(spellInfo, player, false))
                continue;

            player->learnSpell(skillLine->spellId, false);
        }
	}

	bool IsSecondarySkill(SkillType skill) const
	{
		return skill == SKILL_COOKING || skill == SKILL_FIRST_AID;
	}

	void CompleteLearnProfession(Player *pPlayer, Creature *pCreature, SkillType skill)
	{
		if (PlayerAlreadyHasTwoProfessions(pPlayer) && !IsSecondarySkill(skill))
			pCreature->MonsterWhisper("You already know two professions!", pPlayer->GetGUID());
		else
		{
			if (!LearnAllRecipesInProfession(pPlayer, skill))
				pCreature->MonsterWhisper("Enjoy !!",pPlayer->GetGUID());
		}
	}

	void HandleEmblemGive(Player *pPlayer, Creature *pCreature, eEmblems emblem)
	{
		pPlayer->AddItem(static_cast<uint32>(emblem), 1);
		pCreature->MonsterWhisper(("I have given you 1x " + GetEmblemName(emblem) + ".").c_str(), pPlayer->GetGUID());
	}

	void CreatureWhisperBasedOnRidingSkill(Creature *pCreature, const Player *pPlayer, eRidingSkills skill)
	{
		const uint64 &plrGuid = pPlayer->GetGUID();

		switch (skill)
		{
		case RIDING_APPRENTICE:
			pCreature->MonsterWhisper("I taught you Apprentice riding!", plrGuid);
			break;
		case RIDING_JOURNEYMAN:
			pCreature->MonsterWhisper("I taught you Journeyman riding!", plrGuid);
			break;
		case RIDING_EXPERT:
			pCreature->MonsterWhisper("I taught you Expert riding!", plrGuid);
			break;
		case RIDING_ARTISAN:
			pCreature->MonsterWhisper("I taught you Artisan riding!", plrGuid);
			break;
		}
	}

	void GiveRidingSkill(Player *pPlayer, Creature *pCreature)
	{
		if (pPlayer->getLevel() <= 19)
			pCreature->MonsterWhisper("Your level is not high enough!", pPlayer->GetGUID());
		else if (pPlayer->getLevel() >= 20 && pPlayer->getLevel() <= 39)
		{
			if (pPlayer->HasSpell(RIDING_APPRENTICE))
				pCreature->MonsterWhisper("You already know Apprentice riding!", pPlayer->GetGUID());
			else
			{
				pPlayer->learnSpell(RIDING_APPRENTICE, false);
				CreatureWhisperBasedOnRidingSkill(pCreature, pPlayer, RIDING_APPRENTICE);
			}
		}
		else if (pPlayer->getLevel() >= 40 && pPlayer->getLevel() <= 59)
		{
			if (pPlayer->HasSpell(RIDING_JOURNEYMAN))
				pCreature->MonsterWhisper("You already know Journeyman riding!", pPlayer->GetGUID());
			else
			{
				pPlayer->learnSpell(RIDING_JOURNEYMAN, false);
				CreatureWhisperBasedOnRidingSkill(pCreature, pPlayer, RIDING_JOURNEYMAN);
			}
		}
		else if (pPlayer->getLevel() >= 60 && pPlayer->getLevel() <= 69)
		{
			if (pPlayer->HasSpell(RIDING_EXPERT))
				pCreature->MonsterWhisper("You already know Expert riding!", pPlayer->GetGUID());
			else
			{
				pPlayer->learnSpell(RIDING_EXPERT, false);
				CreatureWhisperBasedOnRidingSkill(pCreature, pPlayer, RIDING_EXPERT);
			}
		}
		else if (pPlayer->getLevel() >= 70)
		{
			if (pPlayer->getLevel() >= 77 && !pPlayer->HasSpell(COLD_WEATHER_FLYING))
			{
				pPlayer->learnSpell(COLD_WEATHER_FLYING, false);
				pCreature->MonsterWhisper("I taught you Cold Weather Flying!", pPlayer->GetGUID());
			}

			if (pPlayer->HasSpell(RIDING_ARTISAN))
				pCreature->MonsterWhisper("You already know Artisan riding!", pPlayer->GetGUID());
			else
			{
				pPlayer->learnSpell(RIDING_ARTISAN, false);
				CreatureWhisperBasedOnRidingSkill(pCreature, pPlayer, RIDING_ARTISAN);
			}
		}
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
			case GOSSIP_ACTION_INFO_DEF + 1:
				pPlayer->DurabilityRepairAll(false, 0.0f, true);
				pCreature->MonsterWhisper("I repaired all your items, including items from bank.", pPlayer->GetGUID());
				pPlayer->CLOSE_GOSSIP_MENU();

				break;
			case GOSSIP_ACTION_INFO_DEF + 3:
				pPlayer->ModifyMoney(1000000);
				CreatureWhisperBasedOnBool("I gave you 100 golds.", pCreature, pPlayer, !PlayerReachedMoneyCap(pPlayer));
				pPlayer->CLOSE_GOSSIP_MENU();

				break;
			case GOSSIP_ACTION_INFO_DEF + 4:
				pPlayer->ModifyMoney(5000000);
				CreatureWhisperBasedOnBool("I gave you 500 golds.", pCreature, pPlayer, !PlayerReachedMoneyCap(pPlayer));
				pPlayer->CLOSE_GOSSIP_MENU();

				break;
			case GOSSIP_ACTION_INFO_DEF + 5:
				pPlayer->ModifyMoney(25000000);
				CreatureWhisperBasedOnBool("I gave you 2500 golds.", pCreature, pPlayer, !PlayerReachedMoneyCap(pPlayer));
				pPlayer->CLOSE_GOSSIP_MENU();

				break;
			case GOSSIP_ACTION_INFO_DEF + 6:
				pPlayer->ModifyMoney(50000000);
				CreatureWhisperBasedOnBool("I gave you 5000 golds.", pCreature, pPlayer, !PlayerReachedMoneyCap(pPlayer));
				pPlayer->CLOSE_GOSSIP_MENU();

				break;
			case GOSSIP_ACTION_INFO_DEF + 2:
				pPlayer->ModifyMoney(100000000);
				CreatureWhisperBasedOnBool("I gave you 10000 golds.", pCreature, pPlayer, !PlayerReachedMoneyCap(pPlayer));
				pPlayer->CLOSE_GOSSIP_MENU();

				break;
			case GOSSIP_ACTION_INFO_DEF + 8:
				MainMenu(pPlayer, pCreature);
			
				break;
			case GOSSIP_ACTION_INFO_DEF + 9:
				pPlayer->UpdateSkillsToMaxSkillsForLevel();
				pCreature->MonsterWhisper("Your weapon skills have been advanced to maximum level.", pPlayer->GetGUID());
				pPlayer->CLOSE_GOSSIP_MENU();

				break;
			case GOSSIP_ACTION_INFO_DEF + 10:
			{
				pPlayer->GiveLevel((uint8)PlayerMaxLevel());
				pPlayer->InitTalentForLevel();
				pPlayer->SetUInt32Value(PLAYER_XP, 0);
				std::ostringstream ostr;
				ostr << PlayerMaxLevel();
				pCreature->MonsterWhisper(("You have been advanced to level " + ostr.str()).c_str(), pPlayer->GetGUID());
		
				pPlayer->CLOSE_GOSSIP_MENU();
	
				break;
			}
			

			case GOSSIP_ACTION_INFO_DEF + 12:
			{
				switch (pPlayer->GetTeam())
				{
				case HORDE:
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Orgrimmar", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13);
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Thunderbluff", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 14);
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Silvermoon", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 15);
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Undercity", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 16);

					break;
				case ALLIANCE:
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Stormwind", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 17);
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Ironforge", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 18);
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Exodar", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 19);
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Darnassus", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 20);

					break;
				}

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());

				break;
			}
			case GOSSIP_ACTION_INFO_DEF + 13:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, 1629.36f, -4373.39f, 31.2564f, 3.54839f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 14:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -1277.37f, 124.804f, 131.287f, 5.22274f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 15:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, 9487.69f, -7279.2f, 14.2866f, 6.16478f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 16:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, 1584.07f, 241.987f, -52.1534f, 0.049647f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 17:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -8833.38f, 628.628f, 94.0066f, 1.06535f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 18:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -4918.88f, -940.406f, 501.564f, 5.42347f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 19:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, -3965.7f, -11653.6f, -138.844f, 0.852154f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 20:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, 9949.56f, 2284.21f, 1341.4f, 1.59587f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 21:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Dalaran", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 22);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Shattrath", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 23);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Booty Bay", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 24);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Gadgetzan", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 25);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());

				break;
			case GOSSIP_ACTION_INFO_DEF + 22:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 5804.15f, 624.771f, 647.767f, 1.64f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 23:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, -1838.16f, 5301.79f, -12.428f, 5.9517f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 24:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -14297.2f, 530.993f, 8.77916f, 3.98863f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 25:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -7177.15f, -3785.34f, 8.36981f, 6.10237f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 26:
			{
				uint32 currHp = pPlayer->GetHealth();
				uint32 maxHp = pPlayer->GetMaxHealth();

				if (currHp == maxHp)
					pCreature->MonsterWhisper("Your HP is already full.", pPlayer->GetGUID());
				else
				{
					uint32 hdiff = maxHp - currHp;
					std::ostringstream ostr;
					ostr << "I have healed you for " << hdiff << " HP points.";
					pPlayer->SetHealth(maxHp);
					pCreature->MonsterWhisper(ostr.str().c_str(), pPlayer->GetGUID());
				}

				pPlayer->CLOSE_GOSSIP_MENU();
				break;
			}
			
			case GOSSIP_ACTION_INFO_DEF + 27:
			{
				if (pPlayer->HasAura(15007))
				{
					pPlayer->RemoveAura(15007);
					pCreature->MonsterWhisper("I have removed your ressurection sickness.", pPlayer->GetGUID());
				}
				else
					pCreature->MonsterWhisper("You don't have ressurection sickness.", pPlayer->GetGUID());

				pPlayer->CLOSE_GOSSIP_MENU();
				break;
			}
			
					
			case GOSSIP_ACTION_INFO_DEF + 28:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Gurubashi Arena", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 29);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Circle of Blood Arena", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 30);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "The Ring of Trials", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 31);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());			
				break;
				
			case GOSSIP_ACTION_INFO_DEF + 29:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -13277.4f, 127.372f, 26.1418f, 1.11878f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 30:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, 2839.44f, 5930.17f, 11.1002f, 3.16284f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 31:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, -1999.94f, 6581.71f, 11.32f, 2.36528f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 32:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[Dungeons (1-60)] ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 33);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[Dungeons (60-70)] ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 34);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[Dungeons (70-80)] ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 35);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
				
				break;
			case GOSSIP_ACTION_INFO_DEF + 33:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Ragefire Chasm (15-21)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 36);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "The Deadmines (15-21)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 37);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Wailing Caverns (15-25)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 38);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Shadowfang Keep (16-26)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 39);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Blackfathom Deeps (20-30)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 40);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Stormwind Stockade (20-30)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 41);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Gnomeregan (24-34)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 42);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Scarlet Monastery (26-42)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 43);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Razorfen Kraul (30-40)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 44);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[More] ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 45);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 32);

				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());

				break;
			case GOSSIP_ACTION_INFO_DEF + 45:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Maraudon (30-46)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 46);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Uldaman (35-45)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 47);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Razorfen Dawns (35-43)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 48);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Zul Farrak (40-48)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 49);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Sunken Temple (45-55)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 50);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Dire Maul (50-60)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 51);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Blackrock Depths (50-60)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 52);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Blackrock Spire (50-60)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 53);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Scholomance (50-60)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 54);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Stratholme (50-60)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 55);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 33);

				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
			
				break;
			case GOSSIP_ACTION_INFO_DEF + 36:
			case GOSSIP_ACTION_INFO_DEF + 33005:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, 1811.78f, -4410.5f, -18.4704f, 5.20165f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 37:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -11208.7f, 1673.52f, 24.6361f, 1.51067f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 38:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -805.049f, -2032.03f, 95.8796f, 6.18912f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 39:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -234.675f, 1561.63f, 76.8921f, 1.24031f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 40:
			case GOSSIP_ACTION_INFO_DEF + 33006:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, 4249.99f, 740.102f, -25.671f, 1.34062f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 41:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -8773.32f, 839.031f, 91.6376f, 0.648292f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 42:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -5163.54f, 925.423f, 257.181f, 1.57423f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 43:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, 2843.38f, -692.582f, 139.331f, 5.3825f);
				

				break;
			case GOSSIP_ACTION_INFO_DEF + 44:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -4470.28f, -1677.77f, 81.3925f, 1.16302f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 46:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -1419.13f, 2908.14f, 137.464f, 1.57366f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 47:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -6071.37f, -2955.16f, 209.782f, 0.015708f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 48:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -4657.3f, -2519.35f, 81.0529f, 4.54808f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 49:
			case GOSSIP_ACTION_INFO_DEF + 33007:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -6801.19f, -2893.02f, 9.00388f, 0.158639f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 50:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -10177.9f, -3994.9f, -111.239f, 6.01885f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 51:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -3521.29f, 1085.2f, 161.097f, 4.7281f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 52:
			case GOSSIP_ACTION_INFO_DEF + 33008:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -7179.34f, -921.212f, 165.821f, 5.09599f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 53:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -7527.05f, -1226.77f, 285.732f, 5.29626f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 54:
			case GOSSIP_ACTION_INFO_DEF + 33009:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, 1269.64f, -2556.21f, 93.6088f, 0.620623f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 55:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, 3352.92f, -3379.03f, 144.782f, 6.25978f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 34:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Hellfire Citadel (60-68)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 56);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Coilfang Reservoir (60-69)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 57);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Auchindoun (60-70)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 58);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Tempest Keep (60-70)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 59);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Caverns of Time (60-70)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 60);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Magisters' Terrace (68-72)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 61);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 32);

				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
			
				break;
			case GOSSIP_ACTION_INFO_DEF + 56:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, -390.863f, 3130.64f, 4.51327f, 0.218692f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 57:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, 735.066f, 6883.45f, -66.2913f, 5.89172f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 58:
			case GOSSIP_ACTION_INFO_DEF + 33012:
			case GOSSIP_ACTION_INFO_DEF + 33013:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, -3324.49f, 4943.45f, -101.239f, 4.63901f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 59:
			case GOSSIP_ACTION_INFO_DEF + 33014:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, 3099.36f, 1518.73f, 190.3f, 4.72592f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 60:
			case GOSSIP_ACTION_INFO_DEF + 73:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -8204.88f, -4495.25f, 9.0091f, 4.72574f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 61:
			case GOSSIP_ACTION_INFO_DEF + 33015:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, 12884.6f, -7317.69f, 65.5023f, 4.799f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 35:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Utgarde Keep (70-72)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 62);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "The Nexus (71-73)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 63);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Azjol-Nerub (72-74)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 64);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Ahn'Kahet: The Old Kingdom (73-75)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 65);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Drak'Tharon Keep (74-76)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 66);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "The Violet Hold (75-77)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 67);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Gundrak (76-78)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 68);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Halls of Stone (77-79)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 69);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Halls of Lightning (80)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 70);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[More] ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 71);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 32);

				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());

				break;
			case GOSSIP_ACTION_INFO_DEF + 71:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "The Oculus (80)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 72);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Culling of Stratholme (80)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 73);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Utgarde Pinnacle (80)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 74);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Trial of Champion (80)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 75);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Pit of Saron (80)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 76);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Forge of Souls (80)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 77);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Halls of Reflection (80)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 78);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 35);

				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());

				break;
			case GOSSIP_ACTION_INFO_DEF + 62:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 1219.72f, -4865.28f, 41.2479f, 0.313228f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 63:
			case GOSSIP_ACTION_INFO_DEF + 72:
			case GOSSIP_ACTION_INFO_DEF + 101:
			case GOSSIP_ACTION_INFO_DEF + 33017:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 3781.81f, 6953.65f, 104.82f, 0.467432f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 64:
			case GOSSIP_ACTION_INFO_DEF + 65:
			case GOSSIP_ACTION_INFO_DEF + 43007:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 3707.86f, 2150.23f, 36.76f, 3.22f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 66:
			case GOSSIP_ACTION_INFO_DEF + 43006:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 4774.6f, -2032.92f, 229.15f, 1.59f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 67:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 5696.73f, 507.4f, 652.97f, 4.03f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 68:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 6898.72f, -4584.94f, 451.12f, 2.34455f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 69:
			case GOSSIP_ACTION_INFO_DEF + 70:
			case GOSSIP_ACTION_INFO_DEF + 102:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 9049.37f, -1282.35f, 1060.19f, 5.8395f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 74:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 1259.33f, -4852.02f, 215.763f, 3.48293f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 75:
			case GOSSIP_ACTION_INFO_DEF + 104:
			case GOSSIP_ACTION_INFO_DEF +33026:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 8515.89f, 629.25f, 547.396f, 1.5747f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 76:
			case GOSSIP_ACTION_INFO_DEF + 77:
			case GOSSIP_ACTION_INFO_DEF + 78:
			case GOSSIP_ACTION_INFO_DEF + 33018:
			case GOSSIP_ACTION_INFO_DEF + 33019:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 5638.26f, 2053.01f, 798.046f, 4.59295f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 79:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[Level 60 raids] ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 80);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[Level 70 raids] ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 81);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[Level 80 raids] ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 82);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);

				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());

				break;
			case GOSSIP_ACTION_INFO_DEF + 80:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Zul'Gurub", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 83);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Molten Core", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 84);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Blackwing Lair", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 85);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Ahn'Qiraj Ruins", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 86);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Ahn'Qiraj Temple", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 87);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 79);

				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());

				break;
			case GOSSIP_ACTION_INFO_DEF + 83:
			case GOSSIP_ACTION_INFO_DEF + 43002:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -11916.7f, -1215.72f, 92.289f, 4.72454f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 84:
			case GOSSIP_ACTION_INFO_DEF + 43008:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(230, 1126.64f, -459.94f, -102.535f, 3.46095f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 85:
			case GOSSIP_ACTION_INFO_DEF + 43004:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(229, 164.789f, -475.305f, 116.842f, 0.022714f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 86:
			case GOSSIP_ACTION_INFO_DEF + 43001:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -8409.82f, 1499.06f, 27.7179f, 2.51868f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 87:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -8240.09f, 1991.32f, 129.072f, 0.941603f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 81:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Karazhan", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 88);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Gruul's Lair", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 89);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Magtheridon's Lair", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 90);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Zul'Aman", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 91);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Serpentshrine Cavern", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 92);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Tempest Keep: The Eye", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 93);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Hyjal", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 94);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Black Temple", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 95);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Sunwell Plateau", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 96);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 79);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
			
				break;
			case GOSSIP_ACTION_INFO_DEF + 88:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -11118.9f, -2010.33f, 47.0819f, 0.649895f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 89:
			case GOSSIP_ACTION_INFO_DEF +33025:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, 3530.06f, 5104.08f, 3.50861f, 5.51117f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 90:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, -312.7f, 3087.26f, -116.52f, 5.19026f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 91:
			case GOSSIP_ACTION_INFO_DEF + 33016:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, 6851.78f, -7972.57f, 179.242f, 4.64691f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 92:
			case GOSSIP_ACTION_INFO_DEF + 33010:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, 820.025f, 6864.93f, -66.7556f, 6.28127f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 93:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, 3088.49f, 1381.57f, 184.863f, 4.61973f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 94:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -8177.89f, -4181.23f, -167.552f, 0.913338f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 95:
			case GOSSIP_ACTION_INFO_DEF + 33027:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, -3649.92f, 317.469f, 35.2827f, 2.94285f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 96:
			case GOSSIP_ACTION_INFO_DEF + 43005:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, 12574.1f, -6774.81f, 15.0904f, 3.13788f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 82:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Naxxramas", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 97);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Obsidian Sanctum", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 98);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Ruby Sanctum", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 99);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Vault of Archavon", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 100);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Eye of Eternity", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 101);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Ulduar", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 102);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Icecrown Citadel", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 103);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Trial of the Crusader", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 104);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Onyxia's Lair", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 105);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 79);

				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());

				break;
			case GOSSIP_ACTION_INFO_DEF + 97:
			case GOSSIP_ACTION_INFO_DEF + 33020:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 3668.72f, -1262.46f, 243.622f, 4.785f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 98:
			case GOSSIP_ACTION_INFO_DEF + 99:
			case GOSSIP_ACTION_INFO_DEF + 33021:
			case GOSSIP_ACTION_INFO_DEF + 33023:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 3479.66f, 264.625f, -120.144f, 0.097f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 100:
			case GOSSIP_ACTION_INFO_DEF + 33024:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 5453.72f, 2840.79f, 421.28f, 0.0f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 103:
			case GOSSIP_ACTION_INFO_DEF + 33028:
			case GOSSIP_ACTION_INFO_DEF + 43010:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 5873.82f, 2110.98f, 636.011f, 3.5523f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 105:
			case GOSSIP_ACTION_INFO_DEF + 43009:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -4708.27f, -3727.64f, 54.5589f, 3.72786f);

				break;
				case GOSSIP_ACTION_INFO_DEF + 2301:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -1688.336182f, -4273.490723f, 1.998409f, 2.593258f);

				break;
				case GOSSIP_ACTION_INFO_DEF + 2303:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, 2499.770020f, -41.674599f, 24.625900f, 2.940340f);

				break;
				case GOSSIP_ACTION_INFO_DEF + 2304:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -7721.725586f, -3542.335693f, 37.024323f, 5.384436f);

				break;
				case GOSSIP_ACTION_INFO_DEF + 2306:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, -2543.280273f, 934.985901f, 87.440941f, 5.518139f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 106:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[Eastern Kingdoms] ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 107);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[Kalimdor] ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 108);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[Outland] ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 109);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "[Northrend] ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 110);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());

				break;
			case GOSSIP_ACTION_INFO_DEF + 107:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Eversong Woods (1-10)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 111);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Tirisfal Glades (1-10)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 112);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Dun Morogh (1-10)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 113);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Elwynn Forest (1-10)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 114);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Ghostlands (10-20)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 115);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Silverpine Forest (10-20)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 116);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Westfall (10-20)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 117);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Loch Modan (10-20)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 118);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Redridge Mountains (15-25)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 119);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Duskwood (18-30)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 120);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[More] ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 121);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 106);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());

				break;
			case GOSSIP_ACTION_INFO_DEF + 121:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Wetlands (20-30)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 122);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Hillsbrad Foothills (20-30)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 123);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Alterac Mountains (30-40)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 124);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Arathi Highlands (30-40)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 125);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Stranglethorn Vale (30-45)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 126);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Swamp of Sorrows (35-45)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 127);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Badlads (35-45)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 128);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "The Hinterlands (40-50)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 129);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Searing Gorge (43-50)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 130);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Blasted Lands (45-55)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 131);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Burning Steppes (50-58)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 132);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[More] ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 133);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 107);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());

				break;
			case GOSSIP_ACTION_INFO_DEF + 133:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Western Plaguelands (51-58)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 134);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Eastern Plaguelands (53-60)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 135);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Deadwind Pass (55-60)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 136);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 121);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());

				break;
			case GOSSIP_ACTION_INFO_DEF + 111:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, 9079.92f, -7193.23f, 55.6013f, 5.94597f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 112:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, 2036.02f, 161.331f, 33.8674f, 0.143896f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 11:				
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Main menu]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
				break;
			case GOSSIP_ACTION_INFO_DEF + 113:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -5451.55f, -656.992f, 392.675f, 0.66789f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 114:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -9617.06f, -288.949f, 57.3053f, 4.72687f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 115:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, 7360.86f, -6803.3f, 44.2942f, 5.83679f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 116:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, 878.74f, 1359.33f, 50.355f, 5.89929f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 117:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -10235.2f, 1222.47f, 43.6252f, 6.2427f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 118:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -5202.94f, -2855.18f, 336.822f, 0.37651f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 119:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -9551.81f, -2204.73f, 93.473f, 5.47141f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 120:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -10898.3f, -364.784f, 39.2681f, 3.04614f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 122:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -3242.81f, -2469.04f, 15.9226f, 6.03924f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 123:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -436.657f, -581.254f, 53.5944f, 1.25917f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 124:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, 370.763f, -491.355f, 175.361f, 5.37858f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 125:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -1508.51f, -2732.06f, 32.4986f, 3.35708f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 126:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -12644.3f, -377.411f, 10.1021f, 6.09978f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 127:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -10345.4f, -2773.42f, 21.99f, 5.08426f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 128:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -6779.2f, -3423.64f, 241.667f, 0.647481f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 129:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, 119.387f, -3190.37f, 117.331f, 2.34064f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 130:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -7012.47f, -1065.13f, 241.786f, 5.63162f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 131:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -11182.5f, -3016.67f, 7.42235f, 4.0004f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 132:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -8118.54f, -1633.83f, 132.996f, 0.089067f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 134:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, 1728.65f, -1602.25f, 63.429f, 1.6558f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 135:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, 2300.97f, -4613.36f, 73.6231f, 0.367722f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 136:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -10438.8f, -1932.75f, 104.617f, 4.77402f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 108:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Teldrassil (1-10)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 137);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Azuremyst Isle (1-10)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 138);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Durotar (1-10)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 139);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Mulgore (1-10)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 140);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Bloodmyst Isle (10-20)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 141);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Darkshore (10-20)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 142);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "The Barrens (10-25)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 143);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Stonetalon Mountains (15-27)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 144);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Ashenvale (18-30)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 145);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Thousand Needles (25-35)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 146);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[More] ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 147);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 106);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());

				break;
			case GOSSIP_ACTION_INFO_DEF + 147:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Desolace (30-40)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 148);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Dustwallow Marsh (35-45)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 149);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Tanaris (40-50)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 150);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Feralas (40-50)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 151);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Azshara (45-55)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 152);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Felwood (48-55)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 153);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Un'Goro Crater (45-55)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 154);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Silithus (55-60)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 155);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Winterspring (55-60)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 156);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Moonglade (1-80)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 157);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 108);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());

				break;
			case GOSSIP_ACTION_INFO_DEF + 137:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, 10111.3f, 1557.73f, 1324.33f, 4.04239f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 138:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, -4216.87f, -12336.9f, 4.34247f, 6.02008f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 139:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, 1007.78f, -4446.22f, 11.2022f, 0.20797f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 140:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -2192.62f, -736.317f, -13.3274f, 0.487569f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 141:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, -1993.62f, -11475.8f, 63.9657f, 5.29437f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 142:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, 5756.25f, 298.505f, 20.6049f, 5.96504f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 143:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, 884.54f, -3548.45f, 91.8532f, 2.95957f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 144:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, 1570.92f, 1031.52f, 137.959f, 3.33006f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 145:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, 1928.34f, -2165.95f, 93.7896f, 0.205731f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 146:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -4969.02f, -1726.89f, -62.1269f, 3.7933f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 148:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -606.395f, 2211.75f, 92.9818f, 0.809746f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 149:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -4043.65f, -2991.32f, 36.3984f, 3.37443f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 150:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -7931.2f, -3414.28f, 80.7365f, 0.66522f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 151:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -4841.19f, 1309.44f, 81.3937f, 1.48501f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 152:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, 3341.36f, -4603.79f, 92.5027f, 5.28142f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 153:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, 4102.25f, -1006.79f, 272.717f, 0.790048f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 154:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -7943.22f, -2119.09f, -218.343f, 6.0727f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 155:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -7426.87f, 1005.31f, 1.13359f, 2.96086f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 156:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, 6759.18f, -4419.63f, 763.214f, 4.43476f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 157:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, 7654.3f, -2232.87f, 462.107f, 5.96786f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 109:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Hellfire Peninsula (58-63)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 158);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Zangarmarsh (60-64)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 159);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Terokkar Forest (62-65)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 160);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Nagrand (64-67)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 161);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Blade's Edge Mountains (65-68)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 162);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Shadowmoon Valley (67-70)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 163);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Netherstorm (67-70)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 164);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 106);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());

				break;
			case GOSSIP_ACTION_INFO_DEF + 158:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, -211.237f, 4278.54f, 86.5678f, 4.59776f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 159:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, -54.8621f, 5813.44f, 20.9764f, 0.081722f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 160:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, -2000.47f, 4451.54f, 8.37917f, 4.40447f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 161:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, -1145.95f, 8182.35f, 3.60249f, 6.13478f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 162:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, 3037.67f, 5962.86f, 130.774f, 1.27253f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 163:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, -3179.6f, 2716.43f, 68.6444f, 4.16414f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 164:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(530, 3830.23f, 3426.5f, 88.6145f, 5.16677f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 110:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Borean Tundra (68-72)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 165);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Howling Fjord (68-72)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 166);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Dragonblight (71-74)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 167);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Grizzly Hills (73-75)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 168);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Zul'Drak (74-77)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 169);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Sholazar Basin (76-78)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 170);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Crystalsong Forest (77-80)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 171);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "The Storm Peaks (77-80)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 172);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Icecrown (77-80)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 173);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Wintergrasp (PvP)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 174);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 106);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());

				break;
			case GOSSIP_ACTION_INFO_DEF + 165:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 3256.57f, 5278.23f, 40.8046f, 0.246367f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 166:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 1902.15f, -4883.91f, 171.363f, 3.11537f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 167:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 4103.36f, 264.478f, 50.5019f, 3.09349f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 168:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 4391.73f, -3587.92f, 238.531f, 3.57526f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 169:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 5560.23f, -3211.66f, 371.709f, 5.55055f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 170:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 5323, 4942, -133.5f, 2.17f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 171:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 5659.35f, 359.053f, 158.214f, 3.69933f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 172:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 7527.14f, -1260.89f, 919.049f, 2.0696f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 173:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 7253.64f, 1644.78f, 433.68f, 4.83412f);

				break;
			case GOSSIP_ACTION_INFO_DEF + 174:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 4760.7f, 2143.7f, 423, 1.13f);
				break;

			//custom boss zones
			case GOSSIP_ACTION_INFO_DEF + 710:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "SpiritStep", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 711);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Slithering Revenant", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 712);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Boss for OffSet Gear", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 713);
				
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
				break;
			
			//boss1
			case GOSSIP_ACTION_INFO_DEF + 711:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, -11788.4f, -4733.03f, 2.44108f, 3.92065f);
				break;
			//boss2
			case GOSSIP_ACTION_INFO_DEF + 712:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(309, -12004.4f, -2586.9f, -33.2893f, 3.02922f);
				break;
			//boss3
			case GOSSIP_ACTION_INFO_DEF + 713:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(571, 6899.4638f, -4586.5009f, 452.4584f, 2.370218f);  //Off Set
				break;

				//mall
			case GOSSIP_ACTION_INFO_DEF + 8910:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo (0, 1610.99f, -5526.4f, 111.158f, 1.00078f);
				break;

								
				//custom zones
				case GOSSIP_ACTION_INFO_DEF + 310:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Armor", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 33000);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Weapon", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 43000);
				//pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Misc", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 50000);
				//pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Off Set", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 60000);
				
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
				break;
				
				case GOSSIP_ACTION_INFO_DEF + 33000://armor
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "The Great Sea Wall", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 33001);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "PyreWood", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 33002);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Arathi Farm", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 33003);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Quel Thalas", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 33004);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Ragefire Chasm", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 33005);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Blackfathom Deeps", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 33006);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Zul Farrak", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 33007);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Blackrock Depths", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 33008);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Shcolomance", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 33009);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Serpentshrine Cavern", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 33010);
				
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[More] ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 33011);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 33000);

				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
				break;
				
				case GOSSIP_ACTION_INFO_DEF + 33011://armor
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Mana Tombs", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 33012);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Auchenai Crypts", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 33013);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Tempest Keep", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 33014);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Magister Terrance", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 33015);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Zul Aman", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 33016);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "The Nexus", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 33017);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "The Forge of Souls", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 33018);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "The Pit Saron", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 33019);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Naxxramas", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 33020);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Obsidian Sanctum", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 33021);
				
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[More] ->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 33022);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 33000);

				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
				break;
				
				case GOSSIP_ACTION_INFO_DEF + 33022://armor
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Ruby Sanctum", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 33023);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Vault of Archavon", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 33024);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Gruul Lair", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 33025);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Trial of Crusader", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 33026);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Black Temple", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 33027);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "IceCrown Citadel", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 33028);

				
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
				break;
				
				case GOSSIP_ACTION_INFO_DEF + 43000://weapon
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Ahn'Qiraj Ruins", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 43001);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Zul Gurub", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 43002);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Halls of Lightning", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 43003);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Blackwing Lair", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 43004);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Sunwell Plateau", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 43005);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Drak Tharon Keep", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 43006);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Azjol Nerub", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 43007);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Molten Core", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 43008);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Onyxia Lair", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 43009);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "IceCrown Citadel", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 43010);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
				break;
				
				//ARMOR
				//azshara
				case GOSSIP_ACTION_INFO_DEF + 33001:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -986.8579f, 1579.80273f, 53.6188f, 3.1323f);
				break;
				//LV2
				case GOSSIP_ACTION_INFO_DEF + 33002:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -342.29f, 1392.91f, 30.3151f, 1.86205f);
				break;
				//LV3
				case GOSSIP_ACTION_INFO_DEF + 33003:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo (0, -1853.62f, -4095.71f, 9.07503f, 4.7609f);
				break;
				//LV4
				case GOSSIP_ACTION_INFO_DEF + 33004:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, 4299.21f, -2761.83f, 16.695f, 3.75037f);
				break;
								
				
				//Drop zone
				case GOSSIP_ACTION_INFO_DEF + 3810:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "lighting Fusion Drop Zone", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3920);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Poison Fusion Drop Zone", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3921);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Fire Fusion Drop Zone", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3922);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Nature Fusion Drop Zone", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3923);
				
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
				break;
				
				//ligting
				case GOSSIP_ACTION_INFO_DEF + 3920:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo (309, -10995.6f, -872.132f,64.0393f,5.497f);
				break;
				//posion
				case GOSSIP_ACTION_INFO_DEF + 3921:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo (0,-4814.72f,-1033.11f,438.683f,2.99708f);
				break;
				//fire
				case GOSSIP_ACTION_INFO_DEF + 3922:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo (1,2155.66f,-4767.12f,55.00f,6.06036f);
				break;
				//nature
				case GOSSIP_ACTION_INFO_DEF + 392:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo (1,2155.66f,-4767.12f,55.00f,6.06036f);
				break;
												
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
				break;
				
				
				//Leveling zone
				case GOSSIP_ACTION_INFO_DEF + 8000:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Global Leveling Road", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8002);
				//pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Leveling Road two", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8003);
				//pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Instance Leveling Road 200 -255", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8004);
				
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
				break;
			
				
				// Global
				case GOSSIP_ACTION_INFO_DEF + 8002:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(1, 4610.91f, -3866.39f, 944.186f, 1.11835f);
				break;
				
				// road 1
				case GOSSIP_ACTION_INFO_DEF + 8003:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(37,1112.150513f,34.336452f,319.459045f,3.6249f);
				break;
				
				// road 2
				case GOSSIP_ACTION_INFO_DEF + 8004:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0,3352.92f,-3379.03f,144.782f,6.25978f);
				break;
				
				
			case GOSSIP_ACTION_INFO_DEF + 2500:
            pPlayer->AddAura(48161, pPlayer); // target, spellid, triggered-e
			pPlayer->AddAura(33077, pPlayer);
			pPlayer->AddAura(20217, pPlayer);
			pPlayer->AddAura(48932, pPlayer);
			pPlayer->AddAura(48469, pPlayer);
			pPlayer->AddAura(48469, pPlayer);
			pPlayer->AddAura(42995, pPlayer);
			pPlayer->AddAura(20911, pPlayer);
			pPlayer->AddAura(48073, pPlayer);
			pPlayer->AddAura(48169, pPlayer);
			pPlayer->AddAura(7764, pPlayer);
			pPlayer->AddAura(16612, pPlayer);
			pPlayer->AddAura(33078, pPlayer);
		    pPlayer->AddAura(33079, pPlayer);
		    pPlayer->AddAura(33080, pPlayer);
		    pPlayer->AddAura(33081, pPlayer);
		    pPlayer->AddAura(33082, pPlayer);
		    pPlayer->AddAura(24705, pPlayer);
		    pPlayer->AddAura(26035, pPlayer);
			
		pCreature->MonsterSay("Enjoy your buffs, and remember to vote!", LANG_UNIVERSAL, NULL);
		pPlayer->CLOSE_GOSSIP_MENU();
		    break;
 
			
			case GOSSIP_ACTION_INFO_DEF + 177:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Dark War Talbuk (ground)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 178);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Deathcharger (ground)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 179);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Swift Zulian Tiger (ground)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 240);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "White Polar Bear (ground)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 241);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Great Brewfest Kodo (ground)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 242);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Cobalt Netherwing Drake (flying)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 243);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Reins of Raven Lord (ground)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 244);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Ironbound Proto-Drake (flying)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 245);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 450);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());

				break;
			case GOSSIP_ACTION_INFO_DEF + 178:
				if (PlayerHasItemOrSpell(pPlayer, 29228, 34790))
					pPlayer->SendEquipError(EQUIP_ERR_CANT_CARRY_MORE_OF_THIS, NULL, NULL);
				else
				{
					pPlayer->AddItem(29228, 1);
					pCreature->MonsterWhisper("Enjoy your Dark War Talbuk!", pPlayer->GetGUID());
				}
				pPlayer->CLOSE_GOSSIP_MENU();
				break;
			case GOSSIP_ACTION_INFO_DEF + 179:
				if (PlayerHasItemOrSpell(pPlayer, 13335, 17481))
					pPlayer->SendEquipError(EQUIP_ERR_CANT_CARRY_MORE_OF_THIS, NULL, NULL);
				else
				{
					pPlayer->AddItem(13335, 1);
					pCreature->MonsterWhisper("Enjoy your Deathcharger!", pPlayer->GetGUID());
				}
				pPlayer->CLOSE_GOSSIP_MENU();
				break;
			case GOSSIP_ACTION_INFO_DEF + 240:
				if (PlayerHasItemOrSpell(pPlayer, 19902, 24252))
					pPlayer->SendEquipError(EQUIP_ERR_CANT_CARRY_MORE_OF_THIS, NULL, NULL);
				else
				{
					pPlayer->AddItem(19902, 1);
					pCreature->MonsterWhisper("Enjoy your Swift Zulian Tiger!", pPlayer->GetGUID());
				}
				pPlayer->CLOSE_GOSSIP_MENU();
				break;
			case GOSSIP_ACTION_INFO_DEF + 241:
				if (PlayerHasItemOrSpell(pPlayer, 43962, 54753))
					pPlayer->SendEquipError(EQUIP_ERR_CANT_CARRY_MORE_OF_THIS, NULL, NULL);
				else
				{
					pPlayer->AddItem(43962, 1);
					pCreature->MonsterWhisper("Enjoy your White Polar Bear!", pPlayer->GetGUID());
				}
				pPlayer->CLOSE_GOSSIP_MENU();
				break;
			case GOSSIP_ACTION_INFO_DEF + 242:
				if (PlayerHasItemOrSpell(pPlayer, 37828, 49379))
					pPlayer->SendEquipError(EQUIP_ERR_CANT_CARRY_MORE_OF_THIS, NULL, NULL);
				else
				{
					pPlayer->AddItem(37828, 1);
					pCreature->MonsterWhisper("Enjoy your Great Brewfest Kodo!", pPlayer->GetGUID());
				}
				pPlayer->CLOSE_GOSSIP_MENU();
				break;
			case GOSSIP_ACTION_INFO_DEF + 243:
				if (PlayerHasItemOrSpell(pPlayer, 32859, 41515))
					pPlayer->SendEquipError(EQUIP_ERR_CANT_CARRY_MORE_OF_THIS, NULL, NULL);
				else
				{
					pPlayer->AddItem(32859, 1);
					pCreature->MonsterWhisper("Enjoy your Cobalt Netherwing Drake!", pPlayer->GetGUID());
				}
				pPlayer->CLOSE_GOSSIP_MENU();
				break;
			case GOSSIP_ACTION_INFO_DEF + 244:
				if (PlayerHasItemOrSpell(pPlayer, 32458, 40192))
					pPlayer->SendEquipError(EQUIP_ERR_CANT_CARRY_MORE_OF_THIS, NULL, NULL);
				else
				{
					pPlayer->AddItem(32768, 1);
					pCreature->MonsterWhisper("Enjoy your Reins of Raven Lord!", pPlayer->GetGUID());
				}
				pPlayer->CLOSE_GOSSIP_MENU();
				break;
			case GOSSIP_ACTION_INFO_DEF + 245:
				if (PlayerHasItemOrSpell(pPlayer, 45801, 63956))
					pPlayer->SendEquipError(EQUIP_ERR_CANT_CARRY_MORE_OF_THIS, NULL, NULL);
				else
				{
					pPlayer->AddItem(45801, 1);
					pCreature->MonsterWhisper("Enjoy your Ironbound Proto-Drake!", pPlayer->GetGUID());
				}
				pPlayer->CLOSE_GOSSIP_MENU();
				break;
			case GOSSIP_ACTION_INFO_DEF + 246:
				GiveRidingSkill(pPlayer, pCreature);
				
				case GOSSIP_ACTION_INFO_DEF + 3526:
				{
					if(!pPlayer->duel) // Checks if a player is in a duel or not.
                        {
                        pPlayer->ClearInCombat();
                        ChatHandler(pPlayer->GetSession()).SendSysMessage("Your combat is cleared!");
                        }
                            else
                            {
                        ChatHandler(pPlayer->GetSession()).SendSysMessage("You're in a duel! You can not use this!!");
                        pPlayer->PlayerTalkClass->SendCloseGossip();
                            }
                    return true;
                };

				pPlayer->CLOSE_GOSSIP_MENU();
				break;
			case GOSSIP_ACTION_INFO_DEF + 247:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Give me 10.000 honor.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 248);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Give me 10.000 arena points.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 249);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);

				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
				break;
			case GOSSIP_ACTION_INFO_DEF + 248:
				if (PlayerReachedHonorCap(pPlayer))
					pCreature->MonsterWhisper("Honor cap reached!", pPlayer->GetGUID());
				else
				{
					pPlayer->ModifyHonorPoints(1);
					pCreature->MonsterWhisper("I have given you 1 honor points!", pPlayer->GetGUID());
				}
				pPlayer->CLOSE_GOSSIP_MENU();
				break;
				
			case GOSSIP_ACTION_INFO_DEF + 460:
				
		if(pPlayer->getClass() == CLASS_WARRIOR)
			{
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Learn for my class spell.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3000);
			}
		if(pPlayer->getClass() == CLASS_DEATH_KNIGHT)
			{
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Learn for my class spell.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3001);
			}
 
        if(pPlayer->getClass() == CLASS_DRUID)
			{
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Learn for my class spell.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3002);
			}
 
        if(pPlayer->getClass() == CLASS_HUNTER)
			{
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Learn for my class spell.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3003);
			}
 
        if(pPlayer->getClass() == CLASS_MAGE)
			{
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Learn for my class spell.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3004);
			}
 
        if(pPlayer->getClass() == CLASS_PALADIN)
			{
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Learn for my class spell.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3005);
			}
 
        if(pPlayer->getClass() == CLASS_PRIEST)
			{
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Learn for my class spell.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3006);
			}
 
        if(pPlayer->getClass() == CLASS_ROGUE )
			{
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Learn for my class spell.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3007);
			}
 
        if(pPlayer->getClass() == CLASS_SHAMAN)
			{
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Learn for my class spell.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3008);
			}
 
        if(pPlayer->getClass() == CLASS_WARLOCK)
			{
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Learn for my class spell.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3009);
			}
		 
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
				break;
				
				case GOSSIP_ACTION_INFO_DEF + 3000:
        pPlayer->CLOSE_GOSSIP_MENU();
        pPlayer->learnSpell(2457, false);
        pPlayer->learnSpell(1715, false);
        pPlayer->learnSpell(2687, false);
        pPlayer->learnSpell(71, false);
        pPlayer->learnSpell(355, false);
        pPlayer->learnSpell(7384, false);
        pPlayer->learnSpell(72, false);
        pPlayer->learnSpell(694, false);
        pPlayer->learnSpell(2565, false);
        pPlayer->learnSpell(676, false);
        pPlayer->learnSpell(20230, false);
        pPlayer->learnSpell(12678, false);
        pPlayer->learnSpell(5246, false);
        pPlayer->learnSpell(1161, false);
        pPlayer->learnSpell(871, false);
        pPlayer->learnSpell(2458, false);
        pPlayer->learnSpell(20252, false);
        pPlayer->learnSpell(18449, false);
        pPlayer->learnSpell(1680, false);
        pPlayer->learnSpell(6552, false);
        pPlayer->learnSpell(11578, false);
        pPlayer->learnSpell(1719, false);
        pPlayer->learnSpell(34428, false);
        pPlayer->learnSpell(23920, false);
        pPlayer->learnSpell(3411, false);
        pPlayer->learnSpell(55694, false);
        pPlayer->learnSpell(47450, false);
        pPlayer->learnSpell(47465, false);
        pPlayer->learnSpell(47520, false);
        pPlayer->learnSpell(47436, false);
        pPlayer->learnSpell(47502, false);
        pPlayer->learnSpell(47437, false);
        pPlayer->learnSpell(47475, false);
        pPlayer->learnSpell(47440, false);
        pPlayer->learnSpell(47471, false);
        pPlayer->learnSpell(57755, false);
        pPlayer->learnSpell(57823, false);
        pPlayer->learnSpell(47488, false);
        break;
				case GOSSIP_ACTION_INFO_DEF + 3001:
	    pPlayer->CLOSE_GOSSIP_MENU();
        pPlayer->learnSpell(48778, false);
        pPlayer->learnSpell(48266, false);
        pPlayer->learnSpell(50977, false);
        pPlayer->learnSpell(49576, false);
        pPlayer->learnSpell(49142, false);
        pPlayer->learnSpell(46584, false);
        pPlayer->learnSpell(48263, false);
        pPlayer->learnSpell(48528, false);
        pPlayer->learnSpell(45524, false);
        pPlayer->learnSpell(3714, false);
        pPlayer->learnSpell(48792, false);
        pPlayer->learnSpell(45529, false);
        pPlayer->learnSpell(56222, false);
        pPlayer->learnSpell(48743, false);
        pPlayer->learnSpell(56815, false);
        pPlayer->learnSpell(48707, false);
        pPlayer->learnSpell(48265, false);
        pPlayer->learnSpell(41999, false);
        pPlayer->learnSpell(47568, false);
        pPlayer->learnSpell(57623, false);
        pPlayer->learnSpell(49941, false);
        pPlayer->learnSpell(49909, false);
        pPlayer->learnSpell(42650, false);
        pPlayer->learnSpell(49930, false);
        pPlayer->learnSpell(49938, false);
        pPlayer->learnSpell(49895, false);
        pPlayer->learnSpell(49924, false);
        pPlayer->learnSpell(49921, false);
		break;
		case GOSSIP_ACTION_INFO_DEF + 3002:
			        pPlayer->CLOSE_GOSSIP_MENU();
        pPlayer->learnSpell(5487, false);
        pPlayer->learnSpell(6795, false);
        pPlayer->learnSpell(18960, false);
        pPlayer->learnSpell(5229, false);
        pPlayer->learnSpell(8946, false);
        pPlayer->learnSpell(1066, false);
        pPlayer->learnSpell(768, false);
        pPlayer->learnSpell(2782, false);
        pPlayer->learnSpell(2893, false);
        pPlayer->learnSpell(5209, false);
        pPlayer->learnSpell(783, false);
        pPlayer->learnSpell(5225, false);
        pPlayer->learnSpell(22842, false);
        pPlayer->learnSpell(9634, false);
        pPlayer->learnSpell(20719, false);
        pPlayer->learnSpell(29166, false);
        pPlayer->learnSpell(22812, false);
        pPlayer->learnSpell(8983, false);
        pPlayer->learnSpell(18658, false);
        pPlayer->learnSpell(33357, false);
        pPlayer->learnSpell(33786, false);
        pPlayer->learnSpell(26995, false);
        pPlayer->learnSpell(40120, false);
        pPlayer->learnSpell(62078, false);
        pPlayer->learnSpell(49802, false);
        pPlayer->learnSpell(53307, false);
        pPlayer->learnSpell(52610, false);
        pPlayer->learnSpell(48575, false);
        pPlayer->learnSpell(48476, false);
        pPlayer->learnSpell(48560, false);
        pPlayer->learnSpell(49803, false);
        pPlayer->learnSpell(48443, false);
        pPlayer->learnSpell(48562, false);
        pPlayer->learnSpell(53308, false);
        pPlayer->learnSpell(48577, false);
        pPlayer->learnSpell(53312, false);
        pPlayer->learnSpell(48574, false);
        pPlayer->learnSpell(48465, false);
        pPlayer->learnSpell(48570, false);
        pPlayer->learnSpell(48378, false);
        pPlayer->learnSpell(48480, false);
        pPlayer->learnSpell(48579, false);
        pPlayer->learnSpell(48477, false);
        pPlayer->learnSpell(50213, false);
        pPlayer->learnSpell(48461, false);
        pPlayer->learnSpell(48470, false);
        pPlayer->learnSpell(48467, false);
        pPlayer->learnSpell(48568, false);
        pPlayer->learnSpell(48451, false);
        pPlayer->learnSpell(48469, false);
        pPlayer->learnSpell(48463, false);
        pPlayer->learnSpell(48441, false);
        pPlayer->learnSpell(50763, false);
        pPlayer->learnSpell(49800, false);
        pPlayer->learnSpell(48572, false);
        pPlayer->learnSpell(48447, false);
			break;
			case GOSSIP_ACTION_INFO_DEF + 3003:
				pPlayer->CLOSE_GOSSIP_MENU();
        pPlayer->learnSpell(75, false);
        pPlayer->learnSpell(1494, false);
        pPlayer->learnSpell(13163, false);
        pPlayer->learnSpell(5116, false);
        pPlayer->learnSpell(883, false);
        pPlayer->learnSpell(2641, false);
        pPlayer->learnSpell(6991, false);
        pPlayer->learnSpell(982, false);
        pPlayer->learnSpell(1515, false);
        pPlayer->learnSpell(19883, false);
        pPlayer->learnSpell(20736, false);
        pPlayer->learnSpell(2974, false);
        pPlayer->learnSpell(6197, false);
        pPlayer->learnSpell(1002, false);
        pPlayer->learnSpell(19884, false);
        pPlayer->learnSpell(5118, false);
        pPlayer->learnSpell(34074, false);
        pPlayer->learnSpell(781, false);
        pPlayer->learnSpell(3043, false);
        pPlayer->learnSpell(1462, false);
        pPlayer->learnSpell(19885, false);
        pPlayer->learnSpell(3045, false);
        pPlayer->learnSpell(19880, false);
        pPlayer->learnSpell(13809, false);
        pPlayer->learnSpell(13161, false);
        pPlayer->learnSpell(5384, false);
        pPlayer->learnSpell(1543, false);
        pPlayer->learnSpell(19878, false);
        pPlayer->learnSpell(3034, false);
        pPlayer->learnSpell(13159, false);
        pPlayer->learnSpell(19882, false);
        pPlayer->learnSpell(14327, false);
        pPlayer->learnSpell(19879, false);
        pPlayer->learnSpell(19263, false);
        pPlayer->learnSpell(14311, false);
        pPlayer->learnSpell(19801, false);
        pPlayer->learnSpell(34026, false);
        pPlayer->learnSpell(27044, false);
        pPlayer->learnSpell(34600, false);
        pPlayer->learnSpell(34477, false);
        pPlayer->learnSpell(53271, false);
        pPlayer->learnSpell(49071, false);
        pPlayer->learnSpell(53338, false);
        pPlayer->learnSpell(49067, false);
        pPlayer->learnSpell(48996, false);
        pPlayer->learnSpell(49052, false);
        pPlayer->learnSpell(49056, false);
        pPlayer->learnSpell(49045, false);
        pPlayer->learnSpell(49001, false);
        pPlayer->learnSpell(61847, false);
        pPlayer->learnSpell(60192, false);
        pPlayer->learnSpell(61006, false);
        pPlayer->learnSpell(48990, false);
        pPlayer->learnSpell(53339, false);
        pPlayer->learnSpell(49048, false);
        pPlayer->learnSpell(58434, false);
				break;
			case GOSSIP_ACTION_INFO_DEF + 3004:
				pPlayer->CLOSE_GOSSIP_MENU();
        pPlayer->learnSpell(130, false);
        pPlayer->learnSpell(475, false);
        pPlayer->learnSpell(1953, false);
        pPlayer->learnSpell(12051, false);
        pPlayer->learnSpell(7301, false);
        pPlayer->learnSpell(32271, false);
        pPlayer->learnSpell(3562, false);
        pPlayer->learnSpell(3567, false);
        pPlayer->learnSpell(32272, false);
        pPlayer->learnSpell(3561, false);
        pPlayer->learnSpell(3563, false);
        pPlayer->learnSpell(2139, false);
        pPlayer->learnSpell(45438, false);
        pPlayer->learnSpell(3565, false);
        pPlayer->learnSpell(3566, false);
        pPlayer->learnSpell(32266, false);
        pPlayer->learnSpell(11416, false);
        pPlayer->learnSpell(11417, false);
        pPlayer->learnSpell(32267, false);
        pPlayer->learnSpell(10059, false);
        pPlayer->learnSpell(11418, false);
        pPlayer->learnSpell(11419, false);
        pPlayer->learnSpell(11420, false);
        pPlayer->learnSpell(12826, false);
        pPlayer->learnSpell(66, false);
        pPlayer->learnSpell(30449, false);
        pPlayer->learnSpell(53140, false);
        pPlayer->learnSpell(42917, false);
        pPlayer->learnSpell(43015, false);
        pPlayer->learnSpell(43017, false);
        pPlayer->learnSpell(42985, false);
        pPlayer->learnSpell(43010, false);
        pPlayer->learnSpell(42833, false);
        pPlayer->learnSpell(42914, false);
        pPlayer->learnSpell(42859, false);
        pPlayer->learnSpell(42846, false);
        pPlayer->learnSpell(43012, false);
        pPlayer->learnSpell(42842, false);
        pPlayer->learnSpell(43008, false);
        pPlayer->learnSpell(43024, false);
        pPlayer->learnSpell(43020, false);
        pPlayer->learnSpell(43046, false);
        pPlayer->learnSpell(42897, false);
        pPlayer->learnSpell(43002, false);
        pPlayer->learnSpell(42921, false);
        pPlayer->learnSpell(42940, false);
        pPlayer->learnSpell(42956, false);
        pPlayer->learnSpell(61316, false);
        pPlayer->learnSpell(61024, false);
        pPlayer->learnSpell(42973, false);
        pPlayer->learnSpell(47610, false);
        pPlayer->learnSpell(58659, false);
	if (pPlayer->GetTeam() == HORDE) {
				pPlayer->learnSpell(11418, false);
				pPlayer->learnSpell(11420, false);
				pPlayer->learnSpell(11417, false);
				pPlayer->learnSpell(32267, false);
				pPlayer->learnSpell(32272, false);
				pPlayer->learnSpell(3567, false);
				pPlayer->learnSpell(3563, false);
				pPlayer->learnSpell(3566, false);
		}
			else {
				pPlayer->learnSpell(11419, false);
				pPlayer->learnSpell(32266, false);
				pPlayer->learnSpell(11416, false);
				pPlayer->learnSpell(10059, false);
				pPlayer->learnSpell(3565, false);
				pPlayer->learnSpell(32271, false);
				pPlayer->learnSpell(3562, false);
				pPlayer->learnSpell(3561, false);	
			}
				break;
				case GOSSIP_ACTION_INFO_DEF + 3005:
					pPlayer->CLOSE_GOSSIP_MENU();
        pPlayer->learnSpell(21084, false);
        pPlayer->learnSpell(20271, false);
        pPlayer->learnSpell(498, false);
        pPlayer->learnSpell(1152, false);
        pPlayer->learnSpell(53408, false);
        pPlayer->learnSpell(31789, false);
        pPlayer->learnSpell(62124, false);
        pPlayer->learnSpell(25780, false);
        pPlayer->learnSpell(1044, false);
        pPlayer->learnSpell(5502, false);
        pPlayer->learnSpell(19746, false);
        pPlayer->learnSpell(20164, false);
        pPlayer->learnSpell(10326, false);
        pPlayer->learnSpell(1038, false);
        pPlayer->learnSpell(53407, false);
        pPlayer->learnSpell(19752, false);
        pPlayer->learnSpell(20165, false);
        pPlayer->learnSpell(642, false);
        pPlayer->learnSpell(10278, false);
        pPlayer->learnSpell(20166, false);
        pPlayer->learnSpell(4987, false);
        pPlayer->learnSpell(6940, false);
        pPlayer->learnSpell(10308, false);
        pPlayer->learnSpell(23214, false);
        pPlayer->learnSpell(25898, false);
        pPlayer->learnSpell(25899, false);
        pPlayer->learnSpell(34767, false);
        pPlayer->learnSpell(32223, false);
        pPlayer->learnSpell(33776, false);
        pPlayer->learnSpell(31884, false);
        pPlayer->learnSpell(54428, false);
        pPlayer->learnSpell(54043, false);
        pPlayer->learnSpell(48943, false);
        pPlayer->learnSpell(48936, false);
        pPlayer->learnSpell(48945, false);
        pPlayer->learnSpell(48938, false);
        pPlayer->learnSpell(48947, false);
        pPlayer->learnSpell(48817, false);
        pPlayer->learnSpell(48788, false);
        pPlayer->learnSpell(48932, false);
        pPlayer->learnSpell(48942, false);
        pPlayer->learnSpell(48801, false);
        pPlayer->learnSpell(48785, false);
        pPlayer->learnSpell(48934, false);
        pPlayer->learnSpell(48950, false);
        pPlayer->learnSpell(48819, false);
        pPlayer->learnSpell(48806, false);
        pPlayer->learnSpell(48782, false);
        pPlayer->learnSpell(53601, false);
        pPlayer->learnSpell(61411, false);
					break;
					case GOSSIP_ACTION_INFO_DEF + 3006:
						pPlayer->CLOSE_GOSSIP_MENU();
        pPlayer->learnSpell(586, false);
        pPlayer->learnSpell(2053, false);
        pPlayer->learnSpell(528, false);
        pPlayer->learnSpell(6346, false);
        pPlayer->learnSpell(453, false);
        pPlayer->learnSpell(8129, false);
        pPlayer->learnSpell(605, false);
        pPlayer->learnSpell(552, false);
        pPlayer->learnSpell(6064, false);
        pPlayer->learnSpell(1706, false);
        pPlayer->learnSpell(988, false);
        pPlayer->learnSpell(10909, false);
        pPlayer->learnSpell(10890, false);
        pPlayer->learnSpell(60931, false);
        pPlayer->learnSpell(10955, false);
        pPlayer->learnSpell(34433, false);
        pPlayer->learnSpell(32375, false);
        pPlayer->learnSpell(48072, false);
        pPlayer->learnSpell(48169, false);
        pPlayer->learnSpell(48168, false);
        pPlayer->learnSpell(48170, false);
        pPlayer->learnSpell(48120, false);
        pPlayer->learnSpell(48063, false);
        pPlayer->learnSpell(48135, false);
        pPlayer->learnSpell(48171, false);
        pPlayer->learnSpell(48300, false);
        pPlayer->learnSpell(48071, false);
        pPlayer->learnSpell(48127, false);
        pPlayer->learnSpell(48113, false);
        pPlayer->learnSpell(48123, false);
        pPlayer->learnSpell(48173, false);
        pPlayer->learnSpell(47951, false);
        pPlayer->learnSpell(48073, false);
        pPlayer->learnSpell(48078, false);
        pPlayer->learnSpell(48087, false);
        pPlayer->learnSpell(53023, false);
        pPlayer->learnSpell(48161, false);
        pPlayer->learnSpell(48066, false);
        pPlayer->learnSpell(48162, false);
        pPlayer->learnSpell(48074, false);
        pPlayer->learnSpell(48068, false);
        pPlayer->learnSpell(48158, false);
        pPlayer->learnSpell(48125, false);
						break;
case GOSSIP_ACTION_INFO_DEF + 3007:
	pPlayer->CLOSE_GOSSIP_MENU();
        pPlayer->learnSpell(921, false);
        pPlayer->learnSpell(1776, false);
        pPlayer->learnSpell(1766, false);
        pPlayer->learnSpell(1804, false);
        pPlayer->learnSpell(51722, false);
        pPlayer->learnSpell(1725, false);
        pPlayer->learnSpell(2836, false);
        pPlayer->learnSpell(1833, false);
        pPlayer->learnSpell(1842, false);
        pPlayer->learnSpell(2094, false);
        pPlayer->learnSpell(1860, false);
        pPlayer->learnSpell(6774, false);
        pPlayer->learnSpell(26669, false);
        pPlayer->learnSpell(8643, false);
        pPlayer->learnSpell(11305, false);
        pPlayer->learnSpell(1787, false);
        pPlayer->learnSpell(26889, false);
        pPlayer->learnSpell(31224, false);
        pPlayer->learnSpell(5938, false);
        pPlayer->learnSpell(51724, false);
        pPlayer->learnSpell(57934, false);
        pPlayer->learnSpell(48674, false);
        pPlayer->learnSpell(48659, false);
        pPlayer->learnSpell(48668, false);
        pPlayer->learnSpell(48672, false);
        pPlayer->learnSpell(48691, false);
        pPlayer->learnSpell(48657, false);
        pPlayer->learnSpell(57993, false);
        pPlayer->learnSpell(51723, false);
        pPlayer->learnSpell(48676, false);
        pPlayer->learnSpell(48638, false);
	break;
	case GOSSIP_ACTION_INFO_DEF + 3008:
		pPlayer->CLOSE_GOSSIP_MENU();
        pPlayer->learnSpell(30671, false);
        pPlayer->learnSpell(2484, false);
        pPlayer->learnSpell(526, false);
        pPlayer->learnSpell(57994, false);
        pPlayer->learnSpell(8143, false);
        pPlayer->learnSpell(2645, false);
        pPlayer->learnSpell(2870, false);
        pPlayer->learnSpell(8166, false);
        pPlayer->learnSpell(131, false);
        pPlayer->learnSpell(10399, false);
        pPlayer->learnSpell(6196, false);
        pPlayer->learnSpell(546, false);
        pPlayer->learnSpell(556, false);
        pPlayer->learnSpell(8177, false);
        pPlayer->learnSpell(20608, false);
        pPlayer->learnSpell(36936, false);
        pPlayer->learnSpell(8012, false);
        pPlayer->learnSpell(8512, false);
        pPlayer->learnSpell(6495, false);
        pPlayer->learnSpell(8170, false);
        pPlayer->learnSpell(3738, false);
        pPlayer->learnSpell(2062, false);
        pPlayer->learnSpell(2894, false);
        pPlayer->learnSpell(57960, false);
        pPlayer->learnSpell(49276, false);
        pPlayer->learnSpell(49236, false);
        pPlayer->learnSpell(58734, false);
        pPlayer->learnSpell(58582, false);
        pPlayer->learnSpell(58753, false);
        pPlayer->learnSpell(49231, false);
        pPlayer->learnSpell(49238, false);
        pPlayer->learnSpell(49277, false);
        pPlayer->learnSpell(55459, false);
        pPlayer->learnSpell(49271, false);
        pPlayer->learnSpell(49284, false);
        pPlayer->learnSpell(51994, false);
        pPlayer->learnSpell(61657, false);
        pPlayer->learnSpell(58739, false);
        pPlayer->learnSpell(49233, false);
        pPlayer->learnSpell(58656, false);
        pPlayer->learnSpell(58790, false);
        pPlayer->learnSpell(58745, false);
        pPlayer->learnSpell(58796, false);
        pPlayer->learnSpell(58757, false);
        pPlayer->learnSpell(49273, false);
        pPlayer->learnSpell(51514, false);
        pPlayer->learnSpell(60043, false);
        pPlayer->learnSpell(49281, false);
        pPlayer->learnSpell(58774, false);
        pPlayer->learnSpell(58749, false);
        pPlayer->learnSpell(58704, false);
        pPlayer->learnSpell(58643, false);
        pPlayer->learnSpell(58804, false);
		break;
		case GOSSIP_ACTION_INFO_DEF + 3009:
			pPlayer->CLOSE_GOSSIP_MENU();
        pPlayer->learnSpell(59671, false);
        pPlayer->learnSpell(688, false);
        pPlayer->learnSpell(696, false);
        pPlayer->learnSpell(697, false);
        pPlayer->learnSpell(5697, false);
        pPlayer->learnSpell(698, false);
        pPlayer->learnSpell(712, false);
        pPlayer->learnSpell(126, false);
        pPlayer->learnSpell(5138, false);
        pPlayer->learnSpell(5500, false);
        pPlayer->learnSpell(132, false);
        pPlayer->learnSpell(691, false);
        pPlayer->learnSpell(18647, false);
        pPlayer->learnSpell(11719, false);
        pPlayer->learnSpell(1122, false);
        pPlayer->learnSpell(17928, false);
        pPlayer->learnSpell(6215, false);
        pPlayer->learnSpell(18540, false);
        pPlayer->learnSpell(23161, false);
        pPlayer->learnSpell(29858, false);
        pPlayer->learnSpell(50511, false);
        pPlayer->learnSpell(61191, false);
        pPlayer->learnSpell(47884, false);
        pPlayer->learnSpell(47856, false);
        pPlayer->learnSpell(47813, false);
        pPlayer->learnSpell(47855, false);
        pPlayer->learnSpell(47888, false);
        pPlayer->learnSpell(47865, false);
        pPlayer->learnSpell(47860, false);
        pPlayer->learnSpell(47857, false);
        pPlayer->learnSpell(47823, false);
        pPlayer->learnSpell(47891, false);
        pPlayer->learnSpell(47878, false);
        pPlayer->learnSpell(47864, false);
        pPlayer->learnSpell(57595, false);
        pPlayer->learnSpell(47893, false);
        pPlayer->learnSpell(47820, false);
        pPlayer->learnSpell(47815, false);
        pPlayer->learnSpell(47809, false);
        pPlayer->learnSpell(60220, false);
        pPlayer->learnSpell(47867, false);
        pPlayer->learnSpell(47889, false);
        pPlayer->learnSpell(48018, false);
        pPlayer->learnSpell(47811, false);
        pPlayer->learnSpell(47838, false);
        pPlayer->learnSpell(57946, false);
        pPlayer->learnSpell(58887, false);
        pPlayer->learnSpell(47836, false);
        pPlayer->learnSpell(61290, false);
        pPlayer->learnSpell(47825, false);
			break;
			case GOSSIP_ACTION_INFO_DEF + 249:
				if (PlayerReachedArenaCap(pPlayer))
					pCreature->MonsterWhisper("Arena points cap reached!", pPlayer->GetGUID());
				else
				{
					pPlayer->ModifyArenaPoints(1);
					pCreature->MonsterWhisper("I have given you 1 arena points!", pPlayer->GetGUID());
				}

				pPlayer->CLOSE_GOSSIP_MENU();
				break;
				case GOSSIP_ACTION_INFO_DEF + 3011:
					  pPlayer->CLOSE_GOSSIP_MENU();
        pPlayer->SendTalentWipeConfirm(pCreature->GetGUID());
					break;
					case GOSSIP_ACTION_INFO_DEF + 3012:
        pPlayer->SetDrunkValue(100);
        pCreature->MonsterSay("Sweet... You're drunk now and will die soon  !", LANG_UNIVERSAL, NULL);
						break;
					case GOSSIP_ACTION_INFO_DEF + 3013:
						pPlayer->SetDrunkValue(0, 9);
        pCreature->MonsterSay("It's never to late to get drunk again.", LANG_UNIVERSAL, NULL);
						break;
						case GOSSIP_ACTION_INFO_DEF + 3014:
							  pPlayer->CLOSE_GOSSIP_MENU();
        pPlayer->SetBindPoint(pCreature->GetGUID());
							break;
			case GOSSIP_ACTION_INFO_DEF + 190:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Give me 1 Emblems of Frost.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 191);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Give me 1 Emblems of Triumph.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 192);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Give me 1 Emblems of Valor.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 193);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Give me 1 Emblems of Conquest.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 194);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Give me 1 Emblems of Heroism.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 195);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);

				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
				break;
			case GOSSIP_ACTION_INFO_DEF + 191:
				HandleEmblemGive(pPlayer, pCreature, EMBLEM_OF_FROST);
				pPlayer->CLOSE_GOSSIP_MENU();
				break;
			case GOSSIP_ACTION_INFO_DEF + 192:
				HandleEmblemGive(pPlayer, pCreature, EMBLEM_OF_TRIUMPH);
				pPlayer->CLOSE_GOSSIP_MENU();
				break;
			case GOSSIP_ACTION_INFO_DEF + 193:
				HandleEmblemGive(pPlayer, pCreature, EMBLEM_OF_VALOR);
				pPlayer->CLOSE_GOSSIP_MENU();
				break;
			case GOSSIP_ACTION_INFO_DEF + 194:
				HandleEmblemGive(pPlayer, pCreature, EMBLEM_OF_CONQUEST);
				pPlayer->CLOSE_GOSSIP_MENU();
				break;
			case GOSSIP_ACTION_INFO_DEF + 195:
				HandleEmblemGive(pPlayer, pCreature, EMBLEM_OF_HEROISM);
				pPlayer->CLOSE_GOSSIP_MENU();
				break;
			case GOSSIP_ACTION_INFO_DEF + 196:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Alchemy", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 197);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Blacksmithing", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 198);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Leatherworking", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 199);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Tailoring", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 200);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Engineering", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 201);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Enchanting", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 202);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Jewelcrafting", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 203);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Inscription", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 204);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Cooking", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 205);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "First Aid", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 206);

				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);

				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
				break;

					case GOSSIP_ACTION_INFO_DEF + 450:		
					   pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "I want to repair my items.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
					   pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "I want to get DRUNK!.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3012);
					   pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Ugh, Sober me up, I've had enough...", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3013);
					   pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Heal me.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 26);
					   //pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Combat Clear", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3526);
					   pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Advance my weapon skills to max.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
		               pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Give me maximum riding skill.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 246);
					   //pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Give me Arena & Honor Points.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 247);
					   //pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Give me Emblems.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 190);

					   pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);

				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
				break;
				
				
				
		case GOSSIP_ACTION_INFO_DEF + 50000: //Tame beast
				
		if(pPlayer->getClass() == CLASS_WARRIOR || pPlayer->getClass() == CLASS_PALADIN || pPlayer->getClass() == CLASS_DRUID || pPlayer->getClass() == CLASS_ROGUE)
        {
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Learn for my Custom Tame Beast Spell", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 50001);
		}
		
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
				break;
				
			case GOSSIP_ACTION_INFO_DEF + 50001:
				pPlayer->CLOSE_GOSSIP_MENU();
		
				pPlayer->learnSpell(1579, false);
				pPlayer->learnSpell(982, false);
				pPlayer->learnSpell(6991, false);
			break;
				
			case GOSSIP_ACTION_INFO_DEF + 197:
				CompleteLearnProfession(pPlayer, pCreature, SKILL_ALCHEMY);

				pPlayer->CLOSE_GOSSIP_MENU();
				break;
			case GOSSIP_ACTION_INFO_DEF + 198:
				CompleteLearnProfession(pPlayer, pCreature, SKILL_BLACKSMITHING);

				pPlayer->CLOSE_GOSSIP_MENU();
				break;
			case GOSSIP_ACTION_INFO_DEF + 199:
				CompleteLearnProfession(pPlayer, pCreature, SKILL_LEATHERWORKING);

				pPlayer->CLOSE_GOSSIP_MENU();
				break;
			case GOSSIP_ACTION_INFO_DEF + 200:
				CompleteLearnProfession(pPlayer, pCreature, SKILL_TAILORING);

				pPlayer->CLOSE_GOSSIP_MENU();
				break;
			case GOSSIP_ACTION_INFO_DEF + 201:
				CompleteLearnProfession(pPlayer, pCreature, SKILL_ENGINEERING);

				pPlayer->CLOSE_GOSSIP_MENU();
				break;
			case GOSSIP_ACTION_INFO_DEF + 202:
				CompleteLearnProfession(pPlayer, pCreature, SKILL_ENCHANTING);

				pPlayer->CLOSE_GOSSIP_MENU();
				break;
			case GOSSIP_ACTION_INFO_DEF + 203:
				CompleteLearnProfession(pPlayer, pCreature, SKILL_JEWELCRAFTING);

				pPlayer->CLOSE_GOSSIP_MENU();
				break;
			case GOSSIP_ACTION_INFO_DEF + 204:
				CompleteLearnProfession(pPlayer, pCreature, SKILL_INSCRIPTION);

				pPlayer->CLOSE_GOSSIP_MENU();
				break;
			case GOSSIP_ACTION_INFO_DEF + 205:
				CompleteLearnProfession(pPlayer, pCreature, SKILL_COOKING);

				pPlayer->CLOSE_GOSSIP_MENU();
				break;
			case GOSSIP_ACTION_INFO_DEF + 206:
				CompleteLearnProfession(pPlayer, pCreature, SKILL_FIRST_AID);

				pPlayer->CLOSE_GOSSIP_MENU();
				break;
				
			case GOSSIP_ACTION_INFO_DEF + 9000:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Gold Farm", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9001);
				
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<- [Back]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
				break;
				
				case GOSSIP_ACTION_INFO_DEF + 9001:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -5370.42f, -2540.19f, 484.979f, 0.4117f);
				break;
				
				case GOSSIP_ACTION_INFO_DEF + 1110:
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->TeleportTo(0, -8254.06f, -107.952f, 238.931f, 6.03092f);
				break;
		}

        return true;
	}
};

void AddSc_Script_UTeleporter()
{
	new universal_teleporter();
}