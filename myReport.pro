QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += \
    src/gui/ \
    src/base/ \
    F:\Development\Libs\OpenSSL-Win64\include

SOURCES += \
    src/base/databasemanager.cpp \
    src/base/nospacevalidator.cpp \
    src/base/namevalidator.cpp \
    src/app/main.cpp \
    src/base/password.cpp \
    src/gui/groupslistedit.cpp \
    src/gui/listeditwidget.cpp \
    src/gui/logindialog.cpp \
    src/gui/mainwindow.cpp \
    src/gui/starterdialog.cpp \
    src/gui/subjectslistedit.cpp

HEADERS += \
    src/base/databasemanager.h \
    src/base/nospacevalidator.h \
    src/base/namevalidator.h \
    src/base/password.h \
    src/gui/groupslistedit.h \
    src/gui/listeditwidget.h \
    src/gui/logindialog.h \
    src/gui/mainwindow.h \
    src/gui/starterdialog.h \
    src/gui/subjectslistedit.h

FORMS += \
    src/gui/listeditwidget.ui \
    src/gui/logindialog.ui \
    src/gui/mainwindow.ui \
    src/gui/starterdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src/res/resources.qrc
