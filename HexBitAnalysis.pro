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
        hexbitanalysis.cpp \
    mywidget.cpp

HEADERS  += hexbitanalysis.h \
    mywidget.h

FORMS    += hexbitanalysis.ui

RESOURCES += \
    image.qrc

RC_FILE = appicon.rc

OTHER_FILES +=
