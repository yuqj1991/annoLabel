#include "defaultannodialog.h"
#include "ui_defaultannodialog.h"

DefaultAnnoDialog::DefaultAnnoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DefaultAnnoDialog)
{
    ui->setupUi(this);
}

DefaultAnnoDialog::~DefaultAnnoDialog()
{
    delete ui;
}
