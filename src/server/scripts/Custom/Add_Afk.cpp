#include "Player.h"
#include "ScriptPCH.h"  
class afk_protection : public PlayerScript
{
public:
        afk_protection() : PlayerScript("afk_protection") { }
       
        bool isAFK(Player* player)
        {
                if(player->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_AFK) == true)
                        {
                                player->AddAura(58729, player);
                                return true;
                        }
                        else
                                if(player->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_AFK) == false)
                                        {
                                                player->RemoveAura(58729);
                                                return false;
                                        }
                                }
                        };
                       
                       
void AddSC_afk_protection()
{
        new afk_protection();
}