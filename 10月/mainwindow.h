#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include  <QMainWindow>
#include  <QtMultimedia>
#include  <QListWidgetItem>
#include  <QFileDialog>
#include  <QVariant>
#include  <QKeyEvent>
#include  <QWidget>
#include  <QListWidget>
#include <QAudioOutput>
#include <QDir>
#include <QFileInfo>
#include <QUrl>
#include <QIcon>
#include <QImage>
#include <QPixmap>
#include <QMap>
#include <QEvent>
#include <QMouseEvent>
#include <QPoint>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QStringList picFilePaths;
    QMediaPlayer::PlaybackState playstate;
    QPointF previousPos;
    QMediaPlayer  *player;
    QPixmap icon1,icon2,icon3,icon4,icon5,icon6,icon7,icon8,icon9,icon10;
    //是否循环播放
    int curValue = 0;
    bool muted=true;
    bool isPlaying = false;
    bool    loopPlay=true;
    QString  durationTime;
    QString  positionTime;
    QString picPath;
    qint64 totalTime;
    QMap<QString, QMap<qint64, QString>> songLyricsMap;
    QMap<qint64, QString> lyricsMap;
    QUrl getUrlFromItem(QListWidgetItem *item);
    bool eventFilter(QObject *watched, QEvent *event);
public:
    MainWindow(QWidget *parent = nullptr);
    void updateLyrics(qint64 position);
    void addSong(const QString &songFilePath);
    void titleClick();
    void clickSound();
    ~MainWindow();
protected:
    void enterEvent(QEnterEvent *event);
    void leaveEvent(QEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private slots:
    void do_stateChanged(QMediaPlayer::PlaybackState state);
    void do_sourceChanged(const QUrl &media);
    void do_durationChanged(qint64 duration);
    void do_positionChanged(qint64 position);
    void on_btnAdd_clicked();
    void on_btnStop_clicked();
    void on_listWidget_doubleClicked(const QModelIndex &index);
    void on_btnClear_clicked();
    void on_sliderVolumn_valueChanged(int value);
    void on_btnSound_clicked();
    void on_sliderPosition_valueChanged(int value);
    void on_btnPrevious_clicked();
    void on_btnNext_clicked();
    void on_btnLoop_clicked(bool checked);
    void on_doubleSpinBox_valueChanged(double value);
    void on_btnRemove_clicked();
    void on_btnPlay_clicked();

    void on_btnPause_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
