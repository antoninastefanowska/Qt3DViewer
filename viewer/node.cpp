#include "node.hpp"

Node::Node(vec3 position)
{
    model = NULL;
    visibility = true;
    localModelMatrix = translate(mat4(1.0f), position);
    parent = NULL;
    update();
}

Node::Node(vec3 position, Model *model)
{
    this->model = model;
    visibility = true;
    localModelMatrix = translate(mat4(1.0f), position);
    parent = NULL;
    update();
}

void Node::init()
{
    initializeOpenGLFunctions();
}

void Node::setModel(Model* model)
{
    this->model = model;
}

Model* Node::getModel()
{
    return model;
}

void Node::setName(string name)
{
    this->name = name;
}

string Node::getName()
{
    return name;
}

void Node::setParent(Node* parent)
{
    this->parent = parent;
    update();
}

void Node::addChild(Node* child)
{
    children.push_back(child);
    child->setParent(this);
}

void Node::removeChild(Node* child)
{
    children.remove(child);
    child->setParent(NULL);
    delete child;
}

void Node::update()
{
    if (parent != NULL)
    {
        mat4 parentMatrix = parent->getGlobalModelMatrix();
        globalModelMatrix = parentMatrix * localModelMatrix;
    }
    else
        globalModelMatrix = localModelMatrix;

    for (Node* child : children)
    {
        if (child->isVisible())
            child->update();
    }
}

void Node::drawChildren()
{
    for (Node* child : children)
    {
        if (child->isVisible())
            child->draw();
    }
}

void Node::draw()
{
    glUniformMatrix4fv(globalModelMatrixHandle, 1, GL_FALSE, &globalModelMatrix[0][0]);

    drawChildren();
    if (model != NULL)
        model->draw();
}

void Node::createHandles(ShaderProgram* shaderProgram)
{
    globalModelMatrixHandle = glGetUniformLocation(shaderProgram->getProgramHandle(), "model");
    if (model != NULL)
        model->createHandles(shaderProgram);
}

void Node::show()
{
    visibility = true;
    update();
}

void Node::hide()
{
    visibility = false;
}

bool Node::isVisible()
{
    return visibility;
}

mat4 Node::getGlobalModelMatrix()
{
    return globalModelMatrix;
}

void Node::rotateX(float angle)
{
    localModelMatrix = rotate(localModelMatrix, radians(angle), vec3(1.0f, 0.0f, 0.0f));
    update();
}

void Node::rotateY(float angle)
{
    localModelMatrix = rotate(localModelMatrix, radians(angle), vec3(0.0f, 1.0f, 0.0f));
    update();
}

void Node::rotateZ(float angle)
{
    localModelMatrix = rotate(localModelMatrix, radians(angle), vec3(0.0f, 0.0f, 1.0f));
    update();
}

void Node::translateX(float distance)
{
    localModelMatrix = translate(localModelMatrix, vec3(distance, 0.0f, 0.0f));
    update();
}

void Node::translateY(float distance)
{
    localModelMatrix = translate(localModelMatrix, vec3(0.0f, distance, 0.0f));
    update();
}

void Node::translateZ(float distance)
{
    localModelMatrix = translate(localModelMatrix, vec3(0.0f, 0.0f, distance));
    update();
}

vec3 Node::getPosition()
{
    vec3 position = vec3(globalModelMatrix * vec4(vec3(0.0f), 1.0f));
    return position;
}
