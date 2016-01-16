/*
Author: Rochet2
Source: http://rochet2.github.io/?page=Item_Enchant_Visuals

About:
All weapons looted have a 25% chance to have a random enchant *visual*
This is purely visual fun and the visual will be replaced when the weapon is enchanted.

This script is 100% automatic. Just add it to your source.
*/

static const float chance = 0.25f;

// Do not edit anything below

#include "ScriptPCH.h"

static const uint32 ItemEnchants[] = { 3789, 3854, 3273, 3225, 3870, 1899, 2674, 2675, 2671, 2672, 3365, 2673, 2343, 425, 3855, 1894, 1103, 1898, 3345, 1743, 3093, 1900, 3846, 1606, 283, 1, 3265, 2, 3, 3266, 1903, 13, 26, 7, 803, 1896, 2666, 25 };
static const uint32 ItemEnchants_size = (sizeof(ItemEnchants) / sizeof(*ItemEnchants)) - 1;

namespace
{
    template <typename K, typename V>
    class KVRWHashMap
    {
    public:
        typedef std::unordered_map<K, V> MapType;
        typedef ACE_RW_Thread_Mutex LockType;

        void Insert(K k, V v)
        {
            TRINITY_WRITE_GUARD(LockType, i_lock);
            m_hashMap[k] = v;
        }

        void Remove(K k)
        {
            TRINITY_WRITE_GUARD(LockType, i_lock);
            m_hashMap.erase(k);
        }

        // Note, returns a pointer to a copy of the value
        // You MUST manually delete it to avoid mem leaks
        // use ACE_Auto_Ptr<K>
        V* GetCopy(K k)
        {
            TRINITY_READ_GUARD(LockType, i_lock);
            typename MapType::iterator itr = m_hashMap.find(k);
            if (itr != m_hashMap.end())
                return new V(itr->second);
            else
                return NULL;
        }

        MapType& GetContainer() { return m_hashMap; }

        LockType& GetLock() { return i_lock; }

    private:

        LockType i_lock;
        MapType m_hashMap;
    };
};

typedef std::unordered_map<uint32, uint32> EnchantStoreType;
typedef KVRWHashMap<uint32, EnchantStoreType> ItemStoreType;
static ItemStoreType ItemStore;

uint32 GetItemEnchantVisual(Player* player, Item* item)
{
    if (!player || !item)
        return 0;

    ACE_Auto_Ptr<EnchantStoreType> enchants(ItemStore.GetCopy(player->GetGUIDLow()));
    if (!enchants.get())
        return 0;

    uint32 iguid = item->GetGUIDLow();
    EnchantStoreType::const_iterator it = enchants->find(iguid);

    if (it == enchants->end())
        return 0;

    if (uint32 enchant = item->GetEnchantmentId(PERM_ENCHANTMENT_SLOT))
    {
        CharacterDatabase.PExecute("DELETE FROM custom_item_enchant_visuals WHERE iguid = %u", iguid);
        {
            TRINITY_READ_GUARD(ItemStoreType::LockType, ItemStore.GetLock());
            ItemStoreType::MapType& data = ItemStore.GetContainer();
            data.erase(iguid);
        }
        player->SaveToDB();
        return enchant;
    }

    return it->second;
}

void SetRandomEnchantVisual(Player* player, Item* item)
{
    if (!player || !item)
        return;

    const ItemTemplate* temp = item->GetTemplate();
    if (temp->Class != ITEM_CLASS_WEAPON)
        return;

    if (temp->SubClass == ITEM_SUBCLASS_WEAPON_BOW ||
        temp->SubClass == ITEM_SUBCLASS_WEAPON_GUN ||
        temp->SubClass == ITEM_SUBCLASS_WEAPON_obsolete ||
        temp->SubClass == ITEM_SUBCLASS_WEAPON_FIST ||
        temp->SubClass == ITEM_SUBCLASS_WEAPON_THROWN ||
        temp->SubClass == ITEM_SUBCLASS_WEAPON_SPEAR ||
        temp->SubClass == ITEM_SUBCLASS_WEAPON_CROSSBOW ||
        temp->SubClass == ITEM_SUBCLASS_WEAPON_WAND ||
        temp->SubClass == ITEM_SUBCLASS_WEAPON_FISHING_POLE)
        return;

    if (rand_norm() >= chance)
        return;

    uint32 enchant = ItemEnchants[urand(0, ItemEnchants_size)];
    uint32 iguid = item->GetGUIDLow();
    CharacterDatabase.PExecute("REPLACE INTO custom_item_enchant_visuals (iguid, display) VALUES (%u, %u)", iguid, enchant);
    {
        TRINITY_READ_GUARD(ItemStoreType::LockType, ItemStore.GetLock());
        ItemStoreType::MapType& data = ItemStore.GetContainer();
        data[player->GetGUIDLow()][iguid] = enchant;
    }
    player->SaveToDB();
    player->SetVisibleItemSlot(EQUIPMENT_SLOT_MAINHAND, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND));
    player->SetVisibleItemSlot(EQUIPMENT_SLOT_OFFHAND, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND));
}

class item_enchant_visuals : public PlayerScript
{
public:
    item_enchant_visuals(): PlayerScript("item_enchant_visuals")
    {
        const char* sql =
            "CREATE TABLE IF NOT EXISTS `custom_item_enchant_visuals` ("
            "    `iguid` INT(10) UNSIGNED NOT NULL COMMENT 'item DB guid',"
            "    `display` INT(10) UNSIGNED NOT NULL COMMENT 'enchantID',"
            "    PRIMARY KEY (`iguid`)"
            ")"
            "COMMENT='stores the enchant IDs for the visuals'"
            "COLLATE='latin1_swedish_ci'"
            "ENGINE=InnoDB;";
        CharacterDatabase.DirectExecute(sql);
        CharacterDatabase.DirectExecute("DELETE FROM custom_item_enchant_visuals WHERE NOT EXISTS(SELECT 1 FROM item_instance WHERE custom_item_enchant_visuals.iguid = item_instance.guid)");
    }

    void OnLogin(Player* player, bool /*firstLogin*/)
    {
        QueryResult result = CharacterDatabase.PQuery("SELECT iguid, display FROM custom_item_enchant_visuals WHERE iguid IN(SELECT guid FROM item_instance WHERE owner_guid = %u)", player->GetGUIDLow());
        if (result)
        {
            EnchantStoreType temp;
            do
            {
                uint32 iguid = result->Fetch()[0].GetUInt32();
                uint32 display = result->Fetch()[1].GetUInt32();
                temp[iguid] = display;
            }	while (result->NextRow());

            ItemStore.Insert(player->GetGUIDLow(), temp);

            player->SetVisibleItemSlot(EQUIPMENT_SLOT_MAINHAND, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND));
            player->SetVisibleItemSlot(EQUIPMENT_SLOT_OFFHAND, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND));

        }
    }

    void OnLogout(Player* player) override
    {
        ItemStore.Remove(player->GetGUIDLow());
    }
};

void AddSC_item_enchant_visuals()
{
    new item_enchant_visuals;
}
#undef CHANCE
