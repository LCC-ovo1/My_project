#include "clicklable.h"


CLickLable::CLickLable(const QIcon &normalIcon, const QIcon &boldIcon, QWidget *parent)
    : QLabel(parent), normalIcon(normalIcon), boldIcon(boldIcon)
{
    setMouseTracking(true);
    installEventFilter(this);

    connect(this, &CLickLable::mouseEntered, this, [=]() {
        animate();
        sound();
    });
    connect(this, &CLickLable::clicked, this, &CLickLable::clickSound);

}

bool CLickLable::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == this) {
        if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if (mouseEvent->button() == Qt::LeftButton) {
                emit clicked();
                //clickSound();
            }
        } else if (event->type() == QEvent::Enter) {
            setPixmap(boldIcon.pixmap(QSize(40, 40)));
            // 先动画后音效
            //animate();
            //sound();
            emit mouseEntered();
        } else if (event->type() == QEvent::Leave) {
            setPixmap(normalIcon.pixmap(QSize(40, 40)));
        }
    }

    return QLabel::eventFilter(obj, event);
}

void CLickLable::animate()
{
    // 100毫秒
    animation = new QPropertyAnimation(this, "pos");
    animation->setDuration(100);
    animation->setEasingCurve(QEasingCurve::InOutBack);
    animation->setKeyValueAt(0, pos());

    // 10帧
    for (int i = 1; i < 10; ++i) {
        auto t = i / 10.0;
        auto x = (i % 2 == 0) ? 5 : -5;
        animation->setKeyValueAt(t, pos() + QPoint(x, 0));
    }

    animation->setKeyValueAt(1, pos());
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void CLickLable::sound()
{

//    // 随机选择一种音效播放
    soundEffect.setSource(QUrl::fromLocalFile( "D:\\picture\\天气之子\\音效\\move.wav"));
    soundEffect.setVolume(1.0);
    soundEffect.play();
}

void CLickLable::clickSound()
{
    soundEffect.setSource(QUrl::fromLocalFile("D:\\picture\\天气之子\\音效\\click.wav"));
    soundEffect.setVolume(1.0);
    soundEffect.play();
}
