#include "logic_common.h"

CLogic::CLogic()
{

}

CLogic::~CLogic()
{

}

CLogic* CLogic::GetInstance()
{
    return CLogicImp::GetInstance();
}

VOID CLogic::DestroyInstance()
{
    CLogicImp::DestroyInstance();
}

