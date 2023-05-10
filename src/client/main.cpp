#include "client.h"

#include <QApplication>

int main(int argc, char **argv)
{
    //run
    QApplication app(argc, argv);

    Client client;
    client.show();

    return app.exec();
}
