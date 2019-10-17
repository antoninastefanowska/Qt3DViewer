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
#include "material.hpp"
#include "vertex.hpp"
#include "triangle.hpp"

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
    GLuint randomColorsHandle, indicesHandle, verticesHandle, normalsHandle, uvHandle, ambientHandle, diffuseHandle, specularHandle, emissionHandle;

protected:
    int vertexNumber, indicesNumber;
    Texture* texture;

    virtual void createModel() = 0;
    void loadDataToBuffers(vector<Vertex> &vertices);
    void calculateNormals(vector<Vertex> &vertices, vector<Triangle> &triangles);
    void generateRandomColors();

public:
    Model();
    virtual ~Model();

    void init();
    void draw();
    void createHandles(ShaderProgram* shaderProgram);

    void switchTexture(string filename);
};

#endif //MODEL_HPP
