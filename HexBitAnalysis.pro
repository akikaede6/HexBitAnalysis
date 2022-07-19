#-------------------------------------------------
#
# Project created by QtCreator 2015-01-11T19:53:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HexBitAnalysis
TEMPLATE = app


SOURCES += main.cpp\
    analsiswidget.cpp \
    binarywidget.cpp \
        hexbitanalysis.cpp \
    mywidget.cpp \
    mainwindow.cpp

HEADERS  += hexbitanalysis.h \
    analsiswidget.h \
    binarywidget.h \
    mywidget.h \
    mainwindow.h \
    util.h

FORMS    += hexbitanalysis.ui

RESOURCES += \
    image.qrc

RC_FILE = appicon.rc

OTHER_FILES +=
