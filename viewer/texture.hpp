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
    GLuint textureDataHandle;

public:
    void init();
    void loadTexture(string filename);
    GLuint getTextureDataHandle();
    int getWidth();
    int getHeight();
};

#endif // TEXTURE_HPP
