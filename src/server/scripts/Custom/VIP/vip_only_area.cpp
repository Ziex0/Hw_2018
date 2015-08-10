/*
<--------------------------------------------------------------------------->
- Developer(s): Ghostcrawler336
- Complete: 100%
- ScriptName: 'VIP only area'
- Comment: Tested & Working.
<--------------------------------------------------------------------------->
*/

#include "ScriptPCH.h"

class Vip_Access: public PlayerScript
{
private:
    static const uint32 map = 530;
	static const uint32 x = -266.1f;
	static const uint32 y = 921.734f; //need add another gps w/out -
	static const uint32 z = 84.3799f;
	static const uint32 o = 0.582604f;
	
public:
    Vip_Access() : PlayerScript("Vip_Access") {}
    
    void OnUpdateZone(Player* player, uint32 /*newZone*/, uint32 newArea)
    {
        if (newArea == 3486 && player->GetSession()->GetSecurity() == SEC_PLAYER)
        {
            player->TeleportTo(map, x, y, z, o);
            ChatHandler(player->GetSession()).PSendSysMessage("|cffff6060[Information]:|r You are not allowed to be here, you aren't a VIP!|r!");
        }
    }
};

void AddSC_Vip_Access()
{
    new Vip_Access();
}