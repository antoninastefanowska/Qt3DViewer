#include "myglwidget.hpp"

MyGLWidget::MyGLWidget(QWidget *parent) : QOpenGLWidget(parent) { }

void MyGLWidget::initializeGL()
{
    cylinder = Cylinder(72, 2.0, 8.0);
    cylinder.init();

    prevTransX = 0;
    prevTransY = 0;
    prevTransZ = 0;

    prevRotX = 0;
    prevRotY = 0;
    prevRotZ = 0;

    prevLightX = 0;
    prevLightY = 0;
    prevLightZ = 0;
}

void MyGLWidget::paintGL()
{
    cylinder.frame();
}

void MyGLWidget::resizeGL(int width, int height)
{
    cylinder.changePerspectiveRatio((float)width / (float)height);
}

void MyGLWidget::translateX(int value)
{
    int distance = value - prevTransX;
    cylinder.translateX((float)distance);
    prevTransX = value;
    update();
}

void MyGLWidget::translateY(int value)
{
    int distance = value - prevTransY;
    cylinder.translateY((float)distance);
    prevTransY = value;
    update();
}

void MyGLWidget::translateZ(int value)
{
    int distance = value - prevTransZ;
    cylinder.translateZ((float)distance);
    prevTransZ = value;
    update();
}

void MyGLWidget::rotateX(int value)
{
    int angle = value - prevRotX;
    cylinder.rotateX((float)angle);
    prevRotX = value;
    update();
}

void MyGLWidget::rotateY(int value)
{
    int angle = value - prevRotY;
    cylinder.rotateY((float)angle);
    prevRotY = value;
    update();
}

void MyGLWidget::rotateZ(int value)
{
    int angle = value - prevRotZ;
    cylinder.rotateZ((float)angle);
    prevRotZ = value;
    update();
}

void MyGLWidget::switchToRandomShader()
{
    cylinder.switchShader(RANDOM_SHADER);
    update();
}

void MyGLWidget::switchToPositionShader()
{
    cylinder.switchShader(POSITION_SHADER);
    update();
}

void MyGLWidget::switchToNormalShader()
{
    cylinder.switchShader(NORMAL_SHADER);
    update();
}

void MyGLWidget::switchToLambertShader()
{
    cylinder.switchShader(LAMBERT_SHADER);
    update();
}

void MyGLWidget::moveLightX(int value)
{
    int distance = value - prevLightX;
    cylinder.getLight()->translateX((float)distance);
    prevLightX = value;
    update();
}

void MyGLWidget::moveLightY(int value)
{
    int distance = value - prevLightY;
    cylinder.getLight()->translateY((float)distance);
    prevLightY = value;
    update();
}

void MyGLWidget::moveLightZ(int value)
{
    int distance = value - prevLightZ;
    cylinder.getLight()->translateZ((float)distance);
    prevLightZ = value;
    update();
}

void MyGLWidget::changeN(int value)
{
    cylinder.changeN(value);
    update();
}

void MyGLWidget::changeRadius(int value)
{
    cylinder.changeRadius((float)value);
    update();
}

void MyGLWidget::changeHeight(int value)
{
    cylinder.changeHeight((float)value);
    update();
}
