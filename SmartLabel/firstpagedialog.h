#ifndef FIRSTPAGEDIALOG_H
#define FIRSTPAGEDIALOG_H

#include <QDialog>

namespace Ui {
class FirstPageDialog;
}

class FirstPageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FirstPageDialog(QWidget *parent = nullptr);
    ~FirstPageDialog();

private slots:
    void on_label_linkActivated(const QString &link);

private:
    Ui::FirstPageDialog *ui;
};

#endif // FIRSTPAGEDIALOG_H
