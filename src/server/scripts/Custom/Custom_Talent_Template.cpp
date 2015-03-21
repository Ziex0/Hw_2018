/*
** Copyright (C) AlexeWarr (alexei_93@yahoo.com)
*/
 
#include "Chat.h"
#include "Language.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "Chat.h"
#include <cstring>
 
#define DATABASE "deluxe_custom"
 
struct cTalentTemplateStruct
{
    uint32 SpecID;
    uint32 TalentId;
    uint8 TalentRank;
};
 
static std::map<uint32, cTalentTemplateStruct> cTalentTemplate;

namespace MyTalentTemplate
{
    bool IsAllowedToLearn(Player* player)
    {
        if (player->getLevel() < 80)
            return false;
 
        if (player->GetFreeTalentPoints() < 71)
            return false;
 
        return true;
    }
 
    void LoadTalentContainer()
    {
        uint32 oldMSTime = getMSTime();
        uint32 id = 1;
 
        cTalentTemplate.clear();
 
        QueryResult result = WorldDatabase.PQuery("SELECT spec, talent, rank FROM custom_talent_templates ORDER BY ordination ASC");
        if (result)
        {
            do
            {
                Field* fields = result->Fetch();
                cTalentTemplate[id].SpecID = fields[0].GetUInt8();
                cTalentTemplate[id].TalentId = fields[1].GetUInt32();
                cTalentTemplate[id].TalentRank = fields[2].GetUInt8();
 
                ++id;
            } while (result->NextRow());
        }

        sLog->outInfo(LOG_FILTER_GENERAL, "<#> Talent Template: Loaded %u talent rows in %u ms", id-1, GetMSTimeDiffToNow(oldMSTime));
    }
 
    void LearnTalentTemplate(Creature* creature, Player* player, uint32 spec)
    {
        for (std::map<uint32, cTalentTemplateStruct>::const_iterator it = cTalentTemplate.begin(); it != cTalentTemplate.end(); ++it)
        {
            if (cTalentTemplate[it->first].SpecID != spec)
                continue;
 
            player->LearnTalent(cTalentTemplate[it->first].TalentId, cTalentTemplate[it->first].TalentRank - 1);
        }
 
        player->SendTalentsInfoData(false);

        player->CastSpell(player, 64799, false);

        player->GetSession()->SendNotification("Your talent tree has been changed.", player, true);
    }
};
 
class TalentTemplateWorldScript : public WorldScript
{
public:
 
    TalentTemplateWorldScript() : WorldScript("TalentTemplateWorldScript") { }
 
    void OnStartup() { MyTalentTemplate::LoadTalentContainer(); }
 
    void OnConfigLoad(bool /*reload*/) { MyTalentTemplate::LoadTalentContainer(); }
};
 
enum cTSpects {
    WARRIOR_SPEC_ARMS = 1,
    WARRIOR_SPEC_FURY,
    WARRIOR_SPEC_PROTECTION,
 
    PALADIN_SPEC_HOLY,
    PALADIN_SPEC_PROTECTION,
    PALADIN_SPEC_RETRIBUTION,
 
    ROGUE_SPEC_ASSASSINATION,
    ROGUE_SPEC_COMBAT,
    ROGUE_SPEC_SUBTLEY,
 
    HUNTER_SPEC_BEAST_MASTERY,
    HUNTER_SPEC_MARKSMANSHIP,
    HUNTER_SPEC_SURVIVAL,
 
    MAGE_SPEC_ARCANE,
    MAGE_SPEC_FROST,
    MAGE_SPEC_FIRE,
 
    WARLOCK_SPEC_AFFLICTION,
    WARLOCK_SPEC_DEMONOLOGY,
    WARLOCK_SPEC_DESTRUCTION,
 
    PRIEST_SPEC_DISCIPLINE,
    PRIEST_SPEC_HOLY,
    PRIEST_SPEC_SHADOW,
 
    SHAMAN_SPEC_ELEMENTAL,
    SHAMAN_SPEC_ENHANCEMENT,
    SHAMAN_SPEC_RESTORATION,
 
    DK_SPEC_BLOOD,
    DK_SPEC_FROST,
    DK_SPEC_UNHOLY,
 
    DRUID_SPEC_BALANCE,
    DRUID_SPEC_FERAL,
    DRUID_SPEC_RESTORATION,
 
    CTMAX
};
 
class Custom_Talent_Template : public CreatureScript
{
public:
 
    Custom_Talent_Template() : CreatureScript("Custom_Talent_Template") { }
 
    bool OnGossipHello(Player* player, Creature* creature) override
    {
        switch (player->getClass())
        {
            case CLASS_WARRIOR: {
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TABARD, "|TInterface\\icons\\ability_rogue_eviscerate:25:25:0:0|t Warrior - Arms", GOSSIP_SENDER_MAIN, WARRIOR_SPEC_ARMS, "Set|cffD53925 Arms|r talent template?", 0, false);
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TABARD, "|TInterface\\icons\\ability_warrior_innerrage:25:25:0:0|t Warrior - Fury ", GOSSIP_SENDER_MAIN, WARRIOR_SPEC_FURY, "Set|cffFF9100 Fury|r talent template?", 0, false);
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TABARD, "|TInterface\\icons\\inv_shield_06:25:25:0:0|t Warrior - Protection", GOSSIP_SENDER_MAIN, WARRIOR_SPEC_PROTECTION, "Set|cff8E8E8E Protection|r talent template?", 0, false);
            } break;
 
            case CLASS_ROGUE: {
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TABARD, "|TInterface\\icons\\ability_backstab:25:25:0:0|t Rogue - Assassination", GOSSIP_SENDER_MAIN, ROGUE_SPEC_ASSASSINATION, "Set|cff00276F Assassination|r talent template?", 0, false);
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TABARD, "|TInterface\\icons\\ability_rogue_eviscerate:25:25:0:0|t Rogue - Combat", GOSSIP_SENDER_MAIN, ROGUE_SPEC_COMBAT, "Set|cffFF9500 Combat|r talent template?", 0, false);
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TABARD, "|TInterface\\icons\\ability_stealth:25:25:0:0|t Rogue - Subtley", GOSSIP_SENDER_MAIN, ROGUE_SPEC_SUBTLEY, "Set|cff7932BC Subtley|r talent template?", 0, false);
            } break;
 
            case CLASS_PALADIN: {
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TABARD, "|TInterface\\icons\\spell_holy_holybolt:25:25:0:0|t Paladin - Holy Support", GOSSIP_SENDER_MAIN, PALADIN_SPEC_HOLY, "Set|cffF9FF72 Holy|r talent template?", 0, false);
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TABARD, "|TInterface\\icons\\spell_holy_devotionaura:25:25:0:0|t Paladin - Protection", GOSSIP_SENDER_MAIN, PALADIN_SPEC_PROTECTION, "Set|cff8E8E8E Protection|r talent template?", 0, false);
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TABARD, "|TInterface\\icons\\spell_holy_auraoflight:25:25:0:0|t Paladin - Retribution", GOSSIP_SENDER_MAIN, PALADIN_SPEC_RETRIBUTION, "Set|cff2C56B2 Retribution|r talent template?", 0, false);
            } break;
 
            case CLASS_HUNTER: {
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TABARD, "|TInterface\\icons\\ability_hunter_beasttaming:25:25:0:0|t Hunter - Beast Mastery", GOSSIP_SENDER_MAIN, HUNTER_SPEC_BEAST_MASTERY, "Set|cff016712 Beast Mastery|r talent template?", 0, false);
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TABARD, "|TInterface\\icons\\ability_marksmanship:25:25:0:0|t Hunter - Marksmanship", GOSSIP_SENDER_MAIN, HUNTER_SPEC_MARKSMANSHIP, "Set|cffFF9500 Marksmanship|r talent template?", 0, false);
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TABARD, "|TInterface\\icons\\ability_hunter_swiftstrike:25:25:0:0|t Hunter - Survival", GOSSIP_SENDER_MAIN, HUNTER_SPEC_SURVIVAL, "Set|cff27A11E Survival|r talent template?", 0, false);
            } break;
 
            case CLASS_MAGE: {
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TABARD, "|TInterface\\icons\\spell_holy_magicalsentry:25:25:0:0|t Mage - Arcane", GOSSIP_SENDER_MAIN, MAGE_SPEC_ARCANE, "Set|cff555DFF Arcane|r talent template?", 0, false);
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TABARD, "|TInterface\\icons\\spell_frost_frostbolt02:25:25:0:0|t Mage - Frost", GOSSIP_SENDER_MAIN, MAGE_SPEC_FROST, "Set|cff54C1FF Frost|r talent template?", 0, false);
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TABARD, "|TInterface\\icons\\spell_fire_flamebolt:25:25:0:0|t Mage - Fire", GOSSIP_SENDER_MAIN, MAGE_SPEC_FIRE, "Set|cffFFF300 Fire|r talent template?", 0, false);
            } break;
 
            case CLASS_WARLOCK : {
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TABARD, "|TInterface\\icons\\spell_shadow_deathcoil:25:25:0:0|t Warlock - Affliction", GOSSIP_SENDER_MAIN, WARLOCK_SPEC_AFFLICTION, "Set|cff9E1E10 Affliction|r talent template?", 0, false);
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TABARD, "|TInterface\\icons\\spell_shadow_metamorphosis:25:25:0:0|t Warlock - Demonology", GOSSIP_SENDER_MAIN, WARLOCK_SPEC_DEMONOLOGY, "Set|cffA1A1A1 Demonology|r talent template?", 0, false);
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TABARD, "|TInterface\\icons\\spell_shadow_rainoffire:25:25:0:0|t Warlock- Destruction", GOSSIP_SENDER_MAIN, WARLOCK_SPEC_DESTRUCTION, "Set|cff7932BC Destruction|r talent template?", 0, false);
            } break;
 
            case CLASS_PRIEST: {
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TABARD, "|TInterface\\icons\\spell_holy_wordfortitude:25:25:0:0|t Priest - Discipline", GOSSIP_SENDER_MAIN, PRIEST_SPEC_DISCIPLINE, "Set|cffA4FAFF Discipline|r talent template?", 0, false);
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TABARD, "|TInterface\\icons\\spell_holy_holybolt:25:25:0:0|t Priest - Holy Support", GOSSIP_SENDER_MAIN, PRIEST_SPEC_HOLY, "Set|cffF9FF72 Holy|r talent template?", 0, false);
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TABARD, "|TInterface\\icons\\spell_shadow_shadowwordpain:25:25:0:0|t Priest - Shadow", GOSSIP_SENDER_MAIN, PRIEST_SPEC_SHADOW, "Set|cff7932BC Shadow|r talent template?", 0, false);
            } break;
 
            case CLASS_SHAMAN: {
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TABARD, "|TInterface\\icons\\spell_nature_lightning:25:25:0:0|t Shaman - Elemental", GOSSIP_SENDER_MAIN, SHAMAN_SPEC_ELEMENTAL, "Set|cff3CA5FF Elemental|r talent template?", 0, false);
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TABARD, "|TInterface\\icons\\spell_nature_lightningshield:25:25:0:0|t Shaman - Enhancement", GOSSIP_SENDER_MAIN, SHAMAN_SPEC_ENHANCEMENT, "Set|cffFF9500 Enhancement|r talent template?", 0, false);
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TABARD, "|TInterface\\icons\\spell_nature_magicimmunity:25:25:0:0|t Shaman - Restoration", GOSSIP_SENDER_MAIN, SHAMAN_SPEC_RESTORATION, "Set|cff27A11E Restoration|r talent template?", 0, false);
            } break;
 
            case CLASS_DEATH_KNIGHT: {
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TABARD, "|TInterface\\icons\\spell_deathknight_bloodpresence:25:25:0:0|t Death Knight - Blood", GOSSIP_SENDER_MAIN, DK_SPEC_BLOOD, "Set|cffD53925 Blood|r talent template?", 0, false);
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TABARD, "|TInterface\\icons\\spell_deathknight_frostpresence:25:25:0:0|t Death Knight - Frost", GOSSIP_SENDER_MAIN, DK_SPEC_FROST, "Set|cff54C1FF Frost|r talent template?", 0, false);
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TABARD, "|TInterface\\icons\\spell_deathknight_unholypresence:25:25:0:0|t Death Knight - Unholy", GOSSIP_SENDER_MAIN, DK_SPEC_UNHOLY, "Set|cff259D3B Unholy|r talent template?", 0, false);
            } break;
 
            case CLASS_DRUID: {
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TABARD, "|TInterface\\icons\\spell_nature_starfall:25:25:0:0|t Druid - Balance", GOSSIP_SENDER_MAIN, DRUID_SPEC_BALANCE, "Set|cff16CBBF Balance|r talent template?", 0, false);
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TABARD, "|TInterface\\icons\\ability_racial_bearform:25:25:0:0|t Druid - Feral", GOSSIP_SENDER_MAIN, DRUID_SPEC_FERAL, "Set|cffFF9100 Feral|r talent template?", 0, false);
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TABARD, "|TInterface\\icons\\spell_nature_healingtouch:25:25:0:0|t Druid - Restoration", GOSSIP_SENDER_MAIN, DRUID_SPEC_RESTORATION, "Set |cff27A11E Restoration |r talent template ? ", 0, false);
            } break;
        }
 
        player->PlayerTalkClass->SendGossipMenu(907, creature->GetGUID());
 
        return true;
    }
 
    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
 
        if (!MyTalentTemplate::IsAllowedToLearn(player))
           player->GetSession()->SendNotification("You need to reset your talents first!", player, true);
        else
            MyTalentTemplate::LearnTalentTemplate(creature, player, action);
 
        player->CLOSE_GOSSIP_MENU();
 
        return true;
    }
};
 
void AddSC_Custom_Talent_Template()
{
    new TalentTemplateWorldScript();
    new Custom_Talent_Template();
}