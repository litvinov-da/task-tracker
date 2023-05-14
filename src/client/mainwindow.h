#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "connectiontoserver.h"

#include <QListWidget>
#include <QMainWindow>
#include <QTcpSocket>

#include "../businesslogic/employeeInfo.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void showAllEmployees();

    Ui::MainWindow *ui;

    ConnectionToServer connectionToServer;
    QVector<EmployeeInfo> employeesInformation;

signals:
    void initialization();

private slots:
    void on_getEmployee_clicked();
};

#endif // MAINWINDOW_H
