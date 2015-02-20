#include "ScriptPCH.h"
#include "WeatherMgr.h"
 
class on_gossip_change_weather : public CreatureScript
{
public:
        on_gossip_change_weather() : CreatureScript("on_gossip_change_weather") { }
 
    bool OnGossipHello(Player* player, Creature* creature)
    {
        SendHello(player, creature);
        return true;
    }
 
    bool OnGossipSelect(Player* player, Creature* creature, uint32 /* sender */, uint32 actions)
    {
        player->PlayerTalkClass->ClearMenus();
                Weather* weather = WeatherMgr::FindWeather(player->GetZoneId()); // See if weather is already going on
                if (!weather) // No weather was found in the player's zone
                        weather = WeatherMgr::AddWeather(player->GetZoneId()); // Creating the weather
                switch (actions)
                {
            case 1: // Change Weather (Show Options)
                                SendWeatherOptions(player, creature);
                                break;
            case 2: // Nevermind
                                player->CLOSE_GOSSIP_MENU();
                                break;
                        case 3: // Normal Weather
                                weather->SetWeather(WEATHER_TYPE_FINE, 0);
                                break;
                        case 4: // Rain Weather
                                weather->SetWeather(WEATHER_TYPE_RAIN, GetRandomGrade(WEATHER_TYPE_RAIN));
                                break;
                        case 5: // Snow Weather
                                weather->SetWeather(WEATHER_TYPE_SNOW, GetRandomGrade(WEATHER_TYPE_SNOW));
                                break;
                        case 6: // Storm Weather
                                weather->SetWeather(WEATHER_TYPE_STORM, GetRandomGrade(WEATHER_TYPE_STORM));
                                break;
                        case 7: // Thunder Weather
                                weather->SetWeather(WEATHER_TYPE_THUNDERS, 0);
                                break;
        }
               
        if (actions > 2) // Removing token
            player->DestroyItemCount(16, 1, true); // Change 30000 to the itemId
    }
 
    void SendHello(Player* player, Creature* creature)
    {
        if (player->GetItemCount(16) == 0) // Change 30000 to the correct itemId
        {
            ChatHandler(player->GetSession()).SendSysMessage("You need a shard of Azeroth to change the weather!");
            return;
        }
 
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I want to use my shard to change the weather", 0, 1);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Nevermind..", 0, 2);
        player->SEND_GOSSIP_MENU(1, creature->GetGUID());
    }
 
    void SendWeatherOptions(Player* player, Creature* creature)
    {
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Normal Weather", 0, 3);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Rain Weather", 0, 4);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Snowy Weather", 0, 5);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Sandstorm Weather", 0, 6);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Thunder Weather", 0, 7);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Nevermind..", 0, 2);
        player->SEND_GOSSIP_MENU(1, creature->GetGUID());
    }
 
    WeatherState GetRandomGrade(WeatherType weatherType)
    {
        WeatherState tempState = WEATHER_STATE_FINE;
        int randomNum = urand(0, 2);
        switch (weatherType)
        {
            case WEATHER_TYPE_RAIN:
                if (randomNum == 0)
                    tempState = WEATHER_STATE_LIGHT_RAIN;
                else if (randomNum == 1)
                    tempState = WEATHER_STATE_MEDIUM_RAIN;
                else if (randomNum == 2)
                    tempState == WEATHER_STATE_HEAVY_RAIN;
                break;
            case WEATHER_TYPE_SNOW:
                if (randomNum == 0)
                    tempState = WEATHER_STATE_LIGHT_SNOW;
                else if (randomNum == 1)
                    tempState = WEATHER_STATE_MEDIUM_SNOW;
                else if (randomNum == 2)
                    tempState == WEATHER_STATE_HEAVY_SNOW;
                break;
            case WEATHER_TYPE_STORM:
                if (randomNum == 0)
                    tempState = WEATHER_STATE_LIGHT_SANDSTORM;
                else if (randomNum == 1)
                    tempState = WEATHER_STATE_MEDIUM_SANDSTORM;
                else if (randomNum == 2)
                    tempState == WEATHER_STATE_HEAVY_SANDSTORM;
                break;
        }
 
        return tempState;
    }
};
 
void WeatherChange()
{
    new on_gossip_change_weather;

    }