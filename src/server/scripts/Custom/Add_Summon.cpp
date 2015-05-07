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
 

#include "ScriptPCH.h"
#include "Language.h"

class summon_all_npc : public CreatureScript
{
public:
    summon_all_npc() : CreatureScript("summon_all_npc") { }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|cff00ff00|TInterface\\icons\\Ability_FiegnDead:24|t|r Summon Main Teleporter", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF +1);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|cff00ff00|TInterface\\icons\\Ability_FiegnDead:24|t|r Summon Emerald Mall Teleporter", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF +80);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|cff00ff00|TInterface\\icons\\Ability_FiegnDead:24|t|r Summon Trainer", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF +2);
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|cff00ff00|TInterface\\icons\\Ability_FiegnDead:24|t|r Summon Transmorg NPC", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF +3);
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|cff00ff00|TInterface\\icons\\Ability_FiegnDead:24|t|r Summon Permanent Morph", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF +4);
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|cff00ff00|TInterface\\icons\\Ability_FiegnDead:24|t|r Summon Npc Enchancher", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF +5);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|cff00ff00|TInterface\\icons\\Ability_FiegnDead:24|t|r Summon NPC Quest", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF +6);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|cff00ff00|TInterface\\icons\\Ability_FiegnDead:24|t|r Summon Armor Reward Vendor", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF +70);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|cff00ff00|TInterface\\icons\\Ability_FiegnDead:24|t|r Summon Weapon Reward Vendor", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF +71);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|cff00ff00|TInterface\\icons\\Ability_FiegnDead:24|t|r Summon Misc Reward Vendor", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF +72);
		//pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|cff00ff00|TInterface\\icons\\Ability_FiegnDead:24|t|r Summon Offset Reward Vendor", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF +73);
		//pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|cff00ff00|TInterface\\icons\\Ability_FiegnDead:24|t|r Summon NPC Glyph", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
		//pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|cff00ff00|TInterface\\icons\\Ability_FiegnDead:24|t|r Summon NPC Gems Vendor", GOSSIP_SENDER_MAIN, 9);
        //pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|cff00ff00|TInterface\\icons\\Ability_FiegnDead:24|t|r Summon Fusion Npc (soon)", GOSSIP_SENDER_MAIN, 9);
		//pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|cff00ff00|TInterface\\icons\\Ability_FiegnDead:24|t|r Summon Fusion Failed Excahnger (soon)", GOSSIP_SENDER_MAIN, 6);
        pPlayer->SEND_GOSSIP_MENU(90701, pCreature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
    {
        pPlayer->PlayerTalkClass->ClearMenus();

		switch (uiAction)
        {
            case GOSSIP_ACTION_INFO_DEF +1:
					pPlayer->SummonCreature(40703,pPlayer->GetPositionX()+2 ,pPlayer->GetPositionY(), pPlayer->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,40000);
					pPlayer->CLOSE_GOSSIP_MENU();
					break;
			   
            case GOSSIP_ACTION_INFO_DEF +2:
					pPlayer->SummonCreature(90001,pPlayer->GetPositionX() ,pPlayer->GetPositionY()+2, pPlayer->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,30000);
					pPlayer->CLOSE_GOSSIP_MENU();
					break;
			   
            case GOSSIP_ACTION_INFO_DEF +3:
					pPlayer->SummonCreature(96000,pPlayer->GetPositionX() ,pPlayer->GetPositionY(), pPlayer->GetPositionZ()+2, 0,TEMPSUMMON_TIMED_DESPAWN,30000);
					pPlayer->CLOSE_GOSSIP_MENU();
					break;
			   
            case GOSSIP_ACTION_INFO_DEF +4:
					pPlayer->SummonCreature(190106,pPlayer->GetPositionX()+2 ,pPlayer->GetPositionY(), pPlayer->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,30000);
					pPlayer->CLOSE_GOSSIP_MENU();
					break;
			   
            case GOSSIP_ACTION_INFO_DEF +5:
					pPlayer->SummonCreature(190012,pPlayer->GetPositionX() ,pPlayer->GetPositionY()+2, pPlayer->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,30000);
					pPlayer->CLOSE_GOSSIP_MENU();
					break;
					
			case GOSSIP_ACTION_INFO_DEF +6:              
					pPlayer->SummonCreature(190107,pPlayer->GetPositionX() ,pPlayer->GetPositionY()+2, pPlayer->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,30000);
					pPlayer->CLOSE_GOSSIP_MENU();
					break;
					
			case GOSSIP_ACTION_INFO_DEF +70:
					pPlayer->SummonCreature(190108,pPlayer->GetPositionX() ,pPlayer->GetPositionY()+2, pPlayer->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,40000);
					pPlayer->CLOSE_GOSSIP_MENU();
					break;
					
			case GOSSIP_ACTION_INFO_DEF +71:
					pPlayer->SummonCreature(190109,pPlayer->GetPositionX() ,pPlayer->GetPositionY()+2, pPlayer->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,40000);
					pPlayer->CLOSE_GOSSIP_MENU();
					break;
					
			case GOSSIP_ACTION_INFO_DEF +72:
					pPlayer->SummonCreature(190110,pPlayer->GetPositionX() ,pPlayer->GetPositionY()+2, pPlayer->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,40000);
					pPlayer->CLOSE_GOSSIP_MENU();
					break;
					
			case GOSSIP_ACTION_INFO_DEF +73:
					pPlayer->SummonCreature(190111,pPlayer->GetPositionX() ,pPlayer->GetPositionY()+2, pPlayer->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,40000);
					pPlayer->CLOSE_GOSSIP_MENU();
					break;
			   
			case GOSSIP_ACTION_INFO_DEF +8:               
					pPlayer->SummonCreature(190112,pPlayer->GetPositionX() ,pPlayer->GetPositionY()+2, pPlayer->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,40000);
					pPlayer->CLOSE_GOSSIP_MENU();
					break;
					
			case GOSSIP_ACTION_INFO_DEF +9:               
					pPlayer->SummonCreature(190113,pPlayer->GetPositionX() ,pPlayer->GetPositionY()+4, pPlayer->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,40000);
					pPlayer->CLOSE_GOSSIP_MENU();
					break;
			case GOSSIP_ACTION_INFO_DEF +80:
					pPlayer->SummonCreature(210200,pPlayer->GetPositionX()+2 ,pPlayer->GetPositionY(), pPlayer->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,40000);
					pPlayer->CLOSE_GOSSIP_MENU();
					break;
        }

        return true;
    }
};

void AddSC_summon_all_npc()
{
    new summon_all_npc();
}