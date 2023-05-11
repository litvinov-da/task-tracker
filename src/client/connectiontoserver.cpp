#include "connectiontoserver.h"

#include <QDataStream>
#include <QTcpSocket>


ConnectionToServer::ConnectionToServer(QObject *parent, const QString &_serverHostName, quint16 _serverPort)
    : QObject{parent}
    , serverHostName(_serverHostName)
    , serverPort(_serverPort)
    , socket(new QTcpSocket(this))
{
    socket->connectToHost(serverHostName, serverPort);
    connect(socket, &QTcpSocket::readyRead, this, &ConnectionToServer::getRespond);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
}

QStringList ConnectionToServer::getAllEmployees()
{
    sendRequest(action::getAllEmployeesCode);
    while (!isBufferRespondReady) {} // TODO: check if isBufferRespondReady will change outside execution flow
    return bufferRespond.split(" ");
}

void ConnectionToServer::getRespond()
{
    isBufferRespondReady = false;
    bufferRespond.clear();
    QDataStream in(socket);
    quint16 messageSize = 0;

    in.setVersion(QDataStream::Qt_5_15);
    if (in.status() == QDataStream::Ok) {
        for (;;) {
            if (messageSize == 0) {
                if (socket->bytesAvailable() < 2) {
                    break;
                }
                in >> messageSize;
            }
            if (socket->bytesAvailable() < messageSize) {
                break;
            }
            in >> bufferRespond;
            isBufferRespondReady = true;
            messageSize = 0;
            break;
        }
    }
}

void ConnectionToServer::sendRequest(action code, const QString &data)
{
    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_15);
    out << quint16(0) << code << data;
    out.device()->seek(0);
    out << quint16(buffer.size() - sizeof(quint16));
    out << code << data;
    socket->write(buffer);
}
