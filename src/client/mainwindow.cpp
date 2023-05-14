#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "employeedialogwithonetask.h"
#include "iemployeedialog.h"

#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , connectionToServer(new SocketConnection(this))
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
    employeesInformation = connectionToServer.getAllEmployees(); //TODO: add facade/adaptor
    for (int i = 1; i < employeesInformation.size(); i += 2) {
        QString fullNameEmployee = employeesInformation.at(i);
        ui->employees->addItem(fullNameEmployee);
    }
}

void MainWindow::on_getEmployee_clicked()
{
    IEmployeeDialog *employeeDialog = new EmployeeDialogWithOneTask(this);
    EmployeeInfo employeeInfo = {getEmployeeInformationByName(ui->employees->currentItem()->text())};
    employeeDialog->initEmployee(employeeInfo);
    employeeDialog->initTasks(getEmployeeTasks(employeeInfo.id));
    employeeDialog->show();
}

