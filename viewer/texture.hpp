#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <iostream>

#include <QImage>
#include <QOpenGLFunctions>

#include "shaderprogram.hpp"

using namespace std;

class Texture : public QOpenGLFunctions
{
private:
    static const string BASE_PATH;
    unsigned char* data;
    int width, height;
    GLuint dataHandle, samplerHandle;

public:
    Texture();
    ~Texture();
    void init();

    void loadTexture(string filename);
    void createHandles(ShaderProgram* shaderProgram);
    int getWidth();
    int getHeight();
    void draw();
};

#endif // TEXTURE_HPP
