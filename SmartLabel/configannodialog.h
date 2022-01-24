#ifndef CONFIGANNODIALOG_H
#define CONFIGANNODIALOG_H

#include <QDialog>
#include <memory>
#include "taskdialog.h"

namespace Ui {
class ConfigAnnoDialog;
}

class ConfigAnnoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigAnnoDialog(QWidget *parent = nullptr);
    ~ConfigAnnoDialog();

private slots:
    void on_custum_task_Button_clicked();


private:
    Ui::ConfigAnnoDialog *ui;
    std::unique_ptr<taskDialog> task_dialog;
};

#endif // CONFIGANNODIALOG_H
