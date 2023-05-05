#ifndef TASK_H
#define TASK_H

#include <QDate>
#include <string>

class Employee;

enum TaskStatus {
    noResponsible, //change to notSet
    onWork,
    done,
    overdue //delete
};

class Task
{
    std::string name;
    Task *parent;
    Employee *responsible;
    QDate deadline;
    bool isDone;
public:
    Task(const std::string &_name,
         const QDate &_deadline,
         Employee *_responsible = nullptr,
         bool _isDone = false,
         Task *_parent = nullptr
            );
    ~Task()
        = default;
    Task(const Task &task)
        = delete;
    Task& operator=(const Task &task)
        = delete;

    const std::string &getName() const;
    void setName(const std::string &newName);
    Employee *getResponsible() const;
    void setResponsible(Employee *newResponsible);
    Task *getParent() const;
    const QDate &getDeadline() const;
    TaskStatus getStatus() const;
    void makeDone();
};

#endif // TASK_H
