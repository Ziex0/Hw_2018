    #include "ScriptPCH.h"
     
    class Duel_Reset : public PlayerScript
    {
            public:
                    Duel_Reset() : PlayerScript("Duel_Reset"){}
     
                    void OnDuelEnd(Player* pWinner, Player* pLoser, DuelCompleteType /*type*/)
                    {
					//if (pWinner->GetZoneId() == 139 && pLoser->GetZoneId() == 139)
                            pWinner->RemoveAllSpellCooldown();
                            pLoser->RemoveAllSpellCooldown();
                            pWinner->SetHealth(pWinner->GetMaxHealth());
                            if ( pWinner->getPowerType() == POWER_MANA )
                                    pWinner->SetPower(POWER_MANA, pWinner->GetMaxPower(POWER_MANA));
                            pLoser->SetHealth(pLoser->GetMaxHealth());
                            if ( pLoser->getPowerType() == POWER_MANA )
                                    pLoser->SetPower(POWER_MANA,  pLoser->GetMaxPower(POWER_MANA));
                    }
					void OnPlayerDuelRequest(Player *target, Player *challenger)
					{
					//if (target->GetZoneId() == 139 && challenger->GetZoneId() == 139)
							target->RemoveAllSpellCooldown();
                            challenger->RemoveAllSpellCooldown();
                            target->SetHealth(target->GetMaxHealth());
                            if ( target->getPowerType() == POWER_MANA )
                                    target->SetPower(POWER_MANA, target->GetMaxPower(POWER_MANA));
                            challenger->SetHealth(challenger->GetMaxHealth());
                            if ( challenger->getPowerType() == POWER_MANA )
                                    challenger->SetPower(POWER_MANA,  challenger->GetMaxPower(POWER_MANA));
                    }
    };
     
    void AddSC_Duel_Reset()
    {
            new Duel_Reset();
    }
