/*
Project Maintained by Ak47sigh known as Alexe & Midoking.
You can redistribute it and/or modify but not to sell.
Actions against the Copyright will support consequences!
Copyright (C) 2012-2013 AkMi Project <http://www.wow-like.info/>
*/

#include "ScriptPCH.h"

class welcome_new_login : public PlayerScript
{
public:
    welcome_new_login() : PlayerScript("welcome_new_login") { }

    void OnLogin(Player* player, bool /*loginFirst*/)
    {
        if (player->GetTotalPlayedTime() < 2) // Time in Millisecond means if played time less than 2 seconds it will welcome the player //
        {
            std::string ClassNameString = ""; // this is for the string

            switch (player->getClass()) // now defining class names in string lines
            {
            case CLASS_WARRIOR:
			ClassNameString = "Warrior";
			break;
            case CLASS_PALADIN:			
			ClassNameString = "Paladin";
			break;
            case CLASS_HUNTER:			
			ClassNameString = "Hunter";
			break;
            case CLASS_ROGUE:			
			ClassNameString = "Rogue";
			break;
            case CLASS_PRIEST:			
			ClassNameString = "Priest";
			break;
            case CLASS_DEATH_KNIGHT:	
			ClassNameString = "Death Knight";
			break;
            case CLASS_SHAMAN:			
			ClassNameString = "Shaman";
			break;
            case CLASS_MAGE:			
			ClassNameString = "Mage";
			break;
            case CLASS_WARLOCK:			
			ClassNameString = "Warlock";
			break;
            case CLASS_DRUID:			
			ClassNameString = "Druid";
			break;
			case CLASS_BERSERKER:			
			ClassNameString = "Berserker";
			break;
            }
			char msg[500];
			sprintf(msg, "Welcome %s [|Hplayer:%s|h%s|h].", ClassNameString.c_str(), player->GetName(), player->GetName());
            sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
        }
    }
};

void AddSC_welcome_new_login()
{
    new welcome_new_login;
}