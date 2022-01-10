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
    bool attri_optional = ui->optional_Button->isChecked();

    if (!attri_optional) {
        auto result = QMessageBox::question(this, "info",  "请确认此属性不是必须标注?");
        if (result == QMessageBox::No) {
            return;
        }
    }

    QString default_value = ui->attribute_default_value->toPlainText();
     json_object->insert("sub_task", QJsonValue(attribute_by_task));
    json_object->insert("default_value", QJsonValue(default_value));
    json_object->insert("optional", QJsonValue(attri_optional));
    this->close();
    emit SendData(json_object.get());

}


void AddAttributeDialog::on_cancel_Button_clicked()
{
    this->close();
}

