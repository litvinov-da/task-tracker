#include "server.h"

#include <QtCore>
#include <QSqlDatabase>
#include <QTcpServer>

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);

    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "myCompany", "testTask");


    Server server;


    return app.exec();
}
