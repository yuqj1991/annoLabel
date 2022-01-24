#ifndef TASKDIALOG_H
#define TASKDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <memory>
#include "add_attribute_dialog.h"
#include "wegits_common.h"
#include "point_dialog.h"
#include <QAction>
#include <QMenu>
#include <QLabel>

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

    void execu_menu(QPoint pos);

    void del_attr();
    void modify_attr();

signals:
void  Send_anno_type(const AnnoTool::AnnoType& anno_type);

void Send_task_data(const AnnoTool::task_desc_& task);

void Send_labels_to_attr(QStringList& task);

private:
    Ui::taskDialog *ui;
    std::unique_ptr<AddAttributeDialog> attribute_dialog;
    std::unique_ptr<PointDialog> point_dialog;
    QVBoxLayout grid_layout ;
    std::unique_ptr<QJsonObject> attr_set;
    QStringList get_labels(const QString& labels);
    AnnoTool::task_desc_ task_desc;
    std::vector<std::pair<QString, QStringList>> attri_labels_map_;
    bool all_labels_attr = false;
    std::unique_ptr<QMenu> ocr_menu_;
    std::unique_ptr<QAction> modify_ocr_;
    std::unique_ptr<QAction> del_ocr_;
    std::vector<QLabel*> ocr_labels_;
    QLabel* menu_label_;
    bool use_menu_ = false;
    int label_index = -1;
};

#endif // TASKDIALOG_H
