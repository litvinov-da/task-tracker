#include "createnewtaskdialog.h"
#include "ui_createnewtaskdialog.h"

CreateNewTaskDialog::CreateNewTaskDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateNewTaskDialog)
{
    ui->setupUi(this);
}

CreateNewTaskDialog::~CreateNewTaskDialog()
{
    delete ui;
}
