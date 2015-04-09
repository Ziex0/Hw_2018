#include "ScriptPCH.h"
 
    class Vote_releaser : public ItemScript
{
public: 
    Vote_releaser() : ItemScript("Vote_releaser") { }

    bool OnUse(Player* player, Item* item, SpellCastTargets const& /*targets*/)
    {   
        player->GetSession()->SendNotification("Done!! Now you can use you Vote items");
        return true;
    }
};
 
void AddSC_Vote_releaser()
{
    new Vote_releaser();
}