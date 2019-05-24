#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "node.hpp"

class Camera : public Node
{
private:
    mat4 projectionMatrix;
    GLuint viewMatrixHandle, projectionMatrixHandle;

public:
    using Node::Node;

    void init();
    void draw();
    void createHandles(ShaderProgram* shaderProgram);
    void changePerspectiveRatio(float ratio);

    void hide();
    void update();
    vec3 getPosition();
};

#endif // CAMERA_HPP
