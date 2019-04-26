#ifndef MODEL_HPP
#define MODEL_HPP

#include <iostream>
#include <vector>
#include <map>
#include <time.h>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <QOpenGLFunctions>

#include "shaderprogram.hpp"
#include "light.hpp"
#include "material.hpp"
#include "vertex.hpp"

using namespace std;

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;
using glm::radians;
using glm::perspective;

class Model : public QOpenGLFunctions
{
private:
    mat4 model, view, projection;
    GLuint modelMatrixHandle, viewMatrixHandle, projectionMatrixHandle, colorsHandle, indicesHandle, verticesHandle, normalsHandle, uvHandle;
    Light* light;
    map<string, ShaderProgram*> shaderPrograms;
    string currentShaderProgramName;

    void loadShaderProgram(string name);

protected:
    int indicesNumber;
    Material* material;

    virtual void createModel() = 0;
    void loadDataToBuffers(vector<Vertex> vertices);
    void generateColors();

public:
    Model();

    void init();
    void draw();
    Light* getLight();
    Material* getMaterial();

    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);

    void translateX(float distance);
    void translateY(float distance);
    void translateZ(float distance);

    void switchShaderProgram(string name);
    void reloadCurrentShaderProgram();
    void changePerspectiveRatio(float ratio);
    void cleanUp();
};

#endif // MODEL_HPP
