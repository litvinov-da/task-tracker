#include <QtCore>
#include <QSqlDatabase>

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL", "workDB");
    db.setHostName("localhost");
    db.setPassword("password");
    db.setUserName("postgres");

    if (!db.open())
        return 1;

    return app.exec();
}
