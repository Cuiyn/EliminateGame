#-------------------------------------------------
#
# Project created by QtCreator 2015-05-09T18:44:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp \
    dialog_list.cpp \
    score_list.cpp \
    dialog_entername.cpp \
    replay.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    dialog_list.h \
    score_list.h \
    dialog_entername.h \
    replay.h

FORMS    += mainwindow.ui \
    dialog.ui \
    dialog_list.ui \
    dialog_entername.ui \
    replay.ui

RESOURCES += \
    picture.qrc
