#include "camera.hpp"

void Camera::init()
{
    initializeOpenGLFunctions();

    viewMatrix = lookAt(
        vec3(0, 0, 15),
        vec3(0, 0, 0),
        vec3(0, 1, 0)
    );

    projectionMatrix = perspective(radians(45.0f), 1.0f, 0.1f, 100.0f);
}

void Camera::createHandles(ShaderProgram* shaderProgram)
{
    viewMatrixHandle = glGetUniformLocation(shaderProgram->getProgramHandle(), "view");
    projectionMatrixHandle = glGetUniformLocation(shaderProgram->getProgramHandle(), "projection");
}

void Camera::draw()
{
    glUniformMatrix4fv(viewMatrixHandle, 1, GL_FALSE, &viewMatrix[0][0]);
    glUniformMatrix4fv(projectionMatrixHandle, 1, GL_FALSE, &projectionMatrix[0][0]);
}

void Camera::changePerspectiveRatio(float ratio)
{
    projectionMatrix = perspective(radians(45.0f), ratio, 0.1f, 100.0f);
}
