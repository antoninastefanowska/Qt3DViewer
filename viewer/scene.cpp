#include "scene.hpp"

Scene::~Scene()
{
    for (pair<string, ShaderProgram*> shaderPair : shaderPrograms)
    {
        GLuint shaderProgramID = shaderPair.second->getProgramHandle();
        glDeleteProgram(shaderProgramID);
        delete shaderPair.second;
    }
    shaderPrograms.clear();

    for (Node* child : children)
        delete child;
}

void Scene::init()
{
    initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    light = new Light(vec3(0.0f));
    light->init();
    light->setName("Light");

    camera = new Camera(vec3(0.0f));
    camera->init();
    camera->setName("Camera");

    addChild(light);
    addChild(camera);

    createAllShaderPrograms();
    switchShaderProgram("positionshader");

    this->setName("Scene");
}

void Scene::update()
{
    globalTransformationMatrix = localTransformationMatrix;

    for (Node* child : children)
    {
        if (child != light && child != camera && child->isVisible())
            child->update();
    }
}

void Scene::createShaderProgram(string name)
{
    ShaderProgram* shaderProgram = new ShaderProgram(name);
    shaderProgram->init();
    shaderProgram->createProgram();
    shaderPrograms[name] = shaderProgram;
}

void Scene::createAllShaderPrograms()
{
    createShaderProgram("positionshader");
    createShaderProgram("randomshader");
    createShaderProgram("normalshader");
    createShaderProgram("lambertshader");
    createShaderProgram("phongshader");
    createShaderProgram("textureshader");
    createShaderProgram("combinedshader");
    createShaderProgram("mtlshader");
}

void Scene::draw()
{
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shaderProgram->getProgramHandle());

    drawChildren();
}

Light* Scene::getLight()
{
    return light;
}

Camera* Scene::getCamera()
{
    return camera;
}

void Scene::switchShaderProgram(string name)
{
    shaderProgram = shaderPrograms[name];
    camera->createHandles(shaderProgram);
    light->createHandles(shaderProgram);
    for (Node* child : children)
        child->createHandles(shaderProgram);
}

ShaderProgram* Scene::getShaderProgram()
{
    return shaderProgram;
}

void Scene::generateForest()
{
    Model *treeModel = new LoadedModel("lowpolytree.obj"), *bushModel = new LoadedModel("lowpolybush.obj");
    treeModel->init();
    bushModel->init();

    srand(time(NULL));
    for (int i = 0; i < 200; i++)
    {
        double x = (double)(rand() % 81 - 40), y = 0.0f, z = (double)(rand() % 81 - 40), angle = (double)(rand() % 360);
        int bushes = (int)rand() % 10;
        vec3 position = vec3(x, y, z);

        Node* tree = new Node(position, treeModel);
        tree->init();
        tree->createHandles(shaderProgram);
        tree->setName("Tree " + to_string(i));
        tree->rotateY(angle);
        this->addChild(tree);

        for (int j = 0; j < bushes; j++)
        {
            double xb = (double)(rand() % 11 - 5), yb = 0.0f, zb = (double)(rand() % 11 - 5), angleb = (double)(rand() % 360);
            vec3 positionb = vec3(xb, yb, zb);

            Node* bush = new Node(positionb, bushModel);
            bush->init();
            bush->createHandles(shaderProgram);
            bush->setName("Bush " + to_string(j));
            bush->rotateY(angleb);
            tree->addChild(bush);
        }
    }
}

void Scene::generateStars()
{
    Model* starModel = new LoadedModel("star.obj");
    starModel->init();

    srand(time(NULL));
    for (int i = 0; i < 100; i++)
    {
        double x = (double)(rand() % 81 - 40), y = 0.0f, z = (double)(rand() % 81 - 40);
        unsigned int duration = rand() % 951 + 50;

        Node* star = new Node(vec3(0.0f), starModel);
        star->init();
        star->createHandles(shaderProgram);
        star->setName("Star " + to_string(i));

        Animation *animation1 = new TranslateAnimation(vec3(x - 5, 0, z), vec3(x + 5, 0, z), duration), *animation2 = new TranslateAnimation(vec3(0, 20, 0), vec3(0, -20, 0), duration), *animation3 = new RotateAnimation(0.0f, -360.0f, vec3(0.0f, 0.0f, 1.0f), duration);
        star->addAnimation(animation1);
        star->addAnimation(animation2);
        star->addAnimation(animation3);

        this->addChild(star);
    }
}
