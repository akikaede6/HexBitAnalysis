#-------------------------------------------------
#
# Project created by QtCreator 2015-01-11T19:53:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HexBitAnalysis
TEMPLATE = app

CONFIG += c++17

SOURCES += main.cpp\
    analsiswidget.cpp \
    binarywidget.cpp \
    fontdialog.cpp \
    mainwindow.cpp \
    mousegroupbox.cpp \
    selectedwidget.cpp \
    util.cpp

HEADERS  += \
    analsiswidget.h \
    binarywidget.h \
    fontdialog.h \
    mainwindow.h \
    mousegroupbox.h \
    selectedwidget.h \
    util.h

FORMS    +=

RESOURCES += \
    image.qrc

RC_FILE = appicon.rc

OTHER_FILES +=
