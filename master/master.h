#ifndef MASTER_H
#define MASTER_H

#include <QObject>
#include <QThread>
#include "tcpserver.h"

class Master : public QObject
{
    Q_OBJECT
  public:
    explicit Master();
    ~Master();
    bool init();
    void starTCPConnection();

    QThread *tcpserverThread;
    TCPServer *tcpserver;

  signals:
    void writeTCP(QByteArray data);
    void portStart(uint16_t port);

  public slots:
    void parseTCPMessage(QByteArray data);
};

#endif    // MASTER_H
