#include "server.h"

#include <QDataStream>
#include <QDate>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QTcpSocket>

#include "consolelogger.h"

Server::Server()
{}

Server::Server(ILogger *_logger)
    : logger(_logger)
{}

Server::Server(int _port, const QHostAddress &_address)
    : port(_port)
    , address(_address)
{}

Server::Server(const QString &_dbDriver
               , const QString &_dbHost
               , const QString &_dbName
               , const QString &_dbUserName
               , const QString &_dbPassword
               )
    : dbDriver(_dbDriver)
    , dbHost(_dbHost)
    , dbUserName(_dbUserName)
    , dbName(_dbName)
    , dbPassword(_dbPassword)
{}

Server::Server(int _port
               , const QHostAddress &_address
               , const QString &_dbDriver
               , const QString &_dbHost
               , const QString &_dbName
               , const QString &_dbUserName
               , const QString &_dbPassword
               , ILogger *_logger
               )
    : port(_port)
    , address(_address)
    , dbDriver(_dbDriver)
    , dbHost(_dbHost)
    , dbUserName(_dbUserName)
    , dbName(_dbName)
    , dbPassword(_dbPassword)
    , logger(_logger)
{}

void Server::run()
{
    if (this->listen(address, port))
        logger->info("Server listens " + address.toString() + " address, " + port + " port.");
    else
        logger->critical("Socket listening error.");

    db = QSqlDatabase::addDatabase(dbDriver);
    db.setHostName(dbHost);
    db.setDatabaseName(dbName);
    db.setUserName(dbUserName);
    db.setPassword(dbPassword);

    if (db.open())
        logger->info("Server opens " + db.databaseName() + " database");
    else
        logger->critical("Database opeen error.");
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    auto socket = new QTcpSocket();
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket, SIGNAL (readyRead()), this, SLOT (handleRequest()));
    connect(socket, SIGNAL (disconnect()), socket, SLOT (deleteLater()));

    sockets.push_back(socket);
    logger->info("Socket " + QString::number(socketDescriptor) + " connected.");
}

void Server::handleRequest()
{
    QTcpSocket *socket = (QTcpSocket *) sender();
    quint16 messageSize = 0;

    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_15);
    if (in.status() == QDataStream::Ok) { // maybe error version (a.k.a. else{}) at first?
        logger->info("Read " + QString::number(socket->socketDescriptor()) + " socket");

        for (;;) {
            if (messageSize == 0) {
                if (socket->bytesAvailable() < 2) { //TODO: rename 2
                    break; // should it be here?
                }
                in >> messageSize;
            }
            if (socket->bytesAvailable() < messageSize) {
                break; // should it be here?
            }
            QString request;
            in >> request;
            messageSize = 0; // warning:

            QString response = execute(request);
            send(socket, response);
            break; // should it be here?
        }
    } else {
        logger->critical("Datastream error at reading data from socket.");
    }
}

QString Server::execute(const QString &request)
{

}

void Server::send(QTcpSocket *socket, const QString &data)
{
    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_15);
    out << quint16(0) << data; // TODO: refactor output
    out.device()->seek(0);
    out << quint16(buffer.size() - sizeof(quint16));
    out << data;
    socket->write(buffer);
    logger->info("Send data to " + QString::number(socket->socketDescriptor()) + " socket.");
}
