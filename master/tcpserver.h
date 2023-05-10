#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include "stdint.h"
#include <QDebug>

typedef enum
{
    eNoConnection = 0,
    eVerificationRequired,
    eConnected
} teTCPConnectionType;
class TCPServer : public QTcpServer
{
    Q_OBJECT
  public:
    explicit TCPServer(QObject *parent = 0);
    ~TCPServer();
    //    void start(uint16_t port);
    void incomingConnection(int socketDescriptor);
    bool isConnected();
    QByteArray data;

    teTCPConnectionType getConnectionState() const;
    void setConnectionState(const teTCPConnectionType &value);

  signals:
    void messageReceived(QByteArray data);
    void socketConnected();
    void socketDisconnected();
    void socketStateChanged();
  public slots:
    void write(QByteArray data);
    void readyRead();
    void disconnected();
    void abort();
    void start(uint16_t port);
  private slots:
    void verificationTimeout();

  private:
    QTcpSocket *socket;
    QTimer connectionTimer;
    teTCPConnectionType connectionState;
};

#endif    // TCPSERVER_H
