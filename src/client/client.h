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
    void sendRequest(const QString &request);
    void updateWidgets(const QString &dataChanges);
    void getAllEmployees();

    Ui::MainWindow *ui;

    QTcpSocket *socket;
};

#endif // MAINWINDOW_H
