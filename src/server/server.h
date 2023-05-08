#ifndef SERVER_H
#define SERVER_H

#include <QSqlDatabase>
#include <QTcpServer>

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
    QHostAddress address;
    int port;

//    //TODO: refactor: change the order and make blacks
//    QVector <QTcpSocket *>  sockets;
//    QByteArray buffer;
//    void sendToClient(QString message);
//    quint16 bufferMessageBlockSize;

    QString dbDriver;
    QString dbHost;
    QString dbName;
    QString dbUserName;
    QString dbPassword;

    ILogger *logger;

//    QSqlDatabase database;
};

#endif // SERVER_H
