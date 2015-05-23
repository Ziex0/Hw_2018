
#include "ScriptPCH.h"

class npc_exchanger : public CreatureScript
{
public:
    npc_exchanger() : CreatureScript("npc_exchanger") { }

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
            player->ADD_GOSSIP_ITEM( 4, "|TInterface/ICONS/Achievement_Leader_King_Varian_Wrynn:24|t|rConvert 600 Demon Head to 10 Star Coin"         , GOSSIP_SENDER_MAIN, 3); //Change the ID below
            player->ADD_GOSSIP_ITEM( 8, "|TInterface/ICONS/Achievement_Leader_King_Varian_Wrynn:24|t|rConvert 1000 Demon Soul to 100 Golden Pearl"    , GOSSIP_SENDER_MAIN, 4); //Change the ID below
            player->ADD_GOSSIP_ITEM( 7, "|TInterface/ICONS/Achievement_Leader_King_Varian_Wrynn:24|t|rConvert 1000 Golden Pearl to 100 Black Diamond" , GOSSIP_SENDER_MAIN, 5); //Change the stats below
            player->ADD_GOSSIP_ITEM( 5, "|TInterface/ICONS/Achievement_Leader_King_Varian_Wrynn:24|t|rConvert 1000 Black Diamond to 100 Magic Card"   , GOSSIP_SENDER_MAIN, 6); //Change the stats below
            player->ADD_GOSSIP_ITEM( 6, "|TInterface/ICONS/Achievement_Leader_King_Varian_Wrynn:24|t|rConvert 1000 Magic Card to 1 Donation Points"   , GOSSIP_SENDER_MAIN, 7);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Return.", GOSSIP_SENDER_MAIN, 9999);
			pPlayer->PlayerTalkClass->SendGossipMenu(907, pCreature->GetGUID());
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
            case 3: 
                if (player->HasItemCount( 320286, 600, false ))  //Demon Head
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->DestroyItemCount(320286, 600, true, false);
                    player->AddItem(340006, 10);
                    _creature->MonsterWhisper("Your DH was successfully converted to SC", player->GetGUID());
                }
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    _creature->MonsterWhisper("You don't have any DH Tokens", player->GetGUID());
                    return false;
                }
                break;

            case 4: 
                if (player->HasItemCount( 320287, 1000, false ))  //golden pearl
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->DestroyItemCount(320287, 1000, true, false);
                    player->AddItem(320288, 50);
                    _creature->MonsterWhisper("Your DS was successfully converted to GP!", player->GetGUID());
                }
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    _creature->MonsterWhisper("You don't have any Golden Pearl!!", player->GetGUID());
                    return false;
                }
                break;
            case 5: //token-token
                if (player->HasItemCount( 320288, 1000, false )) //black diamond
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->DestroyItemCount(320288, 1000, true, false);
                    player->AddItem(320289, 50);
                    _creature->MonsterWhisper("You exchanged succesfully!", player->GetGUID());
                }
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    _creature->MonsterWhisper("You don't have any Black Diamond !!.", player->GetGUID());
                    return false;
                }
                break;
			case 6: //token-token
                if (player->HasItemCount( 320288, 1000, false ))
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->DestroyItemCount(320288, 1000, true, false);
                    player->AddItem(320289, 50);
                    _creature->MonsterWhisper("You exchanged succesfully!", player->GetGUID());
                }
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    _creature->MonsterWhisper("You don't have any Black Diamond !!.", player->GetGUID());
                    return false;
                }
                break;
				
			case 9999:
                pPlayer->PlayerTalkClass->ClearMenus();
                OnGossipHello(pPlayer, pCreature);
                break;
            } 
        } 
        return true;
    } 
};

void AddSC_npc_exchanger()
{
    new npc_exchanger();
}