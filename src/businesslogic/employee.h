#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QList>
#include <string>

class Task;

class Employee
{
    std::string name;
    std::string position;
    QList<Task *> tasks;
public:
    Employee(const std::string &name, const std::string &position);

    const std::string &getName() const;
    const std::string &getPosition() const;
    void setPosition(const std::string &newPosition);

    void addTask(Task *task);
    void removeTask(Task *task);

    QList<Task *> getOverdueTasks();
};

#endif // EMPLOYEE_H
