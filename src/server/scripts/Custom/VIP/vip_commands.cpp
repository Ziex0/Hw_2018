/*
  _____                        ____               
 |  ___| __ ___ _______ _ __  / ___|___  _ __ ___ 
 | |_ | '__/ _ \_  / _ \ '_ \| |   / _ \| '__/ _ \
 |  _|| | | (_) / /  __/ | | | |__| (_) | | |  __/
 |_|  |_|  \___/___\___|_| |_|\____\___/|_|  \___|
	 Lightning speed and strength
		 conjured directly from the depths of logic!   
			Infusion-WoW 2011 - 2012 (C)
<--------------------------------------------------------------------------->
 - Developer(s): Styler
 - Complete: 90%
 - ScriptName: 'vipcommands' 
 - Comment: VIP commands for VIPS -> GM rank 1+
<--------------------------------------------------------------------------->
*/

#include "ScriptMgr.h"
#include "ObjectMgr.h"
#include "MapManager.h"
#include "Common.h"
#include "Language.h"


class vipcommands : public CommandScript
{
public:
    vipcommands() : CommandScript("vipcommands") { }

    ChatCommand* GetCommands() const
    {
        static ChatCommand vipCommandTable[] =

        {
			{ "mall",          	 	 SEC_VIP,  false, &HandleVipMallCommand,         	"", NULL },
			{ "changerace",          SEC_VIP,  false, &HandleChangeRaceCommand,      	"", NULL },
			{ "changefaction",		 SEC_VIP,  false, &HandleChangeFactionCommand,		"", NULL },
			{ "maxskills",			 SEC_VIP,  false, &HandleMaxSkillsCommand,			"", NULL },
			{ "customize",			 SEC_VIP,  false, &HandleCustomizeCommand,			"", NULL },
			{ "buffs",      		 SEC_VIP,  false, &HandleBuffCommand,				"", NULL },
			{ "getdrunk",   		 SEC_VIP,  false, &HandleGetDrunkCommand,     		"", NULL },
			{ "soberup",    		 SEC_VIP,  false, &HandleSoberUpCommand,         	"", NULL },
			{ "morph",           	 SEC_VIP,  false, &HandleVIPMorphCommand,          "", NULL },
			{ "demorph",           	 SEC_VIP,  false, &HandleVIPDeMorphCommand,        "", NULL },
			{ "tele",           	 SEC_VIP,  false, &HandleTeleCommand,         		"", NULL },
			{ "scale",        		 SEC_VIP,  false, &HandleScaleCommand,           	"", NULL },
			{ "repair",        		 SEC_VIP,  false, &HandleVIPrepairCommand,          "", NULL },
			{ "heal", 				 SEC_VIP,  false, &HandleHealCommand, 				"", NULL },
			{ "combat", 			 SEC_PLAYER,  false, &HandleCombatStopCommand, 		"", NULL },
			//{ "appear", 			 SEC_VIP,  false, &HandleVIPAppearCommand, 		"", NULL },
			//{ "summon", 			 SEC_VIP,  false, &HandleVIPSummonCommand, 		"", NULL },
			
            { NULL,             0,             false, NULL,                         	"", NULL }
        };
		
				
        static ChatCommand commandTable[] =
        {
            { "vip",	    		 SEC_VIP,   true, NULL,      "",  vipCommandTable},
	        { NULL,             0,                  false, NULL,                               "", NULL }
        };
        return commandTable;
    }

		
	static bool HandlevipCommand(ChatHandler* handler, const char* args)
    {

        Player* me = handler->GetSession()->GetPlayer();

            me->Say("vip command?", LANG_UNIVERSAL);
            return true;
    }
	
	static bool HandleCombatStopCommand(ChatHandler* handler, const char* args)
	{
		Player* player = handler->GetSession()->GetPlayer();

		if (player->GetMap()->IsBattlegroundOrArena())
		{
			handler->PSendSysMessage(LANG_YOU_IN_BATTLEGROUND);
			handler->SetSentErrorMessage(true);
			return false; 
		}
		else
		{
			if (player->GetMap()->Instanceable())
			player->CombatStop(true);
			player->CastSpell(player, 61456, false);
            ChatHandler(player->GetSession()).SendSysMessage("Your combat is cleared!");
			return true;	
		}
	}
	
	static bool HandleHealCommand(ChatHandler * handler, char const* args)
{
                Player* plr = handler->GetSession()->GetPlayer();
                 
                if (plr->isInCombat())
                {plr->GetSession()->SendNotification("You're in combat!");      
                                return true;
                }
                  
                if (plr->InBattleground())
                {plr->GetSession()->SendNotification("You're in a Battleground!");
                                return true;
                }
                 
                if (plr->InArena())
                {plr->GetSession()->SendNotification("You're in a Arena!");
                                return true;
                }
                                
                if (plr->isDead())
                {plr->GetSession()->SendNotification("You're dead and not allowed to use this command");
                                return true;
                }
                                
               
                if (plr->getClass() == CLASS_MAGE || plr->getClass() == CLASS_PRIEST || plr->getClass() == CLASS_WARLOCK)
                {
                                plr->SetPower(POWER_MANA, plr->GetMaxPower(POWER_MANA));
                                plr->SetHealth(plr->GetMaxHealth());
                                plr->GetSession()->SendNotification("Your health and mana has been restored!");
                                return true;
                }
                                plr->SetHealth(plr->GetMaxHealth());
                                plr->GetSession()->SendNotification("Your health has been restored!");
                                return true;
        
}
	
	static bool HandleVIPMorphCommand(ChatHandler* handler, const char* args)
    {
        handler->GetSession()->GetPlayer()->SetDisplayId((uint32)atol((char*)args));
        return true;
    }
	
		
	static bool HandleVIPDeMorphCommand(ChatHandler* handler, const char* /*args*/)
	{
		Player* player = handler->GetSession()->GetPlayer();

		player->DeMorph();

		return true;
	}
	
	static bool HandleVIPrepairCommand(ChatHandler* handler, char const* args)
    {
        Player* target;
        if (!handler->extractPlayerTarget((char*)args, &target))
            return false;

        // check online security
        if (handler->HasLowerSecurity(target, 0))
            return false;

        // Repair items
        target->DurabilityRepairAll(false, 0, false);

        handler->PSendSysMessage(LANG_YOU_REPAIR_ITEMS, handler->GetNameLink(target).c_str());
        if (handler->needReportToTarget(target))
            ChatHandler(target->GetSession()).PSendSysMessage(LANG_YOUR_ITEMS_REPAIRED, handler->GetNameLink().c_str());

        return true;
    }
	/* The commands */
	static bool HandleScaleCommand(ChatHandler* handler, const char* args)
	{
		if (!*args)
			return false;

		float Scale = (float)atof((char*)args);
		if (Scale > 1.5f || Scale < 0.5f)
		{
			handler->PSendSysMessage(LANG_BAD_VALUE);
			handler->SetSentErrorMessage(true);
			return false;
		}

		Player* target = handler->GetSession()->GetPlayer();
		if (target->GetMap()->IsBattlegroundOrArena())
		{
			handler->PSendSysMessage(LANG_YOU_IN_BATTLEGROUND);
			handler->SetSentErrorMessage(true);
			return false;
		}

		

		handler->PSendSysMessage(LANG_YOU_CHANGE_SIZE, Scale, handler->GetNameLink(target).c_str());
		if (handler->needReportToTarget(target))
			handler->PSendSysMessage(LANG_YOURS_SIZE_CHANGED, handler->GetNameLink().c_str(), Scale);

		target->RemoveAurasDueToSpell(16591);
		target->RemoveAurasDueToSpell(16593);
		target->RemoveAurasDueToSpell(16595);
		target->SetFloatValue(OBJECT_FIELD_SCALE_X, Scale);

		return true;
	}
	
		
	static bool HandleSoberUpCommand(ChatHandler* handler, const char* args)
        {
            
			Player* me = handler->GetSession()->GetPlayer();
				me->SetDrunkValue(1);
				handler->PSendSysMessage("It's about time you sober up.");
			return true;
		}
	
	static bool HandleGetDrunkCommand(ChatHandler* handler, const char* args)
        {
            
			Player* me = handler->GetSession()->GetPlayer();
				me->SetDrunkValue(100);
				handler->PSendSysMessage("You're now drunk!");
			return true;
        }
		
	static bool HandleTeleCommand(ChatHandler* handler, const char* args)
    {
        if (!*args)
            return false;
 
        Player* me = handler->GetSession()->GetPlayer();
 
        // id, or string, or [name] Shift-click form |color|Htele:id|h[name]|h|r
        GameTele const* tele = handler->extractGameTeleFromLink((char*)args);
 
        if (!tele)
        {
            handler->SendSysMessage(LANG_COMMAND_TELE_NOTFOUND);
            handler->SetSentErrorMessage(true);
            return false;
        }
 
        if (me->isInCombat())
        {
            handler->SendSysMessage(LANG_YOU_IN_COMBAT);
            handler->SetSentErrorMessage(true);
            return false;
        }
 
        MapEntry const* map = sMapStore.LookupEntry(tele->mapId);
        if (!map || map->IsBattlegroundOrArena())
        {
            handler->SendSysMessage(LANG_CANNOT_TELE_TO_BG);
            handler->SetSentErrorMessage(true);
            return false;
        }
 
        // stop flight if need
        if (me->isInFlight())
        {
            me->GetMotionMaster()->MovementExpired();
            me->CleanupAfterTaxiFlight();
        }
        // save only in non-flight case
        else
            me->SaveRecallPosition();
 
        me->TeleportTo(tele->mapId, tele->position_x, tele->position_y, tele->position_z, tele->orientation);
        return true;
    }
	
	static bool HandleBuffCommand(ChatHandler * handler, const char * args)
    {
        Player * pl = handler->GetSession()->GetPlayer();
		if(pl->isInCombat())
		{
			pl->GetSession()->SendNotification("You can't use this in combat!");
			return false;
		}
		if(pl->InArena())
		{
			pl->GetSession()->SendNotification("You can't use that item in an arena match!");
			return false;
		}
		else
		pl-> AddAura(48161, pl);          // Power Word: Fortitude    
		pl-> AddAura(48073, pl);          // Divine Spirit
		pl-> AddAura(43223, pl);          // Blessing of Kings
		pl-> AddAura(48469, pl);          // Mark of the wild
		pl-> AddAura(70242, pl);          // Spirit of Zandalar
		pl-> AddAura(15366, pl);          // Songflower Serenade
		pl-> AddAura(48169, pl);          // Shadow Protection Rank 5
		pl-> AddAura(83853, pl);          // Combustion
		pl-> AddAura(22888, pl);          // Rallying Cry of the Dragonslayer
		pl-> AddAura(57399, pl);          // Well Fed
		pl-> AddAura(20911, pl);          // Sanctuary
		pl-> AddAura(17013, pl);          // Agamaggan's Agility
		pl-> AddAura(16612, pl);          // Agamaggan's strength
		pl-> AddAura(43816, pl);
		pl-> AddAura(43818, pl);
		pl-> AddAura(43820, pl);
		pl-> AddAura(43822, pl);


		handler->PSendSysMessage("You have been buffed, enjoy!");
		return true;

    }

	static bool HandleChangeRaceCommand(ChatHandler* handler, const char* args)
    {

        Player* me = handler->GetSession()->GetPlayer();
		me->SetAtLoginFlag(AT_LOGIN_CHANGE_RACE);
		handler->PSendSysMessage("Relog to change race of your character.");
        return true;
    }

		static bool HandleChangeFactionCommand(ChatHandler* handler, const char* args)
    {

        Player* me = handler->GetSession()->GetPlayer();
		me->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);
		handler->PSendSysMessage("Relog to change faction of your character.");
        return true;
    }

		static bool HandleMaxSkillsCommand(ChatHandler* handler, const char* args)
    {

        Player* me = handler->GetSession()->GetPlayer();
		me->UpdateSkillsForLevel();
		handler->PSendSysMessage("Your weapon skills are now maximized.");
        return true;
    }

	static bool HandleCustomizeCommand(ChatHandler* handler, const char* args)
    {

        Player* me = handler->GetSession()->GetPlayer();
		me->SetAtLoginFlag(AT_LOGIN_CUSTOMIZE);
		handler->PSendSysMessage("Relog to customize your character.");
        return true;
    }

	static bool HandleVipMallCommand(ChatHandler* handler, const char* args)
    {

            Player* me = handler->GetSession()->GetPlayer();

        if (me->isInCombat())
        {
            handler->SendSysMessage(LANG_YOU_IN_COMBAT);
            handler->SetSentErrorMessage(true);
            return false;
        }

        // stop flight if need
        if (me->isInFlight())
        {
            me->GetMotionMaster()->MovementExpired();
            me->CleanupAfterTaxiFlight();
        }
        // stop flight if need
        if (me->isInFlight())
        {
            me->GetMotionMaster()->MovementExpired();
            me->CleanupAfterTaxiFlight();
        }
        // save only in non-flight case
        else
            me->SaveRecallPosition();

		me->TeleportTo (0, 1569.49f, -5606.73f, 114.19f, 1.13505f);
		handler->PSendSysMessage("You Have Been Teleported!");
        return true;
    }
	    
};

void AddSC_vipcommands()
{
    new vipcommands();
}