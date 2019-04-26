#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <iostream>
#include <vector>

#include <QFile>
#include <QTextStream>
#include <QString>
#include <QOpenGLFunctions>

using namespace std;

class ShaderProgram : public QOpenGLFunctions
{
private:
    static const string BASE_PATH;
    vector<GLuint> shaderHandles;
    GLuint programHandle;

public:
    void init();
    void loadShader(string filename, GLenum type);
    void linkProgram();
    GLuint getProgramHandle();
};

#endif // SHADERPROGRAM_HPP
