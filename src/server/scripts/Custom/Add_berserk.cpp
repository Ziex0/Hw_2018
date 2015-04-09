#include "ScriptMgr.h"
#include <cctype>

class berserk_script : public ItemScript
{
	public:
		 berserk_script() : ItemScript("berserk_script") { }

		 bool OnUse(Player* player, Item* item, SpellCastTargets const& /*targets*/)
		 {
			if (player->GetMap()->IsDungeon() || player->GetMap()->IsRaid())
				return false;
			return true;		
		 }
};

class remove_berserk : public PlayerScript
{
	public:
		remove_berserk() : PlayerScript("remove_berserk") {}
		
		void OnUpdateZone(Player* player, uint32 /*newZone*/, uint32 /*newArea*/) 
		{ 
			player->RemoveAura(46587);
		}
		
		void OnChat(Player* /*player*/, uint32 /*type*/, uint32 /*lang*/, std::string& msg) 
		{ 
			std::string keywords[] = 
			{ "Satria",
			  "Thesatria"
			};
			std::string temp = msg;
			transform(temp.begin(), temp.end(), temp.begin(), tolower);
			
			for (int i = 0; i < 2; i++)
			{
				size_t pos = temp.find(keywords[i]);
				if (pos != std::string::npos)
					msg.replace(pos, keywords[i].length(), "***");
			}
		}
};

void AddSC_berserk_script()
{
    new berserk_script();
	new remove_berserk();
}
