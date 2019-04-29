#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <QOpenGLFunctions>

#include "shaderprogram.hpp"

using namespace std;

using glm::vec3;
using glm::vec4;
using glm::mat4;
using glm::translate;

class Light : QOpenGLFunctions
{
private:
    vec3 position, color;
    GLuint positionHandle, colorHandle;

public:
    Light();
    Light(vec3 position);

    void init();
    void createHandles(ShaderProgram* shaderProgram);

    void translateX(float distance);
    void translateY(float distance);
    void translateZ(float distance);

    void changeColorRed(float value);
    void changeColorGreen(float value);
    void changeColorBlue(float value);

    void draw();
};

#endif // LIGHT_HPP
