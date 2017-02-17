#-------------------------------------------------
#
# Project created by QtCreator 2016-08-12T14:03:05
#
#-------------------------------------------------

QT       += widgets network

TARGET = NComputerInfo
TEMPLATE = lib

DEFINES += NCOMPUTERINFO_LIBRARY

# 引入源码
include(./NComputerInfo_src.pri)

# 引入版本信息
RC_FILE += ./NComputerInfo_resource.rc

win32{
    CONFIG += debug_and_release
    CONFIG(release, debug|release) {
            target_path = ./build_/dist
        } else {
            target_path = ./build_/debug
        }
        DESTDIR = ../bin
        MOC_DIR = $$target_path/moc
        RCC_DIR = $$target_path/rcc
        OBJECTS_DIR = $$target_path/obj
}
CONFIG += c++11
message(Qt version: $$[QT_VERSION])
message(Qt is installed in $$[QT_INSTALL_PREFIX])
message(the NComputerInfo will create in folder: $$target_path)
