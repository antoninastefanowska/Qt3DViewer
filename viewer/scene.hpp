#ifndef SCENE_HPP
#define SCENE_HPP

#include <QOpenGLFunctions>

#include "camera.hpp"
#include "light.hpp"
#include "cylinder.hpp"
#include "cube.hpp"
#include "loadedmodel.hpp"
#include "translateanimation.hpp"
#include "rotateanimation.hpp"

class Scene : public Node
{
private:
    Light* light;
    Camera* camera;
    map<string, ShaderProgram*> shaderPrograms;
    ShaderProgram* shaderProgram;

    void createShaderProgram(string name);
    void createAllShaderPrograms();
    void generateForest();
    void generateStars();

public:
    using Node::Node;
    ~Scene();
    void init();
    void draw();
    void update();

    Light* getLight();
    Camera* getCamera();

    void switchShaderProgram(string name);
    ShaderProgram* getShaderProgram();
};

#endif // SCENE_HPP
