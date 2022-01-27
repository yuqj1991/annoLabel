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
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
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
    QJsonObject json_object;
    json_object.insert(AnnoTool::WidgetUtils::attr_name, QJsonValue(attribute_by_task));
    json_object.insert(AnnoTool::WidgetUtils::attr_map_labels, QJsonValue(QJsonArray::fromStringList(default_values)));
    emit SendData(json_object);
    clear();
    this->close();

}


void AddAttributeDialog::on_cancel_Button_clicked()
{
    clear();
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


void AddAttributeDialog::clear() {
    ui->attribute_text->setText("");
    ui->attribute_default_value->setText("");
    ui->attribute_default_value->setReadOnly(true);
}
