#include <iostream>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QCoreApplication>

class ContainerServer : public QObject
{
    Q_OBJECT

  public:
    ContainerServer(QObject *parent = NULL) : QObject(parent), m_server(new QTcpServer(this))
    {
        connect(m_server, &QTcpServer::newConnection, this, &ContainerServer::onNewConnection);
    }

    bool listen(int port)
    {
        return m_server->listen(QHostAddress::Any, port);
    }

  signals:
    void listening();
    void connectionError(const QString &errorMessage);
    void clientConnected(const QString &clientAddress);
    void messageReceived(const QString &message, const QString &clientAddress);

  private slots:
    void onNewConnection()
    {
        QTcpSocket *socket = m_server->nextPendingConnection();
        if (!socket)
        {
            emit connectionError("Failed to get next pending connection");
            return;
        }

        connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
        connect(socket, &QTcpSocket::readyRead, this, [socket, this]() {
            QByteArray data       = socket->readAll();
            QString clientAddress = socket->peerAddress().toString() + ":" + QString::number(socket->peerPort());
            emit messageReceived(QString::fromUtf8(data), clientAddress);
        });

        QString clientAddress = socket->peerAddress().toString() + ":" + QString::number(socket->peerPort());
        emit clientConnected(clientAddress);
    }

  private:
    QTcpServer *m_server;
};
