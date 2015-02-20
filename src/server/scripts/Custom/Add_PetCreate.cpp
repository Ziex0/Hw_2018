/*
     Messing with the Pet system - Tutorial
*/
#include "Pet.h"

class npc_pet_tutorial : public CreatureScript
{
public:
	npc_pet_tutorial() : CreatureScript("npc_pet_tutorial") { }

	bool OnGossipHello(Player* player, Creature* creature)
	{
		if (player->GetPet())
			return false;

		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Create a pet", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
		player->SEND_GOSSIP_MENU(1, creature->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player* player, Creature* creature, uint32 /* sender */, uint32 actions)
	{
		player->PlayerTalkClass->ClearMenus();

		if (actions == GOSSIP_ACTION_INFO_DEF+1)
			CreatePet(creature, player, 823);
		return true;
	}

	bool CreatePet(Creature* creature, Player* player, uint32 entry)
	{
		float x, y, z;
		player->GetPosition(x, y, z);

		Creature* petCreature = creature->SummonCreature(entry, x+2, y+1, z, 1, TEMPSUMMON_MANUAL_DESPAWN, 0);
		if (!petCreature)
			return false;

		Pet* pet = player->CreateTamedPetFrom(petCreature, 0);
		if (!pet)
			return false;

		pet->SetPower(POWER_HAPPINESS, 100);
		pet->AddUInt64Value(UNIT_FIELD_CREATEDBY, player->GetGUID());
		pet->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, player->getFaction());
		pet->SetUInt32Value(UNIT_FIELD_LEVEL, player->getLevel());
		pet->GetMap()->AddToMap(pet->ToCreature());
		pet->GetCharmInfo()->SetPetNumber(sObjectMgr->GeneratePetNumber(), true);
		player->SetMinion(pet, true);
		pet->SavePetToDB(PET_SAVE_AS_CURRENT);
		pet->InitTalentForLevel();
		pet->InitStatsForLevel(player->getLevel());
		player->PetSpellInitialize();

		petCreature->DespawnOrUnsummon(100);
		return true;
	}
};

void AddSC_pet_tut()
{
	new npc_pet_tutorial();
}