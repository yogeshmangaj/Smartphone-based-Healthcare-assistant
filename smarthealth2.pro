#-------------------------------------------------
#
# Project created by QtCreator 2012-04-13T09:45:33
#
#-------------------------------------------------

QT       += core gui sql

TARGET = smarthealth2
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui

CONFIG += mobility

MOBILITY = messaging


OTHER_FILES += \
    health.db3 \
    qtc_packaging/debian_fremantle/rules \
    qtc_packaging/debian_fremantle/README \
    qtc_packaging/debian_fremantle/copyright \
    qtc_packaging/debian_fremantle/control \
    qtc_packaging/debian_fremantle/compat \
    qtc_packaging/debian_fremantle/changelog















