#ifndef CUSTUMTASKDIALOG_H
#define CUSTUMTASKDIALOG_H

#include <QDialog>
#include <QJsonObject>
#include "defaultannodialog.h"
#include "configannodialog.h"
#include <memory>

namespace Ui {
class CustumTaskDialog;
}

class CustumTaskDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CustumTaskDialog(QWidget *parent = nullptr);
    ~CustumTaskDialog();

private slots:
    void on_custum_anno_Button_clicked();

    void on_default_anno_Button_clicked();

    void on_return_Button_clicked();

    //void receive_task_data();

private:
    Ui::CustumTaskDialog *ui;
    std::unique_ptr<DefaultAnnoDialog> default_dialog;
     std::unique_ptr<ConfigAnnoDialog> custum_dialog;

     // 标注任务表述
     ;
};

#endif // CUSTUMTASKDIALOG_H
