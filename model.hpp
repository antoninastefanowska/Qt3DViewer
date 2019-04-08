#ifndef MODEL_HPP
#define MODEL_HPP

#include <iostream>
#include <vector>
#include <time.h>
#include <filesystem>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <QOpenGLFunctions>

#include "triangle.hpp"
#include "shaderprogram.hpp"

using namespace std;

using glm::vec3;
using glm::vec4;
using glm::mat4;
using glm::radians;
using glm::perspective;

class Model : public QOpenGLFunctions
{
private:
    mat4 model, view, projection;
    vec3 lightPosition;
    GLuint verticesID, normalsID, modelID, viewID, projectionID, lightPositionID, vertexArrayID, colorsID;
    ShaderProgram shaderProgram;

protected:
    int vertexNumber;

public:
    Model();

    void init();

    virtual void generateVertices() = 0;
    void generateColors();
    void loadVerticesData(vector<vec3> verticesData, vector<vec3> normalsData);

    void frame();

    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);

    void translateX(float distance);
    void translateY(float distance);
    void translateZ(float distance);

    void moveLightX(float distance);
    void moveLightY(float distance);
    void moveLightZ(float distance);
};

#endif // MODEL_HPP
