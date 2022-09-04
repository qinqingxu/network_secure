#include "StdAfx.h"
#include "Commond.h"
#include <direct.h>
#include <io.h>
#include <errno.h>

CString g_strWindowTitle = "升级程序 1.0";//标题


//**********************************************
//函数名: GetAppPath
//
//函数功能:得到当前文件的文件目录
//
//参数说明: 无
//          
//
//函数返回说明:  返回相就的字符串
//**********************************************
CString GetAppPath()   
{   
	CString   sModFileName;   
	CString   str1;   
	GetModuleFileName(NULL,   sModFileName.GetBuffer(MAX_PATH),   MAX_PATH);   
	sModFileName.ReleaseBuffer();   
	str1=sModFileName;   
	str1.MakeReverse();   
	return(sModFileName.Left(sModFileName.GetLength()   -   str1.Find('\\')));
}


bool MakeDir(CString strPath)
{
	if (strPath.Right(1) != "\\")
	{
		strPath += "\\";
	}
	
	int nPos = strPath.Find("\\", 0);
	
	while (nPos >= 0)
	{
		CString str = strPath.Left(nPos);
		
		if (str.Right(1) != "\\")
		{
			str += "\\";
		}
		
		CFileStatus   rStatus;
		
		if(!CFile::GetStatus(str, rStatus))                 //判断是否已经存在
		{
			if (_mkdir(str.GetBuffer(0)) != 0)
			{
				if (errno == ENOENT)
				{
					return false;
				}
			}
		}
		
		nPos = strPath.Find("\\", nPos + 1);
	}
	
	return true;
}

bool DeleteDir(CString strPath)
{
	if (strPath.Right(1) != "\\")
	{
		strPath += "\\";
	}

	CStringArray arrayDir;
	CStringArray arrayFile;

	GetAllFileName(strPath.GetBuffer(0), arrayDir, arrayFile);

	int i;

	for (i = 0; i < arrayFile.GetSize(); i++)
	{
		if (!DeleteFile(arrayFile[i]))
		{
			return false;
		}
	}

	for (i = arrayDir.GetSize() - 1; i >= 0; i--)
	{
 		if (arrayDir[i].Right(1) != "\\")
 		{
 			arrayDir[i] += "\\";
 		}
 		if (_rmdir(arrayDir[i]) != 0)
 		{
 			return false;
 		}
	}

	if (_rmdir(strPath) != 0)
	{
		return false;
	}

	return true;
}


void GetAllFileName(char *strDir, CStringArray &strArrayDir, CStringArray &strArrayFiles) 
{
	
	if (_access(strDir, 0) != 0)
	{
		return;
	}
	
	char fname[MAX_PATH];
	ZeroMemory(fname, MAX_PATH);
	

	

	WIN32_FIND_DATA fd;
	ZeroMemory(&fd, sizeof(WIN32_FIND_DATA));
	HANDLE hSearch;
	
	char filePathName[MAX_PATH];
	char tmpPath[MAX_PATH];
	
	ZeroMemory(filePathName, MAX_PATH);
	ZeroMemory(tmpPath, MAX_PATH);
	
	strcpy(filePathName, strDir);
	
	if( filePathName[strlen(filePathName) -1] != '\\' )
	{
		strcat(filePathName, "\\");
	}
	
	strcat(filePathName, "*.*");
	
	hSearch = FindFirstFile(filePathName, &fd);
	
	if (hSearch == INVALID_HANDLE_VALUE) // 如果没有找到或查找失败
		return;
	do
	{
		if( (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			&& strcmp(fd.cFileName, ".") && strcmp(fd.cFileName, "..") )		
		{
			strcpy(tmpPath, strDir);
			if( tmpPath[strlen(tmpPath) -1] != '\\' )
			{
				strcat(tmpPath, "\\");
			}
			strcat(tmpPath, fd.cFileName);
			strArrayDir.Add(tmpPath);
			GetAllFileName(tmpPath, strArrayDir, strArrayFiles);
		}
		else if( strcmp(fd.cFileName, ".") && strcmp(fd.cFileName, "..") )
		{
			CString str = strDir;
			str += "\\";
			str += fd.cFileName;
			strArrayFiles.Add(str);
		}
	}
	while (FindNextFile(hSearch, &fd));
	
	FindClose(hSearch);
}



///return value like "34 Byte", "182 KB", " 999 MB", "333 GB"
CString GetFileSize(int nSize)
{
	if (nSize <= 0)
	{
		return "0.00 Byte";
	}
	
	double dSize = nSize;
	
	int nLevel = 0;
	
	for (int i = 0; i < 4; i++)
	{
		if (dSize >= 1024.0)
		{
			nLevel++;
			dSize = dSize / 1024;
		}
	}
	
	CString strReturn;
	
	switch(nLevel)
	{
	case 0:
		strReturn.Format("%.2f Byte", dSize);
		break;
	case 1:
		strReturn.Format("%.2f KB", dSize);
		break;
	case 2:
		strReturn.Format("%.2f MB", dSize);
		break;
	case 3:
		strReturn.Format("%.2f GB", dSize);
		break;
	default:
		strReturn = "0.00 Byte";
		break;
	}
	return strReturn;
}


///根据一个文件名得到它的路径
CString GetPathFromFileName(CString strFileName)
{
	char chDrive[MAX_PATH];
	char chDir[MAX_PATH];
	_splitpath(strFileName.GetBuffer(0), chDrive, chDir, NULL, NULL);
	
	CString str = chDrive;
	str += chDir;
	
	return str;
}

CString GetFileNameFromPath(CString strPath)
{
	char chFileName[MAX_PATH];
	char chFileExt[MAX_PATH];
	_splitpath(strPath.GetBuffer(0), NULL, NULL, chFileName, chFileExt);
	
	CString str = chFileName;
	str += chFileExt;
	
	return str;
}