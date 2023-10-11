#include "mainwindow.h"
#include "ui_mainwindow.h"


QUrl MainWindow::getUrlFromItem(QListWidgetItem *item)
{
    //QVariant转换为QUrl类型
    QVariant itemData= item->data(Qt::UserRole);
    QUrl source =itemData.value<QUrl>();
    return source;
}
//避免一些按键问题
bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() != QEvent::KeyPress)
        return QWidget::eventFilter(watched,event);

    QKeyEvent *keyEvent=static_cast<QKeyEvent *>(event);
    if (keyEvent->key() != Qt::Key_Delete)
        return QWidget::eventFilter(watched,event);

    if (watched==ui->listWidget)
    {
        QListWidgetItem *item= ui->listWidget->takeItem(ui->listWidget->currentRow());
        delete  item;
    }
    return true;
}
//显示歌词和图片
void MainWindow::updateLyrics(qint64 position)
{
    int currentSongIndex = ui->listWidget->currentRow();
    if (currentSongIndex < 0) {
        // 没有选定歌曲
        ui->labCur->clear();
        ui->labPic->clear();
        return;
    }

    QString currentSongFilePath = ui->listWidget->currentItem()->data(Qt::UserRole).toUrl().toLocalFile();

    if (songLyricsMap.contains(currentSongFilePath)) {
        QMap<qint64, QString> lyricsMap = songLyricsMap[currentSongFilePath];
        QMap<qint64, QString>::iterator it = lyricsMap.lowerBound(position);

        if (it != lyricsMap.end()) {
            // 显示歌词
            ui->labCur->setText(it.value());

            // 显示相关的图片
            int count = picFilePaths.count();
            if (currentSongIndex >= 0 && currentSongIndex < count) {
                QString picFilePath = picFilePaths[currentSongIndex];
                QImage image(picFilePath);
                QSize labelSize = ui->labPic->size();
                QPixmap pixmap = QPixmap::fromImage(image).scaled(labelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

//                QPainter painter;
//                painter.setPen(Qt::NoPen);
//                painter.setRenderHint(QPainter::Antialiasing, true);
//                QPoint centerPoint = rect().center();

//                painter.save();
//                painter.translate(centerPoint);
//                int radius = (std::min(width(),height()) - 10 * 2 ) / 2;
//                painter.setPen(QColor(255, 240, 245));
//                painter.drawEllipse(QPoint(0, 0), radius, radius);
//                painter.restore();
//                QRect rect = QRect(-radius, -radius,
//                                   radius*2, radius*2);
//                painter.drawPixmap(rect,pixmap);

//                QRegion maskedRegion(rect, QRegion::Ellipse);
//                painter.setClipRegion(maskedRegion);

//                QTimer timer;
//                double angle{0.0};
//                connect(&timer,&QTimer::timeout,[this,&angle]
//                        {
//                            angle += 1.0;
//                            if(angle == 360)
//                                angle = 0.0;
//                            update();
//                        });
//                timer.start(40);

                ui->labPic->setPixmap(pixmap);
                ui->labPic->show();

            }
        } else {
            // 清除歌词和图片
            ui->labCur->clear();
            ui->labPic->clear();
        }
    } else {
        // 当前歌曲没有歌词
        ui->labCur->clear();
        ui->labPic->clear();
    }
}


void MainWindow::addSong(const QString &songFilePath)
{
    lyricsMap.clear();

    // 添加歌曲到播放列表
    QListWidgetItem *aItem = new QListWidgetItem(QFileInfo(songFilePath).fileName());
    //aItem->setIcon(QIcon(""));
    aItem->setData(Qt::UserRole, QUrl::fromLocalFile(songFilePath));
    ui->listWidget->addItem(aItem);

    // 构建歌词文件的目标路径
    QFileInfo songFileInfo(songFilePath);
    QString lyricsFileName = QFileInfo(songFileInfo.fileName()).baseName() + ".lrc";
    QString lyricsFilePath = "D:\\图片\\图标\\sucai\\lyrics\\"+ lyricsFileName;

    QString picFileName = QFileInfo(songFilePath).baseName() + ".jpg";
    QString picFilePath = "D:\\图片\\图标\\sucai\\picture\\" + picFileName;

    QFileInfo picFileInfo(picFilePath);
    if (picFileInfo.exists() && picFileInfo.isFile()) {
        picFilePaths.append(picFilePath);
    } else {
        qDebug() << "图片文件不存在：" << picFilePath;
    }

    // 检查目标路径是否存在歌词文件
    QFileInfo lyricsFileInfo(lyricsFilePath);
    if (lyricsFileInfo.exists() && lyricsFileInfo.isFile()) {
        // 读取并解析歌词文件
        QFile lyricsFile(lyricsFilePath);
        if (lyricsFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&lyricsFile);
            while (!in.atEnd()) {
                QString line = in.readLine();
                // 使用正则表达式解析歌词行
                QRegularExpression re("\\[(\\d+):(\\d+).(\\d+)\\](.*)");
                QRegularExpressionMatch match = re.match(line);
                if (match.hasMatch()) {
                    int minutes = match.captured(1).toInt();
                    int seconds = match.captured(2).toInt();
                    int milliseconds = match.captured(3).toInt();
                    QString text = match.captured(4);
                    // 计算歌词时间戳
                    qint64 timestamp = minutes * 60000 + seconds * 1000 + milliseconds;
                    // 关联时间戳和歌词文本
                    //这里有问题 把所有歌曲一次性加入进来就会乱码
                    lyricsMap.insert(timestamp, text);
                }
            }
            lyricsFile.close();
            songLyricsMap[songFilePath] = lyricsMap;
        }
    } else {
        // 未找到歌词文件
        qDebug() << "歌词文件不存在：" << lyricsFilePath;
    }
}

void MainWindow::titleClick()
{
    QPushButton *senderButton = qobject_cast<QPushButton *>(sender());
    if (senderButton == ui->btnClose) {
        this->close();
    } else if (senderButton == ui->btnMin) {
        this->hide();
    }
//    else if(senderButton==ui->btnMax){
//        //界面放大
//    }
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //这里是设置透明窗口而且可以无标题栏
    //this->setMouseTracking(true);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground, true);

    //可移动还要一些事件注册
    ui->listWidget->installEventFilter(this);
    ui->listWidget->setDragEnabled(true);
    ui->listWidget->setDragDropMode(QAbstractItemView::InternalMove);
    //初始隐藏 列表通过按钮点击
    ui->frame->hide();


    //这里是加音乐输出效果
    player = new QMediaPlayer(this);
    QAudioOutput *audioOutput = new QAudioOutput(this);
    player->setAudioOutput(audioOutput);

    connect(player,&QMediaPlayer::positionChanged,
            this, &MainWindow::do_positionChanged);

    connect(player,&QMediaPlayer::durationChanged,
            this, &MainWindow::do_durationChanged);

    connect(player, &QMediaPlayer::sourceChanged,
            this, &MainWindow::do_sourceChanged);

    connect(player, &QMediaPlayer::playbackStateChanged,
            this,  &MainWindow::do_stateChanged);

    connect(this->ui->btnShow,&QPushButton::clicked,[&](){
        if (this->ui->frame->isHidden()) {
            this->ui->frame->show();
            ui->btnShow->setIcon(icon1);
        } else {
            this->ui->frame->hide();
            ui->btnShow->setIcon(icon2);
        }
    });

//    connect(ui->btnPlay, &QPushButton::clicked, [&]() {
//        if (isPlaying) {
//            player->pause();
//            ui->btnPlay->setIcon(QIcon(":/picture/pic/pause1.png"));
//        } else {
//            if (ui->listWidget->currentRow() < 0)
//                ui->listWidget->setCurrentRow(0);
//            player->setSource(getUrlFromItem(ui->listWidget->currentItem()));
//            ui->btnPlay->setIcon(QIcon(":/picture/pic/play.png"));
//            player->play();
//        }
//        loopPlay = ui->btnLoop->isChecked();
//        isPlaying = !isPlaying;
//        clickSound();
//    });
    //进度条和静音的操作
    //connect(ui->sliderVolumn,&QSlider::valueChanged,this,&MainWindow::on_sliderVolumn_valueChanged);
    //connect(ui->btnSound,&QPushButton::clicked,this,&MainWindow::on_btnSound_clicked);

    icon1.load(":/picture/pic/show1.png");
    icon2.load(":/picture/pic/hide.png");
    icon3.load(":/picture/pic/title.png");
    icon4.load(":/picture/pic/100.png");
    icon5.load(":/picture/pic/open1.png");
    icon6.load(":/picture/pic/open2.png");
    icon7.load(":/picture/pic/min.png");
    icon8.load(":/picture/pic/103.png");
    icon9.load(":/picture/pic/close2.png");
    icon10.load(":/picture/pic/close1.png");
    //自定义button
   // ui->btnClose=new MyButton(icon6,icon5);
    //ui->btnMax =new MyButton(icon9,icon10);
    //ui->btnMin =new MyButton(icon7,icon8);

    connect(ui->btnClose,&QPushButton::clicked,this,&MainWindow::titleClick);
    connect(ui->btnMin,&QPushButton::clicked,this,&MainWindow::titleClick);

    //放大的先不实现 界面ui控件布局有点问题
}

MainWindow::~MainWindow()
{
    delete ui;
}
//图标动画
void MainWindow::enterEvent(QEnterEvent *event) {
    if (event->type() == QEvent::Enter) {
        ui->title->setIcon(icon4);
        ui->btnClose->setIcon(icon6);
        ui->btnMin->setIcon(icon7);
        ui->btnMax->setIcon(icon9);
    }
    QMainWindow::enterEvent(event);
}


void MainWindow::leaveEvent(QEvent *event) {
    if (event->type() == QEvent::Leave) {
        ui->title->setIcon(icon3);
        ui->btnClose->setIcon(icon5);
        ui->btnMin->setIcon(icon8);
        ui->btnMax->setIcon(icon10);
    }
    QMainWindow::leaveEvent(event);
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        previousPos = event->globalPosition() - frameGeometry().topLeft();
        event->accept();
    }

}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        QPoint newPos = event->globalPosition().toPoint() - previousPos.toPoint();
        move(newPos);
        event->accept();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        event->accept();
    }
}

void MainWindow::do_stateChanged(QMediaPlayer::PlaybackState state)
{
    playstate=state;
    qDebug() << "Playback state ..........." << state;

    ui->btnPlay->setEnabled(state != QMediaPlayer::PlayingState);
    ui->btnPause->setEnabled(state==QMediaPlayer::PlayingState);
    ui->btnStop->setEnabled(state == QMediaPlayer::PlayingState);

    if (loopPlay && (state == QMediaPlayer::StoppedState))
    {
        qDebug() << "state.................";

        int count = ui->listWidget->count();
        int curRow = ui->listWidget->currentRow();
        curRow++;
        curRow = curRow >= count ? 0 : curRow;
        ui->listWidget->setCurrentRow(curRow);
        player->setSource(getUrlFromItem(ui->listWidget->currentItem()));
        player->play();
    }
}


void MainWindow::do_sourceChanged(const QUrl &media)
{
    QString fileName = media.fileName();
    fileName.remove(".mp3");
    ui->labTitle->setText(fileName);
}

void MainWindow::do_durationChanged(qint64 duration)
{
    totalTime=duration;
    ui->sliderPosition->setMaximum(duration);

    int   secs=duration/1000;  //秒
    int   mins=secs/60;        //分钟
    secs=secs % 60;            //余数秒
    durationTime=QString::asprintf("%d:%d",mins,secs);
    ui->labRatio->setText(positionTime+"/"+durationTime);
}

void MainWindow::do_positionChanged(qint64 position)
{//播放位置变化时执行，更新进度显示
    if (ui->sliderPosition->isSliderDown())
        return;

    ui->sliderPosition->setSliderPosition(position);
    int   secs=position/1000;   //秒
    int   mins=secs/60;         //分钟
    secs=secs % 60;             //余数秒
    positionTime=QString::asprintf("%d:%d",mins,secs);
    ui->labRatio->setText(positionTime+"/"+durationTime);
    updateLyrics(position);
    qDebug() << "音频缓冲状态：";
}


void MainWindow::on_btnAdd_clicked()
{
    QString currentPath = QDir::currentPath();
    //获取系统当前目录
    QString dlgTitle="选择音频";
    //文件过滤
    QString filter="音频文件(*.mp3 *.wav *.wma);;所有文件(*.*)";
    QStringList fileList=QFileDialog::getOpenFileNames(this,dlgTitle,currentPath,filter);
    if (fileList.isEmpty())
        return;

    for(const QString &songFilePath :fileList){
        addSong(songFilePath);
    }
    if (player->playbackState() != QMediaPlayer::PlayingState)
    {  //当前没有在播放，就播放第1个文件
        ui->listWidget->setCurrentRow(0);
        QUrl source= getUrlFromItem(ui->listWidget->currentItem());
        player->setSource(source);
    }
    player->play();
}

void MainWindow::on_btnStop_clicked()
{//停止循环播放
    loopPlay=false;
    player->stop();
}

void MainWindow::on_listWidget_doubleClicked(const QModelIndex &index)
{//双击listWidget时切换播放文件
    Q_UNUSED(index);
    loopPlay=false;
    player->setSource(getUrlFromItem(ui->listWidget->currentItem()));
    player->play();
    loopPlay=ui->btnLoop->isChecked();
}

void MainWindow::on_btnClear_clicked()
{//清空播放列表
    //防止do_stateChanged()里切换曲目
    loopPlay=false;
    ui->listWidget->clear();
    player->stop();
}

void MainWindow::on_sliderVolumn_valueChanged(int value)
{
    // 更新音量值
    curValue=value;
    player->audioOutput()->setVolume(value / 100.0);
    if (value == 0) {
        ui->btnSound->setIcon(QIcon(":/picture/pic/sound_close.png"));
    } else{
        ui->btnSound->setIcon(QIcon(":/picture/pic/sound_start.png"));
    }
}

void MainWindow::on_btnSound_clicked()
{

    bool mute=player->audioOutput()->isMuted();
    player->audioOutput()->setMuted(!mute);
    if (mute){
        ui->btnSound->setIcon(QIcon(":/picture/pic/sound_close.png"));
         }
    else{
        ui->btnSound->setIcon(QIcon(":/picture/pic/sound_start.png"));
        }
}

void MainWindow::on_sliderPosition_valueChanged(int value)
{//播放进度调控
        if (player) {
        player->setPosition(value);
        updateLyrics(value);
        qDebug() << "音频缓冲状态：";
        }
}

void MainWindow::on_btnPrevious_clicked()
{//前一曲
     int count = ui->listWidget->count();
     int curRow = ui->listWidget->currentRow();
     curRow--;
     if (curRow < 0) {
        curRow = count - 1;
     }
     ui->listWidget->setCurrentRow(curRow);

    loopPlay=false;
    player->setSource(getUrlFromItem(ui->listWidget->currentItem()));
    player->play();
    loopPlay=ui->btnLoop->isChecked();
}
void MainWindow::on_btnNext_clicked()
{//下一曲
    int count = ui->listWidget->count();
    int curRow = ui->listWidget->currentRow();
    curRow++;
    if (curRow >= count) {
        curRow = 0;
    }
    ui->listWidget->setCurrentRow(curRow);
    //防止do_stateChanged()里切换曲目
    loopPlay=false;
    player->setSource(getUrlFromItem(ui->listWidget->currentItem()));
    player->play();
    loopPlay=ui->btnLoop->isChecked();
}

void MainWindow::on_btnLoop_clicked(bool checked)
{//"循环" 按钮
    loopPlay=checked;
}

void MainWindow::on_doubleSpinBox_valueChanged(double value)
{//"倍速"
    player->setPlaybackRate(value);
}

void MainWindow::on_btnRemove_clicked()
{//"移除"按钮
    int index =ui->listWidget->currentRow();
    if (index>=0)
    {
        QListWidgetItem *item= ui->listWidget->takeItem(index);
        delete item;
    }
}
void MainWindow::on_btnPlay_clicked()
{//开始播放
    if (ui->listWidget->currentRow()<0){
        ui->listWidget->setCurrentRow(0);
    }
    player->setSource(getUrlFromItem(ui->listWidget->currentItem()));
    player->play();
    qDebug() << "播放器状态: " <<  playstate;
    loopPlay=ui->btnLoop->isChecked();
}
//暂停
void MainWindow::on_btnPause_clicked()
{
    player->pause();
}

