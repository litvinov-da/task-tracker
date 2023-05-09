#ifndef SERVER_H
#define SERVER_H

#include <QSqlDatabase>
#include <QTcpServer>

#include "consolelogger.h"

class ILogger;
class QSettings;

class Server : QTcpServer
{
    Q_OBJECT

public:
    Server();
    explicit Server(ILogger *logger);
    Server(int port, const QHostAddress &address);
    Server(const QString &dbDriver
           , const QString &dbHost
           , const QString &dbName
           , const QString &dbUserName
           , const QString &dbPassword
           );
    Server(int port
           , const QHostAddress &address
           , const QString &dbDriver
           , const QString &dbHost
           , const QString &dbName
           , const QString &dbUserName
           , const QString &dbPassword
           , ILogger *logger
           );

    void run();

public slots:
    void incomingConnection(qintptr socketDescriptor);
    void slotReadyRead();

private:
    QHostAddress address        {QHostAddress::Any};
    int port                    {2323};
    QVector <QTcpSocket *> sockets{};

    QString dbDriver            {"QPSQL"};
    QString dbHost              {"localhost"};
    QString dbName              {"server"};
    QString dbUserName          {"server"};
    QString dbPassword          {"passwordserver"};
    QSqlDatabase db             {};

    ILogger *logger             {new ConsoleLogger()};
};

#endif // SERVER_H
