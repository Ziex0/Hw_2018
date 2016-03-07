#include "ScriptPCH.h"
#include "Language.h"
#include "Chat.h"

class vpredeem : public CreatureScript
{
    public:

        vpredeem()
            : CreatureScript("vpredeem")
        {
        }

        bool OnGossipHello(Player* pPlayer, Creature* pCreature)
        {
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Give me Upgrade Vote token", GOSSIP_SENDER_MAIN, 7000);
			//pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Exchange my Demon Head", GOSSIP_SENDER_MAIN, 8000);
            
            pPlayer->PlayerTalkClass->SendGossipMenu(85007, pCreature->GetGUID());

            return true;
        }

        bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
        {
            pPlayer->PlayerTalkClass->ClearMenus();

            switch (uiAction)
            {
            case 7000:
                pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Give me 10 Vp - 100 Star Coin", GOSSIP_SENDER_MAIN, 7001);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Give me 20 Vp - 200 Star Coin", GOSSIP_SENDER_MAIN, 7002);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Give me 30 Vp - 300 Star Coin", GOSSIP_SENDER_MAIN, 7003);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Give me 40 Vp - 400 Star Coin", GOSSIP_SENDER_MAIN, 7004);
				pPlayer->PlayerTalkClass->SendGossipMenu(85007, pCreature->GetGUID());
                return true;
                break;
				
			case 8000:
                pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Give me 1  SC - 500 DH", GOSSIP_SENDER_MAIN, 8001);
				//pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Give me 10 Dp - 200 Vote Points", GOSSIP_SENDER_MAIN, 8002);
				//pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Give me 15 Dp - 300 Vote Points", GOSSIP_SENDER_MAIN, 8003);
				//pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Give me 20 Dp - 400 Vote Points", GOSSIP_SENDER_MAIN, 8004);
				pPlayer->PlayerTalkClass->SendGossipMenu(85007, pCreature->GetGUID());
                return true;
                break;
				
		case 7001:
				if(pPlayer->HasItemCount(340006, 100))
		{
			pPlayer->DestroyItemCount(340006, 100, true);
			LoginDatabase.PQuery("Update sitez.accounts_more Set vp = vp + 10 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			char str[200];
			sprintf(str,"Success. Your Star Coin item has been removed and your points has been added.Check your vp for detail !!");
                pPlayer->MonsterWhisper(str,pPlayer->GetGUID(),true);        
		} 
		else
			{
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
			}
   		  break;
		  
		case 7002:
			if(pPlayer->HasItemCount(340006, 200))
		{
			
			pPlayer->DestroyItemCount(340006, 200, true);
			LoginDatabase.PQuery("Update sitez.accounts_more Set vp = vp + 20 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			char str[200];
			sprintf(str,"Success. Your Star Coin item has been removed and your points has been added.Check your vp for detail !!");
                pPlayer->MonsterWhisper(str,pPlayer->GetGUID(),true);
                
		} else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;

		case 7003:
			if(pPlayer->HasItemCount(340006, 300))
		{
			
			pPlayer->DestroyItemCount(340006, 300, true);
			LoginDatabase.PQuery("Update sitez.accounts_more Set vp = vp + 30 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			char str[200];
			sprintf(str,"Success. Your Star Coin item has been removed and your points has been added.Check your vp for detail !!");
                pPlayer->MonsterWhisper(str,pPlayer->GetGUID(),true);
                
		} else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;

		case 7004:
			if(pPlayer->HasItemCount(340006, 400))
		{			
			pPlayer->DestroyItemCount(340006, 400, true);
			LoginDatabase.PQuery("Update sitez.accounts_more Set vp = vp + 40 WHERE id = '%u'", pPlayer->GetSession()->GetAccountId());
			char str[200];
			sprintf(str,"Success. Your Star Coin item has been removed and your points has been added.Check your vp for detail !!");
                pPlayer->MonsterWhisper(str,pPlayer->GetGUID(),true);
                
		} else {
			pPlayer->GetSession()->SendNotification("Failed. Make sure you have the desired item");
			pPlayer->PlayerTalkClass->SendCloseGossip();
		  }
   		  break;		  
	    }
		
		return true;
			
     }
};

void AddSC_vpredeem()
{
    new vpredeem();
}