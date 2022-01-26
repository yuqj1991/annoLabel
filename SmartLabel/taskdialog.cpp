#include "taskdialog.h"
#include "ui_taskdialog.h"
#include <iostream>
#include <QDebug>
#include <QMessageBox>
#include <QJsonArray>


QStringList taskDialog::get_labels(const QString& labels) {
    QStringList result =  labels.split(";");
    if (!result.size())
        QMessageBox::warning(this, "warning", "请以英文符号;作为分割符!");
    return result;

}

taskDialog::taskDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::taskDialog)
{
    ui->setupUi(this);
     attribute_dialog =std::make_unique<AddAttributeDialog>();
     ocr_menu_ = std::make_unique<QMenu>();
     modify_ocr_ = std::make_unique<QAction>("修改");
     del_ocr_ = std::make_unique<QAction>("删除");

     ocr_menu_->addAction(modify_ocr_.get());
     ocr_menu_->addAction(del_ocr_.get());
     connect(modify_ocr_.get(), SIGNAL(triggered()), this, SLOT(modify_attr()));
     connect(del_ocr_.get(), SIGNAL(triggered()), this, SLOT(del_attr()));

     attr_set =std::make_unique<QJsonObject>();
     connect(attribute_dialog.get(),  SIGNAL(SendData(QJsonObject*)),  this,  SLOT(receive_attribute_data(QJsonObject*)));
     point_dialog = std::make_unique<PointDialog>();
     connect(point_dialog.get(), SIGNAL(Send_points_data(int&)), this, SLOT(receive_points_data(int&)));
     connect(this, SIGNAL(Send_labels_to_attr(QStringList&)), attribute_dialog.get(), SLOT( recievd_labels_data(QStringList&)));

}

taskDialog::~taskDialog()
{
    delete ui;
}

void taskDialog::del_attr() {
    if (menu_label_ != nullptr) {
        QString attr = menu_label_->text();
        auto attr_descs = attr.split("[sub_attr: ");
        auto last_parts = attr_descs[1].split("](subject to labels: ");
        auto del_attr = last_parts[0];
        attr_set->remove(del_attr);
        for (auto it = attri_labels_map_.begin(); it  != attri_labels_map_.end(); ) {
            if (it->first == del_attr) {
                it = attri_labels_map_.erase(it);
            } else {
                it++;
            }
        }
        menu_label_->hide();
    }

}

void taskDialog::on_add_attribute_clicked()
{
    QString s_labels = ui->text_labels->toPlainText();
    if (s_labels.length() == 0) {
        QMessageBox::information(this, "info", "请添加标签!");
        return;
    }
    task_desc.anno_labels = get_labels(s_labels);
    emit Send_labels_to_attr(task_desc.anno_labels);
    attribute_dialog->setModal(true);
    attribute_dialog->show();
}

void taskDialog::modify_attr() {
    auto attr_descs = menu_label_->text().split("[sub_attr: ");
    auto last_parts = attr_descs[1].split("](subject to labels: ");
    auto del_attr = last_parts[0];
    for (auto i = 0; i < attri_labels_map_.size(); i++) {
        if (attri_labels_map_[i].first == del_attr) {
            label_index = i;
            break;
        }
    }
    attribute_dialog->setModal(true);
    attribute_dialog->show();
    use_menu_ = true;
}


void taskDialog::execu_menu(QPoint pos) {
   QPoint corrpos_point = ui->groupBox_attribute->mapFromGlobal(QCursor::pos());
    menu_label_ = dynamic_cast<QLabel*>(ui->groupBox_attribute->childAt(corrpos_point));
    ocr_menu_->exec(QCursor::pos());

}

void taskDialog::receive_attribute_data(QJsonObject* json_object)
{
    QString s_s("[sub_attr: ");
    QString sub_task = json_object->value("sub_task").toString();
    if (attr_set->contains(sub_task) && !use_menu_) {
        QMessageBox::warning(this, "warning", "the current attr has beed added! please add a new one again!");
        return;
    }
    attr_set->insert(sub_task, QJsonValue("sub_attr"));
    s_s += sub_task;
    s_s +="](subject to labels: ";
    QStringList labels_attr;
    auto label_values = json_object->value("labels").toArray();
    if ( (label_values.count() == 1) &&(label_values.first().toString() == "all_labels")) {
         s_s += "all_labels.";
         labels_attr.append("all_labels");
         all_labels_attr = true;
    } else {
        for (auto i = 0; i < label_values.count(); i++) {
            s_s += label_values.at(i).toString() + ";";
            labels_attr.append( label_values.at(i).toString());
        }
        s_s += ".";
    }
     s_s += ")";
    if (use_menu_) {
        menu_label_->setText(s_s);
        if (label_index != -1) {
            attri_labels_map_[label_index] = std::pair<QString, QStringList>(sub_task, labels_attr);
            label_index = -1;
        }
    } else {
        attri_labels_map_.push_back(std::pair<QString, QStringList>(sub_task, labels_attr));
        QLabel* attri_label = new QLabel();
        attri_label->setText(s_s);
        attri_label->setStyleSheet("QLabel{border:2px solid rgb(27, 23, 10);}");

         QFont font("Arial", 12);
         attri_label->setFont(font);
         attri_label->adjustSize();
         attri_label->setContextMenuPolicy(Qt::CustomContextMenu);
         connect(attri_label, SIGNAL(customContextMenuRequested(QPoint)),this, SLOT(execu_menu(QPoint)));

         grid_layout.addWidget(attri_label);
         ui->groupBox_attribute->setLayout(&grid_layout);
    }
     use_menu_ = false;
}


void taskDialog::on_taskCancell_clicked()
{
    this->close();
}


void taskDialog::on_taskConfirmed_clicked()
{
    QJsonObject anno_task;
    QString s_task = ui->text_anno_task->toPlainText();
    if (s_task.length() == 0) {
        QMessageBox::information(this, "info", "请添加标注任务名称!");
        return;
    }

    QString task_type = ui->TaskType_ComboBox->currentText();
     AnnoTool::AnnoType anno_type = AnnoTool::AnnoType::Points;
    if (task_type == "点") {
       anno_type = AnnoTool::AnnoType::Points;
    } else if (task_type == "矩形框") {
         anno_type = AnnoTool::AnnoType::Rectangle;
    } else if (task_type == "3D目标检测") {
         anno_type = AnnoTool::AnnoType::Segement;
    }
    anno_task.insert("anno_type",QJsonValue(AnnoTool::WidgetUtils::ConvertJsonValue(anno_type)));
    if (anno_type == AnnoTool::AnnoType::Points) {
        anno_task.insert("points_num", QJsonValue(points_num));
    }
    //emit 发送labels_list信号出去;
    emit Send_task_data(anno_task);

}

void taskDialog::receive_points_data(int& data) {
    points_num = data;
}

void taskDialog::on_TaskType_ComboBox_activated(int index)
{
    if (ui->TaskType_ComboBox->currentText() == "点") {
        point_dialog->setModal(true);
        point_dialog->show();
    }
}

