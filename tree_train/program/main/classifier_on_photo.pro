QT += core
QT -= gui

TARGET = classifier_on_photo
CONFIG += console

CONFIG +=   link_pkgconfig\
            c++11

PKGCONFIG   += opencv

TEMPLATE = app

SOURCES += main.cpp
