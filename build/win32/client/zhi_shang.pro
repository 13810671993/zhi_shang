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
DEFINES += NOMINMAX


BASE_DIR = ../../..

INCLUDEPATH += 	$$BASE_DIR/code/client/module	\
                $$BASE_DIR/code/include			\
                $$BASE_DIR/code/include/third

SOURCES += $$BASE_DIR/code/client/apps/main/source/main.cpp

win32-msvc*:QMAKE_CXXFLAGS += /wd"4819"
win32-msvc*:QMAKE_CXXFLAGS += /wd"4099"

# module
MODULE_DIR = $$BASE_DIR/code/client/module
include($$MODULE_DIR/network/network.pri)
include($$MODULE_DIR/page_manager/page_manager.pri)
include($$MODULE_DIR/login/login.pri)
include($$MODULE_DIR/user/user.pri)
include($$MODULE_DIR/home/home.pri)


win32:CONFIG(release, debug|release): LIBS += 						\
    -L$$PWD/../../../lib/win32/Release/ 							\
    -L$$PWD/../../../lib/win32/Third/google_2010/protobuf/Release/ 	\
    -lapp_protocol_2010												\
    -llibprotobuf													\
    -llibprotobuf-lite

else:win32:CONFIG(debug, debug|release): LIBS += 					\
    -L$$PWD/../../../lib/win32/Debug/ 								\
    -L$$PWD/../../../lib/win32/Third/google_2010/protobuf/Debug/ 	\
    -lapp_protocol_2010_d											\
    -llibprotobuf_d													\
    -llibprotobuf-lite_d
