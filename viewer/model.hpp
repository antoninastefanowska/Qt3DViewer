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
    GLuint modelMatrixHandle, viewMatrixHandle, projectionMatrixHandle, lightPositionHandle, colorsHandle, textureHandle;
    Light* light;

    void loadShaderProgram(string name);

protected:
    int vertexNumber;
    GLuint verticesHandle, normalsHandle, uvHandle;
    Material* material;
    map<string, ShaderProgram*> shaderPrograms;
    string currentShaderProgramName;

    virtual void createModel() = 0;
    virtual void loadDataToBuffers(vector<vec3> verticesData, vector<vec3> normalsData, vector<vec2> uvData);
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

    virtual void completeHandles() = 0;
    virtual void completeDrawing() = 0;
};

#endif // MODEL_HPP
