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

#include "shaderprogram.hpp"
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
    GLuint modelMatrixHandle, viewMatrixHandle, projectionMatrixHandle, lightPositionHandle, colorsHandle, textureHandle;
    Light* light;
    map<string, ShaderProgram*> shaderPrograms;
    string currentShaderProgramName;

    void loadShaderProgram(string name);

protected:
    int vertexNumber;
    GLuint verticesHandle, normalsHandle, uvHandle;
    Texture* texture;

    virtual void createModel() = 0;
    void generateColors();

public:
    Model();

    void init();
    void frame();
    Light* getLight();
    Texture* getTexture();

    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);

    void translateX(float distance);
    void translateY(float distance);
    void translateZ(float distance);

    void switchShaderProgram(string name);
    void reloadCurrentShaderProgram();
    void switchTexture(string filename);
    void changePerspectiveRatio(float ratio);
    void scaleTexture(float factor);
    void cleanUp();
};

#endif // MODEL_HPP
