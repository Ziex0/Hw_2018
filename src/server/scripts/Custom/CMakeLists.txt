# Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.


set(scripts_STAT_SRCS
  ${scripts_STAT_SRCS}
  
  #Custom From Core
  Custom/mod_ArenaWatcher.cpp
  Custom/mod_AuctionHouseBot.cpp
  Custom/mod_AutoLearn.cpp
  Custom/mod_BattlegroundHistory.cpp
  Custom/mod_BossHistory.cpp
  Custom/mod_CharacterHistory.cpp
  Custom/mod_CharacterModel.cpp
  Custom/mod_CustomRewardWorldPvP.cpp
  Custom/mod_DefaultSpec.cpp
  Custom/mod_DynamicInsctane.cpp
  Custom/mod_DynamicRate.cpp
  Custom/mod_ExternalMail.cpp
  Custom/mod_Tournaments.cpp
  Custom/mod_GuildDefault.cpp
  Custom/mod_HonorRank.cpp
  Custom/mod_ItemUpgrade.cpp
  Custom/mod_MailHistory.cpp
  Custom/mod_MultiKill.cpp
  Custom/mod_SpecialCode.cpp
  Custom/mod_LexicsCutter.cpp
 
  Custom/Add_Telenpc.cpp
  Custom/Enchant_visuals.cpp
  Custom/Add_Changer.cpp
  Custom/Add_VisualNpc.cpp
  Custom/Add_PetCreate.cpp
  Custom/Add_BeastMaster.cpp
  Custom/Add_Protection.cpp
  Custom/Add_NpcEnchancer
  Custom/Add_Fusion.cpp
  Custom/Transmogrification.h
  Custom/Transmogrification.cpp
  Custom/Transmogrifier.cpp
  Custom/Add_Premium.cpp
  Custom/Add_Summon.cpp
  Custom/Add_BossShadow.cpp
  Custom/Add_Npctitle.cpp
  Custom/1v1.cpp
  Custom/Add_Lotto.cpp
  Custom/Add_PremiumRate.cpp
  Custom/Add_Level.cpp
  Custom/Gm_account.cpp
  Custom/pvp/pvp_duel_reset.cpp
  Custom/Add_Timer.cpp
  Custom/Add_TimerDp.cpp
  Custom/Add_Afk.cpp
  Custom/Add_top.cpp
  Custom/Add_KillStreak.cpp
  Custom/Add_gurubashi.cpp
  Custom/Add_Reforging.cpp
  Custom/Add_Abuse.cpp
  Custom/Add_Glyph.cpp
  Custom/VIP/vip_commands.cpp
  Custom/VIP/vip_do_com.cpp
  Custom/VIP/vip_only_area.cpp
  Custom/Add_thefallen.cpp
  Custom/vp_redeem.cpp
  Custom/system/sec_anti_farming.cpp
  Custom/system/chat_censure.cpp
  Custom/Custom_Talent_Template.cpp
  Custom/vipset.cpp
  Custom/Add_refund.cpp
  Custom/Add_votereleaser.cpp
  Custom/Add_Event_reward.cpp
  Custom/Add_berserk.cpp
  Custom/Add_VIPisland.cpp
  
  Custom/Boss_1.cpp
  Custom/Boss_2.cpp
  Custom/npc_morpher.cpp
  
  Custom/city_conquest_boss.cpp
  Custom/city_conquest_generic.cpp
  Custom/city_conquest_portal.cpp
  Custom/city_conquest_spawner.cpp
	
)

message("  -> Prepared: Custom")

