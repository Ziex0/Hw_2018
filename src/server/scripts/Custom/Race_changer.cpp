#include "ScriptPCH.h"
#include "GuildMgr.h"
#include "Chat.h"
#include "ReputationMgr.h"
 
#define token_id 30
#define token_count 1
 
class RaceChanger : public CreatureScript
{
public:
    RaceChanger() : CreatureScript("RaceChanger") { }
 
    bool OnGossipHello(Player* Plr, Creature* pObject)
    {
       if(Plr->GetSession())
        {
			//Plr->ADD_GOSSIP_ITEM( 0, "Change my gender", 0, 99 );
            Plr->ADD_GOSSIP_ITEM( 0, "|cff00ff00|TInterface\\icons\\Achievement_Boss_Valanar:24|t|rChange me Into Human", 0, 1 );
            Plr->ADD_GOSSIP_ITEM( 0, "|cff00ff00|TInterface\\icons\\Achievement_Boss_Valanar:24|t|rChange me Into NightElf", 0, 4 );
            Plr->ADD_GOSSIP_ITEM( 0, "|cff00ff00|TInterface\\icons\\Achievement_Boss_Valanar:24|t|rChange me Into Dwarf", 0, 3 );
            Plr->ADD_GOSSIP_ITEM( 0, "|cff00ff00|TInterface\\icons\\Achievement_Boss_Valanar:24|t|rChange me Into Gnome", 0, 7 );
            Plr->ADD_GOSSIP_ITEM( 0, "|cff00ff00|TInterface\\icons\\Achievement_Boss_Valanar:24|t|rChange me Into Draenei", 0, 11 );
            Plr->ADD_GOSSIP_ITEM( 0, "|cff00ff00|TInterface\\icons\\Achievement_Boss_Valanar:24|t|rChange me Into Orc", 0, 2 );
            Plr->ADD_GOSSIP_ITEM( 0, "|cff00ff00|TInterface\\icons\\Achievement_Boss_Valanar:24|t|rChange me Into Undead", 0, 5 );
            Plr->ADD_GOSSIP_ITEM( 0, "|cff00ff00|TInterface\\icons\\Achievement_Boss_Valanar:24|t|rChange me Into Tauren", 0, 6 );
            Plr->ADD_GOSSIP_ITEM( 0, "|cff00ff00|TInterface\\icons\\Achievement_Boss_Valanar:24|t|rChange me Into Troll", 0, 8 );
			Plr->ADD_GOSSIP_ITEM( 0, "|cff00ff00|TInterface\\icons\\Achievement_Boss_Valanar:24|t|rChange me Into Blood Elf", 0, 10 );
			Plr->ADD_GOSSIP_ITEM( 0, "|cff00ff00|TInterface\\icons\\Achievement_Boss_Valanar:24|t|rChange me Into Worgen", 0, 21 );
			Plr->ADD_GOSSIP_ITEM( 0, "|cff00ff00|TInterface\\icons\\Achievement_Boss_Valanar:24|t|rChange me Into Goblin", 0, 9 );
			
        }
        else
        {
            Plr->GetSession()->SendNotification("You can not use this right now");
            return false;
        }
			Plr->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pObject->GetGUID());
        return true;
    }
 
    bool OnGossipSelect(Player* Plr, Creature* pObject, uint32 Id, uint32 IntId)
    {
		switch(IntId)
		{
		case 99:
			uint8 gender;
			if(Plr->getGender() == 1)
				gender = 2;
			else
				gender = 1;
			// Set gender
			Plr->SetByteValue(UNIT_FIELD_BYTES_0, 2, gender);
			Plr->SetByteValue(PLAYER_BYTES_3, 0, gender);
			break;	
					default:
			
			if(Plr->GetSession() && Plr->HasItemCount(token_id, token_count, false))
			{
            //remove token
            Plr->DestroyItemCount(token_id, 1, true, false);
 
            uint8 race, race_old, class_, gender;
            Powers powertype;
            // TeamId team;
            race_old = race = IntId; // what are these for? Shouldnt they be different?
                   
            Plr->setFactionForRace(race);
            class_ = Plr->getClass();
            gender = Plr->getGender();
            powertype = Plr->getPowerType();
            // team = Plr->GetTeamId();
                   
            const PlayerInfo* info = sObjectMgr->GetPlayerInfo(race, class_);
            if (!info)
                return true;
                   
            Plr->SetFloatValue(OBJECT_FIELD_SCALE_X, ((race==RACE_TAUREN)?1.3f:1.0f));
            // Plr->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, info->factiontemplate ); // handled by setFactionForRace
            Plr->SetUInt32Value(UNIT_FIELD_BYTES_0, ( ( race ) | ( class_ << 8 ) | ( gender << 16 ) | ( powertype << 24 ) ) );
            Plr->SetUInt32Value(UNIT_FIELD_DISPLAYID, gender ? info->displayId_f : info->displayId_f );
            Plr->SetUInt32Value(UNIT_FIELD_NATIVEDISPLAYID, gender ? info->displayId_f : info->displayId_f );
                   
            // Different races have different number of visuals
            Plr->SetUInt32Value(PLAYER_BYTES, ((urand(0,5))|(urand(0,5)<<8)|(urand(0,5)<<16)|(urand(0,5)<<24))); // urand were RandomUInt. Might not exist in Trinitycore. Not sure what it does either.
            Plr->SetUInt32Value(PLAYER_BYTES_2, (( !gender ? 0 : urand(0,3) ) | (0x02 << 24))); // gender right?
            //Plr->SetUInt32Value(PLAYER_BYTES, ((skin) | (face << 8) | (hairStyle << 16) | (hairColor << 24)));
            //Plr->SetUInt32Value(PLAYER_BYTES_2, (facialHair | (0x02 << 24)));
                   
            Plr->SetUInt32Value(PLAYER_FIELD_WATCHED_FACTION_INDEX, 0xEEEEEEEE);
            //dump reputation data
            FactionStateList m_tempRepMap;
            //store neutral
            for(uint32 i = 0; i < sFactionStore.GetNumRows(); ++i)
            {
                const FactionEntry * f = sFactionStore.LookupEntry(i);
                if(f == 0) continue;
                if( Plr->GetReputation(f->ID) &&
                    f->team != 67 && f->team != 469 && // ream = parentFaction ?
                    f->team != 892 && f->team != 891 &&
                    f->ID != 947 && f->ID != 946 &&
                    f->ID != 892 && f->ID != 891 &&
                    f->ID != 941 && f->ID != 978 &&
                    f->ID != 922
                    )
                {
                    const ReputationMgr & repMgr = Plr->GetReputationMgr();
                    FactionState * rep = new FactionState;
                    /*
                    rep->Flags = 0;
                    rep->Standing = repMgr.GetReputation(f->ID);
                    rep->base = repMgr.GetBaseReputation(f->ID);
                    */
                    FactionState newFaction;
                    newFaction.ID = f->ID;
                    newFaction.ReputationListID = f->reputationListID;
                    newFaction.Standing = repMgr.GetReputation(f->ID);
                    newFaction.Flags = 0;
                    newFaction.needSend = true;
                    newFaction.needSave = true;
                   
                    m_tempRepMap[f->ID] = newFaction; // newFaction.ReputationListID or f->ID?
                }
            }
                   
            Plr->GetReputationMgr().SendInitialReputations(); // does this initialize the rep values?
                   
            for(FactionStateList::iterator itr = m_tempRepMap.begin(); itr != m_tempRepMap.end(); ++itr)
            {
                Plr->SetReputation(itr->first, itr->second.Standing );
                //delete itr->second;
            }
                   
            // Plr->(); // _RemoveLanguages See CharacterHandler.cpp 1736 line ?
            // Seems like languages are handled automatically.
                   
            //remove racial spells along with all starting spells then add them for new race
            const PlayerInfo* old_info = sObjectMgr->GetPlayerInfo(race_old, class_);
            if (!old_info)
                return true;
                   
            for(PlayerCreateInfoSpells::const_iterator sp = old_info->spell.begin(); sp != old_info->spell.end(); sp++) // spell_list
                if (Plr->HasSpell(*sp)) Plr->removeSpell((*sp), false, false);
                   
            for(PlayerCreateInfoSpells::const_iterator sp = info->spell.begin(); sp != info->spell.end(); sp++)
                Plr->addSpell((*sp), true, true, true, false);
                   
            // Shouldnt we also take into account if the faction changes?
            if (Plr->GetGuildId())
            {
                Guild *pGuild = sGuildMgr->GetGuildById( Plr->GetGuildId() );
                   
                if(pGuild && pGuild->GetLeaderGUID() != Plr->GetGUID() )
                {
                    pGuild->DeleteMember(Plr->GetGUID());
                    /*Plr->L SetGuildId(0);
                    Plr->SetGuildRank(0);
                    pGuild->RemoveGuildMember(Plr->m_playerInfo, NULL);
                   
                    WorldPacket data(100);
                    data.Initialize(SMSG_GUILD_EVENT);
                    data << uint8(GUILD_EVENT_LEFT);
                    data << uint8(1);
                    data << Plr->GetName();
                    pGuild->SendPacket(&data);
                    */
                }
            }
                   
            Plr->SaveToDB(false);
            // ChatHandler(Plr).PSendSysMessage("Signed in blood. There is no going back now ...");
            // ChatHandler(Plr).PSendSysMessage("Relog ...");
            //force relog
            Plr->GetSession()->KickPlayer(); // instant kick, cant be bothered to make it delayed.
            Plr->CLOSE_GOSSIP_MENU();
				}
				else
				{
					Plr->GetSession()->SendAreaTriggerMessage("You dont have that token");
					}
			break;
		}
         
        return true;
    }
};
 
void AddSC_RaceChanger()
{
    new RaceChanger();
}