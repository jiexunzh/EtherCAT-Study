QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

soem += $$PWD/soem      # $$PWD: 当前工作目录

SOURCES += \
    $${soem}/soem_src/ethercatbase.c \
    $${soem}/soem_src/ethercatcoe.c \   # 需要打补丁！
    $${soem}/soem_src/ethercatconfig.c \
    $${soem}/soem_src/ethercatdc.c \
    $${soem}/soem_src/ethercateoe.c \
    $${soem}/soem_src/ethercatfoe.c \
    $${soem}/soem_src/ethercatmain.c \
    $${soem}/soem_src/ethercatprint.c \
    $${soem}/soem_src/ethercatsoe.c \
    $${soem}/soem_src/osal.c \
    $${soem}/soem_src/nicdrv.c \
    $${soem}/soem_src/oshw.c \
    eepromtool.c \

INCLUDEPATH += \
    $${soem}/soem_inc \
    $${soem}/wpcap/Include \
    $${soem}/wpcap/Include/pcap \
    $$PWD

LIBS += \
    $${soem}/wpcap/Lib/x64/Packet.lib   \
    $${soem}/wpcap/Lib/x64/wpcap.lib   \

LIBS += -lWinmm          # 链接 Winmm.lib（Windows 多媒体库）
LIBS += -lws2_32         # 链接 ws2_32.lib（Windows Socket 库）

# 启用 C/C++ 标准库中的一些宏定义，如 “INTMAX_MAX” 等
DEFINES +=__STDC_LIMIT_MACROS

