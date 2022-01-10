#ifndef CUSTUMTASKDIALOG_H
#define CUSTUMTASKDIALOG_H

#include <QDialog>

namespace Ui {
class CustumTaskDialog;
}

class CustumTaskDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CustumTaskDialog(QWidget *parent = nullptr);
    ~CustumTaskDialog();

private:
    Ui::CustumTaskDialog *ui;
};

#endif // CUSTUMTASKDIALOG_H
