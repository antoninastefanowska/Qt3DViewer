#ifndef NODE_HPP
#define NODE_HPP

#include "model.hpp"
#include "animation.hpp"

#include <list>

using glm::mat4;

class Node : public QOpenGLFunctions
{
private:
    Model* model;
    bool visibility;
    string name;
    list<Animation*> animations;

protected:
    mat4 localTransformationMatrix, globalTransformationMatrix;
    GLuint globalModelMatrixHandle;
    list<Node*> children;
    Node* parent;

    mat4 getGlobalTransformationMatrix();
    void drawChildren();
    int getChildIndex(Node* child);

    void playAnimation();

public:
    Node(vec3 position);
    Node(vec3 position, Model* model);
    ~Node();

    void setModel(Model *model);
    Model* getModel();

    void setName(string name);
    string getName();

    virtual void createHandles(ShaderProgram* shaderProgram);
    void addChild(Node *child);
    void removeChild(Node *child);
    Node* getChild(int index);
    list<Node*> getChildren();
    void setParent(Node* parent);
    Node* getParent();
    int getIndex();
    int childCount();

    virtual void init();
    virtual void draw();
    virtual void update();

    void show();
    virtual void hide();
    bool isVisible();
    void checkVisibility(Node* camera);

    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);

    void translateX(float distance);
    void translateY(float distance);
    void translateZ(float distance);

    void addAnimation(Animation* animation);

    virtual vec3 getPosition();
};

#endif //NODE_HPP
