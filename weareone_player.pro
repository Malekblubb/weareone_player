#-------------------------------------------------
#
# Project created by QtCreator 2014-10-05T16:24:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXX = clang++
QMAKE_CXXFLAGS += -std=c++1y

TARGET = weareone_player
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    player.cpp \
    infograbber.cpp

HEADERS  += \
    streams.hpp \
    player.hpp \
    mainwindow.hpp \
    infograbber.h

FORMS    += mainwindow.ui
