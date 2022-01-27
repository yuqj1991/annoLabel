#ifndef ADD_ATTRIBUTE_DIALOG_H
#define ADD_ATTRIBUTE_DIALOG_H

#include <QDialog>
#include <QJsonObject>
#include <memory>
#include "wegits_common.h"

namespace Ui {
class AddAttributeDialog;
}


class AddAttributeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddAttributeDialog(QWidget *parent = nullptr);
    ~AddAttributeDialog();

signals:
    void SendData(QJsonObject& json_object);

private slots:
    void on_confirm_Button_clicked();

    void on_cancel_Button_clicked();

    void on_attri_type_activated(int index);

    void recievd_labels_data(QStringList& data);

private:
    Ui::AddAttributeDialog *ui;

    QStringList get_labels(const QString &labels);

    QStringList task_labels_;

    void clear();
};

#endif // ADD_ATTRIBUTE_DIALOG_H
