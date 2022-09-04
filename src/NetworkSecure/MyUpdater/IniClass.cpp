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
	if(bReadOnly)//ֻ��
	{
		if(LoadIniFile(sFileName)==false)//�ļ�������
			 return false;//����
	}

	if(WritePrivateProfileString(sTile,sKey,sText,sFileName))
		  return true;///д���ļ��ɹ�
	else
		  return false;//д���ļ����ɹ�

}


bool CIni::ReadString(const char * sTile,const char * sKey,CString &sText,const char * sFileName)
{

	if(LoadIniFile(sFileName)==false)///�ļ������ڻ��ȡʧ��
		return false;///����

	if(GetPrivateProfileString(sTile,sKey,"",sText.GetBuffer(MAX_PATH),MAX_PATH,sFileName)>0)///��ȡ�ļ���ָ��������
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
 
	if(LoadIniFile(sFileName)==false)///�ļ������ڻ��ȡʧ��
		return "";///����

	CString sTemp;

	GetPrivateProfileString(sTile,sKey,"Default Caption",sTemp.GetBuffer(MAX_PATH),MAX_PATH,sFileName);///��ȡ�ļ���ָ��������
	sTemp.ReleaseBuffer();
	return sTemp;//�����ַ���
}

bool CIni::LoadIniFile(const char * sFileName)///˽�к���
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