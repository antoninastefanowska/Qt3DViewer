#include "node.hpp"

Node::Node(vec3 position)
{
    model = NULL;
    visibility = true;
    localTransformationMatrix = translate(mat4(1.0f), position);
    parent = NULL;
    update();
}

Node::Node(vec3 position, Model *model)
{
    this->model = model;
    visibility = true;
    localTransformationMatrix = translate(mat4(1.0f), position);
    parent = NULL;
    update();
}

Node::~Node()
{
    delete model;
    for (Animation* animation : animations)
        delete animation;
    for (Node* child : children)
        delete child;
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
    child->update();
}

void Node::removeChild(Node* child)
{
    children.remove(child);
    child->setParent(NULL);
    delete child;
}

Node* Node::getChild(int index)
{
    if (children.size() > index)
    {
        list<Node*>::iterator it = children.begin();
        advance(it, index);
        return *it;
    }
    return NULL;
}

list<Node*> Node::getChildren()
{
    return children;
}

Node* Node::getParent()
{
    return parent;
}

int Node::getIndex()
{
    return parent->getChildIndex(this);
}

int Node::getChildIndex(Node* child)
{
    int index = 0;
    for (Node* foundChild : children)
    {
        if (foundChild == child)
            return index;
        index++;
    }
    return -1;
}

int Node::childCount()
{
    return children.size();
}

void Node::update()
{
    if (parent != NULL)
    {
        mat4 parentMatrix = parent->getGlobalTransformationMatrix();
        globalTransformationMatrix = parentMatrix * localTransformationMatrix;
    }
    else
        globalTransformationMatrix = localTransformationMatrix;

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
    if (!animations.empty())
        playAnimation();

    glUniformMatrix4fv(globalModelMatrixHandle, 1, GL_FALSE, &globalTransformationMatrix[0][0]);
    if (model != NULL)
        model->draw();

    drawChildren();
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
}

void Node::hide()
{
    visibility = false;
}

bool Node::isVisible()
{
    return visibility;
}

void Node::checkVisibility(Node* camera)
{
    for (Node* child : children)
    {
        if (distance(child->getPosition(), camera->getPosition()) > 100.0f)
            child->hide();
        else
        {
            child->show();
            child->checkVisibility(camera);
        }
    }
}

mat4 Node::getGlobalTransformationMatrix()
{
    return globalTransformationMatrix;
}

void Node::rotateX(float angle)
{
    localTransformationMatrix = rotate(localTransformationMatrix, radians(angle), vec3(1.0f, 0.0f, 0.0f));
    update();
}

void Node::rotateY(float angle)
{
    localTransformationMatrix = rotate(localTransformationMatrix, radians(angle), vec3(0.0f, 1.0f, 0.0f));
    update();
}

void Node::rotateZ(float angle)
{
    localTransformationMatrix = rotate(localTransformationMatrix, radians(angle), vec3(0.0f, 0.0f, 1.0f));
    update();
}

void Node::translateX(float distance)
{
    localTransformationMatrix = translate(localTransformationMatrix, vec3(distance, 0.0f, 0.0f));
    update();
}

void Node::translateY(float distance)
{
    localTransformationMatrix = translate(localTransformationMatrix, vec3(0.0f, distance, 0.0f));
    update();
}

void Node::translateZ(float distance)
{
    localTransformationMatrix = translate(localTransformationMatrix, vec3(0.0f, 0.0f, distance));
    update();
}

vec3 Node::getPosition()
{
    vec3 position;

    position.x = globalTransformationMatrix[3][0];
    position.y = globalTransformationMatrix[3][1];
    position.z = globalTransformationMatrix[3][2];

    return position;
}

void Node::addAnimation(Animation* animation)
{
    animations.push_back(animation);
}

void Node::playAnimation()
{
    mat4 transformationMatrix = mat4(1.0f);

    for (Animation* animation : animations)
    {
        if (!animation->isFinished())
        {
            transformationMatrix = transformationMatrix * animation->calculateFrameMatrix();
            localTransformationMatrix = transformationMatrix;
        }
        else
            animation->restart();
    }
    update();
}
