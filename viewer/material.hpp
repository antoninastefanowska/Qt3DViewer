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

class Material
{
private:
    Texture* texture;
    vec3 ambient, diffuse, specular, emission;

public:
    Material();
    Material(vec3 ambient, vec3 diffuse, vec3 specular, vec3 emission);
    ~Material();

    void setTexture(Texture* texture);

    vec3 getAmbient();
    void setAmbient(vec3 ambient);
    vec3 getDiffuse();
    void setDiffuse(vec3 diffuse);
    vec3 getSpecular();
    void setSpecular(vec3 specular);
    vec3 getEmission();
    void setEmission(vec3 emission);
};

#endif // MATERIAL_HPP
