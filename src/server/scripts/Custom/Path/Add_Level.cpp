	
    #include "ScriptPCH.h"
     
    enum
    {
    item_id = 320277,
    max_lvl = 255,
     };
     
    class Level_item : public ItemScript
{
public: 
    Level_item() : ItemScript("Level_item") { }

    bool OnUse(Player* player, Item* item, SpellCastTargets const& /*targets*/)
    {
        if  (player->getLevel() == 255)
        {
            player->GetSession()->SendNotification("You already have level 255.");
            return false;
        }
        player->GiveLevel(255);
        player->DestroyItemCount(item->GetEntry(),1,true,false);
        player->GetSession()->SendNotification("Your level was set to 255.");
        return true;
    }
};
 
void AddSC_Level_item()
{
    new Level_item();
}