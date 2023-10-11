#include "framelessWidget.h"
#include "ui_framelessWidget.h"
#include "qtmaterialautocomplete.h"

framelessWidget::framelessWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::framelessWidget)
{
    ui->setupUi(this);
    setMouseTracking(true);

    QTimer *t = new QTimer(this);
    connect(t, &QTimer::timeout, this, [=](){Init();});
    t->setSingleShot(true);
    t->start(10);

    QApplication::setOrganizationName("mymusic");
    QApplication::setApplicationName("10.1");
    readset();
    //loginAnimation();

    connect(ui->checkBox,&QCheckBox::clicked,this,&framelessWidget::clickSound);
    connect(ui->register_2,&QPushButton::clicked,this,&framelessWidget::clickSound);
}

framelessWidget::~framelessWidget()
{
    delete ui;
}

void framelessWidget::readset()
{
    QSettings set;
    bool value = set.value("saved", false).toBool();
    my_user = set.value("Username", "user").toString();
    QString PSWD = encrypt("123456");
    my_pswd = set.value("PSWD", PSWD).toString();

    if (value) {
        ui->username->setText(my_user);
        ui->checkBox->setChecked(value);
    }
}

void framelessWidget::writeset()
{
    QSettings set;
    set.setValue("Username", my_user);
    set.setValue("PSWD", my_pswd);

    // 保存按钮的选中状态
    set.setValue("saved", ui->checkBox->isChecked());
}

//对密码进行加密
QString framelessWidget::encrypt(const QString &str)
{
    QByteArray btArray=str.toLocal8Bit();
    QCryptographicHash hash(QCryptographicHash::Sha512);
    hash.addData(btArray);
    QByteArray resultArray=hash.result();
    QString sha512=resultArray.toHex();
    return sha512;
}

void framelessWidget::CriticalMessage(int &count)
{
    QMessageBox Critial;
    Critial.setIcon(QMessageBox::Critical);
    Critial.setWindowTitle("错误！！！");
    Critial.setWindowIcon(QIcon(":/picture/gif/music-alt.png"));
    QString messageText = QString("<span style='color:#87CEEB; font-family:幼圆; font-size:20pt;'>错误超过%1次了</span>").arg(count);
    Critial.setText(messageText);
    QPixmap Critialmap(":/picture/gif/4.jpg");
    Critial.setIconPixmap(Critialmap);
    QPushButton *Button =Critial.addButton("等一会再试试吧", QMessageBox::ActionRole);
    Button->setStyleSheet("QPushButton {"
        "border: 0.5px solid white;"
        "border-radius: 6px;"
        "background-color: rgb(90,194,198);"
        "min-width: 80px;"
        "font-family: '幼圆';"
        "font-size: 11pt;"
        "font-weight: bold;"
        "color: white;"
    "}"
        "QPushButton:hover {"
        "border: 0.5px solid white;"
        "border-radius: 6px;"
        "background-color: #1fab89;"
        "min-width: 80px;"
        "font-family: '幼圆';"
        "font-size: 10pt;"
        "font-weight: bold;"
        "color: white;"
    "}");
    //这里按钮可以设置居中
    //大小也可以设置
    Critial.exec();
    connect(Button,&QPushButton::clicked,this,&framelessWidget::clickSound);
    if(Critial.clickedButton()==Button){
       Critial.reject();
    }
}

void framelessWidget::WarningMessage(int &count)
{
    QMessageBox Warning;
    Warning.setIcon(QMessageBox::Warning);
    Warning.setWindowIcon(QIcon(":/picture/gif/music-alt.png"));
    QString titleText = QString(" 警告！！！");
    QString messageText = QString("<font color='#87CEEB' face='幼圆' size='20'>呜呜呜....这是第%1回失误</font>").arg(count);
    Warning.setWindowTitle(titleText);
    Warning.setText(messageText);

    QPixmap Warningmap(":/picture/gif/7.jpg");
    Warning.setIconPixmap(Warningmap);
    QPushButton *Button =Warning.addButton("好像哪里不对", QMessageBox::ActionRole);
    Button->setStyleSheet("QPushButton {"
        "border: 0.5px solid white;"
        "border-radius: 6px;"
        "background-color: rgb(90,194,198);"
        "min-width: 80px;"
        "font-family: '幼圆';"
        "font-size: 11pt;"
        "font-weight: bold;"
        "color: white;"
    "}"
        "QPushButton:hover {"
        "border: 0.5px solid white;"
        "border-radius: 6px;"
        "background-color: #1fab89;"
        "min-width: 80px;"
        "font-family: '幼圆';"
        "font-size: 10pt;"
        "font-weight: bold;"
        "color: white;"
    "}");
    connect(Button,&QPushButton::clicked,this,&framelessWidget::clickSound);
    Warning.exec();
    if(Warning.clickedButton()==Button){
       Warning.reject();
    }
}

void framelessWidget::clickSound()
{
    sound.setSource(QUrl::fromLocalFile("D:\\picture\\天气之子\\音效\\click.wav"));
    sound.setVolume(1.0);
    sound.play();
}

//void framelessWidget::loginAnimation()
//{
//    for (int i = 0; i < ui->login->text().length(); ++i) {
//       // 创建一个QPropertyAnimation，控制文本的缩放效果
//       QPropertyAnimation* animation = new QPropertyAnimation(ui->login, QByteArrayLiteral("geometry"));
//       animation->setDuration(500); // 动画持续时间
//       animation->setEasingCurve(QEasingCurve::InOutQuad); // 缓动曲线

//       // 计算每个字母的新位置，使其上下跳动
//       QRect targetRect =ui->login->rect();
//       targetRect.adjust(0, -10, 0, 10);
//       //动画效果更加平滑
//       animation->setEasingCurve(QEasingCurve::Linear);
//       animation->setStartValue(ui->login->geometry());
//       animation->setEndValue(targetRect);

//       sequentialAnimation->addAnimation(animation);
//    }
//    sequentialAnimation->start();
//}

void framelessWidget::Init()
{
    QPainter painter(ui->mainWidget);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    QPainterPath path;
    path.addRoundedRect(ui->mainWidget->rect(), cornerRadius-1 , cornerRadius-1 );
    QRegion mask(path.toFillPolygon().toPolygon());
    ui->mainWidget->setMask(mask);
    // 给mainwidget添加样式
//    QString mainStyle;
//    ui->mainWidget->setObjectName("mainWidget");
//    mainStyle = "QWidget#mainWidget{background-color: rgba(251, 251, 251, 50);" + QString::asprintf("border-radius:%dpx}", cornerRadius);
//    ui->mainWidget->setStyleSheet(mainStyle);

    //这里是遮挡锯齿的边框
    border = new QWidget(this);
    border->move(ui->mainWidget->pos() - QPoint(1, 1));
    border->resize(ui->mainWidget->size() + QSize(2, 2));
    QString borderStyle;
    borderStyle = "background-color:#00FFFFFF;border:1.5px solid white; border-radius:" + QString::asprintf("%d",cornerRadius) + "px";
    border->setStyleSheet(borderStyle);
    border->setAttribute(Qt::WA_TransparentForMouseEvents);
    border->show();
    //搞一个动画
    QMovie *movie = new QMovie(":/picture/gif/2.gif");
    ui->label->setMovie(movie);
    movie->start();


    QPixmap passwordIcon(":/picture/gif/Password.png");
    passwordIcon = passwordIcon.scaled(QSize(100, 100), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QAction *action1 = new QAction(passwordIcon, "Password", this);
    ui->password->addAction(action1, QLineEdit::LeadingPosition);

    QPixmap profileIcon(":/picture/gif/Profile.png");
    profileIcon = profileIcon.scaled(QSize(100, 100), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QAction *action2 = new QAction(profileIcon, "Profile", this);
    ui->username->addAction(action2, QLineEdit::LeadingPosition);


    //给密码输入栏右侧添加图标(只有选中情况下才会显示眼睛图标)
    static bool first_display = true;
    int stat = 0;
    QAction *action = new QAction(this);
    action->setIcon(QIcon(":/picture/gif/preview-close.png"));

    connect(ui->password, &QLineEdit::textEdited, this, [=] {
        if (first_display && !ui->password->text().isEmpty()) {
            ui->password->addAction(action, QLineEdit::TrailingPosition);
            first_display = false;
        } else if (!ui->password->text().isEmpty()){
            ui->password->addAction(action, QLineEdit::TrailingPosition);
        } else {
            ui->password->removeAction(action);
        }
    });

    connect(action, &QAction::triggered, this, [=]() mutable {
        if (stat == 0) {
            action->setIcon(QIcon(":/picture/gif/eyes-open.png"));
            ui->password->addAction(action, QLineEdit::TrailingPosition);
            ui->password->setEchoMode(QLineEdit::Normal);
            stat = 1;
        } else if (stat == 1) {
            action->setIcon(QIcon(":/picture/gif/preview-close.png"));
            ui->password->addAction(action, QLineEdit::TrailingPosition);
            ui->password->setEchoMode(QLineEdit::Password);
            stat = 0;
        }
    });

}

void framelessWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        mousePressed = true;
    }
}

void framelessWidget::on_confirm_clicked()
{
    QString user=ui->username->text().trimmed();
    QString pswd=ui->password->text().trimmed();
    QString encrypt_pswd=encrypt(pswd);
    clickSound();
    QDialog *parentDialog = qobject_cast<QDialog*>(parent());
    if(user==my_user&&encrypt_pswd==my_pswd){
        writeset();
        if(parentDialog){
            parentDialog->accept();
        }
    }
    else{
        trycount++;
        if(trycount>3){
            CriticalMessage(trycount);
            if (parentDialog) {
                parentDialog->reject();
            }
        }
        else
            WarningMessage(trycount);
    }
}


void framelessWidget::on_checkBox_clicked(bool checked)
{
    if(checked){
    QIcon lockIcon(":/picture/gif/Lock.png");
    ui->checkBox->setIcon(lockIcon);
    }
    else{
    QIcon unLockIcon(":/picture/gif/Unlock.png");
    ui->checkBox->setIcon(unLockIcon);
    }
    clickSound();
}

