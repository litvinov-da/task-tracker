#ifndef CONNECTIONTOSERVER_H
#define CONNECTIONTOSERVER_H

#include <QObject>

#include "iconnectiontoserver.h"

#include "../businesslogic/actionCode.h"

class QTcpSocket;

class SocketConnection : public IConnectionToServer
{
    Q_OBJECT
public:
    explicit SocketConnection(QObject *parent = nullptr
                                , const QString &serverHostName = "localhost"
                                , quint16 serverPort = 2323
                                );

    QStringList getAllEmployees() override;
private:
    void getRespond();
    void sendRequest(action code, const QString &data = {});

    const QString serverHostName;
    const quint16 serverPort;
    QTcpSocket *socket;

    QString bufferRespond;
    bool isBufferRespondReady;
};

#endif // CONNECTIONTOSERVER_H
