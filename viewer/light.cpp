#include "light.hpp"

void Light::init()
{
    initializeOpenGLFunctions();
    this->color = vec3(0.5f);
}

void Light::createHandles(ShaderProgram* shaderProgram)
{
    positionHandle = glGetUniformLocation(shaderProgram->getProgramHandle(), "lightPosition");
    colorHandle = glGetUniformLocation(shaderProgram->getProgramHandle(), "lightColor");
}

void Light::changeColorRed(float value)
{
    color.r = value;
}

void Light::changeColorGreen(float value)
{
    color.g = value;
}

void Light::changeColorBlue(float value)
{
    color.b = value;
}

void Light::draw()
{
    vec3 position = getPosition();
    glUniform3f(positionHandle, position.x, position.y, position.z);
    glUniform3f(colorHandle, color.r, color.g, color.b);
}
