#include "ScriptPCH.h"
#include "AccountMgr.h"
#define CHECK_INTERVAL 1000

class Packet_Protection : public WorldScript
{
public:
	Packet_Protection() : WorldScript("Packet_Protection") {}

	void OnStartup()
	{
		timer = CHECK_INTERVAL;
	}

	void OnUpdate(uint32 diff)
	{
		if(timer < diff)
		{
			ResetCounters();
			timer = CHECK_INTERVAL;
		}
		else
			timer -= diff;
	}

	void ResetCounters()
	{
		 SessionMap const& sessions = sWorld->GetAllSessions();
		 for(SessionMap::const_iterator itr = sessions.begin(); itr != sessions.end(); ++itr)
			 for(int i = 0; i < MAX_PROTECTED_PACKETS; ++i)
			    itr->second->protectedPacketsCounter[i] = 0;
	}

private:
	uint32 timer;
};

void AddSC_Packet_Protection()
{
	new Packet_Protection();
}