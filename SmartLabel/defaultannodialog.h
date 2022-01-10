#ifndef DEFAULTANNODIALOG_H
#define DEFAULTANNODIALOG_H

#include <QDialog>

namespace Ui {
class DefaultAnnoDialog;
}

class DefaultAnnoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DefaultAnnoDialog(QWidget *parent = nullptr);
    ~DefaultAnnoDialog();

private:
    Ui::DefaultAnnoDialog *ui;
};

#endif // DEFAULTANNODIALOG_H
