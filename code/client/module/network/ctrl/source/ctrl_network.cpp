#include "network/network_common.h"


CNetwork::CNetwork() : pSocket(nullptr)
{
    InitNetwork();
}

CNetwork::~CNetwork()
{

}

void CNetwork::InitNetwork()
{
    pSocket	= new QTcpSocket(this);


    NewConnect();

    //这里我是采用程序启动就自访问服务端（也可根据实际情况采用手动连接手动输入服务端ip的方式。）

    connect(pSocket,SIGNAL(readyRead()),this,SLOT(revData()));

    //readyRead()表示服务端发送数据过来即发动信号，接着revData()

    //进行处理。

    connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)), this,SLOT(displayError(QAbstractSocket::SocketError)));
}

void CNetwork::NewConnect()
{

}
