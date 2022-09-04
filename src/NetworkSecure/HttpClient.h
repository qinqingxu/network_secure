#pragma once
#include <string>
using namespace std;

class HttpClient
{
public:
	static bool GetHttpViaCURL(const char* URL, string& strContent, string& strError, bool bProxy = false, const char* pHostIP = nullptr, short pHostPort = 0);
};

