#if!defined INILOAD_H_INCLUDE
#define     INILOAD_H_INCLUDE

class CIni
{
public:
	CIni();
	~CIni();

	bool WriteString(const char * sTile,const char * sKey,const char * sText,const char * sFileName,bool bReadOnly);
	CString ReadString(const char * sTile,const char * sKey,const char * sFileName);
	bool ReadString(const char * sTile,const char * sKey,CString & sText,const char * sFileName);
private:
	bool LoadIniFile(const char *);

};

#endif