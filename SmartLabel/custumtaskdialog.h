#ifndef CUSTUMTASKDIALOG_H
#define CUSTUMTASKDIALOG_H

#include <QDialog>
#include <QJsonObject>
#include <QMessageBox>
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

signals:
    void Send_custum_task_dialog(QJsonObject& custum_task);

private slots:
    void on_custum_anno_Button_clicked();

    void on_default_anno_Button_clicked();

    void on_return_Button_clicked();

    //void receive_task_data();

    void on_cancell_Button_clicked();

private:
    Ui::CustumTaskDialog *ui;
    std::unique_ptr<DefaultAnnoDialog> default_dialog;
    std::unique_ptr<ConfigAnnoDialog> custum_dialog;
};

#endif // CUSTUMTASKDIALOG_H
