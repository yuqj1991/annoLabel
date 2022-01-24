#ifndef FIRSTPAGEDIALOG_H
#define FIRSTPAGEDIALOG_H

#include <QDialog>
#include "custumtaskdialog.h"
#include <memory>
#include<QFileDialog>
#include<QFile>
#include<QJsonDocument>
#include<QJsonObject>
#include<QMenu>
#include"login.h"

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

  //  void del_task();
    //void open_task();
   void execu_menu(QPoint pos);

   void on_login_button_clicked();

private:
    Ui::FirstPageDialog *ui;
    std::unique_ptr<CustumTaskDialog> task_dialog;
    std::unique_ptr<QFileDialog> fileDialog;
    QString config_json_path;

    std::unique_ptr<QMenu> task_menu;
    std::unique_ptr<QAction> open_task_action;
    std::unique_ptr<QAction> del_task_action;
    QJsonObject config_task;
    std::unique_ptr<LoginDialog> login_dialog;
};

#endif // FIRSTPAGEDIALOG_H
