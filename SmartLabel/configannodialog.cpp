#include "configannodialog.h"
#include "ui_configannodialog.h"

ConfigAnnoDialog::ConfigAnnoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigAnnoDialog)
{
    ui->setupUi(this);
}

ConfigAnnoDialog::~ConfigAnnoDialog()
{
    delete ui;
}
