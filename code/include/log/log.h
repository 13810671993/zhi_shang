#ifndef __LOG_H__
#define __LOG_H__

#if 0
#ifndef LogFatal

#define LogFatal(format, ...)\
	CLog::PrintLog(FATAL, format, ##__VA_ARGS__);\


#endif
#endif

class CLog
{
public:
	static CLog*	GetInstance();
	static VOID		DestroyInstance();

protected:
    CLog();
    ~CLog();

public:

private:

};

#endif // !__LOG_H__

