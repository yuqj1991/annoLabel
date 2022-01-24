#include "defaultannodialog.h"
#include "ui_defaultannodialog.h"
#include <QFile>

DefaultAnnoDialog::DefaultAnnoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DefaultAnnoDialog)
{
    ui->setupUi(this);
}

DefaultAnnoDialog::~DefaultAnnoDialog()
{
    delete ui;
}

void DefaultAnnoDialog::on_open_dir_Button_clicked()
{
    //定义文件对话框标题
    fileDialog->setWindowTitle("选择task配置文件");
    //设置默认文件路径
    fileDialog->setDirectory(".");
    //设置文件过滤器
    fileDialog->setNameFilter(tr("JSON(*.json)"));
    //设置可以选择多个文件,默认为只能选择一个文件QFileDialog::ExistingFiles
    fileDialog->setFileMode(QFileDialog::ExistingFile);
    //设置视图模式
    fileDialog->setViewMode(QFileDialog::Detail);
    //打印所有选择的文件的路径
    QStringList fileNames;
    if (fileDialog->exec())
    {
        fileNames = fileDialog->selectedFiles();
        if (fileNames.length() > 0)
        {
            ui->jsonPath_textEdit->setText(fileNames[0]);
            config_json_path = fileNames[0];
        }
    }
}

