#include "texture.hpp"

const string Texture::BASE_PATH = ":/textures/resources/textures/";

Texture::Texture() { }

Texture::~Texture()
{
    glDeleteTextures(1, &samplerHandle);
}

void Texture::init()
{
    initializeOpenGLFunctions();
}

void Texture::loadTexture(string filename)
{
    QImage image;

    cout << "Otwieranie pliku tekstury: " << filename << endl;
    image.load((BASE_PATH + filename).c_str());

    data = image.bits();
    width = image.width();
    height = image.height();

    glGenTextures(1, &dataHandle);
    glBindTexture(GL_TEXTURE_2D, dataHandle);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);

    glEnable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
}

void Texture::createHandles(ShaderProgram* shaderProgram)
{
    samplerHandle = glGetUniformLocation(shaderProgram->getProgramHandle(), "textureSampler");
}

int Texture::getWidth()
{
    return width;
}

int Texture::getHeight()
{
    return height;
}

void Texture::draw()
{
    glBindTexture(GL_TEXTURE_2D, dataHandle);
    glUniform1i(samplerHandle, 0);
}
