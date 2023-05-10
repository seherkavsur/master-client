#include "master.h"
#define TCP_PORT 23

Master::Master()
{
    qRegisterMetaType<uint16_t>("uint16_t");
}

Master::~Master()
{
    delete tcpserver;
    delete tcpserverThread;
}

bool Master::init()
{
    this->tcpserver = new TCPServer();
    return true;
}

void Master::starTCPConnection()
{
    tcpserverThread = new QThread();
    tcpserver->moveToThread(tcpserverThread);
    tcpserverThread->start();
    connect(this, SIGNAL(portStart(uint16_t)), tcpserver, SLOT(start(uint16_t)), Qt::QueuedConnection);
    connect(tcpserver,
            SIGNAL(messageReceived(QByteArray)),
            this,
            SLOT(parseTCPMessage(QByteArray)),
            Qt::QueuedConnection);
    connect(this, SIGNAL(writeTCP(QByteArray)), tcpserver, SLOT(write(QByteArray)), Qt::QueuedConnection);
    emit portStart(TCP_PORT);
}

void Master::parseTCPMessage(QByteArray data)
{
    qWarning() << "message received" << data;
}
