#include "add_attribute_dialog.h"
#include "ui_attribute_dialog.h"
#include <QMessageBox>

AddAttributeDialog::AddAttributeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddAttributeDialog)
{
     json_object = std::make_unique<QJsonObject>();
    ui->setupUi(this);
   // json_object = std::make_unique<QJsonObject>();
    ui->attribute_default_value->setReadOnly(true);
}

AddAttributeDialog::~AddAttributeDialog()
{
    delete ui;
}

void AddAttributeDialog::on_confirm_Button_clicked()
{
    QString attribute_by_task = ui->attribute_text->toPlainText();
    if (attribute_by_task.length() == 0) {
        QMessageBox::warning(this, "Warning",  "请添加任务子属性");
        return;
    }


    QString default_value = ui->attribute_default_value->toPlainText();
     json_object->insert("sub_task", QJsonValue(attribute_by_task));
    json_object->insert("default_value", QJsonValue(default_value));
   // json_object->insert("optional", QJsonValue(attri_optional));
    this->close();
    emit SendData(json_object.get());

}


void AddAttributeDialog::on_cancel_Button_clicked()
{
    this->close();
}


void AddAttributeDialog::on_attri_type_activated(int index)
{
    if (ui->attri_type->currentText() == "部分label") {
        ui->attribute_default_value->setReadOnly(false);
    }
}

