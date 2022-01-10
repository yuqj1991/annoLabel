#ifndef ADD_ATTRIBUTE_DIALOG_H
#define ADD_ATTRIBUTE_DIALOG_H

#include <QDialog>
#include <QJsonObject>
#include <memory>


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
    void SendData(QJsonObject* json_object);

private slots:
    void on_confirm_Button_clicked();

    void on_cancel_Button_clicked();

private:
    Ui::AddAttributeDialog *ui;
    std::unique_ptr<QJsonObject> json_object;
};

#endif // ADD_ATTRIBUTE_DIALOG_H
