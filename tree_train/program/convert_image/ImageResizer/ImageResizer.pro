#-------------------------------------------------
#
# Project created by QtCreator 2016-11-14T20:12:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageResizer
TEMPLATE = app

SOURCES += main.cpp

CONFIG += mobility

CONFIG +=   link_pkgconfig\
            c++11
PKGCONFIG   += opencv

