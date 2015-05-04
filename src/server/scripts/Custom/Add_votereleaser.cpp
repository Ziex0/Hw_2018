#include "ScriptPCH.h"

enum defines
{
    vote_id = 985467,
};

class Vote_releaser : public CreatureScript
{
	public:
		Vote_releaser() : CreatureScript("Vote_releaser"){}

		bool OnGossipHello(Player * pPlayer, Creature * pCreature)
		{
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Achievement_Boss_Valanar:24|t|r Release my Voting item  ", GOSSIP_SENDER_MAIN, 0);
			pPlayer->PlayerTalkClass->SendGossipMenu(9425, pCreature->GetGUID());
			return true;
		}

		bool OnGossipSelect(Player * Player, Creature * Creature, uint32 /*uiSender*/, uint32 uiAction)
		{
			if(!Player)
				return true;
				switch(uiAction)
			{
				case 0:
					if(Player->HasItemCount(vote_id, 1))
					{
						Player->DestroyItemCount(vote_id, 1, true, false);
						Player->learnSpell(70235, false);
						Player->GetSession()->SendNotification("Now you can use your voting armor!");
						Player->PlayerTalkClass->SendCloseGossip();
					}
					else
					{
						Player->GetSession()->SendNotification("You need at least one vote releaser token!");
						Player->PlayerTalkClass->SendCloseGossip();
					}
					break;
				
			}
			return true;
		}

};

void AddSC_Vote_releaser()
{
    new Vote_releaser();
}