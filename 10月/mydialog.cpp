#include "mydialog.h"
#include "ui_mydialog.h"


myDialog::myDialog(QWidget *parent) : QDialog(parent), ui(new Ui::myDialog)
{
    ui->setupUi(this);
    ui->titlebar->setMouseTracking(true);
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
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

    w->setGeometry(250,100 , w->width(), w->height());
    w->show();


}

void myDialog::Init()
{
    QMediaPlayer *musicPlayer = new QMediaPlayer(this);
    musicPlayer->setSource(QUrl::fromLocalFile("D:\\picture\\天气之子\\音效\\1.mp3"));
    musicPlayer->play();

//    QPixmap pixmap(":/picture/gif/1.jpg");
//    QPixmap roundedPixmap(pixmap.size());
//    roundedPixmap.fill(Qt::transparent); // 填充透明背景

//    QPainter painter(&roundedPixmap);
//    QRegion region(roundedPixmap.rect());

//    // 开始绘制
//    painter.setClipRegion(region);
//    painter.setRenderHint(QPainter::Antialiasing, true);
//    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

//    // 在圆形区域内绘制图像
//    QPainterPath path;
//    path.addEllipse(roundedPixmap.rect());
//    painter.setClipPath(path);

//    // 将原始图像缩放并绘制到圆形区域内
//    QPixmap scaledPixmap = pixmap.scaled(roundedPixmap.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
//    painter.drawPixmap(roundedPixmap.rect(), scaledPixmap);

//    // 设置 QLabel 的圆形图像
//    ui->title->setPixmap(roundedPixmap);
//    ui->title->setFixedSize(30 * 2, 30 * 2);

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

void myDialog::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    // 获取当前要绘制的背景图片路径
    QString imagePath = imagePaths[currentImageIndex];

    QPixmap backgroundPixmap(imagePath);

    // 考虑边框和圆角，裁剪绘制区域
    QRect rect = this->rect().adjusted(3,3, -3, -3);
    QPainterPath clipPath;
    clipPath.addRoundedRect(rect, 20, 20);
    painter.setClipPath(clipPath);
    QPixmap scaledPixmap = backgroundPixmap.scaled(rect.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // 绘制背景图片
    painter.drawPixmap(rect, scaledPixmap);

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

    // 创建关闭按钮
    QIcon normalIcon("D:\\picture\\天气之子\\Light\\Arrow - Right Square.png");
    QIcon boldIcon("D:\\picture\\天气之子\\Bold\\Arrow - Right Square.png");
    label_close = new CLickLable(normalIcon, boldIcon,ui->titlebar);
    // 创建最小化按钮
    QIcon normalIcon1("D:\\picture\\天气之子\\Light\\Arrow - Down Square.png");
    QIcon boldIcon1("D:\\picture\\天气之子\\Bold\\Arrow - Down Square.png");
    label_min = new CLickLable(normalIcon1, boldIcon1,ui->titlebar);

    label_min->setStyleSheet("border: none;");
    label_close->setStyleSheet("border: none;");

    connect(label_min, &CLickLable::clicked, this, &myDialog::showMinimized);
    connect(label_close, &CLickLable::clicked, this, &myDialog::close);

    titleLayout->addStretch();
    titleLayout->addWidget(label_min);
    titleLayout->addWidget(label_close);

}


myDialog::~myDialog()
{
    delete ui;
}
