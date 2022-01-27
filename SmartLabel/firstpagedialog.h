#ifndef FIRSTPAGEDIALOG_H
#define FIRSTPAGEDIALOG_H

#include <QDialog>
#include <QStandardItemModel>
#include "custumtaskdialog.h"
#include <memory>
#include<QFileDialog>
#include<QFile>
#include<QJsonDocument>
#include<QJsonObject>
#include<QMenu>
#include <QModelIndex>
#include"login.h"
#include "mainwindow.h"

namespace Ui {
class FirstPageDialog;
}

class FirstPageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FirstPageDialog(QWidget *parent = nullptr);
    ~FirstPageDialog();

private slots:

    void on_NewProject_Button_clicked();

    void on_AllProject_Button_clicked();

    void on_project_Dir_Button_clicked();

   void del_task();
   void open_task();
   void modify_task();
   void save_task();
   void execu_menu(QPoint pos);

   void recived_completed_data(QJsonObject& anno_object);

   void on_login_button_clicked();

private:
    Ui::FirstPageDialog *ui;
    std::unique_ptr<CustumTaskDialog> task_dialog;
    std::unique_ptr<QFileDialog> fileDialog;
    std::unique_ptr<MainWindow> anno_canvas_dialog;
    QString config_json_path;

    std::unique_ptr<QMenu> task_menu;
    std::unique_ptr<QAction> open_task_action;
    std::unique_ptr<QAction> modify_task_action;
    std::unique_ptr<QAction> del_task_action;
    std::unique_ptr<QAction> save_task_action;
    QJsonArray anno_tasks;
    std::unique_ptr<LoginDialog> login_dialog;
    std::unique_ptr<QStandardItemModel> stand_model;
    bool is_modify_task = false;
    QModelIndex modify_index;
};

#endif // FIRSTPAGEDIALOG_H
