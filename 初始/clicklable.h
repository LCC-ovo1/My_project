#ifndef CLICKLABLE_H
#define CLICKLABLE_H

#include <QLabel>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include <QPixmap>
#include <QWidget>
#include <QSoundEffect>
#include <QRandomGenerator>

class CLickLable : public QLabel
{
    Q_OBJECT
public:
    CLickLable(const QIcon& normalIcon, const QIcon& blodIcon, QWidget *parent =nullptr);
protected:
    bool eventFilter(QObject *obj, QEvent *event);
private:
    QIcon normalIcon;
    QIcon boldIcon;
    QSoundEffect soundEffect;
    QPropertyAnimation *animation;

    void animate();
    void sound();
    void clickSound();
signals:
    void clicked();
    void mouseEntered();
};

#endif // CLICKLABLE_H
