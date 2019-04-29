#ifndef MYGLWIDGET_HPP
#define MYGLWIDGET_HPP

#include <iostream>

#include <QtOpenGL>
#include <QOpenGLWidget>
#include <QOpenGLContext>
#include <QPoint>

#include "viewer/cylinder.hpp"
#include "viewer/loadedmodel.hpp"
#include "viewer/scene.hpp"

using namespace std;

class MyGLWidget : public QOpenGLWidget
{
    Q_OBJECT

private:
    Scene* scene;
    int prevTransX, prevTransY, prevTransZ, prevRotX, prevRotY, prevRotZ, prevLightX, prevLightY, prevLightZ;
    string currentLoadedModelName;

    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

public:
    explicit MyGLWidget(QWidget *parent = 0);

public slots:
    void translateX(int value);
    void translateY(int value);
    void translateZ(int value);

    void rotateX(int value);
    void rotateY(int value);
    void rotateZ(int value);

    void switchToRandomShader(bool checked);
    void switchToPositionShader(bool checked);
    void switchToNormalShader(bool checked);
    void switchToLambertShader(bool checked);
    void switchToPhongShader(bool checked);
    void switchToTextureShader(bool checked);
    void switchToCombinedShader(bool checked);
    void switchToMTLShader(bool checked);
    void recompileShader();

    void switchToCylinderModel(bool checked);
    void switchToLoadedModel(bool checked);
    void changeLoadedModel(QString value);

    void moveLightX(int value);
    void moveLightY(int value);
    void moveLightZ(int value);

    void changeN(int value);
    void changeRadius(int value);
    void changeHeight(int value);

    void switchTexture(QString value);
    void scaleTexture(int value);

    void close();
};

#endif // MYGLWIDGET_HPP
