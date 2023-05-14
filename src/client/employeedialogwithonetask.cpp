#include "employeedialogwithonetask.h"
#include "ui_employeedialog.h"

EmployeeDialogWithOneTask::EmployeeDialogWithOneTask(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EmployeeDialog)
{
    ui->setupUi(this);
}

EmployeeDialogWithOneTask::~EmployeeDialogWithOneTask()
{
    delete ui;
}

void EmployeeDialogWithOneTask::initEmployee(const EmployeeInfo &_employee)
{
    employee = _employee;
}

void EmployeeDialogWithOneTask::initTasks(const QQueue<TaskInfo> &tasks)
{
    task = tasks.first();
}

void EmployeeDialogWithOneTask::show()
{
    ui->fullName->setText(employee.fullName);
    ui->position->setText(employee.position);

    ui->tasks->addItem(task.name);
}

