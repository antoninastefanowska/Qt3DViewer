#include "myglwidget.hpp"

MyGLWidget::MyGLWidget(QWidget *parent) : QOpenGLWidget(parent) { }

void MyGLWidget::initializeGL()
{
    model = Cylinder(72, 2.0, 8.0);
    model.init();

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
    model.frame();
}

void MyGLWidget::resizeGL(int width, int height)
{
    model.changePerspectiveRatio((float)width / (float)height);
}

Cylinder MyGLWidget::getModel()
{
    return model;
}

void MyGLWidget::translateX(int value)
{
    int distance = value - prevTransX;
    model.translateX((float)distance);
    prevTransX = value;
    update();
}

void MyGLWidget::translateY(int value)
{
    int distance = value - prevTransY;
    model.translateY((float)distance);
    prevTransY = value;
    update();
}

void MyGLWidget::translateZ(int value)
{
    int distance = value - prevTransZ;
    model.translateZ((float)distance);
    prevTransZ = value;
    update();
}

void MyGLWidget::rotateX(int value)
{
    int angle = value - prevRotX;
    model.rotateX((float)angle);
    prevRotX = value;
    update();
}

void MyGLWidget::rotateY(int value)
{
    int angle = value - prevRotY;
    model.rotateY((float)angle);
    prevRotY = value;
    update();
}

void MyGLWidget::rotateZ(int value)
{
    int angle = value - prevRotZ;
    model.rotateZ((float)angle);
    prevRotZ = value;
    update();
}

void MyGLWidget::switchToRandomShader()
{
    model.switchShader(RANDOM_SHADER);
    update();
}

void MyGLWidget::switchToPositionShader()
{
    model.switchShader(POSITION_SHADER);
    update();
}

void MyGLWidget::switchToNormalShader()
{
    model.switchShader(NORMAL_SHADER);
    update();
}

void MyGLWidget::switchToLambertShader()
{
    model.switchShader(LAMBERT_SHADER);
    update();
}

void MyGLWidget::switchToPhongShader()
{
    model.switchShader(PHONG_SHADER);
    update();
}

void MyGLWidget::switchToTextureShader()
{
    model.switchShader(TEXTURE_SHADER);
    update();
}

void MyGLWidget::switchToCombinedShader()
{
    model.switchShader(COMBINED_SHADER);
    update();
}

void MyGLWidget::moveLightX(int value)
{
    int distance = value - prevLightX;
    model.getLight()->translateX((float)distance);
    prevLightX = value;
    update();
}

void MyGLWidget::moveLightY(int value)
{
    int distance = value - prevLightY;
    model.getLight()->translateY((float)distance);
    prevLightY = value;
    update();
}

void MyGLWidget::moveLightZ(int value)
{
    int distance = value - prevLightZ;
    model.getLight()->translateZ((float)distance);
    prevLightZ = value;
    update();
}

void MyGLWidget::changeN(int value)
{
    model.changeN(value);
    update();
}

void MyGLWidget::changeRadius(int value)
{
    model.changeRadius((float)value);
    update();
}

void MyGLWidget::changeHeight(int value)
{
    model.changeHeight((float)value);
    update();
}

void MyGLWidget::recompileShaders()
{
    model.reloadShaders();
    update();
}

void MyGLWidget::close()
{
    model.cleanUp();
}
