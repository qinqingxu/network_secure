#pragma once
#include <string>
using namespace std;


/*
	"ISP": [
		{
			"webSite" : "https://www.whatismyisp.com/",
			"searchKey" : "Microsoft Corporation",
			"essentialInfo" : "Your ISP is"
		},
		{
			"webSite" : "https://myip.ms/",
			"searchKey" : "Microsoft Corporation",
			"essentialInfo" : "Your Organisation"
		},
		{
			"webSite" : "https://www.showmyip.com/",
			"searchKey" : "Microsoft Corporation",
			"essentialInfo" : "Internet Service Provider"
		}
	]
*/
class ISPSearchInfo
{
public:
	ISPSearchInfo()
	{
		m_webSite = "https://www.whatismyisp.com/";
		m_essentialInfo = "Your ISP is";
		m_searchKey = "Microsoft Corporation";
	}

	ISPSearchInfo& operator = (const ISPSearchInfo&other)
	{
		if (this == &other)
			return (*this);

		m_webSite = other.m_webSite;
		m_essentialInfo = other.m_essentialInfo;
		m_searchKey = other.m_searchKey;

		return (*this);
	}

	string m_webSite;
	string m_essentialInfo;
	string m_searchKey;
};

/*
    "proxy": 
	{
		"useProxy" : false,
		"proxyAddress" : "http://127.0.0.1",
		"proxyPort" : 5000
	},
*/
class ProxyInfo
{
public:
	ProxyInfo()
	{
		m_useProxy = false;
		m_proxyAddress = "";
		m_porxyPort = 80;
	}

	ProxyInfo& operator = (const ProxyInfo& other)
	{
		if (this == &other)
			return (*this);

		m_useProxy = other.m_useProxy;
		m_proxyAddress = other.m_proxyAddress;
		m_porxyPort = other.m_porxyPort;

		return (*this);
	}

	bool m_useProxy;
	string m_proxyAddress;
	short m_porxyPort;
};


/*
	"sound":
	{
		"playSound" : true,
		"soundFile" : "http://127.0.0.1",
		"proxyPort" : 5000
	},
*/
class SoundInfo
{
public:
	SoundInfo()
	{
		m_playSound = true;
		m_soundFile = "Alarm03.wav";
	}

	SoundInfo& operator = (const SoundInfo& other)
	{
		if (this == &other)
			return (*this);

		m_playSound = other.m_playSound;
		m_soundFile = other.m_soundFile;

		return (*this);
	}

	bool m_playSound;
	string m_soundFile;
};
