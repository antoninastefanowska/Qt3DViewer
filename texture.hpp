#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <iostream>

#include <QImage>
#include <QOpenGLFunctions>

using namespace std;

class Texture : public QOpenGLFunctions
{
private:
    static const string BASE_PATH;
    unsigned char* data;
    int width, height;
    GLuint textureDataID;

public:
    void init();
    void loadTexture(string filename);
    GLuint getTextureDataID();
    int getWidth();
    int getHeight();
};

#endif // TEXTURE_HPP
