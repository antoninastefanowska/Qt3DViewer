#include "loadedmodel.hpp"

const string LoadedModel::BASE_PATH = "C:/Users/HP/Documents/Qt/Projects/3DViewer/resources/models/";

LoadedModel::LoadedModel(string filename)
{
    this->filename = filename;
}

void LoadedModel::createModel()
{
    vector<unsigned short> verticesIndices, uvIndices, normalsIndices;
    vector<vec3> readVertices, readNormals;
    vector<vec2> readUV;
    vector<Vertex> vertices;

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

    vertices.reserve(verticesIndices.size());

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
        vertices.push_back(vertex);
    }

    material->loadMTL(mtlFilename);

    loadDataToBuffers(vertices);
}
