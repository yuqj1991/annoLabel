#ifndef TASKDIALOG_H
#define TASKDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <memory>
#include "add_attribute_dialog.h"

namespace Ui {
class taskDialog;
}

class taskDialog : public QDialog
{
    Q_OBJECT

public:
    explicit taskDialog(QWidget *parent = nullptr);

    ~taskDialog();

private slots:
    void on_add_attribute_clicked();
    void receive_attribute_data(QJsonObject*  json_object);

    void on_taskCancell_clicked();

    void on_taskConfirmed_clicked();

private:
    Ui::taskDialog *ui;
    std::unique_ptr<AddAttributeDialog> attribute_dialog;
    QGridLayout grid_layout;
    std::unique_ptr<QJsonObject> attr_set;
    QStringList get_labels(const QString& labels);
};

#endif // TASKDIALOG_H
