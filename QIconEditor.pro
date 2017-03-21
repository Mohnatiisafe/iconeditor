#-------------------------------------------------
#
# Project created by QtCreator 2016-11-22T18:28:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QIconEditor
TEMPLATE = app


SOURCES += main.cpp\
        iconeditor.cpp \
    icon.cpp

HEADERS  += iconeditor.h \
    icon.h

FORMS    += iconeditor.ui

RESOURCES += \
    icon.qrc
