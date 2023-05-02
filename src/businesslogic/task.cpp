#include "task.h"

#include "employee.h"

Employee *Task::getResponsible() const
{
    return responsible;
}

void Task::setResponsible(Employee *newResponsible)
{
    responsible->removeTask(this);
    responsible = newResponsible;
    responsible->addTask(this);
}

Task *Task::getParent() const
{
    return parent;
}

const QDate &Task::getDeadline() const
{
    return deadline;
}

TaskStatus Task::getStatus() const
{
    if (isDone)
        return TaskStatus::done;
    else if (!responsible)
        return TaskStatus::noResponsible;
    else if (QDate::currentDate() > deadline)
        return TaskStatus::overdue;
    else
        return TaskStatus::onWork;
}

void Task::makeDone()
{
    isDone = true;
}

const std::string &Task::getName() const
{
    return name;
}

void Task::setName(const std::string &newName)
{
    name = newName;
}
