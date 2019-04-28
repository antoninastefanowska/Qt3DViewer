#include "scene.hpp"

Scene::Scene() { }

Scene::Scene(Model* model)
{
    this->model = model;
}

Scene::~Scene()
{
    for (pair<string, ShaderProgram*> shaderPair : shaderPrograms)
    {
        GLuint shaderProgramID = shaderPair.second->getProgramHandle();
        glDeleteProgram(shaderProgramID);
        delete shaderPair.second;
    }
    shaderPrograms.clear();

    delete model;
    delete light;
}

void Scene::init()
{
    initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    light = new Light(vec3(0.0f, 0.0f, 0.0f));
    light->init();

    view = lookAt(
        vec3(0, 0, 15),
        vec3(0, 0, 0),
        vec3(0, 1, 0)
    );
    projection = perspective(radians(45.0f), 1.0f, 0.1f, 100.0f);

    createAllShaderPrograms();

    model->init();
    switchShaderProgram("positionshader");
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

    glUseProgram(model->getShaderProgram()->getProgramHandle());

    glUniformMatrix4fv(viewMatrixHandle, 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(projectionMatrixHandle, 1, GL_FALSE, &projection[0][0]);

    light->draw();
    model->draw();
}

Light* Scene::getLight()
{
    return light;
}

Model* Scene::getModel()
{
    return model;
}

void Scene::setModel(Model* model)
{
    this->model = model;
}

void Scene::switchShaderProgram(string name)
{
    ShaderProgram* shaderProgram = shaderPrograms[name];
    viewMatrixHandle = glGetUniformLocation(shaderProgram->getProgramHandle(), "view");
    projectionMatrixHandle = glGetUniformLocation(shaderProgram->getProgramHandle(), "projection");
    model->setShaderProgram(shaderProgram);
    light->createHandles(shaderProgram);
}

void Scene::switchModel(Model* model)
{
    ShaderProgram* shaderProgram = this->model->getShaderProgram();
    mat4 modelMatrix = this->model->getModelMatrix();

    delete this->model;
    this->model = model;
    this->model->init();
    this->model->setShaderProgram(shaderProgram);
    this->model->setModelMatrix(modelMatrix);
}

void Scene::changePerspectiveRatio(float ratio)
{
    projection = perspective(radians(45.0f), ratio, 0.1f, 100.0f);
}
