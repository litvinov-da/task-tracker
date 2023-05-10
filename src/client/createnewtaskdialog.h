#ifndef CREATENEWTASKDIALOG_H
#define CREATENEWTASKDIALOG_H

#include <QDialog>

namespace Ui {
class CreateNewTaskDialog;
}

class CreateNewTaskDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateNewTaskDialog(QWidget *parent = nullptr);
    ~CreateNewTaskDialog();

private:
    Ui::CreateNewTaskDialog *ui;
};

#endif // CREATENEWTASKDIALOG_H
