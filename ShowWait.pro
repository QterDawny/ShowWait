#-------------------------------------------------
#
# Project created by QtCreator 2015-05-19T14:27:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ShowWait
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialogwait.cpp \
    formwait.cpp \
    zcyclprogress.cpp

HEADERS  += mainwindow.h \
    dialogwait.h \
    formwait.h \
    zcyclprogress.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc
