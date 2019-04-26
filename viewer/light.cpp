#include "light.hpp"

Light::Light() { }

Light::Light(vec3 position)
{
    this->position = position;
}

void Light::init()
{
    initializeOpenGLFunctions();
}

void Light::translateX(float distance)
{
    mat4 tr = translate(mat4(1.0f), vec3(distance, 0.0f, 0.0f));
    position = vec3(tr * vec4(position, 1.0f));
}

void Light::translateY(float distance)
{
    mat4 tr = translate(mat4(1.0f), vec3(0.0f, distance, 0.0f));
    position = vec3(tr * vec4(position, 1.0f));
}

void Light::translateZ(float distance)
{
    mat4 tr = translate(mat4(1.0f), vec3(0.0f, 0.0f, distance));
    position = vec3(tr * vec4(position, 1.0f));
}

void Light::createHandles(ShaderProgram* shaderProgram)
{
    positionHandle = glGetUniformLocation(shaderProgram->getProgramHandle(), "lightPosition");
}

void Light::draw()
{
    glUniform3f(positionHandle, position.x, position.y, position.z);
}
