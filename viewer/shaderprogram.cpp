#include "shaderprogram.hpp"

const string ShaderProgram::BASE_PATH = "C:/Users/HP/Documents/Qt/Projects/3DViewer/resources/shaders/";

void ShaderProgram::init()
{
    initializeOpenGLFunctions();
}

void ShaderProgram::loadShader(string filename, GLenum type)
{
    GLuint shaderID = glCreateShader(type);
    string shaderCode;

    QFile shaderFile((BASE_PATH + filename).c_str());

    if (shaderFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream str(&shaderFile);
        QString content = str.readAll();
        shaderCode = content.toUtf8().constData();
        shaderFile.close();
    }
    else
    {
        cout << "Blad otwarcia pliku" << endl;
        getchar();
        return;
    }

    GLint result;
    int infoLogLength;
    cout << "Kompilowanie shadera: " << filename << endl;

    char const* shaderSourcePointer = shaderCode.c_str();
    glShaderSource(shaderID, 1, &shaderSourcePointer, NULL);
    glCompileShader(shaderID);

    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0)
    {
        vector<char> shaderErrorMessage(infoLogLength + 1);
        glGetShaderInfoLog(shaderID, infoLogLength, NULL, &shaderErrorMessage[0]);
        cout << &shaderErrorMessage[0] << endl;
    }

    shaderIDs.push_back(shaderID);
}

void ShaderProgram::linkProgram()
{
    cout << "Konsolidowanie programu" << endl;

    GLint result = GL_FALSE;
    int infoLogLength;
    programID = glCreateProgram();

    for (GLuint shaderID : shaderIDs)
        glAttachShader(programID, shaderID);
    glLinkProgram(programID);

    glGetProgramiv(programID, GL_LINK_STATUS, &result);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0)
    {
        vector<char> programErrorMessage(infoLogLength + 1);
        glGetProgramInfoLog(programID, infoLogLength, NULL, &programErrorMessage[0]);
        cout << &programErrorMessage[0] << endl;
    }

    for (GLuint shaderID : shaderIDs)
    {
        glDetachShader(programID, shaderID);
        glDeleteShader(shaderID);
    }

    shaderIDs.clear();
}

GLuint ShaderProgram::getProgramID()
{
    return programID;
}
