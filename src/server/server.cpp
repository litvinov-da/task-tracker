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

#include "../businesslogic/actionCode.h"

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

Server::~Server()
{
    delete logger;
}

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
    if (in.status() == QDataStream::Ok) {
        logger->info("Read " + QString::number(socket->socketDescriptor()) + " socket");

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
            QString request;
            in >> request;
            messageSize = 0;

            QString response = execute(request.split(" "));
            sendResponse(socket, response);
            break;
        }
    } else {
        logger->critical("Datastream error at reading data from socket.");
    }
}

void Server::sendResponse(QTcpSocket *socket, const QString &data) //rename data par
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

QString Server::execute(QStringList request)
{
    int code = request.at(0).toInt();
    request.removeFirst();
    if (code == getAllEmployeesCode) {
        return getAllEmployees(request);
    } else if (code == createTaskCode) {
        insertTask(request);
        return {};
    } else if (code == deleteTaskCode) {
        deleteTaskById(request);
        return {};
    }
}

QString Server::getAllEmployees(const QStringList &employeesInformation)
{
    QString response;
    QSqlQueryModel employees;
    employees.setQuery("SELECT * FROM employees");
    for (int i = 0; i < employees.rowCount(); ++i) {
            response += employees.record(i).value("id").toString();
            response += employees.record(i).value("full_name").toString();
            response += employees.record(i).value("position").toString();
    }
    return response;
}

void Server::insertTask(const QStringList &employeesInformation)
{
    QSqlQuery insertQuery;
    insertQuery.prepare(
                "INSERT INTO tasks (name, overdue, status, responsible) "
                "VALUES (:name, :ovedue, :status, :responsible)"
                );
    insertQuery.bindValue(":name", employeesInformation.at(0));
    insertQuery.bindValue(":overdue", employeesInformation.at(1));
    insertQuery.bindValue(":status", employeesInformation.at(2));
    insertQuery.bindValue("responsible", employeesInformation.at(3));
    insertQuery.exec();
}

void Server::deleteTaskById(const QStringList &employeesInformation)
{
    QSqlQuery deleteQuery;
    deleteQuery.prepare("DELETE FROM tasks WHERE id = :id");
    deleteQuery.bindValue(":id", employeesInformation.at(0));
    deleteQuery.exec();
}
