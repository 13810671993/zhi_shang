#include "log_common.h"

CLogImp::CLogImp()
{

}

CLogImp::~CLogImp()
{

}

CLogImp* CLogImp::m_pLogImp;

CLogImp* CLogImp::GetInstance()
{
	if (m_pLogImp == NULL)
		m_pLogImp = new CLogImp;
	return m_pLogImp;
}

VOID CLogImp::DestroyInstance()
{
	if (m_pLogImp != NULL)
	{
		delete m_pLogImp;
		m_pLogImp = NULL;
	}
}

