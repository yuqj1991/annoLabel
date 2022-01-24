#ifndef DEFAULTANNODIALOG_H
#define DEFAULTANNODIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <memory>

namespace Ui {
class DefaultAnnoDialog;
}

class DefaultAnnoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DefaultAnnoDialog(QWidget *parent = nullptr);
    ~DefaultAnnoDialog();

private slots:
    void on_open_dir_Button_clicked();

private:
    Ui::DefaultAnnoDialog *ui;

};

#endif // DEFAULTANNODIALOG_H
