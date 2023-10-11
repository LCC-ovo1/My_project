#include "mydialog.h"
#include "framelessWidget.h"
#include "mainwindow.h"
#include <QApplication>
#include <QFontDatabase>
#include <QDebug>
#include <QThreadPool>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //这里设置一个全局的线程池 然后有五个线程
    QThreadPool *threadPool = QThreadPool::globalInstance();
    threadPool->setMaxThreadCount(5);

    myDialog  *dlgLogin =new myDialog;
    //通过图片像素设置合适大小的对话框
    dlgLogin->setFixedSize(1024,576);
    if(dlgLogin->exec()==QDialog::Accepted){
        MainWindow w;
        w.setFixedSize(1023,576);
        w.show();
        return a.exec();
    }
    else return 0;
}
