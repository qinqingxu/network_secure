#include "stdafx.h"
#include "IniClass.h"

#include <stdio.h>
#include <io.h>

CIni::CIni()
{
}

CIni::~CIni()
{
	
}


bool CIni::WriteString(const char * sTile,const char * sKey,const char * sText,const char * sFileName,bool bReadOnly=true)
{
	if(bReadOnly)//只读
	{
		if(LoadIniFile(sFileName)==false)//文件不存在
			 return false;//返回
	}

	if(WritePrivateProfileString(sTile,sKey,sText,sFileName))
		  return true;///写入文件成功
	else
		  return false;//写入文件不成功

}


bool CIni::ReadString(const char * sTile,const char * sKey,CString &sText,const char * sFileName)
{

	if(LoadIniFile(sFileName)==false)///文件不存在或读取失败
		return false;///返回

	if(GetPrivateProfileString(sTile,sKey,"",sText.GetBuffer(MAX_PATH),MAX_PATH,sFileName)>0)///读取文件中指定的内容
	{
		sText.ReleaseBuffer();
		return true;
	}
	else
	{
		sText.ReleaseBuffer();
		return false;
	}
}




CString CIni::ReadString(const char * sTile,const char * sKey,const char * sFileName)
{
 
	if(LoadIniFile(sFileName)==false)///文件不存在或读取失败
		return "";///返回

	CString sTemp;

	GetPrivateProfileString(sTile,sKey,"Default Caption",sTemp.GetBuffer(MAX_PATH),MAX_PATH,sFileName);///读取文件中指定的内容
	sTemp.ReleaseBuffer();
	return sTemp;//返回字符串
}

bool CIni::LoadIniFile(const char * sFileName)///私有函数
{

	
	if (access(sFileName, 0) == 0)
	{
		
		return true;
	}
	else
	{
		
		return false;
	}
}