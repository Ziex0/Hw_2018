#include "Language.h"
#include "World.h"
//#include "AuctionHouseMgr.h"

class premium_commandscript : public CommandScript
{
public:
    premium_commandscript() : CommandScript("premium_commandscript") { }

    ChatCommand* GetCommands() const
    {
        static ChatCommand premiumCommandTable[] =
        {
            { "bank",  SEC_PLAYER, false, &HandlePremiumBankCommand,    "", NULL },
            { "mail",  SEC_PLAYER, false, &HandlePremiumMailCommand,    "", NULL },
            //{ "auc",  SEC_PLAYER,  false, &HandlePremiumAuctionCommand, "", NULL },
            { NULL,    0,          false, NULL,                         "", NULL }
        };

        static ChatCommand commandTable[] =
        {
            { "vip", SEC_PLAYER, false, NULL, "", premiumCommandTable },
            { NULL,  0,          false, NULL, "", NULL }
        };

        return commandTable;
    }

    static bool HandlePremiumBankCommand(ChatHandler* handler, char const* /*args*/)
    {
        Player *player = handler->GetSession()->GetPlayer();
        if (player->GetSession()->IsPremium() && sWorld->getBoolConfig(COMMAND_BANK_PREMIUM))
        {
            //Different Checks
            if (player->isInCombat() || player->isInFlight() || player->GetMap()->IsBattlegroundOrArena() || player->HasStealthAura() || player->HasFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH) || player->isDead())
            {
                handler->SendSysMessage(LANG_PREMIUM_CANT_DO);
                handler->SetSentErrorMessage(true);
                return false;
            }

            handler->GetSession()->SendShowBank(handler->GetSession()->GetPlayer()->GetGUID());
        }
        return true;
    }

    static bool HandlePremiumMailCommand(ChatHandler* handler, char const* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();
        if (player->GetSession()->IsPremium() && sWorld->getBoolConfig(COMMAND_MAIL_PREMIUM))
        {
            //Different Checks
            if (player->isInCombat() || player->isInFlight() || player->GetMap()->IsBattlegroundOrArena() || player->HasStealthAura() || player->HasFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH) || player->isDead())
            {
                handler->SendSysMessage(LANG_PREMIUM_CANT_DO);
                handler->SetSentErrorMessage(true);
                return false;
            }

            handler->GetSession()->SendShowMailBox(player->GetGUID());
        }
        return true;
    }

    //static bool HandlePremiumAuctionCommand(ChatHandler* handler, char const* /*args*/)
    //{
        //Player* player = handler->GetSession()->GetPlayer();
        //if(player->GetSession()->IsPremium())
        //{
            //Different Checks
            //if(player->isInCombat() || player->isInFlight() || player->GetMap()->IsBattlegroundOrArena() || player->HasStealthAura() || player->HasFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH) || player->isDead())
            //{
            //    handler->SendSysMessage(LANG_PREMIUM_CANT_DO);
            //    handler->SetSentErrorMessage(true);
            //    return false;
            //}

            //handler->GetSession()->SendAuctionHello(player->GetGUID());
            //handler->GetSession()->SendAuctionHello(player->getFaction());

        //}
        //return true;
    //}

};

void AddSC_premium_commandscript()
{
    new premium_commandscript();
}