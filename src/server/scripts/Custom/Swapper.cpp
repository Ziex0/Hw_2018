/*  
	-Souls -
	soul =	   60000
	10.000	 = 60020
	30.000	 = 60021
	50.000	 = 60022
	100.000 =  60027

	-Unholy-
    emblem =	60004
	10.000	 =  60023
	30.000	 =  60024
	50.000	 =  60025
	100.000 =	60026

	-Demon head-
	dem	 =     60005
	50.000	 = 60033

	Okay so i made this script to learn my friend sephox a bit C++,
	So he is possible to add items in the future by himself
	We hope it's going to be very usefull!
*/
struct tokenData {uint32 TAKE_ENTRY, TAKE_AMOUNT, GIVE_ENTRY, GIVE_AMOUNT; };
struct tokenData Tokens[] =
{
//  {TAKE_ENTRY, TAKE_AMOUNT, GIVE_ENTRY, GIVE_AMOUNT},

	//Souls
    {60000, 10000, 60020, 1},
	{60000, 30000, 60021, 1},
	{60000, 50000, 60022, 1},
	{60000, 100000, 60027, 1},
	//Unholy
	{60004, 10000, 60023, 1},
	{60004, 30000, 60024, 1},
	{60004, 50000, 60025, 1},
	{60004, 100000, 60026, 1},
	//demon
	{60005, 50000, 60033, 1},


};

const uint32 tokensSize = sizeof Tokens/sizeof(*Tokens);
#include "ScriptPCH.h"

class CustomSwapItems : public CreatureScript
{
public:
    CustomSwapItems() : CreatureScript("CustomSwapItems") { }

    std::string GetName(uint32 entry)
    {
        return sObjectMgr->GetItemTemplate(entry)->Name1;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        for (uint32 i = 0; i < tokensSize; ++i)
        {
            std::ostringstream ss;
            // Swap 50 x Token to 10 x token2 (names set automatically)
            ss << "Swap " << Tokens[i].TAKE_AMOUNT << " x " << GetName(Tokens[i].TAKE_ENTRY) << " to " << Tokens[i].GIVE_AMOUNT << " x " << GetName(Tokens[i].GIVE_ENTRY);
            player->ADD_GOSSIP_ITEM_EXTENDED(0, ss.str(), GOSSIP_SENDER_MAIN, i, "Are you sure?", 0, false);
        }
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        if(sender == GOSSIP_SENDER_MAIN && action < tokensSize)
        {
            if(player->HasItemCount(Tokens[action].TAKE_ENTRY, Tokens[action].TAKE_AMOUNT))
            {
                if(player->AddItem(Tokens[action].GIVE_ENTRY, Tokens[action].GIVE_AMOUNT))
                {
                    player->DestroyItemCount(Tokens[action].TAKE_ENTRY, Tokens[action].TAKE_AMOUNT, true);
                    player->GetSession()->SendAreaTriggerMessage("%u x %s swapped to %u x %s", Tokens[action].TAKE_AMOUNT, GetName(Tokens[action].TAKE_ENTRY).c_str(), Tokens[action].GIVE_AMOUNT, GetName(Tokens[action].GIVE_ENTRY).c_str());
                }
            }
            else
                player->GetSession()->SendNotification("You need at least %u x %ss", Tokens[action].TAKE_AMOUNT, GetName(Tokens[action].TAKE_ENTRY).c_str());
        }
        OnGossipHello(player, creature);
        return true;
    }
};

void AddSC_CustomSwapItems()
{
    new CustomSwapItems();
}