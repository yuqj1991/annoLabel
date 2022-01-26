#include "configannodialog.h"
#include "ui_configannodialog.h"
#include <QMessageBox>

ConfigAnnoDialog::ConfigAnnoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigAnnoDialog)
{
    ui->setupUi(this);
    task_dialog = std::make_unique<taskDialog>();
    ui->task_listView->setFrameShape(QFrame::NoFrame);
    connect(task_dialog.get(), SIGNAL(Send_task_data(QJsonObject)), this, SLOT(recive_task_dialog_data(QJsonObject)));
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


bool ConfigAnnoDialog::get_task_data(QJsonObject &config_task) {
  // project_name Textlabel
  QString project_name = ui->project_textEdit->toPlainText();
  if (project_name.length() == 0) {
    QMessageBox::warning(this, tr("warning"), "请添加项目名称!");
    return false;
  }
  config_task.insert("project_name", QJsonValue(project_name));

  // image_folder Textlabel
  QString fileDir_Path = ui->fileDir_textEdit->toPlainText();
  if (fileDir_Path.length() == 0) {
    QMessageBox::warning(this, tr("warning"), "请添加图片文件夹目录!");
    return false;
  }
  config_task.insert("image_folder", QJsonValue(fileDir_Path));
  // anno_file_folder anno_textlabel
  QString annoDir_path = ui->fileDir_textEdit->toPlainText();
  if (annoDir_path.length() == 0) {
    QMessageBox::warning(this, tr("warning"), "请添加图片文件夹目录!");
    return false;
  }
  config_task.insert("anno_folder", QJsonValue(annoDir_path));

  // add sub_tasks
  config_task.insert("anno_tasks", anno_tasks);
  return true;
}


void ConfigAnnoDialog::on_open_fileDir_Button_clicked()
{
    image_Dir_path = QFileDialog::getExistingDirectory(
        this, "选择图片文件夹位置", "./", QFileDialog::ShowDirsOnly);
    ui->fileDir_textEdit->setText(image_Dir_path);
}


void ConfigAnnoDialog::on_open_annoDir_Button_clicked()
{
    anno_Dir_path = QFileDialog::getExistingDirectory(
                this, "选择标注文件保存位置", "./", QFileDialog::ShowDirsOnly);
    ui->save_anno_file_textEdit->setText(anno_Dir_path);
}


void ConfigAnnoDialog::recive_task_dialog_data(QJsonObject json_object) {
   anno_tasks.push_back(json_object);
}
