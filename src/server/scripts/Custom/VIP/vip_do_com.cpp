/*
 * Copyright (C) 2015 TheSatriaCore <http://www.TheSatria.Com>
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
 
#include "ScriptMgr.h"
#include "ObjectMgr.h"
#include "MapManager.h"
#include "Common.h"
#include "Language.h"

class Docommands : public CommandScript
{
public:
    Docommands() : CommandScript("Docommands") { }

    ChatCommand* GetCommands() const
    {
        static ChatCommand DoCommandTable[] =

        {
				{ "talent",         SEC_PLAYER,  false, &HandleDoTalentsCommand,     			"", NULL },
				{ "Lk",        		SEC_PLAYER,  false, &HandleDoTeleCommand,     				"", NULL },
				{ "song",        	SEC_VIP,  	 false, &HandleDoSongCommand,     				"", NULL },
				{ NULL,             0,                  false, NULL,                            "", NULL }
		
		};
		
		static ChatCommand commandTable[] =
        {
				{ "do",	    	SEC_PLAYER,   			true, NULL,      "",  DoCommandTable},
				{ NULL,             0,                  false, NULL,                               "", NULL }
        };
        return commandTable;
	}	
		
	static bool HandleDoCommand(ChatHandler* handler, const char* args)
    {

        Player* me = handler->GetSession()->GetPlayer();

            me->Say("Do command?", LANG_UNIVERSAL);
            return true;
    }
	
	static bool HandleDoSongCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        uint32 soundId = atoi((char*)args);

        if (!sSoundEntriesStore.LookupEntry(soundId))
        {
            handler->PSendSysMessage(LANG_SOUND_NOT_EXIST, soundId);
            handler->SetSentErrorMessage(true);
            return false;
        }

        WorldPacket data(SMSG_PLAY_SOUND, 4);
        data << uint32(soundId) << handler->GetSession()->GetPlayer()->GetGUID();
        sWorld->SendGlobalMessage(&data);

        handler->PSendSysMessage(LANG_COMMAND_PLAYED_TO_ALL, soundId);
        return true;
    }
	
	static bool HandleDoTeleCommand(ChatHandler * handler, const char * args)
    { 

		Player* me = handler->GetSession()->GetPlayer();
	
		if (me->isInCombat())
        {
            handler->SendSysMessage(LANG_YOU_IN_COMBAT);
            handler->SetSentErrorMessage(true);
            return false;
        }
		
		else
            me->SaveRecallPosition();
			me-> TeleportTo(631, 505.212006f, -2124.3500f, 840.9400f, 0.0000f);
			//handler->PSendSysMessage("You Have Been Teleported to Lich King Place!");
            return true;
    }
	
	static bool HandleDoTalentsCommand(ChatHandler* handler, char const* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();
        uint32 classMask = player->getClassMask();

        for (uint32 i = 0; i < sTalentStore.GetNumRows(); ++i)
        {
            TalentEntry const* talentInfo = sTalentStore.LookupEntry(i);
            if (!talentInfo)
                continue;

            TalentTabEntry const* talentTabInfo = sTalentTabStore.LookupEntry(talentInfo->TalentTab);
            if (!talentTabInfo)
                continue;

            if ((classMask & talentTabInfo->ClassMask) == 0)
                continue;

            // search highest talent rank
            uint32 spellId = 0;
            for (int8 rank = MAX_TALENT_RANK - 1; rank >= 0; --rank)
            {
                if (talentInfo->RankID[rank] != 0)
                {
                    spellId = talentInfo->RankID[rank];
                    break;
                }
            }

            if (!spellId)                                        // ??? none spells in talent
                continue;

            SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spellId);
            if (!spellInfo || !SpellMgr::IsSpellValid(spellInfo, handler->GetSession()->GetPlayer(), false))
                continue;

            // learn highest rank of talent and learn all non-talent spell ranks (recursive by tree)
            player->learnSpellHighRank(spellId);
            player->AddTalent(spellId, player->GetActiveSpec(), true);
        }

        player->SetFreeTalentPoints(0);

        handler->SendSysMessage(LANG_COMMAND_LEARN_CLASS_TALENTS);
        return true;
		
	}
		
};

void AddSC_Docommands()
{
    new Docommands();
}
