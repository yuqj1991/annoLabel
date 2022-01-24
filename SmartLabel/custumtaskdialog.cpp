#include "custumtaskdialog.h"
#include "ui_custumtaskdialog.h"

CustumTaskDialog::CustumTaskDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustumTaskDialog)
{
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
    this->close();
    auto task = ui->anno_stackedWidget->currentWidget();
    // 还要总结新建项目的结果
    // emit

}

