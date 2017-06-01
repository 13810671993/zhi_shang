#include "log_common.h"

#pragma warning(disable:4996)
#pragma warning(disable:4703)
CLog::CLog()
{

}

CLog::~CLog()
{

}

VOID CLog::PrintLog(E_SEVERITY_LEVEL eLogLevel, CHAR* format, ...)
{
    va_list arg;
    va_start(arg, format);
    CHAR pcLog[MAX_LOG_SIZE] = { 0 };
    //snprintf(pcMsg, strlen(arg) + strlen(format) + 1, format, arg);   // 这里不可以用sprintf
    vsnprintf(pcLog, MAX_LOG_SIZE, format, arg);
    va_end(arg);
    CLogImp::PrintLog(eLogLevel, pcLog);
}

CLog* CLog::GetInstance(E_SEVERITY_LEVEL eLogLevel)
{
    return CLogImp::GetInstance(eLogLevel);
}

VOID CLog::DestroyInstance()
{
    CLogImp::DestroyInstance();
}

