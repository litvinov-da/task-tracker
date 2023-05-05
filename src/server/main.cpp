#include "server.h"

#include <QtCore>
#include <QSqlDatabase>
#include <QTcpServer>

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);

   Server server;


    return app.exec();
}
