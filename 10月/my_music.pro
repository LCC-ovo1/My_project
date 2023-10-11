QT       += core gui
QT += widgets
QT += multimedia
QT +=multimediawidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


LIBS += -L$$PWD/libs/lcomponents.a
INCLUDEPATH += $$PWD/libs/include

SOURCES += \
    clicklable.cpp \
    framelessWidget.cpp \
    main.cpp \
    mainwindow.cpp \
    mydialog.cpp

HEADERS += \
    clicklable.h \
    framelessWidget.h \
    mainwindow.h \
    mydialog.h

FORMS += \
    framelessWidget.ui \
    mainwindow.ui \
    mydialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ../../图片/gif/rec.qrc \
    ../../图片/gif/recs.qrc \
    ../../图片/gif/recs.qrc \
    recsoure.qrc \
    res/resc.qrc

DISTFILES += \
    ../../picture/gif/music-alt.png \
    ../../图片/天气之子/Light/2 User.png \
    ../../图片/天气之子/Light/3 User.png \
    ../../图片/天气之子/Light/Activity.png \
    ../../图片/天气之子/Light/Add User.png \
    ../../图片/天气之子/Light/Arrow - Down 2.png \
    ../../图片/天气之子/Light/Arrow - Down 3.png \
    ../../图片/天气之子/Light/Arrow - Down Circle.png \
    ../../图片/天气之子/Light/Arrow - Down Square.png \
    ../../图片/天气之子/Light/Arrow - Down.png \
    ../../图片/天气之子/Light/Arrow - Left 2.png \
    ../../图片/天气之子/Light/Arrow - Left 3.png \
    ../../图片/天气之子/Light/Arrow - Left Circle.png \
    ../../图片/天气之子/Light/Arrow - Left Square.png \
    ../../图片/天气之子/Light/Arrow - Left.png \
    ../../图片/天气之子/Light/Arrow - Right 2.png \
    ../../图片/天气之子/Light/Arrow - Right 3.png \
    ../../图片/天气之子/Light/Arrow - Right Circle.png \
    ../../图片/天气之子/Light/Arrow - Right Square.png \
    ../../图片/天气之子/Light/Arrow - Right.png \
    ../../图片/天气之子/Light/Arrow - Up 2.png \
    ../../图片/天气之子/Light/Arrow - Up 3.png \
    ../../图片/天气之子/Light/Arrow - Up Circle.png \
    ../../图片/天气之子/Light/Arrow - Up Square.png \
    ../../图片/天气之子/Light/Arrow - Up.png \
    ../../图片/天气之子/Light/Bag 2.png \
    ../../图片/天气之子/Light/Bag.png \
    ../../图片/天气之子/Light/Bookmark.png \
    ../../图片/天气之子/Light/Buy.png \
    ../../图片/天气之子/Light/Calendar.png \
    ../../图片/天气之子/Light/Call Missed.png \
    ../../图片/天气之子/Light/Call Silent.png \
    ../../图片/天气之子/Light/Call.png \
    ../../图片/天气之子/Light/Calling.png \
    ../../图片/天气之子/Light/Camera.png \
    ../../图片/天气之子/Light/Category.png \
    ../../图片/天气之子/Light/Chart.png \
    ../../图片/天气之子/Light/Chat.png \
    ../../图片/天气之子/Light/Close Square.png \
    ../../图片/天气之子/Light/Danger.png \
    ../../图片/天气之子/Light/Delete.png \
    ../../图片/天气之子/Light/Discount.png \
    ../../图片/天气之子/Light/Discovery.png \
    ../../图片/天气之子/Light/Document.png \
    ../../图片/天气之子/Light/Download.png \
    ../../图片/天气之子/Light/Edit Square.png \
    ../../图片/天气之子/Light/Edit.png \
    ../../图片/天气之子/Light/Filter 2.png \
    ../../图片/天气之子/Light/Filter.png \
    ../../图片/天气之子/Light/Folder.png \
    ../../图片/天气之子/Light/Game.png \
    ../../图片/天气之子/Light/Graph.png \
    ../../图片/天气之子/Light/Heart.png \
    ../../图片/天气之子/Light/Hide.png \
    ../../图片/天气之子/Light/Home.png \
    ../../图片/天气之子/Light/Image 2.png \
    ../../图片/天气之子/Light/Image.png \
    ../../图片/天气之子/Light/Info Circle.png \
    ../../图片/天气之子/Light/Info Square.png \
    ../../图片/天气之子/Light/Location.png \
    ../../图片/天气之子/Light/Lock.png \
    ../../图片/天气之子/Light/Login.png \
    ../../图片/天气之子/Light/Logout.png \
    ../../图片/天气之子/Light/Message.png \
    ../../图片/天气之子/Light/More Circle.png \
    ../../图片/天气之子/Light/More Square.png \
    ../../图片/天气之子/Light/Notification.png \
    ../../图片/天气之子/Light/Paper Download.png \
    ../../图片/天气之子/Light/Paper Fail.png \
    ../../图片/天气之子/Light/Paper Negative.png \
    ../../图片/天气之子/Light/Paper Plus.png \
    ../../图片/天气之子/Light/Paper Upload.png \
    ../../图片/天气之子/Light/Paper.png \
    ../../图片/天气之子/Light/Password.png \
    ../../图片/天气之子/Light/Play.png \
    ../../图片/天气之子/Light/Plus.png \
    ../../图片/天气之子/Light/Profile.png \
    ../../图片/天气之子/Light/Scan.png \
    ../../图片/天气之子/Light/Search.png \
    ../../图片/天气之子/Light/Send.png \
    ../../图片/天气之子/Light/Setting.png \
    ../../图片/天气之子/Light/Shield Done.png \
    ../../图片/天气之子/Light/Shield Fail.png \
    ../../图片/天气之子/Light/Show.png \
    ../../图片/天气之子/Light/Star.png \
    ../../图片/天气之子/Light/Swap.png \
    ../../图片/天气之子/Light/Tick Square.png \
    ../../图片/天气之子/Light/Ticket Star.png \
    ../../图片/天气之子/Light/Ticket.png \
    ../../图片/天气之子/Light/Time Circle.png \
    ../../图片/天气之子/Light/Time Square.png \
    ../../图片/天气之子/Light/Unlock.png \
    ../../图片/天气之子/Light/Upload.png \
    ../../图片/天气之子/Light/Video.png \
    ../../图片/天气之子/Light/Voice 2.png \
    ../../图片/天气之子/Light/Voice.png \
    ../../图片/天气之子/Light/Volume Down.png \
    ../../图片/天气之子/Light/Volume Off.png \
    ../../图片/天气之子/Light/Volume Up.png \
    ../../图片/天气之子/Light/Wallet.png \
    ../../图片/天气之子/Light/Work.png \
    C:/Users/雷驰/Desktop/04《Qt 6 C++开发指南》全书示例源码--CMake完整版 V1.1(1).zip \
    images/001.GIF \
    images/110.JPG \
    images/132.bmp \
    images/212.bmp \
    images/214.bmp \
    images/224.bmp \
    images/237.GIF \
    images/316.bmp \
    images/318.bmp \
    images/430.bmp \
    images/610.bmp \
    images/612.bmp \
    images/616.bmp \
    images/620.bmp \
    images/622.bmp \
    images/624.bmp \
    images/630.bmp \
    images/632.bmp \
    images/828.bmp \
    images/audio24.png \
    images/music24.png \
    images/musicFile.png \
    images/musicFile32.png \
    images/mute.bmp \
    images/refresh16.png \
    images/volumn.bmp
