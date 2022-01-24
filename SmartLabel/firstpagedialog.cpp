#include "firstpagedialog.h"
#include "ui_firstpagedialog.h"
#include "annotations/annotationitem.h"
#include "controllers/filemanager.h"
#include <QLabel>

FirstPageDialog::FirstPageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FirstPageDialog)
{
    ui->setupUi(this);
    task_dialog = std::make_unique<CustumTaskDialog>();
    fileDialog = std::make_unique<QFileDialog>();
    login_dialog = std::make_unique<LoginDialog>();

    task_menu = std::make_unique<QMenu>();
    open_task_action = std::make_unique<QAction>();
    del_task_action = std::make_unique<QAction>();

    task_menu->addAction(open_task_action.get());
    task_menu->addAction(del_task_action.get());
}

FirstPageDialog::~FirstPageDialog()
{
    delete ui;
}

void FirstPageDialog::execu_menu(QPoint pos) {
   // QPoint corrpos_point = ui->groupBox_attribute->mapFromGlobal(QCursor::pos());
    // menu_label_ = dynamic_cast<QLabel*>(ui->groupBox_attribute->childAt(corrpos_point));
    task_menu->exec(QCursor::pos());
}

void FirstPageDialog::on_NewProject_Button_clicked()
{
    task_dialog->setModal(true);
    task_dialog->show();
}


void FirstPageDialog::on_AllProject_Button_clicked()
{
    QFile config_file(config_json_path);
    if (!config_file.open(QFile::ReadOnly | QFile::Text)){
        throw FileException(std::string(QByteArray(config_json_path.toLocal8Bit()).data())+": file not open");
    } else {
        QString val = config_file.readAll();
        config_file.close();
        QJsonDocument document = QJsonDocument::fromJson(val.toUtf8());
        if (!document.isNull()){
            if (document.isObject()){
               auto anno_tak = document.object();
              // QLabel* task_label = new QLabel();
            }else{
                throw JsonException("document is not object");
            }
        }else{
           throw JsonException("document read error");
        }
    }
}


void FirstPageDialog::on_project_Dir_Button_clicked()
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


void FirstPageDialog::on_login_button_clicked()
{
    login_dialog->setModal(true);
    login_dialog->show();
}

