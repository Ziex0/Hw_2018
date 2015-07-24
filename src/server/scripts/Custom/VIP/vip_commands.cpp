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
			{ "title",            	 SEC_VIP_2,     false, &HandleTiAddCommand,            		    "", NULL },
			{ "summon",            	 SEC_VIP_2,     false, &HandleVipSummonCommand,            		"", NULL },
			{ "appear",            	 SEC_VIP_2,     false, &HandleVipAppearCommand,            		"", NULL },
			{ "whisper",     		 SEC_VIP_2,     false, &HandleVipWhisperCommand,            	"", NULL },
			{ "anno",     		 	 SEC_VIP,  false,  &HandleVIPannounceCommand,           "", NULL },
						
            { NULL,             0,             false, NULL,                         	"", NULL }
        };
		
        static ChatCommand commandTable[] =
        {
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
	
	// Teleport to Player
    static bool HandleVipAppearCommand(ChatHandler* handler, char const* args)
    {
        Player* target;
        uint64 targetGuid;
        std::string targetName;
        if (!handler->extractPlayerTarget((char*)args, &target, &targetGuid, &targetName))
            return false;

        Player* _player = handler->GetSession()->GetPlayer();
        if (target == _player || targetGuid == _player->GetGUID())
        {
            handler->SendSysMessage(LANG_CANT_TELEPORT_SELF);
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (target)
        {
            // check online security
            if (handler->HasLowerSecurity(target, 0))
                return false;

            std::string chrNameLink = handler->playerLink(targetName);

            Map* map = target->GetMap();
            if (map->IsBattlegroundOrArena())
            {
                // only allow if gm mode is on
                if (!_player->isGameMaster())
                {
                    handler->PSendSysMessage(LANG_CANNOT_GO_TO_BG_GM, chrNameLink.c_str());
                    handler->SetSentErrorMessage(true);
                    return false;
                }
                // if both players are in different bgs
                else if (_player->GetBattlegroundId() && _player->GetBattlegroundId() != target->GetBattlegroundId())
                    _player->LeaveBattleground(false); // Note: should be changed so _player gets no Deserter debuff

                // all's well, set bg id
                // when porting out from the bg, it will be reset to 0
                _player->SetBattlegroundId(target->GetBattlegroundId(), target->GetBattlegroundTypeId());
                // remember current position as entry point for return at bg end teleportation
                if (!_player->GetMap()->IsBattlegroundOrArena())
                    _player->SetBattlegroundEntryPoint();
            }
            else if (map->IsDungeon())
            {
                // we have to go to instance, and can go to player only if:
                //   1) we are in his group (either as leader or as member)
                //   2) we are not bound to any group and have GM mode on
                if (_player->GetGroup())
                {
                    // we are in group, we can go only if we are in the player group
                    if (_player->GetGroup() != target->GetGroup())
                    {
                        handler->PSendSysMessage(LANG_CANNOT_GO_TO_INST_PARTY, chrNameLink.c_str());
                        handler->SetSentErrorMessage(true);
                        return false;
                    }
                }
                else
                {
                    // we are not in group, let's verify our GM mode
                    if (!_player->isGameMaster())
                    {
                        handler->PSendSysMessage(LANG_CANNOT_GO_TO_INST_GM, chrNameLink.c_str());
                        handler->SetSentErrorMessage(true);
                        return false;
                    }
                }

                // if the player or the player's group is bound to another instance
                // the player will not be bound to another one
                /*InstancePlayerBind* bind = _player->GetBoundInstance(target->GetMapId(), target->GetDifficulty(map->IsRaid()));
                if (!bind)
                {
                    Group* group = _player->GetGroup();
                    // if no bind exists, create a solo bind
                    InstanceGroupBind* gBind = group ? group->GetBoundInstance(target) : NULL;                // if no bind exists, create a solo bind
                    if (!gBind)
                        if (InstanceSave* save = sInstanceSaveMgr->GetInstanceSave(target->GetInstanceId()))
                            _player->BindToInstance(save, !save->CanReset());
                }*/

                if (map->IsRaid())
                    _player->SetRaidDifficulty(target->GetRaidDifficulty());
                else
                    _player->SetDungeonDifficulty(target->GetDungeonDifficulty());
            }

            handler->PSendSysMessage(LANG_APPEARING_AT, chrNameLink.c_str());

            // stop flight if need
            if (_player->isInFlight())
            {
                _player->GetMotionMaster()->MovementExpired();
                _player->CleanupAfterTaxiFlight();
            }
            // save only in non-flight case
            else
                _player->SaveRecallPosition();

            // to point to see at target with same orientation
            float x, y, z;
            target->GetContactPoint(_player, x, y, z);

            _player->TeleportTo(target->GetMapId(), x, y, z, _player->GetAngle(target), TELE_TO_GM_MODE);
            _player->SetPhaseMask(target->GetPhaseMask(), true);
        }
        else
        {
            // check offline security
            if (handler->HasLowerSecurity(NULL, targetGuid))
                return false;

            std::string nameLink = handler->playerLink(targetName);

            handler->PSendSysMessage(LANG_APPEARING_AT, nameLink.c_str());

            // to point where player stay (if loaded)
            float x, y, z, o;
            uint32 map;
            bool in_flight;
            if (!Player::LoadPositionFromDB(map, x, y, z, o, in_flight, targetGuid))
                return false;

            // stop flight if need
            if (_player->isInFlight())
            {
                _player->GetMotionMaster()->MovementExpired();
                _player->CleanupAfterTaxiFlight();
            }
            // save only in non-flight case
            else
                _player->SaveRecallPosition();

            _player->TeleportTo(map, x, y, z, _player->GetOrientation());
        }

        return true;
    }
    // Summon Player
    static bool HandleVipSummonCommand(ChatHandler* handler, char const* args)
    {
        Player* target;
        uint64 targetGuid;
        std::string targetName;
        if (!handler->extractPlayerTarget((char*)args, &target, &targetGuid, &targetName))
            return false;

        Player* _player = handler->GetSession()->GetPlayer();
        if (target == _player || targetGuid == _player->GetGUID())
        {
            handler->PSendSysMessage(LANG_CANT_TELEPORT_SELF);
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (target)
        {
            std::string nameLink = handler->playerLink(targetName);
            // check online security
            if (handler->HasLowerSecurity(target, 0))
                return false;

            if (target->IsBeingTeleported())
            {
                handler->PSendSysMessage(LANG_IS_TELEPORTED, nameLink.c_str());
                handler->SetSentErrorMessage(true);
                return false;
            }

            Map* map = handler->GetSession()->GetPlayer()->GetMap();

            if (map->IsBattlegroundOrArena())
            {
                // only allow if gm mode is on
                if (!_player->isGameMaster())
                {
                    handler->PSendSysMessage(LANG_CANNOT_GO_TO_BG_GM, nameLink.c_str());
                    handler->SetSentErrorMessage(true);
                    return false;
                }
                // if both players are in different bgs
                else if (target->GetBattlegroundId() && handler->GetSession()->GetPlayer()->GetBattlegroundId() != target->GetBattlegroundId())
                    target->LeaveBattleground(false); // Note: should be changed so target gets no Deserter debuff

                // all's well, set bg id
                // when porting out from the bg, it will be reset to 0
                target->SetBattlegroundId(handler->GetSession()->GetPlayer()->GetBattlegroundId(), handler->GetSession()->GetPlayer()->GetBattlegroundTypeId());
                // remember current position as entry point for return at bg end teleportation
                if (!target->GetMap()->IsBattlegroundOrArena())
                    target->SetBattlegroundEntryPoint();
            }
            else if (map->IsDungeon())
            {
                Map* destMap = target->GetMap();

                if (destMap->Instanceable() && destMap->GetInstanceId() != map->GetInstanceId())
                    target->UnbindInstance(map->GetInstanceId(), target->GetDungeonDifficulty(), true);

                // we are in an instance, and can only summon players in our group with us as leader
                /*if (!handler->GetSession()->GetPlayer()->GetGroup() || !target->GetGroup() ||
                    (target->GetGroup()->GetLeaderGUID() != handler->GetSession()->GetPlayer()->GetGUID()) ||
                    (handler->GetSession()->GetPlayer()->GetGroup()->GetLeaderGUID() != handler->GetSession()->GetPlayer()->GetGUID()))
                    // the last check is a bit excessive, but let it be, just in case*/
                {
                    handler->PSendSysMessage(LANG_CANNOT_SUMMON_TO_INST, nameLink.c_str());
                    handler->SetSentErrorMessage(true);
                    return false;
                }
            }

            handler->PSendSysMessage(LANG_SUMMONING, nameLink.c_str(), "");
            if (handler->needReportToTarget(target))
                ChatHandler(target->GetSession()).PSendSysMessage(LANG_SUMMONED_BY, handler->playerLink(_player->GetName()).c_str());

            // stop flight if need
            if (target->isInFlight())
            {
                target->GetMotionMaster()->MovementExpired();
                target->CleanupAfterTaxiFlight();
            }
            // save only in non-flight case
            else
                target->SaveRecallPosition();

            // before GM
            float x, y, z;
            handler->GetSession()->GetPlayer()->GetClosePoint(x, y, z, target->GetObjectSize());
            target->TeleportTo(handler->GetSession()->GetPlayer()->GetMapId(), x, y, z, target->GetOrientation());
            target->SetPhaseMask(handler->GetSession()->GetPlayer()->GetPhaseMask(), true);
        }
        else
        {
            // check offline security
            if (handler->HasLowerSecurity(NULL, targetGuid))
                return false;

            std::string nameLink = handler->playerLink(targetName);

            handler->PSendSysMessage(LANG_SUMMONING, nameLink.c_str(), handler->GetTrinityString(LANG_OFFLINE));

            // in point where GM stay
            Player::SavePositionInDB(handler->GetSession()->GetPlayer()->GetMapId(),
                handler->GetSession()->GetPlayer()->GetPositionX(),
                handler->GetSession()->GetPlayer()->GetPositionY(),
                handler->GetSession()->GetPlayer()->GetPositionZ(),
                handler->GetSession()->GetPlayer()->GetOrientation(),
                handler->GetSession()->GetPlayer()->GetZoneId(),
                targetGuid);
        }

        return true;
    }
	
	// Enable\Dissable accept whispers (for GM)
    static bool HandleVipWhisperCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
        {
            handler->PSendSysMessage(LANG_COMMAND_WHISPERACCEPTING, handler->GetSession()->GetPlayer()->isAcceptWhispers() ?  handler->GetTrinityString(LANG_ON) : handler->GetTrinityString(LANG_OFF));
            return true;
        }

        std::string argStr = strtok((char*)args, " ");
        // whisper on
        if (argStr == "on")
        {
            handler->GetSession()->GetPlayer()->SetAcceptWhispers(true);
            handler->SendSysMessage(LANG_COMMAND_WHISPERON);
            return true;
        }

        // whisper off
        if (argStr == "off")
        {
            // Remove all players from the Gamemaster's whisper whitelist
            handler->GetSession()->GetPlayer()->ClearWhisperWhiteList();
            handler->GetSession()->GetPlayer()->SetAcceptWhispers(false);
            handler->SendSysMessage(LANG_COMMAND_WHISPEROFF);
            return true;
        }

        if (argStr == "remove")
        {
            std::string name = strtok(NULL, " ");
            if (normalizePlayerName(name))
            {
                if (Player* player = sObjectAccessor->FindPlayerByName(name))
                {
                    handler->GetSession()->GetPlayer()->RemoveFromWhisperWhiteList(player->GetGUID());
                    handler->PSendSysMessage(LANG_COMMAND_WHISPEROFFPLAYER, name.c_str());
                    return true;
                }
                else
                {
                    handler->PSendSysMessage(LANG_PLAYER_NOT_FOUND, name.c_str());
                    handler->SetSentErrorMessage(true);
                    return false;
                }
            }
        }
        handler->SendSysMessage(LANG_USE_BOL);
        handler->SetSentErrorMessage(true);
        return false;
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
			Player *pPlr = handler->GetSession()->GetPlayer();
			ItemPosCountVec dest;
			Item* pItem;
				
				//send 1 item
				pPlr->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, 30, 1, 0);
				pItem = pPlr->StoreNewItem(dest, 30,true,Item::GenerateItemRandomPropertyId(30));
				pPlr->SendNewItem(pItem, 1, true, false);
				dest.clear(); //anytime you add another item. you have to add this to the end! dont forget!
				break;
				return true;
		}

	static bool HandleChangeFactionCommand(ChatHandler* handler, const char* args)
		{
			Player *pPlr = handler->GetSession()->GetPlayer();
			ItemPosCountVec dest;
			Item* pItem;
				
				//send 1 item
				pPlr->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, 29, 1, 0);
				pItem = pPlr->StoreNewItem(dest, 29,true,Item::GenerateItemRandomPropertyId(29));
				pPlr->SendNewItem(pItem, 1, true, false);
				dest.clear(); //anytime you add another item. you have to add this to the end! dont forget!
				break;
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