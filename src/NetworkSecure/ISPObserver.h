#pragma once
#include <string>
#include <vector>
#include "PublicClasses.h"
using namespace std;

class ISPObserver
{
public:
	ISPObserver()
	{
	}


	bool CheckISPValid(vector<ISPSearchInfo> searchInfo, ProxyInfo proxyInfo);

	string GetLastError();

private:
	vector<ISPSearchInfo> m_searchInfo;
	string m_lastError;
};

