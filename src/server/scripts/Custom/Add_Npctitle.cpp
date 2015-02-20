#include "ScriptPCH.h"
#include "Language.h"
#include "ArenaTeamMgr.h"


enum eRanks
{
	PRIVATE = 1,
	CORPORAL = 2,
	SERGEANT = 3,
	MASTER_SERGEANT = 4,
	SERGEANT_MAJOR = 5,
	KNIGHT = 6,
	KNIGHT_LIEUTENANT = 7,
	KNIGHT_CAPTAIN = 8,
	KNIGHT_CHAMPION = 9,
	LIEUTENANT_COMMANDER = 10,
	COMMANDER = 11,
	MARSHAL = 12,
	FIELD_MARSHAL = 13,
	GRAND_MARSHAL = 14,
	SCOUT = 15,
	GRUNT = 16,
	SERGEANT_H = 17,
	SENIOR_SERGEANT = 18,
	FIRST_SERGEANT = 19,
	STONE_GUARD = 20,
	BLOOD_GUARD = 21,
	LEGIONNAIRE = 22,
	CENTURION = 23,
	CHAMPION = 24,
	LIEUTENANT_GENERAL = 25,
	GENERAL = 26,
	WARLORD = 27,
	HIGH_WARLORD = 28,
};

enum eKills
{
	KILLS_1 = 1,
	KILLS_2 = 50,
	KILLS_3 = 100,
	KILLS_4 = 250,
	KILLS_5 = 500,
	KILLS_6 = 750,
	KILLS_7 = 1000,
	KILLS_8 = 1500,
	KILLS_9 = 3000,
	KILLS_10 = 5000,
	KILLS_11 = 7500,
	KILLS_12 = 10000,
	KILLS_13 = 15000,
	KILLS_14 = 30000,
};


class universal_npc : public CreatureScript //titles vendor
{
   public:
	   universal_npc() : CreatureScript("universal_npc") { }

	   bool OnGossipHello(Player * player, Creature * _creature)
	   {
		   player->PlayerTalkClass->ClearMenus();
		   if (player->GetTeam() == HORDE)
			   player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "|TInterface/icons/Achievement_Arena_2v2_2:30|tPVP Titles", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
		   else
			   player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "|TInterface/icons/Achievement_Arena_2v2_2:30|tPVP Titles", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2); 
		   		     
		   player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "|TInterface/icons/Achievement_BG_DefendXtowers_AV:30|tReset MMR", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
		   player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Nevermind", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+99); 
		   player->PlayerTalkClass->SendGossipMenu(1, _creature->GetGUID());
		   
		   return true;
	   }

	   bool OnGossipSelect(Player * player, Creature * _creature, uint32 sender, uint32 actions)
	   {
		   ArenaTeamMember* member = NULL;
		   ArenaTeam* arena_team = NULL;
		   uint8 slot;
		   player->PlayerTalkClass->ClearMenus();
		   if(sender == GOSSIP_SENDER_MAIN)
		   {
			   switch(actions)
			   {		   
			    case GOSSIP_ACTION_INFO_DEF+1:
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "SCOUT.(1 Kill)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "GRUNT.(50 Kills)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "SERGEANT_H.(100 Kills)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "SENIOR_SERGEANT.(250 Kills)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "FIRST_SERGEANT.(500 Kills)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 14);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "STONE_GUARD.(750 Kills)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 15);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "BLOOD_GUARD.(1000 Kills)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 16);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "LEGIONNAIRE.(1500 Kills)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 17);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "CENTURION.(3000 Kills)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 18);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "CHAMPION.(5000 Kills)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 19);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "LIEUTENANT_GENERAL.(7500 Kills)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 20);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "GENERAL.(10000 Kills)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 21);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "WARLORD.(15000 Kills)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 22);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "HIGH_WARLORD.(30000 Kills)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 23);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Nevermind", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+99); 
				player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _creature->GetGUID());
				break;
				
                case GOSSIP_ACTION_INFO_DEF+2:
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "PRIVATE.(1 Kill)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 30);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "CORPORAL.(50 Kills)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 31);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "SERGEANT.(100 Kills)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 32);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "MASTER_SERGEANT.(250 Kills)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 33);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "SERGEANT_MAJOR.(500 Kills)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 34);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "KNIGHT.(750 Kills)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 35);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "KNIGHT_LIEUTENANT.(1000 Kills)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 36);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "KNIGHT_CAPTAIN.(1500 Kills)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 37);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "KNIGHT_CHAMPION.(3000 Kills)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 38);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "LIEUTENANT_COMMANDER.(5000 Kills)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 39);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "COMMANDER.(7500 Kills)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 40);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "MARSHAL.(10000 Kills)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 41);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "FIELD_MARSHAL.(15000 Kills)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 42);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "GRAND_MARSHAL.(30000 Kills)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 43);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Nevermind", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+99); 
				player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _creature->GetGUID());
				break;

				
												
				case GOSSIP_ACTION_INFO_DEF + 7:
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Reset 1v1 MMR", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 49);
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Reset 2v2 MMR", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 50);
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Reset 3v3 MMR", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 51);
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Reset 5v5 MMR", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 52);
					player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _creature->GetGUID());
					break;
				
				case GOSSIP_ACTION_INFO_DEF + 49:
				case GOSSIP_ACTION_INFO_DEF + 50:
				case GOSSIP_ACTION_INFO_DEF + 51:
				case GOSSIP_ACTION_INFO_DEF + 52:
					slot = actions - GOSSIP_ACTION_INFO_DEF - 49;
					arena_team = sArenaTeamMgr->GetArenaTeamById(player->GetArenaTeamId(slot));
					if( ! arena_team)
					{
						_creature->MonsterWhisper("You dont have team.", player->GetGUID());
						OnGossipHello(player, _creature);
						break;
					}
					member = arena_team->GetMember(player->GetGUID());
					if ( ! member)
					{
						_creature->MonsterWhisper("Error Cant Find Member(tell gm about this).", player->GetGUID());
						player->PlayerTalkClass->SendCloseGossip();
						break;
					}
					if(member->MatchMakerRating != sWorld->getIntConfig(CONFIG_ARENA_START_MATCHMAKER_RATING))
					{
						member->ModifyMatchmakerRating(sWorld->getIntConfig(CONFIG_ARENA_START_MATCHMAKER_RATING) - member->MatchMakerRating, slot);
						_creature->MonsterWhisper("Your MMR successfuly reset.", player->GetGUID());
					}
					else
						_creature->MonsterWhisper("Your MMR is already reset.", player->GetGUID());

					OnGossipHello(player, _creature);
					break;			
				  
				case GOSSIP_ACTION_INFO_DEF+10:
                if(player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS)>=1)
				    player->SetTitle(sCharTitlesStore.LookupEntry(SCOUT));
				    else 
					_creature->MonsterWhisper("You don't have enough Life Time Kills!!", player->GetGUID());
				break;
				
				case GOSSIP_ACTION_INFO_DEF+11:
                if(player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS)>=50)
				    player->SetTitle(sCharTitlesStore.LookupEntry(GRUNT));
				    else 
					_creature->MonsterWhisper("You don't have enough Life Time Kills!!", player->GetGUID());
				break;
				
				case GOSSIP_ACTION_INFO_DEF+12:
                if(player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS)>=100)
				    player->SetTitle(sCharTitlesStore.LookupEntry(SERGEANT_H));
				    else 
					_creature->MonsterWhisper("You don't have enough Life Time Kills!!", player->GetGUID());
				break;
				
				case GOSSIP_ACTION_INFO_DEF+13:
                if(player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS)>=250)
				    player->SetTitle(sCharTitlesStore.LookupEntry(SENIOR_SERGEANT));
				    else 
					_creature->MonsterWhisper("You don't have enough Life Time Kills!!", player->GetGUID());
				break;
				
				case GOSSIP_ACTION_INFO_DEF+14:
                if(player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS)>=500)
				    player->SetTitle(sCharTitlesStore.LookupEntry(FIRST_SERGEANT));
				    else 
					_creature->MonsterWhisper("You don't have enough Life Time Kills!!", player->GetGUID());
				break;
				
				case GOSSIP_ACTION_INFO_DEF+15:
                if(player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS)>=750)
				    player->SetTitle(sCharTitlesStore.LookupEntry(STONE_GUARD));
				    else 
					_creature->MonsterWhisper("You don't have enough Life Time Kills!!", player->GetGUID());
				break;
				
				case GOSSIP_ACTION_INFO_DEF+16:
                if(player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS)>=1000)
				    player->SetTitle(sCharTitlesStore.LookupEntry(BLOOD_GUARD));
				    else 
					_creature->MonsterWhisper("You don't have enough Life Time Kills!!", player->GetGUID());
				break;
				
				case GOSSIP_ACTION_INFO_DEF+17:
                if(player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS)>=1500)
				    player->SetTitle(sCharTitlesStore.LookupEntry(LEGIONNAIRE));
				    else 
					_creature->MonsterWhisper("You don't have enough Life Time Kills!!", player->GetGUID());
				break;
				
				case GOSSIP_ACTION_INFO_DEF+18:
                if(player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS)>=3000)
				    player->SetTitle(sCharTitlesStore.LookupEntry(CENTURION));
				    else 
					_creature->MonsterWhisper("You don't have enough Life Time Kills!!", player->GetGUID());
				break;
				
				case GOSSIP_ACTION_INFO_DEF+19:
                if(player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS)>=5000)
				    player->SetTitle(sCharTitlesStore.LookupEntry(CHAMPION));
				    else 
					_creature->MonsterWhisper("You don't have enough Life Time Kills!!", player->GetGUID());
				break;
				
				case GOSSIP_ACTION_INFO_DEF+20:
                if(player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS)>=7500)
				    player->SetTitle(sCharTitlesStore.LookupEntry(LIEUTENANT_GENERAL));
				    else 
					_creature->MonsterWhisper("You don't have enough Life Time Kills!!", player->GetGUID());
				break;
				
				case GOSSIP_ACTION_INFO_DEF+21:
                if(player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS)>=10000)
				    player->SetTitle(sCharTitlesStore.LookupEntry(GENERAL));
				    else 
					_creature->MonsterWhisper("You don't have enough Life Time Kills!!", player->GetGUID());
				break;
				
				case GOSSIP_ACTION_INFO_DEF+22:
                if(player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS)>=15000)
				    player->SetTitle(sCharTitlesStore.LookupEntry(WARLORD));
				    else 
					_creature->MonsterWhisper("You don't have enough Life Time Kills!!", player->GetGUID());
				break;
				
				case GOSSIP_ACTION_INFO_DEF+23:
                if(player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS)>=30000)
				    player->SetTitle(sCharTitlesStore.LookupEntry(HIGH_WARLORD));
				    else 
					_creature->MonsterWhisper("You don't have enough Life Time Kills!!", player->GetGUID());
				break;
				
				case GOSSIP_ACTION_INFO_DEF+30:
                if(player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS)>=1)
				    player->SetTitle(sCharTitlesStore.LookupEntry(PRIVATE));
				    else 
					_creature->MonsterWhisper("You don't have enough Life Time Kills!!", player->GetGUID());
				break;
				
				case GOSSIP_ACTION_INFO_DEF+31:
                if(player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS)>=50)
				    player->SetTitle(sCharTitlesStore.LookupEntry(CORPORAL));
				    else 
					_creature->MonsterWhisper("You don't have enough Life Time Kills!!", player->GetGUID());
				break;
				
				case GOSSIP_ACTION_INFO_DEF+32:
                if(player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS)>=100)
				    player->SetTitle(sCharTitlesStore.LookupEntry(SERGEANT));
				    else 
					_creature->MonsterWhisper("You don't have enough Life Time Kills!!", player->GetGUID());
				break;
				
				case GOSSIP_ACTION_INFO_DEF+33:
                if(player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS)>=250)
				    player->SetTitle(sCharTitlesStore.LookupEntry(MASTER_SERGEANT));
				    else 
					_creature->MonsterWhisper("You don't have enough Life Time Kills!!", player->GetGUID());
				break;
				
				case GOSSIP_ACTION_INFO_DEF+34:
                if(player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS)>=500)
				    player->SetTitle(sCharTitlesStore.LookupEntry(SERGEANT_MAJOR));
				    else 
					_creature->MonsterWhisper("You don't have enough Life Time Kills!!", player->GetGUID());
				break;
				
				case GOSSIP_ACTION_INFO_DEF+35:
                if(player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS)>=750)
				    player->SetTitle(sCharTitlesStore.LookupEntry(KNIGHT));
				    else 
					_creature->MonsterWhisper("You don't have enough Life Time Kills!!", player->GetGUID());
				break;
				
				case GOSSIP_ACTION_INFO_DEF+36:
                if(player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS)>=1000)
				    player->SetTitle(sCharTitlesStore.LookupEntry(KNIGHT_LIEUTENANT));
				    else 
					_creature->MonsterWhisper("You don't have enough Life Time Kills!!", player->GetGUID());
				break;
				
				case GOSSIP_ACTION_INFO_DEF+37:
                if(player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS)>=1500)
				    player->SetTitle(sCharTitlesStore.LookupEntry(KNIGHT_CAPTAIN));
				    else 
					_creature->MonsterWhisper("You don't have enough Life Time Kills!!", player->GetGUID());
				break;
				
				case GOSSIP_ACTION_INFO_DEF+38:
                if(player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS)>=3000)
				    player->SetTitle(sCharTitlesStore.LookupEntry(KNIGHT_CHAMPION));
				    else 
					_creature->MonsterWhisper("You don't have enough Life Time Kills!!", player->GetGUID());
				break;
				
				case GOSSIP_ACTION_INFO_DEF+39:
                if(player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS)>=5000)
				    player->SetTitle(sCharTitlesStore.LookupEntry(LIEUTENANT_COMMANDER));
				    else 
					_creature->MonsterWhisper("You don't have enough Life Time Kills!!", player->GetGUID());
				break;
				
				case GOSSIP_ACTION_INFO_DEF+40:
                if(player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS)>=7500)
				    player->SetTitle(sCharTitlesStore.LookupEntry(COMMANDER));
				    else 
					_creature->MonsterWhisper("You don't have enough Life Time Kills!!", player->GetGUID());
				break;
				
				case GOSSIP_ACTION_INFO_DEF+41:
                if(player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS)>=10000)
				    player->SetTitle(sCharTitlesStore.LookupEntry(MARSHAL));
				    else 
					_creature->MonsterWhisper("You don't have enough Life Time Kills!!", player->GetGUID());
				break;
				
				case GOSSIP_ACTION_INFO_DEF+42:
                if(player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS)>=15000)
				    player->SetTitle(sCharTitlesStore.LookupEntry(FIELD_MARSHAL));
				    else 
					_creature->MonsterWhisper("You don't have enough Life Time Kills!!", player->GetGUID());
				break;
				
				case GOSSIP_ACTION_INFO_DEF+43:
                if(player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS)>=30000)
				    player->SetTitle(sCharTitlesStore.LookupEntry(GRAND_MARSHAL));
				    else 
					_creature->MonsterWhisper("You don't have enough Life Time Kills!!", player->GetGUID());
				break;
				
				case GOSSIP_ACTION_INFO_DEF+99:
					player->PlayerTalkClass->SendCloseGossip();
				break;
			   }
		   }
		   return true;
	   }
};


void AddSC_universal_npc()
{
        
		new universal_npc;
		
}