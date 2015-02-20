/*
 * Copyright (C) 2015 TheSatriaCore <http://www.TheSatria.Con/>
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
				{ "talent",        SEC_PLAYER,  false, &HandleDoTalentsCommand,     			"", NULL },
				{ NULL,             0,                  false, NULL,                                "", NULL }
		
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
