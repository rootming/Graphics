#-------------------------------------------------
#
# Project created by QtCreator 2016-09-21T16:15:08
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Test_1
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    glwidget.cpp \
    transform3d.cpp

HEADERS  += widget.h \
    glwidget.h \
    transform3d.h

DISTFILES += \
    vertex.vert \
    frag.frag

RESOURCES += \
    file.qrc
