#ifndef MODEL_HPP
#define MODEL_HPP

#include <iostream>
#include <vector>
#include <map>
#include <time.h>
#include <filesystem>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <QOpenGLFunctions>

#include "triangle.hpp"
#include "shaderprogram.hpp"
#include "shadertype.hpp"
#include "light.hpp"
#include "texture.hpp"

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
    GLuint verticesID, normalsID, modelID, viewID, projectionID, lightPositionID, vertexArrayID, colorsID, uvID, textureID;
    Light* light;
    ShaderProgram* currentShaderProgram;
    map<ShaderType, ShaderProgram*> shaderPrograms;

    void loadShaders();

protected:
    int vertexNumber;
    Texture* texture;

    virtual void generateVertices();
    void generateColors();
    void loadVerticesData(vector<vec3> verticesData, vector<vec3> normalsData, vector<vec2> uvData);

public:
    Model();

    void init();
    void frame();
    Light* getLight();

    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);

    void translateX(float distance);
    void translateY(float distance);
    void translateZ(float distance);

    void switchShader(ShaderType shaderType);
    void changePerspectiveRatio(float ratio);
    void reloadShaders();
    void cleanUp();
};

#endif // MODEL_HPP
