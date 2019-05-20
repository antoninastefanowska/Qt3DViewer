#ifndef NODE_HPP
#define NODE_HPP

#include "model.hpp"

#include <list>

using glm::mat4;

class Node : public QOpenGLFunctions
{
private:
    GLuint globalModelMatrixHandle;
    Model* model;
    bool visibility;
    string name;

protected:
    mat4 localModelMatrix, globalModelMatrix;
    list<Node*> children;
    Node* parent;

    mat4 getGlobalModelMatrix();
    void drawChildren();  
    void setParent(Node* parent);

public:
    Node(vec3 position);
    Node(vec3 position, Model* model);

    void setModel(Model *model);
    Model* getModel();

    void setName(string name);
    string getName();

    virtual void createHandles(ShaderProgram* shaderProgram);
    void addChild(Node *child);
    void removeChild(Node *child);

    virtual void init();
    virtual void draw();
    void update();

    void show();
    void hide();
    bool isVisible();

    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);

    void translateX(float distance);
    void translateY(float distance);
    void translateZ(float distance);

    vec3 getPosition();
};

#endif //NODE_HPP
