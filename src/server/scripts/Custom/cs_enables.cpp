#include "ScriptMgr.h"
#include "Chat.h"

class enables_commandscript : public CommandScript
{
public:
    enables_commandscript() : CommandScript("enables_commandscript") { }

    ChatCommand* GetCommands() const
    {
        static ChatCommand toggleCommandTable[] =
        {
            { "summon",         SEC_PLAYER,      false, &HandleToggleSummonCommand,         "", NULL },
            { "appear",         SEC_PLAYER,      false, &HandleToggleAppearCommand,         "", NULL },
            { "status",         SEC_PLAYER,      false, &HandleToggleStatusCommand,         "", NULL },
            { NULL,             0,               false, NULL,                               "", NULL }
        };

        static ChatCommand commandTable[] =
        {
            { "toggle",         SEC_PLAYER,     false, NULL,                  "", toggleCommandTable },
            { NULL,             0,              false, NULL,                               "", NULL }
        };
        return commandTable;
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
			handler->PSendSysMessage("| cff00FFFFYou have | cffFF0000enabled | cff00FFFFappearing.You can be appeared.");
		    return true;
	    }
	    else if (argstr == "off")
	    {
		    handler->GetSession()->GetPlayer()->m_toggleAppear = false;
			handler->PSendSysMessage("| cff00FFFFYou have | cffFF0000disabled | cff00FFFFappearing.You can't be appeared.");
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
};

void AddSC_enables_commandscript()
{
    new enables_commandscript();
}
