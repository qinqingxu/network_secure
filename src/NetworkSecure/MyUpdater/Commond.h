#if !defined COMMOND_H_FILE_INCLUDE
#define COMMOND_H_FILE_INCLUDE

extern CString g_strWindowTitle;//����

//������
#define G_TEXT_COLOR_DOING RGB(255, 128, 64)

//�Ѿ����
#define G_TEXT_COLOR_DONE RGB(0, 0, 255)



//**********************************************
//������: GetAppPath
//
//��������:�õ���ǰ�ļ����ļ�Ŀ¼
//
//����˵��: ��
//          
//
//��������˵��:  ������͵��ַ���
//**********************************************
extern CString GetAppPath();


///����һ���ļ����õ�����·��
extern CString GetPathFromFileName(CString strFileName);

///����һ��·���õ������ļ���
extern CString GetFileNameFromPath(CString strPath);

const CString g_strContractUSWeb = "http://www.jelllove.com";


extern bool MakeDir(CString strPath);

extern bool DeleteDir(CString strPath);

extern void GetAllFileName(char *strDir, CStringArray &strArrayDir, CStringArray &strArrayFiles);



///return value like "34 Byte", "182 KB", " 999 MB", "333 GB"
extern CString GetFileSize(int nSize);

#endif