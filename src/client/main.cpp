#include "mainwindow.h"

#include <QApplication>

int main(int argc, char **argv)
{
    //run
    QApplication app(argc, argv);

    MainWindow client;
    client.show();

    return app.exec();
}
