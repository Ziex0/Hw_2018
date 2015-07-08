/*
Idea and base script by Vextah.
Help and fixes on original script by: Core surgeon & (cant remember other who initially helped but kudos)
Modified by LordPsyan
*/

#include "ScriptMgr.h"

class custom_CongratsOnLevel : public PlayerScript
{
public:
    custom_CongratsOnLevel() : PlayerScript("custom_CongratsOnLevel") { }

    void OnLevelChanged(Player* player, uint8 newLevel)
    {
        uint32 money, item, count;

        switch(++newLevel)
        {
            case 80:
        money = 100000;
        item = 60000;
        //item2 = ITEMID2;
        //spell = SPELLID;
        break;
            case 120:
        money = 150000;
        item = 60000;
        //item2 = ITEMID2;
        //spell = SPELLID;
        break;
            case 150:
        money = 200000;
        item = 60000;
        //item2 = ITEMID2;
        //spell = SPELLID;
        break;
            case 200:
        money = 250000;
        item = 60000;
        //item2 = ITEMID2;
        //spell = SPELLID;
        break;
            case 255:
        money = 350000;
        item = 60000;
        //item2 = ITEMID2;
        //spell = SPELLID;
        break;
            
            default:
        return;
        }

        std::ostringstream ss;
        ss << "|cffFF0000[Iron Knights]|r Congrats to " << player->GetName() << " on reaching level " << (uint32)newLevel;
        sWorld->SendServerMessage(SERVER_MSG_STRING, ss.str().c_str());

        std::ostringstream ss2;
        ss2 << "For your hard work and dedication you have been awarded " << money << " gold and a special item!";
        player->GetSession()->SendNotification(ss2.str().c_str());

        player->ModifyMoney(money*GOLD);
		player->AddItem(item, 400);
        //player->AddItem(item2, 1);
		//player->LearnSpell(spell, false);
    }
};

void AddSC_custom_CongratsOnLevel()

    new custom_CongratsOnLevel();
}