#include "mybutton.h"
MyButton::MyButton(QWidget *parent, const QIcon &icon1, const QIcon &icon2):QPushButton(parent),icon1(icon1),icon2(icon2)
{
    this->setStyleSheet("QPushButton {border-radius: 20px;background-color: transparent;border: none;}QPushButton:hover {border-radius: 20px;background-color: #CCCCCC;}");
}

MyButton::MyButton()
{

}

void MyButton::enterEvent(QEnterEvent *event)
{
    if(event->type()==QEvent::Enter){
        this->setIcon(icon1);
    }
    QPushButton::enterEvent(event);
}

void MyButton::leaveEvent(QEvent *event)
{
    if(event->type()==QEvent::Leave){
        this->setIcon(icon2);
    }
    QPushButton::leaveEvent(event);
}

void MyButton::clickSound()
{
   sound.setSource(QUrl::fromLocalFile( "D:\\picture\\天气之子\\音效\\click.wav"));
   sound.setVolume(1.0);
   sound.play();
}
