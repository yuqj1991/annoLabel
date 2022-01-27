#include "defaultannodialog.h"
#include "ui_defaultannodialog.h"
#include "wegits_common.h"
#include <QFile>
#include<QMessageBox>
#include<QJsonArray>

QStringList DefaultAnnoDialog::get_labels(const QString &labels) {
  QStringList result = labels.split(";");
  if (!result.size())
    QMessageBox::warning(this, "warning", "请以英文符号;作为分割符!");
  return result;
}

DefaultAnnoDialog::DefaultAnnoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DefaultAnnoDialog)
{
    ui->setupUi(this);
    fileDialog = std::make_unique<QFileDialog>();
    points_dialog = std::make_unique<PointDialog>();
    connect(points_dialog.get(), SIGNAL(Send_points_data(int&)), this, SLOT(reveive_points_data(int&)));
}

DefaultAnnoDialog::~DefaultAnnoDialog()
{
    delete ui;
}

bool DefaultAnnoDialog::get_task_data(QJsonObject &config_task) {
  // project_name Textlabel
  QString project_name = ui->project_textEdit->toPlainText();
  if (project_name.length() == 0) {
    QMessageBox::warning(this, tr("warning"), "请添加项目名称!");
    return false;
  }
  config_task.insert(AnnoTool::WidgetUtils::project_name, QJsonValue(project_name));


  // image_folder Textlabel
  QString fileDir_Path = ui->fileDir_textEdit->toPlainText();
  if (fileDir_Path.length() == 0) {
    QMessageBox::warning(this, tr("warning"), "请添加图片文件夹目录!");
    return false;
  }
  config_task.insert(AnnoTool::WidgetUtils::images_path, QJsonValue(fileDir_Path));
  // anno_file_folder anno_textlabel
  QString annoDir_path = ui->save_anno_textEdit->toPlainText();
  if (annoDir_path.length() == 0) {
    QMessageBox::warning(this, tr("warning"), "请添加图片文件夹目录!");
    return false;
  }
  config_task.insert(AnnoTool::WidgetUtils::annos_path, QJsonValue(annoDir_path));

  // anno_task
  QJsonArray anno_tasks;
  QJsonObject anno;
  // anno_name
  anno.insert(AnnoTool::WidgetUtils::anno_name, "...");
  // anno_type ComboBox
  AnnoTool::AnnoType anno_type =
      AnnoTool::WidgetUtils::getAnnoType(ui->annoType_comboBox->currentText());

  anno.insert(AnnoTool::WidgetUtils::anno_type, QJsonValue(AnnoTool::WidgetUtils::ConvertJsonValue(anno_type)));
  if (anno_type == AnnoTool::AnnoType::Points) {
    anno.insert(AnnoTool::WidgetUtils::anno_points, QJsonValue(points_num));
  }
  // annolabels Textlabel
  QString str_labels = ui->labels_textEdit->toPlainText();
  if (str_labels.length() == 0) {
    QMessageBox::warning(this, tr("warning"), "请添加标注标签!");
    return false;
  }
  QStringList project_labels = get_labels(str_labels);
  anno.insert(AnnoTool::WidgetUtils::anno_labels,
                     QJsonValue(QJsonArray::fromStringList(project_labels)));
  anno_tasks.push_back(anno);
  config_task.insert(AnnoTool::WidgetUtils::anno_tasks, anno_tasks);
  config_task.insert(AnnoTool::WidgetUtils::is_defaulted, QJsonValue(false));

  return true;
}

void DefaultAnnoDialog::on_open_dir_Button_clicked() {
  image_folder_path = QFileDialog::getExistingDirectory(
      this, "选择图片文件夹", "./", QFileDialog::ShowDirsOnly);
  ui->fileDir_textEdit->setText(image_folder_path);
}


void DefaultAnnoDialog::on_open_anno_Button_clicked()
{
    anno_folder_path = QFileDialog::getExistingDirectory(
        this, "选择文件夹保存位置", "./", QFileDialog::ShowDirsOnly);
    ui->save_anno_textEdit->setText(anno_folder_path);
}

void DefaultAnnoDialog::reveive_points_data(int& point_num){
    points_num = point_num;
}

void DefaultAnnoDialog::on_annoType_comboBox_activated(int index)
{
    if (ui->annoType_comboBox->currentText() == "点_points") {
        points_dialog.get()->setModal(true);
        points_dialog.get()->show();
    }
}

