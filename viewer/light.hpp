#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <QOpenGLFunctions>

#include "node.hpp"
#include "shaderprogram.hpp"

using namespace std;

using glm::vec3;
using glm::vec4;
using glm::mat4;
using glm::translate;

class Light : public Node
{
private:
    vec3 color;
    GLuint positionHandle, colorHandle;

public:
    using Node::Node;
    void init();
    void createHandles(ShaderProgram* shaderProgram);

    void changeColorRed(float value);
    void changeColorGreen(float value);
    void changeColorBlue(float value);

    void hide();
    void draw();
};

#endif // LIGHT_HPP
