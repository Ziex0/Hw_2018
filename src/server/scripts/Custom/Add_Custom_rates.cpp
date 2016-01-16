#include "ScriptMgr.h"
#include "Chat.h"
#include "Language.h"

class CustomRates
{
public:
	static uint32 GetXpRateForVip(const Player *player)
	{
		uint32 XpRate = 1;
		switch(player->GetSession()->GetVipLevel())
		{
		case 1:
			XpRate = sWorld->getIntConfig(CONFIG_VIP_XP_RATE_LEVEL_1);
			break;
		case 2:
			XpRate = sWorld->getIntConfig(CONFIG_VIP_XP_RATE_LEVEL_2);
			break;
		
		}
		return XpRate;
	}

	static int32 GetLootRateForVip(const Player *player)
	{
		uint32 LootRate = 1;
		switch(player->GetSession()->GetVipLevel())
		{
		case 1:
			LootRate = sWorld->getIntConfig(CONFIG_VIP_LOOT_RATE_LEVEL_1);
			break;
		case 2:
			LootRate = sWorld->getIntConfig(CONFIG_VIP_LOOT_RATE_LEVEL_2);
			break;
		
		}
		return LootRate;
	}
};

class add_del_rates : public PlayerScript
{
public:
	add_del_rates() : PlayerScript("add_del_rates") { }

	void OnLogin(Player *player, bool /*firstLogin*/)
	{
		// set custom xp rate for player on login
		uint32 rateXP = CustomRates::GetXpRateForVip(player);
		player->SetCustomXpRate(static_cast<uint32>(rateXP));

		// set custom loot rate for player on login
		uint32 rateLoot = CustomRates::GetLootRateForVip(player);
		player->SetCustomLootRate(static_cast<uint32>(rateLoot));

		ChatHandler(player->GetSession()).PSendSysMessage("Your XP rate %u, loot rate %u", rateXP, rateLoot);
	}
};

void AddSC_Custom_Rates()
{
	new add_del_rates();
}