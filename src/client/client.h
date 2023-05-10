#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Client : public QMainWindow
{
    Q_OBJECT
public:
    explicit Client(QWidget *parent = nullptr, const QString &hostName = "localhost", quint16 port = 2323);
    ~Client();

public slots:
    void getResponse();

private:
    enum action
    {
        getAllEmployeesCode, createEmployeeCode, deleteEmployeeCode, createTaskCode, deleteTaskCode
    };

    void sendRequest(action code, const QString &data = {});
    void dispatchResponse(QStringList response);

    void showAllEmployees(const QStringList &employeesInformation);
    void createEmployee();
    void deleteEmployee(const QStringList &employeesInformation);
    void createTask();
    void deleteTask(const QStringList &employeesInformation);

    Ui::MainWindow *ui;

    QTcpSocket *socket;

};

#endif // MAINWINDOW_H
