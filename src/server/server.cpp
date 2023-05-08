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
    : port(2323)
    , address(QHostAddress::Any)
    , dbDriver("QPSQL")
    , dbHost("localhost")
    , dbUserName("server")
    , dbName("server")
    , dbPassword("passwordserver")
    , logger(new ConsoleLogger())
{}

Server::Server(ILogger *_logger)
    : port(2323)
    , address(QHostAddress::Any)
    , dbDriver("QPSQL")
    , dbHost("localhost")
    , dbUserName("server")
    , dbName("server")
    , dbPassword("passwordserver")
    , logger(_logger)
{}

Server::Server(int _port, const QHostAddress &_address)
    : port(_port)
    , address(_address)
    , dbDriver("QPSQL")
    , dbHost("localhost")
    , dbUserName("server")
    , dbName("server")
    , dbPassword("passwordserver")
    , logger(new ConsoleLogger())
{}

Server::Server(const QString &_dbDriver
               , const QString &_dbHost
               , const QString &_dbName
               , const QString &_dbUserName
               , const QString &_dbPassword
               )
    : port(2323)
    , address(QHostAddress::Any)
    , dbDriver(_dbDriver)
    , dbHost(_dbHost)
    , dbUserName(_dbUserName)
    , dbName(_dbName)
    , dbPassword(_dbPassword)
    , logger(new ConsoleLogger())
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

//void Server::sendToClient(QString message)
//{
//    buffer.clear();

//    QDataStream out(&buffer, QIODevice::WriteOnly);
//    out.setVersion(QDataStream::Qt_5_15); //mark how works this
//    out << quint16(0) << message;
//    out.device()->seek(0);
//    out << quint16(buffer.size() - sizeof(quint16));
//    for (QTcpSocket *socket : sockets) {
//        socket->write(buffer);
//    }
//}

//void Server::incomingConnection(qintptr socketDescriptor)
//{
//    socket = new QTcpSocket();
//    socket->setSocketDescriptor(socketDescriptor);
//    connect(socket, SIGNAL (readyRead()), this, SLOT (slotReadyRead()));
//    connect(socket, SIGNAL (disconnect()), socket, SLOT (deleteLater()));

//    sockets.push_back(socket);
//    qDebug() << "socket " << socketDescriptor << " connected." << Qt::endl;
//}

//void Server::slotReadyRead()
//{
//    socket = (QTcpSocket *) sender();

//    QDataStream in(socket);
//    in.setVersion(QDataStream::Qt_5_15);
//    if (in.status() == QDataStream::Ok) {
//        qDebug() << Qt::endl << "read...";

//        for (;;) {
//            if (bufferMessageBlockSize == 0) {
//                if (socket->bytesAvailable() < 2) { //TODO: rename 2
//                    break;
//                }
//                in >> bufferMessageBlockSize;
//            }
//            if (socket->bytesAvailable() < bufferMessageBlockSize) {
//                break;
//            }
//            QString inputString;
//            in >> inputString;
//            bufferMessageBlockSize = 0;
//            sendToClient(inputString);
//            qDebug() << Qt::endl << " message: " << inputString;
//            break;
//        }
//    } else {
//        qDebug() << Qt::endl << "datastream error.";
//    }
//}
