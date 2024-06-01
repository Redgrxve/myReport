QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += \
    src/gui/ \
    src/base/ \
    src/utils/ \
    libs/OpenSSL/include

LIBS += \
    -L$$PWD/libs/OpenSSL/lib/MDd -lssl -lcrypto

SOURCES += \
    src/base/appconfig.cpp \
    src/base/comboboxdelegate.cpp \
    src/base/databasemanager.cpp \
    src/app/main.cpp \
    src/base/windowmanager.cpp \
    src/gui/calendardialog.cpp \
    src/gui/groupslistedit.cpp \
    src/gui/listeditwidget.cpp \
    src/gui/logindialog.cpp \
    src/gui/mainwindow.cpp \
    src/gui/reportdetailswidget.cpp \
    src/gui/reportlistitemwidget.cpp \
    src/gui/studentslistedit.cpp \
    src/gui/subjectslistedit.cpp

HEADERS += \
    src/base/appconfig.h \
    src/base/comboboxdelegate.h \
    src/base/databasemanager.h \
    src/base/windowmanager.h \
    src/gui/calendardialog.h \
    src/gui/groupslistedit.h \
    src/gui/listeditwidget.h \
    src/gui/logindialog.h \
    src/gui/mainwindow.h \
    src/gui/reportdetailswidget.h \
    src/gui/reportlistitemwidget.h \
    src/gui/studentslistedit.h \
    src/gui/subjectslistedit.h \
    src/utils/passwordencrypt.h

FORMS += \
    src/gui/calendardialog.ui \
    src/gui/listeditwidget.ui \
    src/gui/logindialog.ui \
    src/gui/mainwindow.ui \
    src/gui/reportdetailswidget.ui \
    src/gui/reportlistitemwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src/res/resources.qrc
