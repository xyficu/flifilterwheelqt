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

#INCLUDEPATH += /home/xyf/fli/libfli
#LIBS += ./libfli.a

SOURCES += main.cpp\
        mainwindow.cpp \
    cfw12.cpp \

HEADERS  += mainwindow.h \
    cfw12.h


FORMS    += mainwindow.ui



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/release/ -lfli
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/debug/ -lfli
else:unix: LIBS += -L$$PWD/ -lfli

INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/release/libfli.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/debug/libfli.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/release/fli.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/debug/fli.lib
else:unix: PRE_TARGETDEPS += $$PWD/libfli.a
