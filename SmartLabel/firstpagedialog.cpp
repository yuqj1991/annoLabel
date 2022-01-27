#include "firstpagedialog.h"
#include "ui_firstpagedialog.h"
#include "annotations/annotationitem.h"
#include "controllers/filemanager.h"
#include <QLabel>
#include <QJsonDocument>
#include "wegits_common.h"

FirstPageDialog::FirstPageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FirstPageDialog)
{
    ui->setupUi(this);

    task_dialog = std::make_unique<CustumTaskDialog>();
    connect(task_dialog.get(), SIGNAL(Send_custum_task_dialog(QJsonObject&)), this, SLOT(recived_completed_data(QJsonObject&)));
    anno_canvas_dialog = std::make_unique<MainWindow>();
    fileDialog = std::make_unique<QFileDialog>();
    login_dialog = std::make_unique<LoginDialog>();

    task_menu = std::make_unique<QMenu>();
    open_task_action = std::make_unique<QAction>("开始任务");
    del_task_action = std::make_unique<QAction>("删除任务");
    modify_task_action = std::make_unique<QAction>("修改任务");
    save_task_action = std::make_unique<QAction>("保存任务");
    connect(open_task_action.get(), SIGNAL(triggered()), this, SLOT(open_task()));
    connect(del_task_action.get(), SIGNAL(triggered()), this, SLOT(del_task()));
    connect(modify_task_action.get(), SIGNAL(triggered()), this, SLOT(modify_task()));
    connect(save_task_action.get(), SIGNAL(triggered()), this, SLOT(save_task()));

    task_menu->addAction(open_task_action.get());
    task_menu->addAction(del_task_action.get());
    task_menu->addAction(modify_task_action.get());
    task_menu->addAction(save_task_action.get());
    stand_model = std::make_unique<QStandardItemModel>();
    ui->listView_Project->setModel(stand_model.get());
    ui->listView_Project->setFrameShape(QFrame::NoFrame);
    ui->listView_Project->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listView_Project->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->listView_Project, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(execu_menu(QPoint)));
}

FirstPageDialog::~FirstPageDialog()
{
    delete ui;
}

void FirstPageDialog::open_task() {
    auto row = ui->listView_Project->currentIndex();
    auto config_task = anno_tasks.at(row.row()).toObject();
    //anno_canvas_dialog->setModal(true);
    anno_canvas_dialog->show();
}

void FirstPageDialog::save_task() {
    auto row = ui->listView_Project->currentIndex();
    auto config_task = anno_tasks.at(row.row());
    QString file_name = config_task.toObject().value(AnnoTool::WidgetUtils::project_name).toString() + ".json";
    FileManager::saveJson(config_task.toObject(), file_name);
}

void FirstPageDialog::del_task() {
    auto row = ui->listView_Project->currentIndex();
    stand_model->removeRow(row.row());
    anno_tasks.removeAt(row.row());
}

void FirstPageDialog::modify_task() {
    modify_index = ui->listView_Project->currentIndex();
    is_modify_task =true;
    on_NewProject_Button_clicked();
}

void FirstPageDialog::execu_menu(QPoint pos) {
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
               auto anno_task = document.object();
               anno_tasks.push_back(anno_task);
               QStandardItem *item = new QStandardItem(AnnoTool::WidgetUtils::ConvertToQStringFromJsonObject(anno_task));
               stand_model->appendRow(item);
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

void FirstPageDialog::recived_completed_data(QJsonObject& anno_object) {
    if (is_modify_task) {
        stand_model->setData(modify_index, AnnoTool::WidgetUtils::ConvertToQStringFromJsonObject(anno_object));
        is_modify_task = false;
        anno_tasks.removeAt(modify_index.row());
    } else {
        QStandardItem *item = new QStandardItem(AnnoTool::WidgetUtils::ConvertToQStringFromJsonObject(anno_object));
        anno_tasks.push_back(anno_object);
        stand_model->appendRow(item);
    }
}
