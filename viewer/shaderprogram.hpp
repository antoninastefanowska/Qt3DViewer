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
    string name;

    void loadShader(string filename, GLenum type);
    void linkProgram();

public:
    ShaderProgram();
    ShaderProgram(string name);
    void init();
    void createProgram();
    void reloadProgram();
    GLuint getProgramHandle();
};

#endif // SHADERPROGRAM_HPP
