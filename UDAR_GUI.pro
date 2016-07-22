#-------------------------------------------------
#
# Project created by QtCreator 2016-06-27T21:11:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = UDAR_GUI
TEMPLATE = app


SOURCES += main.cpp\
        udar_controller.cpp \
    getip.cpp \
    netinterface.cpp \
    packet_rx.cpp \
    qcustomplot.cpp \
    fftCT.cpp \
    hexspinbox.cpp \
    decode_pcap.cpp

HEADERS  += udar_controller.h \
    getip.h \
    netinterface.h \
    packet_rx.h \
    qcustomplot.h \
    fftCT.h \
    hexspinbox.h \
    decode_pcap.h

FORMS    += udar_controller.ui

INCLUDEPATH += "usr/include/pcap/"
LIBS    +=  -lpcap
