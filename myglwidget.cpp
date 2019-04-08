#include "myglwidget.hpp"

MyGLWidget::MyGLWidget(QWidget *parent) : QOpenGLWidget(parent) { }

void MyGLWidget::initializeGL()
{
    cylinder = Cylinder(72, 2.0, 8.0);
    cylinder.init();
}

void MyGLWidget::paintGL()
{
    cylinder.frame();
}

void MyGLWidget::resizeGL(int width, int height)
{
    QOpenGLWidget::resizeGL(width, height);
}
