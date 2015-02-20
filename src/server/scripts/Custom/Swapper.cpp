#include "ScriptPCH.h"

struct tokenData {uint32 TAKE_ENTRY, TAKE_AMOUNT, GIVE_ENTRY, GIVE_AMOUNT; };
struct tokenData Tokens[] =
{
//  {TAKE_ENTRY, TAKE_AMOUNT, GIVE_ENTRY, GIVE_AMOUNT},
// Make a custom structure, so for example.

    //this takes itemid 50 and gives itemid 62 in return
		{50, 1, 62, 1},
	//you can also take 5000 and give itemid 62 back 1000 times.
        {50, 500, 62, 1000},
	
/*
This is all up to you you can do whatever u want with it.
Enjoy :)
*/	

};
 
const uint32 tokensSize = sizeof Tokens/sizeof(*Tokens);
 
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