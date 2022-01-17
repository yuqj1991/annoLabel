#include "point_dialog.h"
#include "ui_point_dialog.h"
#include <QMessageBox>

PointDialog::PointDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PointDialog)
{

    ui->setupUi(this);
    ui->num_lineEdit->setValidator(new FixUpValidator(1, 35, this));
}

PointDialog::~PointDialog()
{
    delete ui;
}

void PointDialog::on_confirmedPushButton_clicked()
{
    QString points_num_str = ui->num_lineEdit->text();
    if (points_num_str.length() == 0) {
        QMessageBox::warning(this, "warning", "请输入有效数字1-35！");
        return;
    }
    int points = points_num_str.toInt();
    if (points >=36 || points <=0) {
        QMessageBox::warning(this, "warning", "请输入有效数字1-35！");
        return;
    }
    emit Send_points_data(points);
    this->close();
}


void PointDialog::on_cancellPushButton_clicked()
{
    this->close();
}

