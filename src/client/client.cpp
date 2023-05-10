#include "addnewemployeedialog.h"
#include "client.h"
#include "ui_mainwindow.h"

#include <QLabel>

MainWindow::MainWindow(QWidget *parent, const QString &hostName, quint16 port)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , employeesList(new QListWidget(this))
    , socket(new QTcpSocket(this))
{
    ui->setupUi(this);

    socket->connectToHost(hostName, port);
    connect(socket, &QIODevice::readyRead, this, &MainWindow::getResponse);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

    sendRequest(action::getAllEmployeesCode);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getResponse()
{
    QDataStream in(socket);
    quint16 messageSize = 0;

    in.setVersion(QDataStream::Qt_5_15);
    if (in.status() == QDataStream::Ok) { // maybe error version (a.k.a. else{}) at first?
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
            QString response;
            in >> response;
            messageSize = 0; // warning:

            dispatchResponse(response.split(" "));
            break; // should it be here?
        }
    }
}

void MainWindow::sendRequest(action code, const QString &data)
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

void MainWindow::dispatchResponse(QStringList response)
{
    int code = response.at(0).toInt();
    response.removeFirst();
    switch (code) {
    case getAllEmployeesCode:
        showAllEmployees(response);
        break;
    case createTaskCode:
        createTask();
        break;
    case deleteTaskCode:
        deleteTask(response);
        break;
    }
}

void MainWindow::showAllEmployees(const QStringList &employeesInformation)
{
    for (int i = 1; i < employeesInformation.size(); i += 2) {
        QString fullNameEmployee = employeesInformation.at(i);
        this->employeesList->addItem(fullNameEmployee);
    }
}
