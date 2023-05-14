#ifndef TASKINFO_H
#define TASKINFO_H

#include <QString>


struct TaskInfo
{
    QString id;
    QString name;
    QString parent;
    QString overdue;
    QString status;
    QString responsible;
};

#endif // TASKINFO_H
