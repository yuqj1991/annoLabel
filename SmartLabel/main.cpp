#include "mainwindow.h"
#include "login.h"
#include "firstpagedialog.h"
#include <QApplication>
#include <ctime>
#include <QMessageBox>
#include <QString>
#include <QtDebug>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    qsrand(static_cast<uint>(time(nullptr)));

    QApplication a(argc, argv);

    // 使用qss美化ui界面，但是与部分部件兼容不佳
    QFile f(":qdarkstyle/style.qss");
   if (!f.exists()) {
        printf("Unable to set stylesheet, file not found\n");
    }  else   {
        f.open(QFile::ReadOnly | QFile::Text);
       QTextStream ts(&f);
       qApp->setStyleSheet(ts.readAll());
  }

    try {
        //MainWindow w;
        FirstPageDialog w;
       //w.setWindowState(Qt::Win);
       Qt::WindowFlags flags = Qt::Window;
       //flags |= Qt::WindowMinimizeButtonHint;
       //flags |=Qt::WindowMaximizeButtonHint;
      // w.setWindowFlags(flags); // 设置禁止最大化
       //w.setFixedSize(547, 403); // 禁止改变窗口大小。
        w.show();
        return a.exec();
    } catch (const char *errorStr) {
        qDebug()<<errorStr;
        QString msg;
        msg = QString("The program has crashed.\n")
                +"Message: "+errorStr;
        QMessageBox::warning(nullptr, "Program crashed", msg);
    }
    return 0;
}
