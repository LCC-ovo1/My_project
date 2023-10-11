#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>
#include <QEvent>
#include <QEnterEvent>
#include <QIcon>
#include <QSoundEffect>
#include <QWidget>
class MyButton : public QPushButton
{
    Q_OBJECT
public:
    MyButton(QWidget &parent,const QIcon &icon1,const QIcon &icon2);
    MyButton();
protected:
    void enterEvent(QEnterEvent* event);
    void leaveEvent(QEvent *event);
    void clickSound();
private:
    QIcon icon1;
    QIcon icon2;
    QSoundEffect sound;
};

#endif // MYBUTTON_H
