#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "connectiontoserver.h"

#include <QListWidget>
#include <QMainWindow>
#include <QTcpSocket>

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

signals:
    void initialization();
};

#endif // MAINWINDOW_H
