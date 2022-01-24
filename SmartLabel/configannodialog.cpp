#include "configannodialog.h"
#include "ui_configannodialog.h"

ConfigAnnoDialog::ConfigAnnoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigAnnoDialog)
{
    ui->setupUi(this);
    task_dialog = std::make_unique<taskDialog>();
    ui->task_listView->setFrameShape(QFrame::NoFrame);
}

ConfigAnnoDialog::~ConfigAnnoDialog()
{
    delete ui;
}

void ConfigAnnoDialog::on_custum_task_Button_clicked()
{
    task_dialog->setModal(true);
    task_dialog->show();
}

