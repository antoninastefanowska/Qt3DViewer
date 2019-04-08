#ifndef MYGLWIDGET_HPP
#define MYGLWIDGET_HPP

#include <QOpenGLWidget>
#include <QOpenGLContext>
#include "cylinder.hpp"

class MyGLWidget : public QOpenGLWidget
{
private:
    Cylinder cylinder;

    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

public:
    explicit MyGLWidget(QWidget *parent = 0);
};

#endif // MYGLWIDGET_HPP
