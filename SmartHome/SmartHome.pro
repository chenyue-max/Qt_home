#-------------------------------------------------
#
# Project created by QtCreator 2021-07-18T10:03:33
#
#-------------------------------------------------

QT       += core gui sql network charts serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SmartHome
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        widget.cpp \
    login.cpp \
    resi.cpp \
    weather.cpp \
    weatherwidget.cpp \
    menu.cpp \
    data_visualization.cpp \
    showdata.cpp \
    showdatas.cpp

HEADERS += \
        widget.h \
    login.h \
    resi.h \
    weather.h \
    weatherwidget.h \
    menu.h \
    data_visualization.h \
    showdata.h \
    showdatas.h

FORMS += \
        widget.ui \
    login.ui \
    resi.ui \
    weatherwidget.ui \
    menu.ui \
    data_visualization.ui \
    showdata.ui \
    showdatas.ui

RESOURCES += \
    img.qrc \
    qss.qrc \
    image.qrc
