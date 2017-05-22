#include "log_common.h"

CLog::CLog()
{

}

CLog::~CLog()
{

}

CLog* CLog::GetInstance()
{
	return CLogImp::GetInstance();
}

VOID CLog::DestroyInstance()
{
	CLogImp::DestroyInstance();
}

