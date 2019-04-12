#-------------------------------------------------
#
# Project created by QtCreator 2019-04-07T22:52:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 3DViewer
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

CONFIG += c++11

TEMPLATE = app

QT += core gui \
      opengl

SOURCES += \
        cylinder.cpp \
        light.cpp \
        main.cpp \
        mainwindow.cpp \
        model.cpp \
        myglwidget.cpp \
        shaderprogram.cpp \
        triangle.cpp \
        vertex.cpp

HEADERS += \
        cylinder.hpp \
        light.hpp \
        mainwindow.hpp \
        model.hpp \
        myglwidget.hpp \
        shaderprogram.hpp \
        shadertype.hpp \
        triangle.hpp \
        vertex.hpp

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    lambertshader.frag \
    lambertshader.vert \
    normalshader.frag \
    normalshader.vert \
    positionshader.frag \
    positionshader.vert \
    randomshader.frag \
    randomshader.vert

INCLUDEPATH += $$PWD/dependencies/include
DEPENDPATH += $$PWD/dependencies/include

RESOURCES += \
    resources.qrc
