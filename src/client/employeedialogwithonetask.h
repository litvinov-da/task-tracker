#ifndef EMPLOYEEDIALOG_H
#define EMPLOYEEDIALOG_H

#include "iemployeedialog.h"

#include <QDialog>
#include <QQueue>

namespace Ui {
class EmployeeDialog;
}

class EmployeeDialogWithOneTask : public QDialog, public IEmployeeDialog
{
    Q_OBJECT

public:
    explicit EmployeeDialogWithOneTask(QWidget *parent = nullptr);
    ~EmployeeDialogWithOneTask();

    void initEmployee(const EmployeeInfo &employee) override;
    void initTasks(const QQueue<TaskInfo> &tasks) override;
    void show() override;

private:
    Ui::EmployeeDialog *ui;

    EmployeeInfo employee;
    TaskInfo task;
};

#endif // EMPLOYEEDIALOG_H
