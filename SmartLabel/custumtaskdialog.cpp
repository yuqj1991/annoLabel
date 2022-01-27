#include "custumtaskdialog.h"
#include "ui_custumtaskdialog.h"
#include <iostream>

CustumTaskDialog::CustumTaskDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustumTaskDialog)
{
    setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint);
    ui->setupUi(this);
    custum_dialog = std::make_unique<ConfigAnnoDialog>();
    default_dialog = std::make_unique<DefaultAnnoDialog>();
    ui->anno_stackedWidget->addWidget(custum_dialog.get());
    ui->anno_stackedWidget->addWidget(default_dialog.get());
    ui->anno_stackedWidget->setCurrentWidget(default_dialog.get());

}

CustumTaskDialog::~CustumTaskDialog()
{
    delete ui;
}

void CustumTaskDialog::on_custum_anno_Button_clicked()
{
    ui->anno_stackedWidget->setCurrentWidget(custum_dialog.get());
}


void CustumTaskDialog::on_default_anno_Button_clicked()
{
    ui->anno_stackedWidget->setCurrentWidget(default_dialog.get());
}


void CustumTaskDialog::on_return_Button_clicked()
{
    auto task_widget = ui->anno_stackedWidget->currentWidget();

    QJsonObject custumTask_object;
    if (custum_dialog.get() == dynamic_cast<ConfigAnnoDialog*>(task_widget)) {
        if (!custum_dialog->get_task_data(custumTask_object)) {
            QJsonObject().swap(custumTask_object);
            QMessageBox::warning(this, "error", "自定义任务出错");
            return;
        }
    } else if (default_dialog.get() == dynamic_cast<DefaultAnnoDialog*>(task_widget)) {
        if (!default_dialog->get_task_data(custumTask_object)) {
            QJsonObject().swap(custumTask_object);
            QMessageBox::warning(this, "error", "自定义任务出错");
            return;
        }
    } else {
        return;
    }
    emit Send_custum_task_dialog(custumTask_object);
    this->close();
}


void CustumTaskDialog::on_cancell_Button_clicked()
{
    this->close();
}

