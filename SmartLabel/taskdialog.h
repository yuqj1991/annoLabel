#ifndef TASKDIALOG_H
#define TASKDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <memory>
#include "add_attribute_dialog.h"
#include "wegits_common.h"
#include "point_dialog.h"

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

    void receive_points_data(int& data);

    void on_taskCancell_clicked();

    void on_taskConfirmed_clicked();

    void on_TaskType_ComboBox_activated(int index);

signals:
void  Send_anno_type(const AnnoTool::AnnoType& anno_type);

void Send_task_data(const AnnoTool::task_desc_& task);

private:
    Ui::taskDialog *ui;
    std::unique_ptr<AddAttributeDialog> attribute_dialog;
    std::unique_ptr<PointDialog> point_dialog;
    QGridLayout grid_layout;
    std::unique_ptr<QJsonObject> attr_set;
    QStringList get_labels(const QString& labels);
    AnnoTool::task_desc_ task_desc;
};

#endif // TASKDIALOG_H
