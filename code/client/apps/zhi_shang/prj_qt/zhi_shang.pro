#-------------------------------------------------
#
# Project created by QtCreator 2017-05-23T15:20:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zhi_shang
TEMPLATE = app
CONFIG += c++11

DISTFILES +=

BASE_DIR = ../../..

INCLUDEPATH += $$BASE_DIR/module

SOURCES += ../source/main.cpp

# module
MODULE_DIR = $$BASE_DIR/module
include($$MODULE_DIR/main/main.pri)
include($$MODULE_DIR/network/network.pri)
