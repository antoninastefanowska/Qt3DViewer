#ifndef SCENE_HPP
#define SCENE_HPP

#include <QOpenGLFunctions>

#include "model.hpp"

class Scene : QOpenGLFunctions
{
private:
    Model* model;
    mat4 view, projection;
    GLuint viewMatrixHandle, projectionMatrixHandle;
    Light* light;
    map<string, ShaderProgram*> shaderPrograms;

    void createShaderProgram(string name);
    void createAllShaderPrograms();

public:
    Scene();
    Scene(Model* model);
    ~Scene();
    void init();
    void draw();

    Light* getLight();
    Model* getModel();
    void setModel(Model* model);

    void switchShaderProgram(string name);
    void switchModel(Model* model);
    void changePerspectiveRatio(float ratio);
};

#endif // SCENE_HPP
