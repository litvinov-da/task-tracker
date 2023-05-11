#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QListWidget>
#include <QMainWindow>
#include <QTcpSocket>

#include "../businesslogic/actionCode.h"


namespace Ui {
class MainWindow;
}

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

    QTcpSocket *socket;

private slots:
};

#endif // MAINWINDOW_H
