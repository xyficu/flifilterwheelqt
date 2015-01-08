#-------------------------------------------------
#
# Project created by QtCreator 2014-12-12T00:01:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = flifilterwheelqt
TEMPLATE = app

#CONFIG += static
#CONFIG += shared
#CONFIG += qt thread

SOURCES += main.cpp\
        mainwindow.cpp \
    cfw12.cpp \
    about.cpp \
    cfwthread.cpp \
    cfwtcp.cpp

HEADERS  += mainwindow.h \
    cfw12.h \
    about.h \
    cfwthread.h \
    cfwtcp.h


FORMS    += mainwindow.ui \
    about.ui




unix:!macx: LIBS += -L$$PWD/ -lfli

INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/

unix:!macx: PRE_TARGETDEPS += $$PWD/libfli.a

OTHER_FILES +=
