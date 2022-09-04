#include "pch.h"
#include "HttpClient.h"
#include "curl/curl.h"
#include <vector>
#include <string>
#include <string.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <string.h>
#include <process.h>
#include <vector>
#include <stack>
#include <map>
#include <iterator>
#include <list>
#include <io.h>
#include <algorithm>
using namespace std;
#pragma comment(lib, "libcurl.dll.a" )


int curl_writer(char* data, size_t size, size_t nmemb, std::string* writerData)
{
	if (writerData == NULL)
	{
		return 0;
	}

	writerData->append(data, size * nmemb);

	return int(size * nmemb);
}

bool my_curl_init(CURL*& conn, char* url, char* error_buffer, string& contentBuffer)
{
	CURLcode code;

	conn = curl_easy_init();

	if (conn == NULL)
	{
		sprintf_s(error_buffer, CURL_ERROR_SIZE, "Failed to create CURL connection\n");
		return false;
	}

	code = curl_easy_setopt(conn, CURLOPT_ERRORBUFFER, error_buffer);
	if (code != CURLE_OK)
	{
		sprintf_s(error_buffer, CURL_ERROR_SIZE, "Failed to set error buffer [%d]\n", code);
		return false;
	}

	code = curl_easy_setopt(conn, CURLOPT_URL, url);
	if (code != CURLE_OK) {
		return false;
	}

	curl_easy_setopt(conn, CURLOPT_SSL_VERIFYPEER, 0L);
	if (code != CURLE_OK) {
		return false;
	}

	code = curl_easy_setopt(conn, CURLOPT_FOLLOWLOCATION, 1L);
	if (code != CURLE_OK) {
		return false;
	}

	code = curl_easy_setopt(conn, CURLOPT_WRITEFUNCTION, curl_writer);
	if (code != CURLE_OK)
	{
		return false;
	}

	code = curl_easy_setopt(conn, CURLOPT_WRITEDATA, &contentBuffer);
	if (code != CURLE_OK) {
		return false;
	}

	return true;
}

bool HttpClient::GetHttpViaCURL(const char* URL, string& strContent, string& strError, bool bProxy, const char* pHostIP, short pHostPort)
{
	CURL* conn = NULL;
	CURLcode code;
	char error_buffer[CURL_ERROR_SIZE] = { 0 };

	// Initialize CURL connection
	if (!my_curl_init(conn, (char *)URL, error_buffer, strContent)) {
		strError = error_buffer;
		if (conn != NULL)
		{
			curl_easy_cleanup(conn);
			conn = NULL;
		}

		return false;
	}

	if (bProxy)
	{
		curl_easy_setopt(conn, CURLOPT_PROXYAUTH, CURLAUTH_BASIC); //代理认证模式

		curl_easy_setopt(conn, CURLOPT_PROXY, pHostIP); //代理服务器地址

		curl_easy_setopt(conn, CURLOPT_PROXYPORT, pHostPort); //代理服务器端口

		curl_easy_setopt(conn, CURLOPT_PROXYTYPE, CURLPROXY_HTTP); //使用http代理模式
	}

	//get the content 
	code = curl_easy_perform(conn);

	if (code != CURLE_OK)
	{
		if (conn != NULL)
		{
			curl_easy_cleanup(conn);
			conn = NULL;
		}

		strError = "Failure to get the content";
		return false;
	}
	curl_easy_cleanup(conn);

	return true;
}