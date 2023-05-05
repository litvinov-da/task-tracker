#ifndef SERVER_H
#define SERVER_H

#include <QSqlDatabase>
#include <QTcpServer>



class Server : QTcpServer
{
    Q_OBJECT

public:
    Server();
    QTcpSocket *socket;

private:
    QVector <QTcpSocket *>  sockets;
    QByteArray buffer;
    void sendToClient(QString message);
    quint16 bufferMessageBlockSize;
    QSqlDatabase database;
public slots:
    void incomingConnection(qintptr socketDescriptor);
    void slotReadyRead();
};

#endif // SERVER_H
