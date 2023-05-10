#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QListWidget>
#include <QMainWindow>
#include <QTcpSocket>

#include "../businesslogic/actionCode.h"

#include "createnewtaskdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr, const QString &hostName = "localhost", quint16 port = 2323);
    ~MainWindow();

public slots:
    void getResponse();

private:
    void sendRequest(action code, const QString &data = {});
    void dispatchResponse(QStringList response);

    void showAllEmployees(const QStringList &employeesInformation);

    Ui::MainWindow *ui;
    QListWidget *employeesList;
    CreateNewTaskDialog newTaskDialog;

    QTcpSocket *socket;

private slots:
    void createTask();
};

#endif // MAINWINDOW_H
