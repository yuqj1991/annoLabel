#include "firstpagedialog.h"
#include "ui_firstpagedialog.h"

FirstPageDialog::FirstPageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FirstPageDialog)
{
    ui->setupUi(this);
}

FirstPageDialog::~FirstPageDialog()
{
    delete ui;
}

void FirstPageDialog::on_label_linkActivated(const QString &link)
{

}

