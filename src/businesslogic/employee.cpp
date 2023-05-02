#include "employee.h"

#include <string>

#include "task.h"

const std::string &Employee::getName() const
{
    return name;
}

const std::string &Employee::getPosition() const
{
    return position;
}

void Employee::setPosition(const std::string &newPosition)
{
    position = newPosition;
}

void Employee::addTask(Task *task)
{
    tasks.append(task);
    task->setResponsible(this);
}

void Employee::removeTask(Task *task)
{
    tasks.removeOne(task);
    task->setResponsible(nullptr);
}

QList<Task *> Employee::getOverdueTasks()
{
    QList<Task *> overdueTasks;
    for (auto task : tasks) {
        if (task->getStatus() == TaskStatus::overdue)
            overdueTasks.append(task);
    }
    return overdueTasks;
}

Employee::Employee(const std::string &name, const std::string &position)
    :name(name),
    position(position),
    tasks()
{}
