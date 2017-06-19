#include "subscriber_common.h"

CSubscriber::CSubscriber()
{

}

CSubscriber::~CSubscriber()
{

}

CSubscriber* CSubscriber::GetInstance()
{
    return CSubscriberImp::GetInstance();
}

VOID CSubscriber::DestroyInstance()
{
    CSubscriberImp::DestroyInstance();
}

