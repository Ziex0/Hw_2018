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
    static const uint32 map = 0;
	static const uint32 x = 1610.99f;
	static const uint32 y = -5526.4f;
	static const uint32 z = 111.158f;
	static const uint32 o = 1.00078f;
public:
    Vip_Access() : PlayerScript("Vip_Access") {}
    
    void OnUpdateZone(Player* player, uint32 /*newZone*/, uint32 newArea)
    {
        if (newArea == 3486 && player->GetSession()->GetSecurity() == SEC_VIP)
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