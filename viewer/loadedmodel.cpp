#include "loadedmodel.hpp"

const string LoadedModel::BASE_PATH = "C:/Users/HP/Documents/Qt/Projects/3DViewer/resources/models/";

LoadedModel::LoadedModel(string filename)
{
    this->filename = filename;
}

void LoadedModel::createModel()
{
    vector<unsigned int> verticesIndices, uvIndices, normalsIndices;
    vector<vec3> readVertices, readNormals, verticesData, normalsData;
    vector<vec2> readUV, uvData;
    vector<Vertex> verticesIn, verticesOut;
    string mtlFilename;

    cout << "Otwieranie pliku: " << filename << endl;
    QFile objFile((BASE_PATH + filename).c_str());
    string fileContent;

    if (!objFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        cout << "Blad otwarcia pliku." << endl;
        return;
    }
    QTextStream stream(&objFile);
    QString line;
    while (stream.readLineInto(&line))
    {
        QStringList words = line.split(" ");
        string lineHeader = words.value(0).toUtf8().constData();

        if (lineHeader.compare("mtllib") == 0)
            mtlFilename = words.value(1).toUtf8().constData();

        else if (lineHeader.compare("v") == 0)
        {
            vec3 vertex;
            vertex.x = words.value(1).toFloat();
            vertex.y = words.value(2).toFloat();
            vertex.z = words.value(3).toFloat();
            readVertices.push_back(vertex);
        }
        else if (lineHeader.compare("vn") == 0)
        {
            vec3 normal;
            normal.x = words.value(1).toFloat();
            normal.y = words.value(2).toFloat();
            normal.z = words.value(3).toFloat();
            readNormals.push_back(normal);
        }
        else if (lineHeader.compare("vt") == 0)
        {
            vec2 uv;
            uv.x = words.value(1).toFloat();
            uv.y = words.value(2).toFloat();
            readUV.push_back(uv);
        }
        else if (lineHeader.compare("f") == 0)
        {
            QStringList indicesWords[3];
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];

            indicesWords[0] = words.value(1).split('/');
            indicesWords[1] = words.value(2).split('/');
            indicesWords[2] = words.value(3).split('/');

            for (int i = 0; i < 3; i++)
            {
                vertexIndex[i] = indicesWords[i].value(0).toInt();
                uvIndex[i] = indicesWords[i].value(1).toInt();
                normalIndex[i] = indicesWords[i].value(2).toInt();
            }

            for (int i = 0; i < 3; i++)
            {
                verticesIndices.push_back(vertexIndex[i]);
                uvIndices.push_back(uvIndex[i]);
                normalsIndices.push_back(normalIndex[i]);
            }
        }
    }

    objFile.close();

    verticesData.reserve(verticesIndices.size());
    normalsData.reserve(normalsIndices.size());
    uvData.reserve(uvIndices.size());

    verticesIn.reserve(verticesIndices.size());

    cout << verticesIndices.size() << ' ' << normalsIndices.size() << ' ' << uvIndices.size() << endl;

    for (unsigned int i = 0; i < verticesIndices.size(); i++)
    {
        unsigned int vertexIndex = verticesIndices[i];
        unsigned int normalIndex = normalsIndices[i];
        unsigned int uvIndex = uvIndices[i];

        vec3 vertexPosition = readVertices[vertexIndex - 1];
        vec3 vertexNormal = readNormals[normalIndex - 1];
        vec2 vertexUV = readUV[uvIndex - 1];

        Vertex vertex = Vertex(vertexPosition);
        vertex.setNormal(vertexNormal);
        vertex.setUV(vertexUV);
        verticesIn.push_back(vertex);
        //vec3 vertex = readVertices[vertexIndex - 1];
        //verticesData.push_back(vertex);
    }

    /*
    for (unsigned int i = 0; i < normalsIndices.size(); i++)
    {
        unsigned int normalIndex = normalsIndices[i];
        vec3 normal = readNormals[normalIndex - 1];
        normalsData.push_back(normal);
    }

    for (unsigned int i = 0; i < uvIndices.size(); i++)
    {
        unsigned int uvIndex = uvIndices[i];
        vec2 uv = readUV[uvIndex - 1];
        uvData.push_back(uv);
    } */

    for (Vertex vertex : verticesIn)
    {
        int foundIndex = vertex.getSimilarVertexIndex(verticesOut);
        if (foundIndex != -1)
            indices.push_back(foundIndex);
        else
        {
            verticesData.push_back(vertex.getPosition());
            normalsData.push_back(vertex.getNormal());
            uvData.push_back(vertex.getUV());
            verticesOut.push_back(vertex);
            indices.push_back((unsigned short)verticesOut.size() - 1);
        }
    }

    material->loadMTL(mtlFilename);

    vertexNumber = verticesData.size();

    cout << "tu jestem 1" << endl;

    loadDataToBuffers(verticesData, normalsData, uvData);

    cout << "tu jestem 2" << endl;
}

void LoadedModel::loadDataToBuffers(vector<vec3> verticesData, vector<vec3> normalsData, vector<vec2> uvData)
{
    glGenBuffers(1, &verticesHandle);
    glBindBuffer(GL_ARRAY_BUFFER, verticesHandle);
    glBufferData(GL_ARRAY_BUFFER, verticesData.size() * sizeof(vec3), &verticesData[0], GL_STATIC_DRAW);

    glGenBuffers(1, &normalsHandle);
    glBindBuffer(GL_ARRAY_BUFFER, normalsHandle);
    glBufferData(GL_ARRAY_BUFFER, normalsData.size() * sizeof(vec3), &normalsData[0], GL_STATIC_DRAW);

    glGenBuffers(1, &uvHandle);
    glBindBuffer(GL_ARRAY_BUFFER, uvHandle);
    glBufferData(GL_ARRAY_BUFFER, uvData.size() * sizeof(vec2), &uvData[0], GL_STATIC_DRAW);

    glGenBuffers(1, &indicesHandle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesHandle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);

}

void LoadedModel::completeHandles()
{
    ShaderProgram* currentShaderProgram = shaderPrograms[currentShaderProgramName];

    kaHandle = glGetUniformLocation(currentShaderProgram->getProgramID(), "ka");
    kdHandle = glGetUniformLocation(currentShaderProgram->getProgramID(), "kd");
    ksHandle = glGetUniformLocation(currentShaderProgram->getProgramID(), "ks");
    keHandle = glGetUniformLocation(currentShaderProgram->getProgramID(), "ke");
}

void LoadedModel::completeDrawing()
{
    glUniform3f(kaHandle, material->ka.x, material->ka.y, material->ka.z);
    glUniform3f(kdHandle, material->kd.x, material->kd.y, material->kd.z);
    glUniform3f(ksHandle, material->ks.x, material->ks.y, material->ks.z);
    glUniform3f(keHandle, material->ke.x, material->ke.y, material->ke.z);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesHandle);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, (void*)0);
}
