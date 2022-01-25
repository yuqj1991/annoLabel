#ifndef DEFAULTANNODIALOG_H
#define DEFAULTANNODIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QJsonObject>
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

    bool get_task_data(QJsonObject &config_task);

  private slots:
    void on_open_dir_Button_clicked();
    QStringList get_labels(const QString &labels);

    void on_open_anno_Button_clicked();

private:
    Ui::DefaultAnnoDialog *ui;
    std::unique_ptr<QFileDialog> fileDialog;
    QString image_folder_path;
    QString anno_folder_path;
    int points_num;
};

#endif // DEFAULTANNODIALOG_H
