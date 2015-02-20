	
    #include "ScriptPCH.h"
     
    enum
    {
    item_id = 320277,
    max_lvl = 254,
     };
     
    class Level_item : public ItemScript
{
public: 
    Level_item() : ItemScript("Level_item") { }

    bool OnUse(Player* player, Item* item, SpellCastTargets const& /*targets*/)
    {
        if  (player->getLevel() == 254)
        {
            player->GetSession()->SendNotification("You already have level 254.");
            return false;
        }
        player->GiveLevel(254);
        player->DestroyItemCount(item->GetEntry(),1,true,false);
        player->GetSession()->SendNotification("Your level was set to 254.");
        return true;
    }
};
 
void AddSC_Level_item()
{
    new Level_item();
}