#pragma once
#include "PublicClasses.h"
#include <vector>
using namespace std;

class Configurator
{
public:
	Configurator()
	{

	}

	bool ReadJsonFile(const char* fileName);

	bool WriteJsonFile(const char* fileName);

	vector<ISPSearchInfo> GetISPSearchInfo();
	
	ProxyInfo GetProxyInfo();
	void SetProxyInfo(ProxyInfo);

	SoundInfo GetSoundInfo();
	void SetSoundInfo(SoundInfo);

	int GetScanInterval();
	void SetScanInterval(int);

	const char* GetLastError();

private:
	int m_scanInterval;
	ProxyInfo m_proxyInfo;
	vector<ISPSearchInfo> m_ISPSearchInfo;
	SoundInfo m_soundInfo;
	
	string m_lastError;
};

