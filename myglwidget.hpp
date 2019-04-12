#ifndef MYGLWIDGET_HPP
#define MYGLWIDGET_HPP

#include <QtOpenGL>
#include <QOpenGLWidget>
#include <QOpenGLContext>
#include <QPoint>

#include "cylinder.hpp"
#include "shadertype.hpp"

class MyGLWidget : public QOpenGLWidget
{
    Q_OBJECT

private:
    Cylinder cylinder;
    int prevTransX, prevTransY, prevTransZ, prevRotX, prevRotY, prevRotZ, prevLightX, prevLightY, prevLightZ;
    QPoint prevPos;

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

    void switchToRandomShader();
    void switchToPositionShader();
    void switchToNormalShader();
    void switchToLambertShader();

    void moveLightX(int value);
    void moveLightY(int value);
    void moveLightZ(int value);

    void changeN(int value);
    void changeRadius(int value);
    void changeHeight(int value);
};

#endif // MYGLWIDGET_HPP
