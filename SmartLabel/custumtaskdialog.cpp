#include "custumtaskdialog.h"
#include "ui_custumtaskdialog.h"

CustumTaskDialog::CustumTaskDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustumTaskDialog)
{
    ui->setupUi(this);
}

CustumTaskDialog::~CustumTaskDialog()
{
    delete ui;
}
