#-------------------------------------------------
#
# Project created by QtCreator 2019-04-07T22:52:08
#
#-------------------------------------------------

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
    main.cpp \
    mainwindow.cpp \
    myglwidget.cpp \
    viewer/animation.cpp \
    viewer/camera.cpp \
    viewer/cube.cpp \
    viewer/cylinder.cpp \
    viewer/light.cpp \
    viewer/loadedmodel.cpp \
    viewer/material.cpp \
    viewer/model.cpp \
    viewer/node.cpp \
    viewer/rotateanimation.cpp \
    viewer/scene.cpp \
    viewer/shaderprogram.cpp \
    viewer/texture.cpp \
    viewer/translateanimation.cpp \
    viewer/triangle.cpp \
    viewer/vertex.cpp

HEADERS += \
    mainwindow.hpp \
    myglwidget.hpp \
    viewer/animation.hpp \
    viewer/camera.hpp \
    viewer/cube.hpp \
    viewer/cylinder.hpp \
    viewer/light.hpp \
    viewer/loadedmodel.hpp \
    viewer/material.hpp \
    viewer/model.hpp \
    viewer/node.hpp \
    viewer/rotateanimation.hpp \
    viewer/scene.hpp \
    viewer/shaderprogram.hpp \
    viewer/texture.hpp \
    viewer/translateanimation.hpp \
    viewer/triangle.hpp \
    viewer/vertex.hpp

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    resources/models/bush.mtl \
    resources/models/bush.obj \
    resources/models/lowpolybush.mtl \
    resources/models/lowpolybush.obj \
    resources/models/lowpolytree.mtl \
    resources/models/lowpolytree.obj \
    resources/models/monkey.mtl \
    resources/models/monkey.obj \
    resources/models/star.mtl \
    resources/models/star.obj \
    resources/models/starwitch.mtl \
    resources/models/starwitch.obj \
    resources/models/tree.mtl \
    resources/models/tree.obj \
    resources/shaders/combinedshader.frag \
    resources/shaders/combinedshader.vert \
    resources/shaders/lambertshader.frag \
    resources/shaders/lambertshader.vert \
    resources/shaders/mtlshader.frag \
    resources/shaders/mtlshader.vert \
    resources/shaders/normalshader.frag \
    resources/shaders/normalshader.vert \
    resources/shaders/phongshader.frag \
    resources/shaders/phongshader.vert \
    resources/shaders/positionshader.frag \
    resources/shaders/positionshader.vert \
    resources/shaders/randomshader.frag \
    resources/shaders/randomshader.vert \
    resources/shaders/textureshader.frag \
    resources/shaders/textureshader.vert \
    resources/textures/checkered.png \
    resources/textures/squares.png \
    resources/textures/stars.png \
    resources.qrc

INCLUDEPATH += $$PWD/dependencies/include
DEPENDPATH += $$PWD/dependencies/include

LIBS += -lOpenGL32

#RESOURCES += \
    #resources.qrc
