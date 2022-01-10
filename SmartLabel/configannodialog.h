#ifndef CONFIGANNODIALOG_H
#define CONFIGANNODIALOG_H

#include <QDialog>

namespace Ui {
class ConfigAnnoDialog;
}

class ConfigAnnoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigAnnoDialog(QWidget *parent = nullptr);
    ~ConfigAnnoDialog();

private:
    Ui::ConfigAnnoDialog *ui;
};

#endif // CONFIGANNODIALOG_H
