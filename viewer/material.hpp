#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "texture.hpp"
#include "shaderprogram.hpp"

#include <iostream>
#include <glm/glm.hpp>

#include <QFile>
#include <QTextStream>
#include <QString>
#include <QOpenGLFunctions>

using namespace std;
using glm::vec3;

class Material : QOpenGLFunctions
{
private:
    static const string BASE_PATH;
    Texture* texture;
    GLuint kaHandle, kdHandle, ksHandle, keHandle;
    vec3 ka, kd, ks, ke;

public:
    Material();
    ~Material();
    void init();
    void loadMTL(string filename);
    void createHandles(ShaderProgram* shaderProgram);

    void setTexture(Texture* texture);
    void switchTexture(string filename);
    void draw();
};

#endif // MATERIAL_HPP
