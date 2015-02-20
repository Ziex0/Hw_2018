//Deluxe-WoW © 2014
//Made by AlexeWarr

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "Player.h"
#include "Chat.h"
#include <cstring>

#define DATABASE "deluxe_custom"

#define MIN_NUMBER 1

#define MAX_NUMBER 10

#define LOTTERY_DURATION 60000            // default 1hour

#define MIN_BET 105000                // 10 gold 50 silver 0 copper

#define MIN_PRIZE 100000            // 10 gold

#define MAX_PRIZE 150000            // 15 gold

#define INCREASE_PRIZE uint32(MIN_BET / 2)

namespace lottery
{
    bool SendMailReward(uint32 receiverGuid, uint32 money)
    {
        Player * player = sObjectAccessor->FindPlayer(receiverGuid);

        if (money <= 0)
            return false;

        std::string subject = "Lottery Reward";
        std::string text = "Congratulations for winning in the lottery!";

        MailSender sender(MAIL_NORMAL, 0, MAIL_STATIONERY_GM);

        SQLTransaction trans = CharacterDatabase.BeginTransaction();

        MailDraft(subject, text).AddMoney(money).SendMailTo(trans, MailReceiver(player ? player : NULL, receiverGuid), sender);

        CharacterDatabase.CommitTransaction(trans);

        if (player)
            ChatHandler(player->GetSession()).PSendSysMessage("Congratulations %s, you win in lottery. Please check your mailbox to pick the reward!", player->GetName());

        return true;
    }

    uint32 GetLastSessionID()
    {
        QueryResult Q = WorldDatabase.PQuery("SELECT id FROM %s.lottery_sessions WHERE finished = 0 ORDER BY id DESC LIMIT 1", DATABASE);

        return Q ? Q->Fetch()[0].GetUInt32() : 0;
    }

    uint32 GetSessionWinners()
    {
        QueryResult Q = WorldDatabase.PQuery("SELECT * FROM %s.lottery_tickets WHERE ticket_flag = 1", DATABASE);

        return Q ? Q->GetRowCount() : 0;
    }

    uint32 GetLotteryTickets()
    {
        QueryResult Q = WorldDatabase.PQuery("SELECT * FROM %s.lottery_tickets", DATABASE);

        return Q ? Q->GetRowCount() : 0;
    }

    uint32 GetLotteryJackpot()
    {
        QueryResult Q = WorldDatabase.PQuery("SELECT jackpot_prize FROM %s.lottery_sessions WHERE id = %u AND finished = 0 ORDER BY id DESC LIMIT 1", DATABASE, GetLastSessionID());

        return Q ? Q->Fetch()[0].GetUInt32() : 0;
    }

    void RewardWinners()
    {
        uint32 jackpot = GetLotteryJackpot();

        if (QueryResult Q = WorldDatabase.PQuery("SELECT guid FROM %s.lottery_tickets WHERE ticket_flag = 1", DATABASE))
        {
            do
            {
                Field * f = Q->Fetch();
                SendMailReward(f[0].GetUInt32(), jackpot);
            } while (Q->NextRow());
        }
    }

    void FinishThisSession(uint32 session_id, uint32 winners)
    {
        char msg[255];
        snprintf(msg, 255, "|cFF007eff[Lottery]|r |cffff7800Session |cffFF00FF#%u|r |cffff7800has finished, congratulations to |cffFF0000%u |cffff7800winners!", lottery::GetLastSessionID(), winners);
        sWorld->SendGlobalText(msg, NULL);

        sLog->outInfo(LOG_FILTER_GENERAL , "server.loading, LOTTERY: Session #%u has finished.", lottery::GetLastSessionID());

        RewardWinners();

        WorldDatabase.PQuery("UPDATE %s.lottery_sessions SET finished = 1, winners = %u WHERE id = %u", DATABASE, winners, session_id);
        WorldDatabase.PQuery("DELETE FROM %s.lottery_tickets", DATABASE);
    }

    bool HasPendingSession()
    {
        QueryResult Q = WorldDatabase.PQuery("SELECT * FROM %s.lottery_sessions WHERE finished = 0 ORDER BY id DESC LIMIT 1", DATABASE);

        return Q ? true : false;
    }

    std::string SessionTimeleftString()
    {
        std::string timeleft = "expired";

        uint32 t_left = 0;

        if (QueryResult Q = WorldDatabase.PQuery("SELECT schedule_date FROM %s.lottery_sessions WHERE finished = 0 ORDER BY id DESC LIMIT 1", DATABASE))
            t_left = Q->Fetch()[0].GetUInt32() - sWorld->GetGameTime();

        timeleft = secsToTimeString(t_left, false);

        return timeleft.c_str();
    }

    void StartNewSession()
    {
        uint32 win_number = urand(MIN_NUMBER, MAX_NUMBER);

        uint32 initial_prize = urand(MIN_PRIZE, MAX_PRIZE);

        WorldDatabase.PQuery("INSERT INTO %s.lottery_sessions (start_date, schedule_date, win_number, jackpot_prize) VALUES (UNIX_TIMESTAMP(), UNIX_TIMESTAMP()+%u, %u, %u)", DATABASE, LOTTERY_DURATION, win_number, initial_prize);

        char msg[255];
        snprintf(msg, 255, "|cFF007eff[Lottery] |cffff7800Session |cffff00ff#%u |cffff7800has started, you may subscribe now.", GetLastSessionID());
        sWorld->SendGlobalText(msg, NULL);

		sLog->outInfo(LOG_FILTER_GENERAL ,"server.loading, LOTTERY: New Session #%u has started.", lottery::GetLastSessionID());
    }

    bool HasAlreadyTicket(Player* player)
    {
        uint32 guid = GUID_LOPART(player->GetGUID());

        QueryResult Q = WorldDatabase.PQuery("SELECT * FROM %s.lottery_tickets WHERE guid = %u", DATABASE, guid);

        return Q ? true : false;
    }

    uint32 TicketFlag(uint32 number)
    {
        QueryResult Q = WorldDatabase.PQuery("SELECT * FROM %s.lottery_sessions WHERE win_number = %u ORDER BY id DESC LIMIT 1", DATABASE, number);

        return Q ? 1 : 0;
    }

    void IncreaseWinPrize()
    {
        WorldDatabase.PQuery("UPDATE %s.lottery_sessions SET jackpot_prize = (jackpot_prize + %u)", DATABASE, INCREASE_PRIZE);
        sLog->outInfo(LOG_FILTER_GENERAL ,"server.loading, LOTTERY: Session #%u has jackpot increased by %u gold.", lottery::GetLastSessionID(), INCREASE_PRIZE / GOLD);
    }

    void InsertTicket(Player* player, uint32 number)
    {
        uint32 guid = GUID_LOPART(player->GetGUID());

        if (HasAlreadyTicket(player))
            return;

        WorldDatabase.PQuery("INSERT INTO %s.lottery_tickets (guid, number, ticket_flag) VALUES (%u, %u, %u)", DATABASE, guid, number, TicketFlag(number));

        player->GetSession()->SendAreaTriggerMessage("Your number |cFFff00ff%u|r, Good Luck!", number);

        sLog->outInfo(LOG_FILTER_GENERAL ,"server.loading, LOTTERY: Player [%s] joined session #%u with number %u.", player->GetName().c_str(), lottery::GetLastSessionID(), number);

        IncreaseWinPrize();
    }
}

enum Lottery_sessions {
    LE_ANNOUNCE_WINNERS = 1,
    LE_MAX
};

class Lottery_pScript : public PlayerScript
{
public: Lottery_pScript() : PlayerScript("Lottery_pScript") { }

    void OnLogin(Player* player /*player*/) 
    {
        if (lottery::HasPendingSession())
        {
            player->GetSession()->SendAreaTriggerMessage("Lottery session |cffFF00FF#%u|r expires in %s", lottery::GetLastSessionID(), lottery::SessionTimeleftString().c_str());
            ChatHandler(player->GetSession()).PSendSysMessage("Lottery session |cffFF00FF#%u|r expires in %s", lottery::GetLastSessionID(), lottery::SessionTimeleftString().c_str());
        }
    }
};

class Lottery_System : public WorldScript
{
public: Lottery_System() : WorldScript("Lottery_System") { }

        void OnStartup() 
        {
            if (lottery::HasPendingSession()) // continue last session
            {
                QueryResult Q = WorldDatabase.PQuery("SELECT schedule_date FROM %s.lottery_sessions WHERE finished = 0 ORDER BY id DESC LIMIT 1", DATABASE);

                uint32 sc_date = Q ? Q->Fetch()[0].GetUInt32() : 0;

                if (sWorld->GetGameTime() < sc_date) // if pending session not expired
                {
                    uint32 left_time = sc_date - sWorld->GetGameTime();

                    Events.ScheduleEvent(LE_ANNOUNCE_WINNERS, left_time * IN_MILLISECONDS);

                   sLog->outInfo(LOG_FILTER_GENERAL ,"server.loading, LOTTERY: Session #%u is on pending, timeleft %s.", lottery::GetLastSessionID(), secsToTimeString(left_time, false).c_str());
                }
                else // if pending session already expired, then reward players, finish session, start a new session
                {
                   sLog->outInfo(LOG_FILTER_GENERAL ,"server.loading, LOTTERY: Pending session #%u expired.", lottery::GetLastSessionID());

                    lottery::FinishThisSession(lottery::GetLastSessionID(), lottery::GetSessionWinners());

                    lottery::StartNewSession();

                    Events.ScheduleEvent(LE_ANNOUNCE_WINNERS, LOTTERY_DURATION * IN_MILLISECONDS);
                }
            }
            else
            {
                lottery::StartNewSession();
                Events.ScheduleEvent(LE_ANNOUNCE_WINNERS, LOTTERY_DURATION * IN_MILLISECONDS);
            }
        }

        void OnUpdate(uint32 diff)
        {
            Events.Update(diff);
            while (uint32 eventId = Events.ExecuteEvent())
            {
                if (eventId == LE_ANNOUNCE_WINNERS)
                {
                    lottery::FinishThisSession(lottery::GetLastSessionID(), lottery::GetSessionWinners());

                    lottery::StartNewSession();

                    Events.ScheduleEvent(LE_ANNOUNCE_WINNERS, LOTTERY_DURATION * IN_MILLISECONDS);
                }
            }
        }

private:
    EventMap Events;
};

class Lottery_Gossip : public CreatureScript
{
public:
    Lottery_Gossip() : CreatureScript("Lottery_Gossip") { }

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        if (lottery::HasAlreadyTicket(player))
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Already subscribed!", GOSSIP_SENDER_MAIN, 0);
        }
        else
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_CHAT, "Pay Ticket", GOSSIP_SENDER_MAIN, 1, "There is the ticket price my friend, Good Luck!", MIN_BET, true);

        player->PlayerTalkClass->SendGossipMenu(907, creature->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action) override
    {
        player->PlayerTalkClass->ClearMenus();

        player->CLOSE_GOSSIP_MENU();

        return true;
    }

    bool OnGossipSelectCode(Player* player, Creature* creature, uint32 sender, uint32 action, char const* code) override
    {
        player->PlayerTalkClass->ClearMenus();

        uint32 p_number = atoi(code);

        if (!lottery::HasAlreadyTicket(player))
        {
            if (player->GetMoney() >= MIN_BET)
            {
                if (p_number && (p_number >= MIN_NUMBER && p_number <= MAX_NUMBER))
                {
                    player->SetMoney(player->GetMoney() - uint32(MIN_BET));
                    lottery::InsertTicket(player, p_number);
                }
                else
                    player->GetSession()->SendAreaTriggerMessage("Must be between %u and %u! Please try again.", MIN_NUMBER, MAX_NUMBER);
            }
            // else not enough money
        }
        // else has ticket

        player->CLOSE_GOSSIP_MENU();
        return false;
    }
};


void AddSC_Pro_Lottery()
{
    new Lottery_pScript();
    new Lottery_System();
    new Lottery_Gossip();
}