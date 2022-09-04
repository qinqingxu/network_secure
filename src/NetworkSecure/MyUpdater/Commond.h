#if !defined COMMOND_H_FILE_INCLUDE
#define COMMOND_H_FILE_INCLUDE

extern CString g_strWindowTitle;//标题

//正在做
#define G_TEXT_COLOR_DOING RGB(255, 128, 64)

//已经完成
#define G_TEXT_COLOR_DONE RGB(0, 0, 255)



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
extern CString GetAppPath();


///根据一个文件名得到它的路径
extern CString GetPathFromFileName(CString strFileName);

///根据一个路径得到它的文件名
extern CString GetFileNameFromPath(CString strPath);

const CString g_strContractUSWeb = "http://www.jelllove.com";


extern bool MakeDir(CString strPath);

extern bool DeleteDir(CString strPath);

extern void GetAllFileName(char *strDir, CStringArray &strArrayDir, CStringArray &strArrayFiles);



///return value like "34 Byte", "182 KB", " 999 MB", "333 GB"
extern CString GetFileSize(int nSize);

#endif