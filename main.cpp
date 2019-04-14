#include "mainwindow.hpp"

#include <iostream>
#include <QApplication>

#include "myglwidget.hpp"
#include "model.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    MyGLWidget* glWidget;
    glWidget = window.findChild<MyGLWidget*>("myGLWidget");
    QObject::connect(&app, SIGNAL(aboutToQuit()), glWidget, SLOT(close()));

    window.show();

    return app.exec();
}
