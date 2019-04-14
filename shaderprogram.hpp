#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <iostream>
#include <vector>

#include <QFile>
#include <QTextStream>
#include <QString>
#include <QOpenGLFunctions>

#include "shadertype.hpp"

using namespace std;

class ShaderProgram : public QOpenGLFunctions
{
private:
    static const string BASE_PATH;
    vector<GLuint> shaderIDs;
    GLuint programID;
    ShaderType type;

public:
    void init();
    void loadShader(string filename, GLenum type);
    void linkProgram();
    GLuint getProgramID();

    ShaderType getType();
    void setType(ShaderType type);
};

#endif // SHADERPROGRAM_HPP
