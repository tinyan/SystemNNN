#include "SteamWork.h"



char CSteamWork::m_dummyPlayerName[] = "Tinyan";


CSteamWork::CSteamWork()
{
	m_successInitialized = false;
}

CSteamWork::~CSteamWork()
{
	End();
}

void CSteamWork::End(void)
{
	ShutDown();
}


bool CSteamWork::IsNeedRestart(int appID)
{
#if defined __USE_STEAMWORK__

	if (SteamAPI_RestartAppIfNecessary(appID))
	{
		return true;
	}
	return false;
#else
	return false;
#endif

//	return false;
}


bool CSteamWork::InitSteam(void)
{
#if defined __USE_STEAMWORK__
	if (!SteamAPI_Init())
	{
		printf("Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed).\n");
		return false;
	}
	m_successInitialized = true;
	return true;
#else
	return true;
#endif

}


void CSteamWork::ShutDown(void)
{
#if defined __USE_STEAMWORK__
	if (IsInitailzed())
	{
		SteamAPI_Shutdown();
	}
	m_successInitialized = false;
#endif
}



bool CSteamWork::IsInitailzed(void)
{
	return m_successInitialized;
}







#if defined __USE_STEAMWORK__



#else


#endif


/*_*/

