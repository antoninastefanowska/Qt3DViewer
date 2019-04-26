#include "myglwidget.hpp"

MyGLWidget::MyGLWidget(QWidget *parent) : QOpenGLWidget(parent) { }

void MyGLWidget::initializeGL()
{
    //model = new Cylinder(72, 2.0, 8.0);
    model = new LoadedModel("monkey.obj");
    model->init();

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
    model->draw();
}

void MyGLWidget::resizeGL(int width, int height)
{
    model->changePerspectiveRatio((float)width / (float)height);
}

Model* MyGLWidget::getModel()
{
    return model;
}

void MyGLWidget::translateX(int value)
{
    int distance = value - prevTransX;
    model->translateX((float)distance);
    prevTransX = value;
    update();
}

void MyGLWidget::translateY(int value)
{
    int distance = value - prevTransY;
    model->translateY((float)distance);
    prevTransY = value;
    update();
}

void MyGLWidget::translateZ(int value)
{
    int distance = value - prevTransZ;
    model->translateZ((float)distance);
    prevTransZ = value;
    update();
}

void MyGLWidget::rotateX(int value)
{
    int angle = value - prevRotX;
    model->rotateX((float)angle);
    prevRotX = value;
    update();
}

void MyGLWidget::rotateY(int value)
{
    int angle = value - prevRotY;
    model->rotateY((float)angle);
    prevRotY = value;
    update();
}

void MyGLWidget::rotateZ(int value)
{
    int angle = value - prevRotZ;
    model->rotateZ((float)angle);
    prevRotZ = value;
    update();
}

void MyGLWidget::switchToRandomShader()
{
    model->switchShaderProgram("randomshader");
    update();
}

void MyGLWidget::switchToPositionShader()
{
    model->switchShaderProgram("positionshader");
    update();
}

void MyGLWidget::switchToNormalShader()
{
    model->switchShaderProgram("normalshader");
    update();
}

void MyGLWidget::switchToLambertShader()
{
    model->switchShaderProgram("lambertshader");
    update();
}

void MyGLWidget::switchToPhongShader()
{
    model->switchShaderProgram("phongshader");
    update();
}

void MyGLWidget::switchToTextureShader()
{
    model->switchShaderProgram("textureshader");
    update();
}

void MyGLWidget::switchToCombinedShader()
{
    model->switchShaderProgram("combinedshader");
    update();
}

void MyGLWidget::switchToMTLShader()
{
    model->switchShaderProgram("mtlshader");
    update();
}

void MyGLWidget::switchToCylinderModel()
{
    cout << "switch to cylinder" << endl;
    /*
    model->cleanUp();
    delete model;
    model = new Cylinder(72, 2.0, 8.0);
    model->init();
    update(); */
}

void MyGLWidget::switchToLoadedModel(QString value)
{
    cout << "switch to loaded model" << endl;
    cout << value.toUtf8().constData() << endl;
    /*
    model->cleanUp();
    delete model;
    model = new LoadedModel(value.toUtf8().constData());
    model->init();
    update(); */
}

void MyGLWidget::moveLightX(int value)
{
    int distance = value - prevLightX;
    model->getLight()->translateX((float)distance);
    prevLightX = value;
    update();
}

void MyGLWidget::moveLightY(int value)
{
    int distance = value - prevLightY;
    model->getLight()->translateY((float)distance);
    prevLightY = value;
    update();
}

void MyGLWidget::moveLightZ(int value)
{
    int distance = value - prevLightZ;
    model->getLight()->translateZ((float)distance);
    prevLightZ = value;
    update();
}

void MyGLWidget::changeN(int value)
{
    Cylinder* cylinder = dynamic_cast<Cylinder*>(model);
    if (cylinder)
    {
        cylinder->changeN(value);
        update();
    }
}

void MyGLWidget::changeRadius(int value)
{
    Cylinder* cylinder = dynamic_cast<Cylinder*>(model);
    if (cylinder)
    {
        cylinder->changeRadius((float)value);
        update();
    }
}

void MyGLWidget::changeHeight(int value)
{
    Cylinder* cylinder = dynamic_cast<Cylinder*>(model);
    if (cylinder)
    {
        cylinder->changeHeight((float)value);
        update();
    }
}

void MyGLWidget::recompileShader()
{
    model->reloadCurrentShaderProgram();
    update();
}

void MyGLWidget::switchTexture(QString value)
{
    model->getMaterial()->switchTexture(value.toUtf8().constData());
    update();
}

void MyGLWidget::scaleTexture(int value)
{
    Cylinder* cylinder = dynamic_cast<Cylinder*>(model);
    if (cylinder)
    {
        cylinder->changeUVScale((float)value / 10.0);
        update();
    }
}

void MyGLWidget::close()
{
    model->cleanUp();
    delete model;
}
