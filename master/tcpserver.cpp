#include "tcpserver.h"
#include "unistd.h"
#include <QThread>
const QByteArray SOH = QByteArray("\xAA\x55");

#define SECOND 1000
TCPServer::TCPServer(QObject *parent) : QTcpServer(parent)
{
    this->socket          = NULL;
    this->connectionState = eNoConnection;
    connect(this, SIGNAL(socketConnected()), this, SIGNAL(socketStateChanged()));
    connect(this, SIGNAL(socketDisconnected()), this, SIGNAL(socketStateChanged()));

    this->connectionTimer.setInterval(5 * SECOND);
    this->connectionTimer.setSingleShot(true);
    connect(&this->connectionTimer, SIGNAL(timeout()), this, SLOT(verificationTimeout()));
}

TCPServer::~TCPServer()
{
    if (socket == NULL)
    {
        return;
    }
    socket->abort();
    socket->deleteLater();
    delete socket;
    disconnect(this, SIGNAL(socketConnected()), this, SIGNAL(socketStateChanged()));
    disconnect(this, SIGNAL(socketDisconnected()), this, SIGNAL(socketStateChanged()));
    disconnect(&this->connectionTimer, SIGNAL(timeout()), this, SLOT(abort()));
}

void TCPServer::start(uint16_t port)
{
    if (this->listen(QHostAddress::Any, port))
    {
        qDebug() << "Listening...";
    }
    else
    {
        qDebug() << "Couldn't start server.";
    }
}

void TCPServer::verificationTimeout()
{
    QByteArray error = "Verification Timeout";
    qWarning() << error;
    error.prepend(uint8_t(SOH.at(0)));
    this->socket->write(error);
    this->socket->flush();
    this->socket->waitForBytesWritten(20000);
    this->abort();
}

teTCPConnectionType TCPServer::getConnectionState() const
{
    return connectionState;
}

void TCPServer::setConnectionState(const teTCPConnectionType &value)
{
    connectionState = value;
}

void TCPServer::incomingConnection(int socketDescriptor)
{
    if (this->getConnectionState() == eNoConnection)
    {
        this->socket = new QTcpSocket(this);
        if (this->socket->setSocketDescriptor(socketDescriptor))
        {
            this->setConnectionState(eVerificationRequired);
            connect(this->socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
            connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
            this->connectionTimer.start();
            emit socketStateChanged();
        }
        else
        {
            this->socket->abort();
            qWarning() << "Connection failed.";
        }
    }
    else
    {
        QTcpSocket socket;
        if (socket.setSocketDescriptor(socketDescriptor))
        {
            QString message = "";
            message.append(SOH.at(0)).append("Connection rejected: There is already a user");
            socket.write(message.toLocal8Bit());
            socket.flush();
            socket.waitForBytesWritten();
            socket.disconnectFromHost();
        }
    }
}

void TCPServer::write(QByteArray data)
{
    if (this->isConnected())
    {
        data.prepend(uint8_t(SOH.at(0)));
        this->socket->write(data);
        this->socket->flush();
        this->socket->waitForBytesWritten(20000);
        this->data.clear();
    }
}
void TCPServer::readyRead()
{
    qWarning() << "ready read";
    data.append(this->socket->readAll());
    //    QDataStream dataStream(&data, QIODevice::ReadOnly);
    //    uint8_t start;
    //    dataStream >> start;
    if (data.at(0) != uint8_t(SOH.at(0)))
    {
        qWarning() << "TCP message format error";
        data.clear();
        return;

        if (this->getConnectionState() == eVerificationRequired)
        {
            this->connectionTimer.stop();
            this->connectionState = eConnected;
            qWarning() << "Client connected. User:" << data.mid(2) << "Socket: " << this->socket->socketDescriptor();

            emit socketConnected();
        }
        else if (this->getConnectionState() == eConnected)
        {
            emit messageReceived(data.mid(1));
        }
        else
        {
            // error
            qWarning() << "ReadyRead: No Connection";
        }
    }
}
void TCPServer::disconnected()
{
    this->connectionState = eNoConnection;
    qWarning() << "Client disconnected.";
    this->socket->abort();
    disconnect(this->socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    disconnect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    this->socket->deleteLater();
    emit socketDisconnected();
}

void TCPServer::abort()
{
    qWarning() << "";
    this->connectionState = eNoConnection;
    this->socket->abort();
}
bool TCPServer::isConnected()
{
    return this->connectionState == eConnected;
}
