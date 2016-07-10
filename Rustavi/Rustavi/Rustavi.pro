#-------------------------------------------------
#
# Project created by QtCreator 2016-03-03T14:25:43
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Rustavi
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    NetUDPClient.cpp \
    NetUDPClient_Rustavi.cpp \
    TIndicatorFrame.cpp

HEADERS  += mainwindow.h \
    HWPacket.h \
    NetPacket.hpp \
    NetDevice.h \
    NetUDPClient.h \
    NetUDPClient_Rustavi.h \
    NetModule.h \
    NetCommand.h \
    NetState.h \
    TIndicatorFrame.h

FORMS    += mainwindow.ui
QMAKE_CXXFLAGS += -std=c++11

RESOURCES += \
    images.qrc
