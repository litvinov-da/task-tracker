#ifndef ICONNECTIONTOSERVER_H
#define ICONNECTIONTOSERVER_H

#include <QObject>

class IConnectionToServer : public QObject
{
    Q_OBJECT

public:
    explicit IConnectionToServer(QObject *parent = nullptr)
        :QObject(parent)
    {
    }

    virtual ~IConnectionToServer() = 0;

    virtual QStringList getAllEmployees() = 0;
};

#endif // ICONNECTIONTOSERVER_H
