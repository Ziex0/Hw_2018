/*
<--------------------------------------------------------------------------->
 - Developer(s): Zie
 - Complete: 100%
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
			{ "combatstop", 		 SEC_VIP,  false, &HandleCombatStopCommand, 		"", NULL },
			{ "tadd",            	 SEC_VIP_2,     false, &HandleTiAddCommand,            		"", NULL },
			{ "anno",     		 	 SEC_VIP,     false,  &HandleVIPannounceCommand,           "", NULL },
						
            { NULL,             0,             false, NULL,                         	"", NULL }
        };
		
		static ChatCommand toggleCommandTable[] =
        {
            { "summon",         SEC_PLAYER,      false, &HandleToggleSummonCommand,         "", NULL },
            { "appear",         SEC_PLAYER,      false, &HandleToggleAppearCommand,         "", NULL },
            { "status",         SEC_MODERATOR,      false, &HandleToggleStatusCommand,         "", NULL },
            { NULL,             0,               false, NULL,                               "", NULL }
        };
		
        static ChatCommand commandTable[] =
        {
			{ "toggle",						SEC_PLAYER,			false, NULL, "", toggleCommandTable },
            { "vip",	    				SEC_VIP,			true, NULL,      "",  vipCommandTable},
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
	
	static bool HandleToggleAppearCommand(ChatHandler* handler, const char* args)
    {
	    if (!handler->GetSession() && !handler->GetSession()->GetPlayer())
		    return false;

	    std::string argstr = (char*)args;

	    if (!*args)
	    {
		    if (handler->GetSession()->GetPlayer()->GetCommandStatus(TOGGLE_APPEAR))
			    argstr = "off";	
		    else
			    argstr = "on";
	    }

	    if (argstr == "on")
	    {
		    handler->GetSession()->GetPlayer()->m_toggleAppear = true;
			handler->PSendSysMessage("|cff00FFFFYou have |cffFF0000enabled |cff00FFFFappearing.You can be appeared.");
		    return true;
	    }
	    else if (argstr == "off")
	    {
		    handler->GetSession()->GetPlayer()->m_toggleAppear = false;
			handler->PSendSysMessage("|cff00FFFFYou have |cffFF0000disabled |cff00FFFFappearing.You can't be appeared.");
		    return true;
	    }

        return false;
    }

    static bool HandleToggleSummonCommand(ChatHandler* handler, const char* args)
    {
	    if (!handler->GetSession() && !handler->GetSession()->GetPlayer())
		    return false;

	    std::string argstr = (char*)args;

	    if (!*args)
	    {
		    if (handler->GetSession()->GetPlayer()->GetCommandStatus(TOGGLE_SUMMON))
			    argstr = "off";	
		    else
			    argstr = "on";
	    }

	    if (argstr == "on")
	    {
		    handler->GetSession()->GetPlayer()->m_toggleSummon = true;
		    handler->PSendSysMessage("|cff00FFFFYou have |cffFF0000enabled |cff00FFFFsummoning. You can be summoned.");
		    return true;
	    }
	    else if (argstr == "off")
	    {
		    handler->GetSession()->GetPlayer()->m_toggleSummon = false;
		    handler->PSendSysMessage("|cff00FFFFYou have |cffFF0000disabled |cff00FFFFsummoning. You can't be summoned.");
		    return true;
	    }

        return false;
    }

    static bool HandleToggleStatusCommand(ChatHandler* handler, char const* /*args*/)
    {
	    if (!handler->GetSession() && !handler->GetSession()->GetPlayer())
		    return false;

	    Player* player = handler->GetSession()->GetPlayer();

	    if(player->GetCommandStatus(TOGGLE_APPEAR))
	       handler->PSendSysMessage("|cffFF0000Status: |cff00FFFFCurrently you can be appeared.");
	    if(player->GetCommandStatus(TOGGLE_SUMMON))
	       handler->PSendSysMessage("|cffFF0000Status: |cff00FFFFCurrently you can be summoned.");

	    if(!player->GetCommandStatus(TOGGLE_APPEAR))
	       handler->PSendSysMessage("|cffFF0000Status: |cff00FFFFCurrently you can't be appeared.");
	    if(!player->GetCommandStatus(TOGGLE_SUMMON))
	       handler->PSendSysMessage("|cffFF0000Status: |cff00FFFFCurrently you can't be summoned.");

        return true;
    }
	
	static bool HandleTiAddCommand(ChatHandler* handler, char const* args)
    {
        // number or [name] Shift-click form |color|Htitle:title_id|h[name]|h|r
        char* id_p = handler->extractKeyFromLink((char*)args, "Htitle");
        if (!id_p)
            return false;

        int32 id = atoi(id_p);
        if (id <= 0)
        {
            handler->PSendSysMessage(LANG_INVALID_TITLE_ID, id);
            handler->SetSentErrorMessage(true);
            return false;
        }

        Player* target = handler->getSelectedPlayer();
        if (!target)
        {
            handler->SendSysMessage(LANG_NO_CHAR_SELECTED);
            handler->SetSentErrorMessage(true);
            return false;
        }

        // check online security
        if (handler->HasLowerSecurity(target, 0))
            return false;

        CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(id);
        if (!titleInfo)
        {
            handler->PSendSysMessage(LANG_INVALID_TITLE_ID, id);
            handler->SetSentErrorMessage(true);
            return false;
        }

        std::string tNameLink = handler->GetNameLink(target);

        char titleNameStr[80];
        snprintf(titleNameStr, 80, titleInfo->name[handler->GetSessionDbcLocale()], target->GetName().c_str());

        target->SetTitle(titleInfo);
        handler->PSendSysMessage(LANG_TITLE_ADD_RES, id, titleNameStr, tNameLink.c_str());

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
			//if (player->GetMap()->Instanceable())
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
	
	static bool HandleVIPannounceCommand(ChatHandler* handler, const char* args)
    {			
        if (!*args)
            return false;

        std::string name("Console");
        if (WorldSession* session = handler->GetSession())
            name = session->GetPlayer()->GetName();

        sWorld->SendWorldText(LANG_VIP_NAME_ANNOUNCE, name.c_str(), args);
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

		me->TeleportTo (530, -266.10f, 921.734f, 84.3799f, 0.582604f);
		handler->PSendSysMessage("You Have Been Teleported!");
        return true;
    }
	    
};

void AddSC_vipcommands()
{
    new vipcommands();
}