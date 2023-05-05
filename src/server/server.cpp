#include "server.h"

#include <QDataStream>
#include <QDate>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QTcpSocket>

Server::Server() // TODO: configs for socket connection & smth for independent api
{
    if (this->listen(QHostAddress::Any, 2323)) {
        qDebug() << Qt::endl << "socket listening OK.";
    } else {
        qDebug() << Qt::endl <<  "socket listening error.";
    }
    bufferMessageBlockSize = 0;

    database = QSqlDatabase::addDatabase("QPSQL");
    database.setHostName("localhost");
    database.setDatabaseName("server");
    database.setUserName("server");
    database.setPassword("serverpassword");
    if (database.open()) {
        qDebug() << Qt::endl << "connection to database OK.";

        QSqlQuery allEmployees;
        allEmployees.exec("SELECT * FROM employees");
        while (allEmployees.next()) {
                   qDebug()
                        << Qt::endl << "Record: "
                        << allEmployees.value(1).toString()
                        << allEmployees.value(2).toString()
                           ;
        }

        QSqlTableModel allTasks;
        allTasks.setTable("tasks");
        allTasks.select();
        for (int i = 0; i < allTasks.rowCount(); ++i) {
            qDebug()
                 << Qt::endl << "Record: "
                 << allTasks.record(i).value("name").toString()
                 << allTasks.record(i).value("overdue").toDate()
                    ;
        }
    } else {
        qDebug() << Qt::endl << "connection to database error";
        qDebug() << Qt::endl << QSqlDatabase::drivers();
    }


}

void Server::sendToClient(QString message)
{
    buffer.clear();

    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_15); //mark how works this
    out << quint16(0) << message;
    out.device()->seek(0);
    out << quint16(buffer.size() - sizeof(quint16));
    for (QTcpSocket *socket : sockets) {
        socket->write(buffer);
    }
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    socket = new QTcpSocket();
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket, SIGNAL (readyRead()), this, SLOT (slotReadyRead()));
    connect(socket, SIGNAL (disconnect()), socket, SLOT (deleteLater()));

    sockets.push_back(socket);
    qDebug() << "socket " << socketDescriptor << " connected." << Qt::endl;
}

void Server::slotReadyRead()
{
    socket = (QTcpSocket *) sender();

    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_15);
    if (in.status() == QDataStream::Ok) {
        qDebug() << Qt::endl << "read...";

        for (;;) {
            if (bufferMessageBlockSize == 0) {
                if (socket->bytesAvailable() < 2) { //rename 2
                    break;
                }
                in >> bufferMessageBlockSize;
            }
            if (socket->bytesAvailable() < bufferMessageBlockSize) {
                break;
            }
            QString inputString;
            in >> inputString;
            bufferMessageBlockSize = 0;
            sendToClient(inputString);
            qDebug() << Qt::endl << " message: " << inputString;
            break;
        }
    } else {
        qDebug() << Qt::endl << "datastream error.";
    }
}
