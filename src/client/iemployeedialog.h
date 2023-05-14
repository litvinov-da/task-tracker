#ifndef IEMPLOYEEDIALOG_H
#define IEMPLOYEEDIALOG_H

#include "../businesslogic/employeeInfo.h"
#include "../businesslogic/taskInfo.h"

class IEmployeeDialog
{
public:
    virtual ~IEmployeeDialog() = 0;

    virtual void initEmployee(const EmployeeInfo &employee) = 0;
    virtual void initTasks(const QQueue<TaskInfo> &tasks) = 0;

    virtual void show();
};

#endif // IEMPLOYEEDIALOG_H
