#include "ScriptMgr.h"
#include "Pet.h"


static const uint32 tokenid = 26;
static const uint32 pageentries = 14; // Will add 1-2 more entries for forward and backwards.
static const uint32 gossiptextid = 1;

class pet_transmogger : public CreatureScript
{
public:

    pet_transmogger() : CreatureScript("pet_transmogger") { }

    void AddMenuItem(Player* player, uint8 icon, std::string message, uint32 sender, uint32 action)
    {
        player->PlayerTalkClass->GetGossipMenu().AddMenuItem(-1, icon, message, sender, action, "", 0);
    }

    void ShowPage(Player* player, uint32 page)
    {
        uint32 pos = 0;
        --page;

        for (ObjectMgr::PetTransmogContainer::const_iterator itr = sObjectMgr->m_PetTransmogContainer.begin();
            itr != sObjectMgr->m_PetTransmogContainer.end(); ++itr)
        {
            if (pos >= page*pageentries && pos < page*pageentries+pageentries)
                AddMenuItem(player, 0, itr->name, 0, itr->displayid);

            ++pos;
        }

        // Page+1 = Currently viewed page.
        if (page != 0)
            AddMenuItem(player, 0, "Previous", page, 0);

        if (pos > page*pageentries+pageentries)
            AddMenuItem(player, 0, "Next", page+2, 0);
    }

    uint32 GetPrice(uint32 displayid)
    {
        for (ObjectMgr::PetTransmogContainer::const_iterator itr = sObjectMgr->m_PetTransmogContainer.begin();
            itr != sObjectMgr->m_PetTransmogContainer.end(); ++itr)
            if (itr->displayid == displayid)
                return itr->price;

        return 0;
    }

    bool FoundID(uint32 displayid)
    {
        for (ObjectMgr::PetTransmogContainer::const_iterator itr = sObjectMgr->m_PetTransmogContainer.begin();
            itr != sObjectMgr->m_PetTransmogContainer.end(); ++itr)
            if (itr->displayid == displayid)
                return true;

        return false;
    }

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        // Just an empty gossip that will transfer us to gossipselect.
        ShowPage(player, 1);

        if (!player->PlayerTalkClass->GetGossipMenu().Empty())
            player->PlayerTalkClass->SendGossipMenu(gossiptextid, creature->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) override
    {
        player->PlayerTalkClass->ClearMenus();

        if (sender != 0)
            ShowPage(player, sender);
        else
        {
            if (FoundID(action))
            {
                if (player->GetItemCount(tokenid) >= GetPrice(action))
                {
                    if (Pet* pPet = player->GetPet())
                    {
                        if (pPet->GetDisplayId() == action && pPet->checkdisplayid)
                        {
                            pPet->SetNativeDisplayId(action);
                            player->DestroyItemCount(tokenid, GetPrice(action), true);
                            ChatHandler(player->GetSession()).PSendSysMessage("Your pets look was pimped out permanently!");
                        }
                        else
                        {
                            pPet->SetDisplayId(action);
                            pPet->checkdisplayid = true;
                            ChatHandler(player->GetSession()).PSendSysMessage("You now have 60 seconds to preview how this pet will look, if you wanna keep it just select the same option again within 60 seconds.");
                        }
                    }
                }
						else
							ChatHandler(player->GetSession()).PSendSysMessage("You do not have enough tokens to pimp your pet!");
            }
        }

        if (!player->PlayerTalkClass->GetGossipMenu().Empty())
            player->PlayerTalkClass->SendGossipMenu(gossiptextid, creature->GetGUID());
        else
            player->PlayerTalkClass->SendCloseGossip();

        return true;
    }
};

void AddSC_pet_transmog()
{
    new pet_transmogger();
}
