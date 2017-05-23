#include "log_common.h"

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
    std::vector<CHAR> cLogMessageVec(strlen(format) + 1, 0);
    snprintf(cLogMessageVec.data(), strlen(format) + 1, format, arg);
    va_end(arg);
    CLogImp::PrintLog(eLogLevel, cLogMessageVec.data());
}

CLog* CLog::GetInstance(E_SEVERITY_LEVEL eLogLevel)
{
    return CLogImp::GetInstance(eLogLevel);
}

VOID CLog::DestroyInstance()
{
    CLogImp::DestroyInstance();
}

