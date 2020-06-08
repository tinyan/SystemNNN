#pragma once


class CSteamWork
{
public:
	CSteamWork();
	virtual ~CSteamWork();
	void End(void);

	bool IsNeedRestart(int appID);
	bool InitSteam(void);
	void ShutDown(void);

#if defined __USE_STEAMWORK__




#endif
protected:
	bool IsInitailzed(void);
	bool m_successInitialized;

	static char m_dummyPlayerName[];
};


/*_*/