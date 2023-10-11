#ifndef _FRAMELESWIDGET_H
#define _FRAMELESWIDGET_H

#include <QMainWindow>
#include <QTimer>
#include <QMouseEvent>
#include <QCryptographicHash>
#include <QMessageBox>
#include <QPainterPath>
#include <QPainter>
#include <QMovie>
#include <QSettings>
#include <QDialog>
#include <QSoundEffect>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>

QT_BEGIN_NAMESPACE
namespace Ui { class framelessWidget; }
QT_END_NAMESPACE

class framelessWidget : public QWidget
{
    Q_OBJECT

public:
    framelessWidget(QWidget *parent = nullptr);
    ~framelessWidget();
private:
    QString my_user="myuser";
    QString my_pswd="123456";
    void readset();
    void writeset();
    QString encrypt(const QString &str);
    //这里加一个试错次数
    int trycount=0;
protected:
    //自定义一个消息对话框
    void CriticalMessage(int &count);
    void WarningMessage(int &count);
    void clickSound();
    //void loginAnimation();
private slots:

    void on_confirm_clicked();
    //这里没有实现注册按钮 因为还需要一个界面

    void on_checkBox_clicked(bool checked);

private:
    Ui::framelessWidget *ui;

    int cornerRadius = 20;
    QWidget *border = nullptr;
    bool mousePressed = false;
    QSoundEffect sound;
    QSequentialAnimationGroup* sequentialAnimation;
    void Init();
    void mousePressEvent(QMouseEvent *event);
};
#endif // _FRAMELESWIDGET_H
