#include <QCoreApplication>
#include "containerserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ContainerServer server;

    QObject::connect(&server, &ContainerServer::listening, []() { qDebug() << "Server is listening..."; });

    QObject::connect(&server, &ContainerServer::connectionError, [](const QString &errorMessage) {
        qWarning() << "Connection error:" << errorMessage;
    });

    QObject::connect(&server, &ContainerServer::clientConnected, [](const QString &clientAddress) {
        qDebug() << "Client connected:" << clientAddress;
    });

    QObject::connect(&server,
                     &ContainerServer::messageReceived,
                     [](const QString &message, const QString &clientAddress) {
                         qDebug() << "Received message from" << clientAddress << ":" << message;
                     });

    if (server.listen(1234))
    {
        qDebug() << "Listening on port 1234...";
    }
    else
    {
        qWarning() << "Failed to listen on port 1234!";
    }

    return a.exec();
}
