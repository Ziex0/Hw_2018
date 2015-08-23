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
 
/////////////////////////////////////////////////////////////////////////////
//         			Developed by Zie For Thesatria.Com                     //
//                     Copyright (C) 2015 Zie                              //
//                          Thesatria.Com                                  //
/////////////////////////////////////////////////////////////////////////////

#include "ScriptPCH.h"


class npc_Fusion : public CreatureScript
{
	public:
		npc_Fusion() : CreatureScript("npc_Fusion"){}
		
	uint32 SelectDPoints(Player* pPlayer)
	{
		QueryResult select = LoginDatabase.PQuery("SELECT dp FROM web_db.account_data WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
		if (!select) // Just in case, but should not happen
		{
			pPlayer->CLOSE_GOSSIP_MENU();
			return 0;
		}

		Field* fields = select->Fetch();
		uint32 dp = fields[0].GetUInt32();

		return dp;
	}
	
	bool OnGossipHello(Player *player, Creature *_creature)
    {
        if (player->isInCombat())
        {
            player->CLOSE_GOSSIP_MENU();
            _creature->MonsterWhisper("You are in combat!", player->GetGUID());
            return true;
        }
        else
        {		
			player->ADD_GOSSIP_ITEM( 4,  "|TInterface/ICONS/Achievement_Leader_King_Varian_Wrynn:24|t|r I want Upgrade my Vote Armor ", GOSSIP_SENDER_MAIN, 1);
			//Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT,  "|TInterface/ICONS/Achievement_Leader_King_Varian_Wrynn:24|t|r I want Upgrade my Vote Armor ", GOSSIP_SENDER_MAIN, 1);
			//Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT,  "|TInterface/ICONS/Achievement_Leader_King_Varian_Wrynn:24|t|r I want Upgrade my Vote Armor ", GOSSIP_SENDER_MAIN, 1);			
			//Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT,  "|TInterface/ICONS/Achievement_Leader_King_Varian_Wrynn:24|t|r I want Upgrade my Vote Armor ", GOSSIP_SENDER_MAIN, 1);
			player->SEND_GOSSIP_MENU(85006, _creature->GetGUID());
			 }

        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _creature->GetGUID());         
        return true;
    }
		
		bool OnGossipSelect(Player *player, Creature *_creature, uint32 sender, uint32 uiAction)
    {
        if (sender == GOSSIP_SENDER_MAIN)
        {
            player->PlayerTalkClass->ClearMenus();
            switch(uiAction)
            {
				case 1:
					if(player->HasItemCount(urand(173289,173408), 1, true))
					{
						/*player->CLOSE_GOSSIP_MENU();
						ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(VOTE_ARMOR);
						player->DestroyItemCount(urand(173289,173408), 1, true);					
						ChatHandler(player->GetSession()).PSendSysMessage("Your item %s % %s will be taken", itemTemplate->Name1.c_str());
						player->AddItem(27, 1);
						const uint32 arrayNum[1]={300210};
						uint32 RandIndex = rand()%2; //
						_creature->MonsterWhisper("Success. you got upgrade Token, please Check your bag !!", player->GetGUID());*/
							player->CLOSE_GOSSIP_MENU();
							player->DestroyItemCount(urand(173289,173408), 1, true);
							player->AddItem(27, 1);	
							_creature->MonsterWhisper("Success. you got upgrade Token, please Check your bag !!", player->GetGUID());
					}
                else
                {
                    player->CLOSE_GOSSIP_MENU();
					_creature->MonsterWhisper("Failed. Make sure you have vote in item in your bag", player->GetGUID());
					return false;
                }
                break;
				
			}
		}
			return true;
	}
	

};

void AddSC_npc_Fusion()
{
    new npc_Fusion();
}
