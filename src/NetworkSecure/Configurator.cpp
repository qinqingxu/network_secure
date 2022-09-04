#include "pch.h"
#include "Configurator.h"
#include <iostream>
#include <fstream>
using namespace std;
#include "json/json.h"


bool Configurator::ReadJsonFile(const char* fileName)
{
	
	Json::Reader reader;
	Json::Value root;
	
	ifstream fileStream(fileName, ios::binary);

	if (!fileStream.is_open())
	{
		m_lastError = "Error opening file";
		return false;
	}

	if (reader.parse(fileStream, root))
	{
		//Scan Internval
		m_scanInterval = root.get("scanInterval", 30000).asInt();

		//Proxy Info
		m_proxyInfo.m_useProxy = root["proxy"].get("useProxy", false).asBool();
		m_proxyInfo.m_proxyAddress = root["proxy"].get("proxyAddress", "").asCString();
		m_proxyInfo.m_porxyPort = root["proxy"].get("proxyPort", 80).asInt();

		//ISP info
		m_ISPSearchInfo.clear();
		Json::Value& ISPList = root["ISP"];
		for (int i = 0; i < (int)ISPList.size(); ++i)
		{
			ISPSearchInfo ispInfo;
			ispInfo.m_webSite = ISPList[i]["webSite"].asCString();
			ispInfo.m_searchKey = ISPList[i]["searchKey"].asCString();
			ispInfo.m_essentialInfo = ISPList[i]["essentialInfo"].asCString();

			m_ISPSearchInfo.push_back(ispInfo);
		}

		if (m_ISPSearchInfo.size() == 0)
		{
			ISPSearchInfo ispInfo;
			m_ISPSearchInfo.push_back(ispInfo);
		}

		//Sound Info
		m_soundInfo.m_playSound = root["sound"].get("playSound", true).asBool();
		m_soundInfo.m_soundFile = root["sound"].get("soundFile", "Alarm03.wav").asCString();

		fileStream.close();
		return true;
	}
	else
	{
		m_lastError = "Json file parse failed.";
		fileStream.close();
		return false;
	}
	return true;

}

bool Configurator::WriteJsonFile(const char* fileName)
{
	Json::Value root;

	//Scan interval node
	root["scanInterval"] = Json::Value(m_scanInterval);


	//Proxy node
	Json::Value proxy;
	//Proxy nested nodes 
	proxy["useProxy"] = Json::Value(m_proxyInfo.m_useProxy);
	proxy["proxyAddress"] = Json::Value(m_proxyInfo.m_proxyAddress);
	proxy["proxyPort"] = Json::Value(m_proxyInfo.m_porxyPort);
	//Append the proxy node to root.
	root["proxy"] = Json::Value(proxy);

	//ISP
	for (int i = 0; i < m_ISPSearchInfo.size(); ++i)
	{
		Json::Value singleISPSearchInfo;
		singleISPSearchInfo["webSite"] = Json::Value(m_ISPSearchInfo[i].m_webSite);
		singleISPSearchInfo["searchKey"] = Json::Value(m_ISPSearchInfo[i].m_searchKey);
		singleISPSearchInfo["essentialInfo"] = Json::Value(m_ISPSearchInfo[i].m_essentialInfo);

		root["ISP"].append(singleISPSearchInfo);
	}

	//Sound node
	Json::Value sound;
	//sound nested nodes 
	sound["playSound"] = Json::Value(m_soundInfo.m_playSound);
	sound["soundFile"] = Json::Value(m_soundInfo.m_soundFile);
	//Append the proxy node to root.
	root["sound"] = Json::Value(sound);

	Json::StyledWriter sw;
	ofstream os;
	os.open(fileName, std::ios::out);
	if (!os.is_open())
	{
		m_lastError = "File create failed";
		return false;
	}
	os << sw.write(root);
	os.close();
	return true;
}

int Configurator::GetScanInterval()
{
	return m_scanInterval;
}
vector<ISPSearchInfo> Configurator::GetISPSearchInfo()
{
	return m_ISPSearchInfo;
}

ProxyInfo Configurator::GetProxyInfo()
{
	return m_proxyInfo;
}

const char* Configurator::GetLastError()
{
	return m_lastError.c_str();
}

SoundInfo Configurator::GetSoundInfo()
{
	return m_soundInfo;
}

void Configurator::SetProxyInfo(ProxyInfo proxyInfo)
{
	m_proxyInfo = proxyInfo;
}

void Configurator::SetSoundInfo(SoundInfo soundInfo)
{
	m_soundInfo = soundInfo;
}

void Configurator::SetScanInterval(int scanInterval)
{
	m_scanInterval = scanInterval;
}