#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class ContainerServer : public QObject
{
    Q_OBJECT
  public:
    explicit ContainerServer(QObject *parent = NULL);

    bool listen(quint16 port);

  signals:
    void listening();
    void connectionError(const QString &errorMessage);
    void clientConnected(const QString &clientAddress);
    void messageReceived(const QString &message, const QString &clientAddress);

  private slots:
    void onNewConnection();
    void onReadyRead();
    void onError(QAbstractSocket::SocketError socketError);

  private:
    QTcpServer m_tcpServer;
    QList<QTcpSocket *> m_clientConnections;
};
