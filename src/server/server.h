#ifndef SERVER_H
#define SERVER_H

#include <QSqlDatabase>
#include <QTcpServer>

class QSettings;


class Server : QTcpServer
{
    Q_OBJECT

public:
    Server();
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
           );

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

//    QSqlDatabase database;
};

#endif // SERVER_H
