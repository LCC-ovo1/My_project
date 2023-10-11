#ifndef MYDIALOG_H
#define MYDIALOG_H
#include "clicklable.h"
#include "framelessWidget.h"

#include <QDialog>
#include <clicklable.h>
#include "qtmaterialappbar.h"
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include <QIcon>
#include <QBrush>
#include <QPainterPath>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPaintEvent>
#include <QMovie>
#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QMediaPlayer>
#include <QPainterPath>

namespace Ui {
class myDialog;
}

class myDialog : public QDialog
{
    Q_OBJECT

public:
    explicit myDialog(QWidget *parent = nullptr);
    ~myDialog();
private:
    bool moving=false;
    QPoint lastpoint;
    bool isTitleBarHovered = false;
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent* event);
    void updateImage();
    void close_and_min();
    void Init();
private:
    Ui::myDialog *ui;
    CLickLable* label_close;
    CLickLable* label_min;
    QTimer *timer;
    QStringList imagePaths;
    int currentImageIndex;
};

#endif // MYDIALOG_H
