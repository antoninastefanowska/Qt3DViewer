#ifndef MYGLWIDGET_HPP
#define MYGLWIDGET_HPP

#include <iostream>
#include <deque>

#include <QtOpenGL>
#include <QOpenGLWidget>
#include <QOpenGLContext>
#include <QStandardItemModel>
#include <QPoint>

#include "viewer/cube.hpp"
#include "viewer/cylinder.hpp"
#include "viewer/loadedmodel.hpp"
#include "viewer/scene.hpp"

using namespace std;

class MyGLWidget : public QOpenGLWidget
{
    Q_OBJECT

private:
    Scene* scene;
    Node* currentObject;
    int prevTransX, prevTransY, prevTransZ, prevRotX, prevRotY, prevRotZ, prevLightX, prevLightY, prevLightZ;
    string currentLoadedModelName;
    QStandardItem* treeControl;

    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

public:
    explicit MyGLWidget(QWidget *parent = 0);
    Scene* getScene();
    Node* getCurrentObject();

    void setTreeControl(QStandardItem* treeControl);
    void populateObjectTree(Node* node, QStandardItem* parent);

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

    void switchToCubeModel(bool checked);
    void switchToCylinderModel(bool checked);
    void switchToLoadedModel(bool checked);
    void changeLoadedModel(QString value);

    void moveLightX(int value);
    void moveLightY(int value);
    void moveLightZ(int value);

    void changeLightColorRed(int value);
    void changeLightColorGreen(int value);
    void changeLightColorBlue(int value);

    void changeN(int value);
    void changeRadius(int value);
    void changeHeight(int value);

    void switchTexture(QString value);
    void scaleTexture(int value);

    void close();

    void changeCurrentModel(QModelIndex index);
};

#endif // MYGLWIDGET_HPP
