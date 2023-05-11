#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , connectionToServer()
{
    ui->setupUi(this);
    connect(this, &MainWindow::initialization, this, &MainWindow::showAllEmployees);

    emit initialization();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showAllEmployees()
{
    QStringList employeesInformation = connectionToServer.getAllEmployees();
    for (int i = 1; i < employeesInformation.size(); i += 2) {
        QString fullNameEmployee = employeesInformation.at(i);
        ui->employees->addItem(fullNameEmployee);
    }
}
