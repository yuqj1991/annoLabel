#ifndef POINT_DIALOG_H
#define POINT_DIALOG_H

#include <QDialog>
#include <QIntValidator>

namespace Ui {
class PointDialog;
}


class FixUpValidator : public QIntValidator
{
    Q_OBJECT
public:
    explicit FixUpValidator(QObject * parent = 0):QIntValidator(parent)
    {
    }
    FixUpValidator(int bottom, int top, QObject * parent):QIntValidator(bottom, top, parent)
    {
    }
    virtual void setRange(int bottom, int top)
    {
        QIntValidator::setRange(bottom, top);
    }
    ~FixUpValidator()
    {
    }
    virtual State validate(QString &s, int &n) const
    {
        return QIntValidator::validate(s, n);
    }
    virtual void fixup(QString &s) const
    {
        s = QString("%1").arg(bottom());
    }
};


class PointDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PointDialog(QWidget *parent = nullptr);
    ~PointDialog();

signals:
    void Send_points_data(int& point_nums);

private slots:

    void on_confirmedPushButton_clicked();

    void on_cancellPushButton_clicked();

private:
    Ui::PointDialog *ui;
};

#endif // POINT_DIALOG_H
