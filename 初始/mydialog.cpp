#include "mydialog.h"
#include "ui_mydialog.h"

#include "clicklable.h"
#include "framelessWidget.h"

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

myDialog::myDialog(QWidget *parent) : QDialog(parent), ui(new Ui::myDialog)
{
    ui->setupUi(this);
    ui->titlebar->setObjectName("mytitlebar");
    ui->titlebar->setMouseTracking(true);
    ui->titlebar->installEventFilter(this);
     updateTitleBarStyle();
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::MSWindowsFixedSizeDialogHint);
    //this->setWindowFlags(Qt::WindowMinMaxButtonsHint |Qt::WindowCloseButtonHint);
    this->setAttribute(Qt::WA_DeleteOnClose);

    Init();

    QTimer *t = new QTimer(this);
    connect(t, &QTimer::timeout, this, [=](){close_and_min();});
    t->setSingleShot(true);
    t->start();

    imagePaths << "D:\\图片\\图标\\1.jpg" << "D:\\图片\\图标\\2.jpg" << "D:\\图片\\图标\\3.jpg"
               << "D:\\图片\\图标\\4.jpg"<< "D:\\图片\\图标\\5.jpg"<< "D:\\图片\\图标\\6.jpg"
               << "D:\\图片\\图标\\7.jpg"<< "D:\\图片\\图标\\8.jpg"
            ;

    timer = new QTimer(this);
    //3秒延时
    timer->setInterval(3000);
    connect(timer, &QTimer::timeout, this, &myDialog::updateImage);
    timer->start();
    currentImageIndex = 0;


    framelessWidget *w = new framelessWidget(this);
    w->setWindowFlag(Qt::FramelessWindowHint);
    w->setAttribute(Qt::WA_TranslucentBackground);

    w->setGeometry(200,150 , w->width(), w->height());
    w->show();


}

void myDialog::Init()
{
    QPixmap pixmap(":/picture/gif/1.jpg");
    ui->label_3->setPixmap(pixmap);
    ui->label_3->setFixedSize(60, 60);
    QPixmap roundedPixmap(ui->label_3->size());
    roundedPixmap.fill(Qt::transparent);
    QPainter painter(&roundedPixmap);
    QRegion region = roundedPixmap.rect();
    painter.setClipRegion(region);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.drawPixmap(0, 0, ui->label_3->pixmap().scaled(ui->label_3->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->label_3->setPixmap(roundedPixmap);

    QMediaPlayer *musicPlayer = new QMediaPlayer(this);
    musicPlayer->setSource(QUrl::fromLocalFile("D:\\picture\\天气之子\\音效\\1.mp3"));
    musicPlayer->play();

}

void myDialog::mouseMoveEvent(QMouseEvent *event)
{
    QPoint eventPos=event->globalPosition().toPoint();
    if(moving&&(event->buttons()&Qt::LeftButton)&&
        (eventPos-lastpoint).manhattanLength()>QApplication::startDragDistance()){
        move(eventPos-lastpoint);
        lastpoint=eventPos-this->pos();
    }
    return QDialog::mouseMoveEvent(event);
}

void myDialog::mousePressEvent(QMouseEvent *event)
{

    if(event->button()==Qt::LeftButton){
        moving=true;
        lastpoint=event->globalPosition().toPoint()-this->pos();
    }
    return QDialog::mousePressEvent(event);
}

void myDialog::mouseReleaseEvent(QMouseEvent *event)
{
    moving=false;
    event->accept();
}

void myDialog::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    int height = ui->titlebar->height();

    // 获取当前要绘制的背景图片路径
    QString imagePath = imagePaths[currentImageIndex];

    QPixmap backgroundPixmap(imagePath);
    QPixmap scaledPixmap = backgroundPixmap.scaled(this->width(), this->height() - height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    // 绘制背景图片
    painter.drawPixmap(0, height, scaledPixmap);

    event->accept();
}
void myDialog::updateImage()
{
    currentImageIndex = (currentImageIndex + 1) % imagePaths.size();
    update();
}

void myDialog::close_and_min()
{
    QHBoxLayout* titleLayout = new QHBoxLayout(ui->titlebar);
    // 创建伸展项，将按钮推到右侧
    //titleLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    //titleLayout->addStretch();

    // 创建关闭按钮
    QIcon normalIcon("D:\\picture\\天气之子\\Light\\Arrow - Right Square.png");
    QIcon boldIcon("D:\\picture\\天气之子\\Bold\\Arrow - Right Square.png");
    label_close = new CLickLable(normalIcon, boldIcon,ui->titlebar);

    // 创建最小化按钮
    QIcon normalIcon1("D:\\picture\\天气之子\\Light\\Arrow - Down Square.png");
    QIcon boldIcon1("D:\\picture\\天气之子\\Bold\\Arrow - Down Square.png");
    label_min = new CLickLable(normalIcon1, boldIcon1,ui->titlebar);

    connect(label_min, &CLickLable::clicked, this, &myDialog::showMinimized);
    connect(label_close, &CLickLable::clicked, this, &myDialog::close);
    // 添加按钮到布局
    titleLayout->addWidget(label_min);
    titleLayout->addWidget(label_close);

}


myDialog::~myDialog()
{
    delete ui;
}

bool myDialog::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->titlebar) {
        if (event->type() == QEvent::Enter) {
            // 鼠标进入titleBar
            isTitleBarHovered = true;
            updateTitleBarStyle();
        } else if (event->type() == QEvent::Leave) {
            // 鼠标离开titleBar
            isTitleBarHovered = false;
            updateTitleBarStyle();
        }
    }
    return QDialog::eventFilter(watched, event);
}

void myDialog::updateTitleBarStyle()
{
    if (isTitleBarHovered) {
        // 鼠标在titleBar上，应用悬停样式
        ui->titlebar->setStyleSheet("QWidget#myTitleBar {"
                                    "border: 0.5px solid white;"
                                    "border-radius: 6px;"
                                    "background-color: #1fab89;"
                                    "min-width: 80px;"
                                    "font-family: \"Microsoft YaHei\";"
                                    "font-size: 10pt;"
                                    "font-weight: bold;"
                                    "color: white;"
                                    "}");
    } else {
        ui->titlebar->setStyleSheet("QWidget#myTitleBar {"
                                    "border: 0.5px solid white;"
                                    "border-radius: 6px;"
                                    "background-color: rgb(90, 194, 198);"
                                    "min-width: 80px;"
                                    "font-family: \"Microsoft YaHei\";"
                                    "font-size: 11pt;"
                                    "font-weight: bold;"
                                    "color: white;"
                                    "}");
    }
}
