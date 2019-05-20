#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "node.hpp"

class Camera : public Node
{
private:
    mat4 viewMatrix, projectionMatrix;
    GLuint viewMatrixHandle, projectionMatrixHandle;

public:
    using Node::Node;

    void init();
    void draw();
    void createHandles(ShaderProgram* shaderProgram);
    void changePerspectiveRatio(float ratio);
};

#endif // CAMERA_HPP
