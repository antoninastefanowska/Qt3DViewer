#include "material.hpp"

const string Material::BASE_PATH = "C:/Users/HP/Documents/Qt/Projects/3DViewer/resources/models/";

Material::Material()
{
    ka = vec3(0.0f);
    kd = vec3(0.0f);
    ks = vec3(0.0f);
    ke = vec3(0.0f);
}

Material::~Material()
{
    delete texture;
}

void Material::init()
{
    initializeOpenGLFunctions();
}

void Material::loadMTL(string filename)
{
    cout << "Otwieranie pliku: " << filename << endl;
    QFile mtlFile((BASE_PATH + filename).c_str());
    string fileContent;
    if (!mtlFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        cout << "Blad otwarcia pliku." << endl;
        return;
    }
    QTextStream stream(&mtlFile);
    QString line;
    while (stream.readLineInto(&line))
    {
        QStringList words = line.split(" ");
        string lineHeader = words.value(0).toUtf8().constData();

        if (lineHeader.compare("Ka") == 0)
        {
            ka.x = words.value(1).toFloat();
            ka.y = words.value(2).toFloat();
            ka.z = words.value(3).toFloat();
        }

        else if (lineHeader.compare("Kd") == 0)
        {
            kd.x = words.value(1).toFloat();
            kd.y = words.value(2).toFloat();
            kd.z = words.value(3).toFloat();
        }

        else if (lineHeader.compare("Ks") == 0)
        {
            ks.x = words.value(1).toFloat();
            ks.y = words.value(2).toFloat();
            ks.z = words.value(3).toFloat();
        }

        else if (lineHeader.compare("Ke") == 0)
        {
            ke.x = words.value(1).toFloat();
            ke.y = words.value(2).toFloat();
            ks.z = words.value(3).toFloat();
        }

        else if (lineHeader.compare("map_Kd") == 0)
        {
            string textureFilename = words.value(1).toUtf8().constData();
            texture = new Texture();
            texture->init();
            texture->loadTexture(textureFilename);
        }
    }

    mtlFile.close();
}

void Material::createHandles(ShaderProgram* shaderProgram)
{
    kaHandle = glGetUniformLocation(shaderProgram->getProgramHandle(), "ka");
    kdHandle = glGetUniformLocation(shaderProgram->getProgramHandle(), "kd");
    ksHandle = glGetUniformLocation(shaderProgram->getProgramHandle(), "ks");
    keHandle = glGetUniformLocation(shaderProgram->getProgramHandle(), "ke");
}

void Material::setTexture(Texture* texture)
{
    this->texture = texture;
}

void Material::switchTexture(string filename)
{
    texture->loadTexture(filename);
}

void Material::draw()
{
    glUniform3f(kaHandle, ka.x, ka.y, ka.z);
    glUniform3f(kdHandle, kd.x, kd.y, kd.z);
    glUniform3f(ksHandle, ks.x, ks.y, ks.z);
    glUniform3f(keHandle, ke.x, ke.y, ke.z);

    texture->draw();
}
