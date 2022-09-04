#include "pch.h"
#include "ISPObserver.h"
#include "HttpClient.h"

bool ISPObserver::CheckISPValid(vector<ISPSearchInfo> searchInfo, ProxyInfo proxyInfo)
{
	for (int i = 0; i < searchInfo.size(); ++i)
	{
		string retHtml = "";
		string retError = "";
		if (!HttpClient::GetHttpViaCURL((char*)searchInfo[i].m_webSite.c_str(), retHtml, retError, proxyInfo.m_useProxy, proxyInfo.m_proxyAddress.c_str(), proxyInfo.m_porxyPort))
		{
			continue;
		}

		//If the GET html operation success, we need to make sure the page content is what we expected, but not other error page.
		if (retHtml.find(searchInfo[i].m_essentialInfo, 0) == string::npos)
		{
			continue;
		}

		if (retHtml.find(searchInfo[i].m_searchKey, 0) == string::npos)
		{
			m_lastError = "The ISP is not Microsoft";
			return false;
		}
		else
		{
			return true;
		}
	}
	
	if (searchInfo.size() == 0)
	{
		m_lastError = "JSON configuration file invalid.";
	}
	else
	{
		m_lastError = "Check ISP failed, please check your network.";
	}
	
	return false;
	
}


string ISPObserver::GetLastError()
{
	return m_lastError;
}