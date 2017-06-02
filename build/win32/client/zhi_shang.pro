#-------------------------------------------------
#
# Project created by QtCreator 2017-06-02T14:05:32
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zhi_shang

TEMPLATE = app
CONFIG += c++11

BASE_DIR = ../../..

INCLUDEPATH += $$BASE_DIR/code/client/module

SOURCES += $$BASE_DIR/code/client/apps/main/source/main.cpp

# module
MODULE_DIR = $$BASE_DIR/code/client/module
include($$MODULE_DIR/main/main.pri)
include($$MODULE_DIR/network/network.pri)
