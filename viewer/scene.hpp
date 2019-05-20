#ifndef SCENE_HPP
#define SCENE_HPP

#include <QOpenGLFunctions>

#include "camera.hpp"
#include "light.hpp"
#include "cylinder.hpp"
#include "loadedmodel.hpp"

class Scene : public Node
{
private:
    Light* light;
    Camera* camera;
    map<string, ShaderProgram*> shaderPrograms;
    ShaderProgram* shaderProgram;

    void createShaderProgram(string name);
    void createAllShaderPrograms();

public:
    using Node::Node;
    ~Scene();
    void init();
    void draw();

    Light* getLight();
    Camera* getCamera();

    void switchShaderProgram(string name);
    ShaderProgram* getShaderProgram();
};

#endif // SCENE_HPP
