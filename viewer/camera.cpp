#include "camera.hpp"

void Camera::init()
{
    initializeOpenGLFunctions();
    localTransformationMatrix = lookAt(
        vec3(0.0f, 0.0f, 15.0f),
        vec3(0.0f, 0.0f, 0.0f),
        vec3(0.0f, 1.0f, 0.0f)
    );
    projectionMatrix = perspective(radians(45.0f), 1.0f, 0.1f, 100.0f);
}

void Camera::update()
{
    globalTransformationMatrix = localTransformationMatrix;
    parent->checkVisibility(this);
}

void Camera::createHandles(ShaderProgram* shaderProgram)
{
    viewMatrixHandle = glGetUniformLocation(shaderProgram->getProgramHandle(), "view");
    projectionMatrixHandle = glGetUniformLocation(shaderProgram->getProgramHandle(), "projection");
}

void Camera::draw()
{
    glUniformMatrix4fv(viewMatrixHandle, 1, GL_FALSE, &globalTransformationMatrix[0][0]);
    glUniformMatrix4fv(projectionMatrixHandle, 1, GL_FALSE, &projectionMatrix[0][0]);
}

void Camera::changePerspectiveRatio(float ratio)
{
    projectionMatrix = perspective(radians(45.0f), ratio, 0.1f, 100.0f);
}

vec3 Camera::getPosition()
{
    mat4 invView = inverse(globalTransformationMatrix);
    vec3 position;
    position.x = invView[3][0];
    position.y = invView[3][1];
    position.z = invView[3][2];

    return position;
}

void Camera::hide() { }
