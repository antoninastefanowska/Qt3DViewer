#include "myglwidget.hpp"

MyGLWidget::MyGLWidget(QWidget *parent) : QOpenGLWidget(parent) { }

void MyGLWidget::initializeGL()
{
    scene = new Scene(vec3(0.0f));
    scene->init();

    Model* cubeModel = new Cube();
    cubeModel->init();

    Node* cube = new Node(vec3(0.0f), cubeModel);
    cube->init();
    cube->createHandles(scene->getShaderProgram());
    cube->setName("Cube");
    currentObject = cube;

    scene->addChild(cube);
    scene->update();

    prevTransX = 0;
    prevTransY = 0;
    prevTransZ = 0;

    prevRotX = 0;
    prevRotY = 0;
    prevRotZ = 0;

    prevLightX = 0;
    prevLightY = 0;
    prevLightZ = 0;

    currentLoadedModelName = "monkey.obj";
}

void MyGLWidget::paintGL()
{
    scene->draw();
}

void MyGLWidget::resizeGL(int width, int height)
{
    scene->getCamera()->changePerspectiveRatio((float)width / (float)height);
}

Scene* MyGLWidget::getScene()
{
    return scene;
}

void MyGLWidget::populateObjectTree(Node* node, QStandardItem* parent)
{
    int i = 0;
    for (Node* child : node->getChildren())
    {
        QStandardItem *item = new QStandardItem;
        item->setText(QString(child->getName().c_str()));
        parent->setChild(i, 0, item);
        i++;
        populateObjectTree(child, item);
    }
}

Node* MyGLWidget::getCurrentObject()
{
    return currentObject;
}

void MyGLWidget::setTreeControl(QStandardItem *treeControl)
{
    this->treeControl = treeControl;
}

void MyGLWidget::translateX(int value)
{
    int distance = value - prevTransX;
    currentObject->translateX((float)distance);
    prevTransX = value;
    update();
}

void MyGLWidget::translateY(int value)
{
    int distance = value - prevTransY;
    currentObject->translateY((float)distance);
    prevTransY = value;
    update();
}

void MyGLWidget::translateZ(int value)
{
    int distance = value - prevTransZ;
    currentObject->translateZ((float)distance);
    prevTransZ = value;
    update();
}

void MyGLWidget::rotateX(int value)
{
    int angle = value - prevRotX;
    currentObject->rotateX((float)angle);
    prevRotX = value;
    update();
}

void MyGLWidget::rotateY(int value)
{
    int angle = value - prevRotY;
    currentObject->rotateY((float)angle);
    prevRotY = value;
    update();
}

void MyGLWidget::rotateZ(int value)
{
    int angle = value - prevRotZ;
    currentObject->rotateZ((float)angle);
    prevRotZ = value;
    update();
}

void MyGLWidget::switchToRandomShader(bool checked)
{
    if (checked)
    {
        scene->switchShaderProgram("randomshader");
        update();
    }
}

void MyGLWidget::switchToPositionShader(bool checked)
{
    if (checked)
    {
        scene->switchShaderProgram("positionshader");
        update();
    }
}

void MyGLWidget::switchToNormalShader(bool checked)
{
    if (checked)
    {
        scene->switchShaderProgram("normalshader");
        update();
    }
}

void MyGLWidget::switchToLambertShader(bool checked)
{
    if (checked)
    {
        scene->switchShaderProgram("lambertshader");
        update();
    }
}

void MyGLWidget::switchToPhongShader(bool checked)
{
    if (checked)
    {
        scene->switchShaderProgram("phongshader");
        update();
    }
}

void MyGLWidget::switchToTextureShader(bool checked)
{
    if (checked)
    {
        scene->switchShaderProgram("textureshader");
        update();
    }
}

void MyGLWidget::switchToCombinedShader(bool checked)
{
    if (checked)
    {
        scene->switchShaderProgram("combinedshader");
        update();
    }
}

void MyGLWidget::switchToMTLShader(bool checked)
{
    if (checked)
    {
        scene->switchShaderProgram("mtlshader");
        update();
    }
}

void MyGLWidget::switchToCubeModel(bool checked)
{
    if (checked)
    {
        Model* model = new Cube();
        model->init();
        Node* modelNode = new Node(vec3(0.0f), model);
        modelNode->init();
        modelNode->createHandles(scene->getShaderProgram());
        modelNode->setName("Cube");

        scene->removeChild(currentObject);
        currentObject = modelNode;
        scene->addChild(modelNode);
        scene->update();
        update();

        populateObjectTree(scene, treeControl);
    }
}

void MyGLWidget::switchToCylinderModel(bool checked)
{
    if (checked)
    {
        Model* model = new Cylinder(72, 2.0, 8.0);
        model->init();
        Node* modelNode = new Node(vec3(0.0f), model);
        modelNode->init();
        modelNode->createHandles(scene->getShaderProgram());
        modelNode->setName("Cylinder");

        scene->removeChild(currentObject);
        currentObject = modelNode;
        scene->addChild(modelNode);
        scene->update();
        update();

        populateObjectTree(scene, treeControl);
    }
}

void MyGLWidget::switchToLoadedModel(bool checked)
{
    if (checked)
    {
        Model* model = new LoadedModel(currentLoadedModelName);
        model->init();
        Node* modelNode = new Node(vec3(0.0f), model);
        modelNode->init();

        modelNode->createHandles(scene->getShaderProgram());
        modelNode->setName(currentLoadedModelName);
        scene->removeChild(currentObject);
        currentObject = modelNode;
        scene->addChild(modelNode);
        scene->update();
        update();

        populateObjectTree(scene, treeControl);
    }
}

void MyGLWidget::changeLoadedModel(QString value)
{
    currentLoadedModelName = value.toUtf8().constData();
    switchToLoadedModel(true);
}

void MyGLWidget::moveLightX(int value)
{
    int distance = value - prevLightX;
    scene->getLight()->translateX((float)distance);
    prevLightX = value;
    update();
}

void MyGLWidget::moveLightY(int value)
{
    int distance = value - prevLightY;
    scene->getLight()->translateY((float)distance);
    prevLightY = value;
    update();
}

void MyGLWidget::moveLightZ(int value)
{
    int distance = value - prevLightZ;
    scene->getLight()->translateZ((float)distance);
    prevLightZ = value;
    update();
}

void MyGLWidget::changeLightColorRed(int value)
{
    float red = (float)value / 10.0;
    scene->getLight()->changeColorRed(red);
    update();
}

void MyGLWidget::changeLightColorGreen(int value)
{
    float green = (float)value / 10.0;
    scene->getLight()->changeColorGreen(green);
    update();
}

void MyGLWidget::changeLightColorBlue(int value)
{
    float blue = (float)value / 10.0;
    scene->getLight()->changeColorBlue(blue);
    update();
}

void MyGLWidget::changeN(int value)
{
    Cylinder* cylinder = dynamic_cast<Cylinder*>(currentObject->getChild(2)->getModel());
    if (cylinder)
    {
        cylinder->changeN(value);
        update();
    }
}

void MyGLWidget::changeRadius(int value)
{
    Cylinder* cylinder = dynamic_cast<Cylinder*>(currentObject->getChild(2)->getModel());
    if (cylinder)
    {
        cylinder->changeRadius((float)value);
        update();
    }
}

void MyGLWidget::changeHeight(int value)
{
    Cylinder* cylinder = dynamic_cast<Cylinder*>(currentObject->getChild(2)->getModel());
    if (cylinder)
    {
        cylinder->changeHeight((float)value);
        update();
    }
}

void MyGLWidget::recompileShader()
{
    scene->getShaderProgram()->reloadProgram();
    update();
}

void MyGLWidget::switchTexture(QString value)
{
    scene->getModel()->switchTexture(value.toUtf8().constData());
    update();
}

void MyGLWidget::scaleTexture(int value)
{
    Cylinder* cylinder = dynamic_cast<Cylinder*>(currentObject->getChild(2)->getModel());
    if (cylinder)
    {
        cylinder->changeUVScale((float)value / 10.0);
        update();
    }
}

void MyGLWidget::close()
{
    delete scene;
}

void MyGLWidget::changeCurrentModel(QModelIndex index)
{
    Node* node = scene;

    if (index.parent().isValid())
    {
        deque<int> rows;
        rows.push_front(index.row());
        while (index.parent().parent().isValid())
        {
            index = index.parent();
            rows.push_front(index.row());
        }

        for (int row : rows)
            node = node->getChild(row);
    }
    currentObject = node;
}
