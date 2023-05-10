#include <QCoreApplication>
#include <QDebug>
#include "master.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Master *master = new Master();
    if (master->init())
    {
        qWarning() << "master init ok";
    }
    master->starTCPConnection();

    return a.exec();
}
