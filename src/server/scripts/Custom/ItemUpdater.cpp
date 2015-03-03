#include "ScriptPCH.h"
#include "Transmogrification.h"

enum defines
{
	Nothing_here = 0
};

    enum Senders
    {
        MAIN_MENU = GOSSIP_ACTION_INFO_DEF+1,
        SELECT_ITEM,
        SELECT_STAT_INCREASE,
        SELECT_TOKEN_COST,
		VENDOR = GOSSIP_ACTION_INFO_DEF+2,
        REFORGE,
    };

    UNORDERED_MAP<uint32, Item*> selectedItem;

    char * GetSlotName(uint8 slot, WorldSession* session)
    {
        switch (slot)
        {
        case EQUIPMENT_SLOT_HEAD      : return "Head";
        case EQUIPMENT_SLOT_NECK      : return "Neck";
        case EQUIPMENT_SLOT_SHOULDERS : return "Shoulders";
        case EQUIPMENT_SLOT_BODY      : return "Shirt";
        case EQUIPMENT_SLOT_CHEST     : return "Chest";
        case EQUIPMENT_SLOT_WAIST     : return "Waist";
        case EQUIPMENT_SLOT_LEGS      : return "Legs";
        case EQUIPMENT_SLOT_FEET      : return "Feet";
        case EQUIPMENT_SLOT_WRISTS    : return "Wrists";
        case EQUIPMENT_SLOT_HANDS     : return "Hands";
        case EQUIPMENT_SLOT_FINGER1   : return "Right finger";
        case EQUIPMENT_SLOT_FINGER2   : return "left finger";
        case EQUIPMENT_SLOT_TRINKET1  : return "Right trinket";
        case EQUIPMENT_SLOT_TRINKET2  : return "Left trinket";
        case EQUIPMENT_SLOT_BACK      : return "Back";
        case EQUIPMENT_SLOT_MAINHAND  : return "Main hand";
        case EQUIPMENT_SLOT_OFFHAND   : return "Off hand";
        case EQUIPMENT_SLOT_RANGED    : return "Ranged";
        case EQUIPMENT_SLOT_TABARD    : return "Tabard";
        default: return NULL;
        }
    }

class ItemUpdater : public CreatureScript
{
public:
    ItemUpdater() : CreatureScript("ItemUpdater") { }

	static void addItem(Player* player, EquipmentSlots slot, uint32 entry)
    {
        if(slot >= EQUIPMENT_SLOT_START && slot < EQUIPMENT_SLOT_END)
        {
            uint16 dest;
            InventoryResult msg = player->CanEquipNewItem(slot, dest, entry, false);
            if (msg != EQUIP_ERR_OK)
            {
                return; // skip equipping if cant equip
            }
            player->EquipNewItem(dest, entry, true);
        }
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/INV_Misc_Book_11:35:35:-19:0|t How item upgrading works", EQUIPMENT_SLOT_END+9, 0);
		for (uint8 slot = EQUIPMENT_SLOT_START; slot < EQUIPMENT_SLOT_END; slot++)
        {
            if(Item* invItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot))
			{
				std::string icon = sTransmogrification->GetItemIcon(invItem->GetEntry(),30,30,-19,0);

                    if(char* slotname = GetSlotName(slot, player->GetSession()))
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, icon+std::string(slotname), SELECT_STAT_INCREASE, slot);
			}
        }
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/PaperDollInfoFrame/UI-GearManager-Undo:35:35:-19:0|t Update menu", MAIN_MENU, 0);
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        switch(sender)
        {
		case EQUIPMENT_SLOT_END+9:
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "", EQUIPMENT_SLOT_END+1, 0);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:50:50:-19:0|tBack..", MAIN_MENU, 0);
            player->SEND_GOSSIP_MENU(50004, creature->GetGUID());
			break;
        case MAIN_MENU: OnGossipHello(player, creature); break;
		case 3137:
			player->GetSession()->SendListInventory(creature->GetGUID());
			break;
        case SELECT_STAT_INCREASE:
            // action = slot
            if (Item* invItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, action))
            {
                    selectedItem[player->GetGUIDLow()] = invItem;
                    const ItemTemplate* proto = invItem->GetTemplate();
					int32 cost = proto->BuyPrice * sWorld->getFloatConfig(CONFIG_RATE_ITEM_UPDATE_COST);
					char price[250];

					if (proto->StatsCount == 0)
					{
						player->GetSession()->SendAreaTriggerMessage("The item: %s\nCan't be upgraded.", sTransmogrification->GetItemLink(invItem->GetEntry(), player->GetSession()).c_str());
						player->PlayerTalkClass->SendCloseGossip();
						return false;
					}

					uint32 newItem = invItem->GetEntry() + 1000000;
					
					if(!sObjectMgr->GetItemTemplate(newItem)) // an item template doesnt exist for the item
					{
						player->GetSession()->SendAreaTriggerMessage("The item: %s\nCan't be upgraded.", sTransmogrification->GetItemLink(invItem->GetEntry(), player->GetSession()).c_str());
						player->PlayerTalkClass->SendCloseGossip();
						return false;
					}

					uint16 Brokens;
					uint16 Stolen;
					uint16 Pure;
					uint16 Horns;
					uint16 Run;
					uint16 Shoot;
					uint16 Event;
					uint16 Coin;
					uint16 Lava;

					//modifiers
					if (invItem->GetEntry() < 1000000)
					{
						Brokens = 10;
						Stolen = 10;
						Pure = 1;
						Horns = 1;
						Run = 1;
						Shoot = 1;
						Event = 50;
						Coin = 10;
						Lava = 5;
					}
					else if (invItem->GetEntry() < 2000000 && invItem->GetEntry() > 1000000)
					{
						Brokens = 20;
						Stolen = 20;
						Pure = 3;
						Horns = 1;
						Run = 2;
						Shoot = 1;
						Event = 75;
						Coin = 20;
						Lava = 10;
					}
					else if (invItem->GetEntry() < 3000000 && invItem->GetEntry() > 2000000)
					{
						Brokens = 50;
						Stolen = 50;
						Pure = 10;
						Horns = 2;
						Run = 3;
						Shoot = 2;
						Event = 150;
						Coin = 25;
						Lava = 15;
					}
					else if (invItem->GetEntry() < 4000000 && invItem->GetEntry() > 3000000)
					{
						Brokens = 100;
						Stolen = 100;
						Pure = 25;
						Horns = 3;
						Run = 5;
						Shoot = 3;
						Event = 300;
						Coin = 100;
						Lava = 50;
					}
					else if (invItem->GetEntry() < 5000000 && invItem->GetEntry() > 4000000)
					{
						Brokens = 500;
						Stolen = 500;
						Pure = 250;
						Horns = 10;
						Run = 10;
						Shoot = 5;
						Event = 500;
						Coin = 200;
						Lava = 100;
					}

					//addItem(Player* player, EquipmentSlots slot, uint32 entry)
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Paladin_BlessedHands:35:35:-19:0|tNOTE: REFORGE IS LOST WHEN UPGRADING.", sender, action);
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "-------------------------", sender, action);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Paladin_BlessedHands:35:35:-19:0|tSelected item:", sender, action);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, sTransmogrification->GetItemIcon(invItem->GetEntry(), 20, 20, -19, 0)+sTransmogrification->GetItemLink(invItem->GetEntry(), player->GetSession()).c_str(), sender, action);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Achievement_BG_returnXflags_def_WSG:35:35:-19:0|tUpgrade to:", sender, action);
					
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, sTransmogrification->GetItemIcon(invItem->GetEntry(), 20, 20, -19, 0)+sTransmogrification->GetItemLink(newItem, player->GetSession()).c_str(), SELECT_TOKEN_COST, action);

					snprintf(price, 250, "|TInterface/ICONS/INV_Misc_Coin_02:35:35:-19:0|t\nPrice: %u Rare Ancient Coin & %u Gold.\n%u Broken Souls & %u Stolen Souls.\n%u Pure Souls & %u Horns of Thorim.\n%u Running Event Rune & %u Golden Arrow.\n%u Pure Lava Core & %u Event Tokens.",
						Coin, cost / 10000, Brokens, Stolen, Pure, Horns, Run, Shoot, Lava, Event);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, price, SELECT_STAT_INCREASE, action);
					
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:35:35:-19:0|tBack..", MAIN_MENU, 0);
                    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
					return true;
            }
            else
            {
                player->GetSession()->SendNotification("No item selected");
                OnGossipHello(player, creature);
            }
            break;
        case SELECT_TOKEN_COST:
            // action = stat_count_id
            {
                Item* invItem = selectedItem[player->GetGUIDLow()];
				int32 cost = invItem->GetTemplate()->BuyPrice * sWorld->getFloatConfig(CONFIG_RATE_ITEM_UPDATE_COST);

				uint32 newItem = invItem->GetEntry() + 1000000;

				uint16 Brokens;
				uint16 Stolen;
				uint16 Pure;
				uint16 Horns;
				uint16 Run;
				uint16 Shoot;
				uint16 Event;
				uint16 Coin;
				uint16 Lava;

				//modifiers
				if (invItem->GetEntry() < 1000000)
				{
					Brokens = 10;
					Stolen = 10;
					Pure = 1;
					Horns = 1;
					Run = 1;
					Shoot = 1;
					Event = 50;
					Coin = 5;
					Lava = 2;
				}
				else if (invItem->GetEntry() < 2000000 && invItem->GetEntry() > 1000000)
				{
					Brokens = 20;
					Stolen = 20;
					Pure = 3;
					Horns = 1;
					Run = 2;
					Shoot = 1;
					Event = 75;
					Coin = 10;
					Lava = 5;
				}
				else if (invItem->GetEntry() < 3000000 && invItem->GetEntry() > 2000000)
				{
					Brokens = 50;
					Stolen = 50;
					Pure = 10;
					Horns = 2;
					Run = 3;
					Shoot = 2;
					Event = 150;
					Coin = 15;
					Lava = 10;
				}
				else if (invItem->GetEntry() < 4000000 && invItem->GetEntry() > 3000000)
				{
					Brokens = 100;
					Stolen = 100;
					Pure = 25;
					Horns = 3;
					Run = 5;
					Shoot = 3;
					Event = 300;
					Coin = 30;
					Lava = 20;
				}
				else if (invItem->GetEntry() < 5000000 && invItem->GetEntry() > 4000000)
				{
					Brokens = 500;
					Stolen = 500;
					Pure = 250;
					Horns = 10;
					Run = 10;
					Shoot = 5;
					Event = 500;
					Coin = 100;
					Lava = 50;
				}

				if (!player->HasEnoughMoney(cost))
                {
                    player->GetSession()->SendNotification("You do not have enough money for this update.\nThe price is: %u gold.", cost / 10000);
					OnGossipSelect(player, creature, SELECT_STAT_INCREASE, action);
                    return false;
                }

				if (!player->HasItemCount(29438, Brokens))
				{
					player->GetSession()->SendNotification("You do not have enough Broken Souls for this update.\nThe price is: %u.", Brokens);
					OnGossipSelect(player, creature, SELECT_STAT_INCREASE, action);
					return false;
				}
				if (!player->HasItemCount(29437, Pure))
				{
					player->GetSession()->SendNotification("You do not have enough Pure Souls for this update.\nThe price is: %u.", Pure);
					OnGossipSelect(player, creature, SELECT_STAT_INCREASE, action);
					return false;
				}
				if (!player->HasItemCount(29435, Stolen))
				{
					player->GetSession()->SendNotification("You do not have enough Stolen Souls for this update.\nThe price is: %u.", Stolen);
					OnGossipSelect(player, creature, SELECT_STAT_INCREASE, action);
					return false;
				}
				if (!player->HasItemCount(98501, Horns))
				{
					player->GetSession()->SendNotification("You do not have enough Horns of Thorim for this update.\nThe price is: %u.", Horns);
					OnGossipSelect(player, creature, SELECT_STAT_INCREASE, action);
					return false;
				}
				if (!player->HasItemCount(13815, Run))
				{
					player->GetSession()->SendNotification("You do not have enough Running Event Runes for this update.\nThe price is: %u.", Run);
					OnGossipSelect(player, creature, SELECT_STAT_INCREASE, action);
					return false;
				}
				if (!player->HasItemCount(3030, Shoot))
				{
					player->GetSession()->SendNotification("You do not have enough Golden Arrows for this update.\nThe price is: %u.", Shoot);
					OnGossipSelect(player, creature, SELECT_STAT_INCREASE, action);
					return false;
				}
				if (!player->HasItemCount(985092, Coin))
				{
					player->GetSession()->SendNotification("You do not have enough Rare Ancient Coins for this update.\nThe price is: %u.", Coin);
					OnGossipSelect(player, creature, SELECT_STAT_INCREASE, action);
					return false;
				}
				if (!player->HasItemCount(23247, Event))
				{
					player->GetSession()->SendNotification("You do not have enough Event Tokens for this update.\nThe price is: %u.", Event);
					OnGossipSelect(player, creature, SELECT_STAT_INCREASE, action);
					return false;
				}
				if (!player->HasItemCount(17011, Lava))
				{
					player->GetSession()->SendNotification("You do not have enough Pure Lava Cores for this update.\nThe price is: %u.", Lava);
					OnGossipSelect(player, creature, SELECT_STAT_INCREASE, action);
					return false;
				}

				player->DestroyItemCount(23248,  Brokens, true);
				player->DestroyItemCount(23245,  Stolen, true);
				player->DestroyItemCount(23247,  Pure, true);
				player->DestroyItemCount(98501,  Horns, true);
				player->DestroyItemCount(13815,  Run, true);
				player->DestroyItemCount(3030,   Shoot, true);
				player->DestroyItemCount(23247,  Event, true);
				player->DestroyItemCount(985092, Coin, true);
				player->DestroyItemCount(17011,  Lava, true);

				player->DestroyItemCount(invItem->GetEntry(), 1, true);
				player->ModifyMoney(-cost);
				addItem(player, EquipmentSlots(action), newItem);
				player->SaveToDB();

				ChatHandler(player->GetSession()).PSendSysMessage("Success! You have upgraded your item into the next mode.");
				player->GetSession()->SendAreaTriggerMessage("Success!\nYou have upgraded your item into the next mode.");
				player->PlayerTalkClass->SendCloseGossip();
				return true;
            }
            break;
        default: // Reforge
            break;
        }
        return true;
    }
};

class ItemUpdaterUltimate : public CreatureScript
{
public:
    ItemUpdaterUltimate() : CreatureScript("ItemUpdaterUltimate") { }

	static void addItem(Player* player, EquipmentSlots slot, uint32 entry)
    {
        if(slot >= EQUIPMENT_SLOT_START && slot < EQUIPMENT_SLOT_END)
        {
            uint16 dest;
            InventoryResult msg = player->CanEquipNewItem(slot, dest, entry, false);
            if (msg != EQUIP_ERR_OK)
            {
                return; // skip equipping if cant equip
            }
            player->EquipNewItem(dest, entry, true);
        }
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
		if (player->GetItemByGuid() == PATH_NONE || player->GetItemByGuid() > PATH_MAGE)
		{
			player->PlayerTalkClass->SendCloseGossip();
			player->GetSession()->SendNotification("You have no secondary path chosen, you must set that before updating your items.");
			return true;
		}

		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/INV_Misc_Book_11:35:35:-19:0|t How item upgrading works", EQUIPMENT_SLOT_END+9, 0);
		for (uint8 slot = EQUIPMENT_SLOT_START; slot < EQUIPMENT_SLOT_END; slot++)
        {
            if(Item* invItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot))
			{
				std::string icon = sTransmogrification->GetItemIcon(invItem->GetEntry(),30,30,-19,0);

				if((invItem->GetEntry() <= 400000 && invItem->GetEntry() > 100000) || (invItem->GetEntry() >= 800000 && invItem->GetEntry() <= 1100000))
                    if(char* slotname = GetSlotName(slot, player->GetSession()))
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, icon+std::string(slotname), SELECT_STAT_INCREASE, slot);
			}
        }
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface\\icons\\INV_Enchant_ShardPrismaticSmall:35:35:-19:0|t Buy Ancient Tokens", 3137, 0);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/PaperDollInfoFrame/UI-GearManager-Undo:35:35:-19:0|t Update menu", MAIN_MENU, 0);
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        switch(sender)
        {
		case EQUIPMENT_SLOT_END+9:
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "", EQUIPMENT_SLOT_END+1, 0);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:50:50:-19:0|tBack..", MAIN_MENU, 0);
            player->SEND_GOSSIP_MENU(50004, creature->GetGUID());
			break;
        case MAIN_MENU: OnGossipHello(player, creature); break;
		case 3137:
			player->GetSession()->SendListInventory(creature->GetGUID());
			break;
        case SELECT_STAT_INCREASE:
            // action = slot
            if (Item* invItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, action))
            {
                    selectedItem[player->GetGUIDLow()] = invItem;
                    const ItemTemplate* proto = invItem->GetTemplate();
					int32 cost = sTransmogrification->GetSpecialPrice(proto) * sWorld->getFloatConfig(CONFIG_RATE_ITEM_UPDATE_COST);
					char price[250];

					if (proto->StatsCount == 0)
					{
						player->GetSession()->SendAreaTriggerMessage("The item: %s\nCan't be upgraded.", sTransmogrification->GetItemLink(invItem->GetEntry(), player->GetSession()).c_str());
						player->PlayerTalkClass->SendCloseGossip();
						return false;
					}

					uint32 newItem = invItem->GetEntry() + 300000;
					if(!sObjectMgr->GetItemTemplate(newItem)) // an item template doesnt exist for the item
					{
						player->GetSession()->SendAreaTriggerMessage("The item: %s\nCan't be upgraded.", sTransmogrification->GetItemLink(invItem->GetEntry(), player->GetSession()).c_str());
						player->PlayerTalkClass->SendCloseGossip();
						return false;
					}

					//addItem(Player* player, EquipmentSlots slot, uint32 entry)
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Paladin_BlessedHands:35:35:-19:0|tSelected item:", sender, action);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, sTransmogrification->GetItemIcon(invItem->GetEntry(), 20, 20, -19, 0)+sTransmogrification->GetItemLink(invItem->GetEntry(), player->GetSession()).c_str(), sender, action);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Achievement_BG_returnXflags_def_WSG:35:35:-19:0|tUpgrade to:", sender, action);
					
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, sTransmogrification->GetItemIcon(invItem->GetEntry(), 20, 20, -19, 0)+sTransmogrification->GetItemLink(newItem, player->GetSession()).c_str(), SELECT_TOKEN_COST, action);

					snprintf(price, 250, "|TInterface/ICONS/INV_Misc_Coin_02:35:35:-19:0|tPrice: 10x Ancient Token & %u Gold.\n%u Honor Points & 100 Stolen Souls.", cost / 10000, (invItem->GetTemplate()->ItemLevel * 15));
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, price, SELECT_STAT_INCREASE, action);
					
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "|TInterface/ICONS/Ability_Spy:35:35:-19:0|tBack..", MAIN_MENU, 0);
                    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
					return true;
            }
            else
            {
                player->GetSession()->SendNotification("No item selected");
                OnGossipHello(player, creature);
            }
            break;
        case SELECT_TOKEN_COST:
            // action = stat_count_id
            {
                Item* invItem = selectedItem[player->GetGUIDLow()];
				int32 cost = sTransmogrification->GetSpecialPrice(invItem->GetTemplate()) * sWorld->getFloatConfig(CONFIG_RATE_ITEM_UPDATE_COST);

				uint32 tokenEntry;
				switch(player->GetItemCount())
				{
					case PATH_ASSAULT:
						tokenEntry = 1;
						break;
					case PATH_GUARDIAN:
						tokenEntry = 2;
						break;
					case PATH_MAGE:
						tokenEntry = 3;
						break;
				}

				uint32 newItem = invItem->GetEntry() + 300000;
				if(!sObjectMgr->GetItemTemplate(newItem) || !invItem) // an item template doesnt exist for the item
				{
					player->GetSession()->SendAreaTriggerMessage("The item: %s\nCan't be upgraded.", sTransmogrification->GetItemLink(invItem->GetEntry(), player->GetSession()).c_str());
					player->PlayerTalkClass->SendCloseGossip();
					return false;
				}

				if (!HasCost(player, cost, invItem))
                {
					OnGossipSelect(player, creature, SELECT_STAT_INCREASE, action);
                    return false;
                }

				if (!player->HasItemCount(tokenEntry, 10))
				{
					player->GetSession()->SendNotification("You do not have enough tokens for this update.\nThe price is: 10 Ancient Token.");
					OnGossipSelect(player, creature, SELECT_STAT_INCREASE, action);
					return false;
				}

				if (invItem->GetTemplate()->RequiredHonorRank > player->GetHonorPoints())
				{
					player->GetSession()->SendNotification("You'r rank is not high enough to upgrade this item.\nRankpoints needed: %u You have: %u.", invItem->GetTemplate()->RequiredHonorRank > player->GetHonorPoints());
					OnGossipSelect(player, creature, SELECT_STAT_INCREASE, action);
					return false;
				}

				player->DestroyItemCount(tokenEntry, 10, true);
				player->DestroyItemCount(invItem->GetEntry(), 1, true);
				player->ModifyMoney(-cost);
				player->ModifyHonorPoints(-(invItem->GetTemplate()->ItemLevel * 10));
				player->DestroyItemCount(29437, 100, true);
				addItem(player, EquipmentSlots(action), newItem);
				player->SaveToDB();

				ChatHandler(player->GetSession()).PSendSysMessage("Success! You have upgraded your item into your specific secondary class ultimate mode.");
				player->GetSession()->SendAreaTriggerMessage("Success!\nYou have upgraded your item into your specific secondary class ultimate mode.");
				player->PlayerTalkClass->SendCloseGossip();
                return true;
            }
            break;
        default: // Reforge
            break;
        }
        return true;
    }
	private:

		bool HasCost(Player* player, int32 cost, Item* item)
		{
			if (!player->HasEnoughMoney(cost))
			{
				ChatHandler(player->GetSession()).PSendSysMessage("You need %i gold to upgrade this item.", cost / 10000);
				return false;
			}
			if (!player->HasItemCount(29437, 100))
			{
				ChatHandler(player->GetSession()).PSendSysMessage("You need 100 Stolen Souls to upgrade this item.");
				return false;
			}
			if (player->GetHonorPoints() < item->GetTemplate()->ItemLevel * 15)
			{
				ChatHandler(player->GetSession()).PSendSysMessage("You need %u honor points to upgrade this item.", item->GetTemplate()->ItemLevel * 15);
				return false;
			}
			return true;
		}
};

void AddSC_ItemUpdater()
{
    new ItemUpdater();
	new ItemUpdaterUltimate();
}