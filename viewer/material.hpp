#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "texture.hpp"

#include <iostream>
#include <glm/glm.hpp>

#include <QFile>
#include <QTextStream>
#include <QString>

using namespace std;
using glm::vec3;

class Material
{
private:
    static const string BASE_PATH;
    Texture* texture;

public:
    vec3 ka, kd, ks, ke;

    Material();
    ~Material();
    void loadMTL(string filename);
    Texture* getTexture();
    void setTexture(Texture* texture);
    void switchTexture(string filename);
};

#endif // MATERIAL_HPP
