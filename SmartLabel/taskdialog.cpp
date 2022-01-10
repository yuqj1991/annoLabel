#include "taskdialog.h"
#include "ui_taskdialog.h"
#include <iostream>
#include <QDebug>
#include <QMessageBox>


QStringList taskDialog::get_labels(const QString& labels) {
    QStringList result =  labels.split(";");
    if (!result.size())
        QMessageBox::warning(this, "warning", "请以英文符号;作为分割符!");
    return result;

}

taskDialog::taskDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::taskDialog)
{
    ui->setupUi(this);
     attribute_dialog =std::make_unique<AddAttributeDialog>();
     attr_set =std::make_unique<QJsonObject>();
     connect(attribute_dialog.get(),  SIGNAL(SendData(QJsonObject*)),  this,  SLOT(receive_attribute_data(QJsonObject*)));
}

taskDialog::~taskDialog()
{
    delete ui;
}


void taskDialog::on_add_attribute_clicked()
{
    attribute_dialog->setModal(true);

    attribute_dialog->show();

}

void taskDialog::receive_attribute_data(QJsonObject* json_object)
{
    QString s_s("[sub_attr: ");
    QString sub_task = json_object->value("sub_task").toString();
    if (attr_set->contains(sub_task)) {
        QMessageBox::warning(this, "warning", "the current attr has beed added! please add it again!");
        return;
    }
    attr_set->insert(sub_task, QJsonValue("sub_attr"));
    s_s += json_object->value("sub_task").toString();
    s_s +="](default_value: ";
    s_s += json_object->value("default_value").toString();
    s_s += "; optional: ";
    s_s += QString::number(json_object->value("optional").toBool());
    s_s += ")";

    QLabel* attri_label = new QLabel();
    attri_label->setText(s_s);
    attri_label->setStyleSheet("QLabel{border:2px solid rgb(27, 23, 10);}");

     QFont font("Arial", 12);
     attri_label->setFont(font);
     attri_label->adjustSize();

     grid_layout.addWidget(attri_label);
     ui->groupBox_attribute->setLayout(&grid_layout);
}


void taskDialog::on_taskCancell_clicked()
{
    this->close();
}


void taskDialog::on_taskConfirmed_clicked()
{
    QString s_task = ui->text_anno_task->toPlainText();
    if (s_task.length() == 0) {
        QMessageBox::information(this, "info", "请添加标注任务名称!");
        return;
    }
    QString task_type = ui->TaskType_ComboBox->currentText();

    // emit 发送task_type信号出去

    QString s_labels = ui->text_labels->toPlainText();
    if (s_labels.length() == 0) {
        QMessageBox::information(this, "info", "请添加标签!");
        return;
    }
    auto labels_list = get_labels(s_labels);
    //emit 发送labels_list信号出去;

    /*
     * 输出的数据标识
**/



}



