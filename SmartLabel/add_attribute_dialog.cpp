#include "add_attribute_dialog.h"
#include "ui_attribute_dialog.h"
#include <QMessageBox>
#include <qjsonarray.h>
#include <QDebug>

QStringList AddAttributeDialog::get_labels(const QString &labels) {
  QStringList result = labels.split(";");
  if (!result.size())
    QMessageBox::warning(this, "warning", "请以英文符号;作为分割符!");
  return result;
}

AddAttributeDialog::AddAttributeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddAttributeDialog)
{
     json_object = std::make_unique<QJsonObject>();
    ui->setupUi(this);
    ui->attribute_default_value->setReadOnly(true);
}

AddAttributeDialog::~AddAttributeDialog()
{
    delete ui;
}

void AddAttributeDialog:: recievd_labels_data(QStringList& data) {
    task_labels_ = data;
}

void AddAttributeDialog::on_confirm_Button_clicked()
{
    QString attribute_by_task = ui->attribute_text->toPlainText();
    if (attribute_by_task.length() == 0) {
        QMessageBox::warning(this, "Warning",  "请添加任务子属性");
        return;
    }
    QStringList default_values = {"all_labels"};
    if (ui->attri_type->currentText() == "部分label") {
      default_values = get_labels(ui->attribute_default_value->toPlainText());
      if (default_values.length() == 0)
        return;
      for (auto i = 0; i <default_values.size(); i++) {
          if (!task_labels_.contains(default_values[i])) {
              QMessageBox::warning(this, "warning", "the attr which specialised is not belong to task!") ;
              return;
          }
      }
    }

    json_object->insert("sub_task", QJsonValue(attribute_by_task));
    json_object->insert("labels", QJsonValue(QJsonArray::fromStringList(default_values)));
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
    }else {
        ui->attribute_default_value->setReadOnly(true);
    }
}

