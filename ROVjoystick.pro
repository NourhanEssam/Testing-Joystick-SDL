#-------------------------------------------------
#
# Project created by QtCreator 2015-12-03T18:07:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ROVjoystick
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    joysticksdl.cpp

HEADERS  += mainwindow.h \
    joysticksdl.h

FORMS    += mainwindow.ui

LIBS += -LC:/Users/Esam/Downloads/SDL-devel-1.2.15-mingw32/SDL-1.2.15/lib -lSDL
INCLUDEPATH += C:/Users/Esam/Downloads/SDL-devel-1.2.15-mingw32/SDL-1.2.15/include/SDL
