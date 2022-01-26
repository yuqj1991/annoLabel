#ifndef CONFIGANNODIALOG_H
#define CONFIGANNODIALOG_H

#include <QDialog>
#include <QJsonArray>
#include <QJsonObject>
#include<QJsonValue>
#include <memory>
#include "taskdialog.h"
#include<QFileDialog>

namespace Ui {
class ConfigAnnoDialog;
}

class ConfigAnnoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigAnnoDialog(QWidget *parent = nullptr);
    ~ConfigAnnoDialog();

    bool get_task_data(QJsonObject &config_task);

private slots:
    void on_custum_task_Button_clicked();


    void on_open_fileDir_Button_clicked();

    void on_open_annoDir_Button_clicked();

    void recive_task_dialog_data(QJsonObject json_object);


private:
    Ui::ConfigAnnoDialog *ui;
    std::unique_ptr<taskDialog> task_dialog;
    QString image_Dir_path;
    QString anno_Dir_path;
    QJsonObject sub_task_object;
    QJsonArray anno_tasks;
};

#endif // CONFIGANNODIALOG_H
