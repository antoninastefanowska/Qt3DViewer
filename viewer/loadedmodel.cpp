#include "loadedmodel.hpp"

const string LoadedModel::BASE_PATH = "C:/Users/HP/Documents/Qt/Projects/3DViewer/resources/models/";

LoadedModel::LoadedModel(string filename)
{
    this->filename = filename;
}

void LoadedModel::createModel()
{   
    vector<unsigned int> verticesIndices, uvIndices, normalsIndices;
    vector<vec3> readVertices, readNormals;
    vector<vec2> readUV;
    vector<Material*> materialsOut;
    vector<Vertex> vertices;

    map<string, Material*> materials;
    string currentMaterialName;

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
        {
            string mtlFilename = words.value(1).toUtf8().constData();
            materials = loadMTL(mtlFilename);
        }
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
        else if (lineHeader.compare("usemtl") == 0)
            currentMaterialName = words.value(1).toUtf8().constData();

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
                uvIndex[i] = indicesWords[i].value(1).size() > 0 ? indicesWords[i].value(1).toInt() : 0;
                normalIndex[i] = indicesWords[i].value(2).toInt();
            }

            for (int i = 0; i < 3; i++)
            {
                verticesIndices.push_back(vertexIndex[i]);
                uvIndices.push_back(uvIndex[i]);
                normalsIndices.push_back(normalIndex[i]);
                materialsOut.push_back(materials[currentMaterialName]);
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
        vec2 vertexUV = uvIndex != 0 ? readUV[uvIndex - 1] : vec2(0.0f);

        Vertex vertex = Vertex(vertexPosition);
        vertex.setNormal(vertexNormal);
        vertex.setUV(vertexUV);
        vertex.setMaterial(materialsOut[i]);
        vertices.push_back(vertex);
    }

    loadDataToBuffers(vertices);

    for (pair<string, Material*> materialPair : materials)
        delete materialPair.second;
}

map<string, Material*> LoadedModel::loadMTL(string filename)
{
    map<string, Material*> materials;
    string currentMaterialName;

    cout << "Otwieranie pliku: " << filename << endl;
    QFile mtlFile((BASE_PATH + filename).c_str());
    string fileContent;
    if (!mtlFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        cout << "Blad otwarcia pliku." << endl;
        return map<string, Material*>();
    }
    QTextStream stream(&mtlFile);
    QString line;
    while (stream.readLineInto(&line))
    {
        QStringList words = line.split(" ");
        string lineHeader = words.value(0).toUtf8().constData();

        if (lineHeader.compare("newmtl") == 0)
        {
            currentMaterialName = words.value(1).toUtf8().constData();
            materials[currentMaterialName] = new Material();
        }
        else if (lineHeader.compare("Ka") == 0)
        {
            float r, g, b;
            r = words.value(1).toFloat();
            g = words.value(2).toFloat();
            b = words.value(3).toFloat();
            materials[currentMaterialName]->setAmbient(vec3(r, g, b));
        }

        else if (lineHeader.compare("Kd") == 0)
        {
            float r, g, b;
            r = words.value(1).toFloat();
            g = words.value(2).toFloat();
            b = words.value(3).toFloat();
            materials[currentMaterialName]->setDiffuse(vec3(r, g, b));
        }

        else if (lineHeader.compare("Ks") == 0)
        {
            float r, g, b;
            r = words.value(1).toFloat();
            g = words.value(2).toFloat();
            b = words.value(3).toFloat();
            materials[currentMaterialName]->setSpecular(vec3(r, g, b));
        }

        else if (lineHeader.compare("Ke") == 0)
        {
            float r, g, b;
            r = words.value(1).toFloat();
            g = words.value(2).toFloat();
            b = words.value(3).toFloat();
            materials[currentMaterialName]->setEmission(vec3(r, g, b));
        }

        else if (lineHeader.compare("map_Kd") == 0)
        {
            string textureFilename = words.value(1).toUtf8().constData();
            texture = new Texture();
            texture->init();
            texture->loadTexture(textureFilename);
            materials[currentMaterialName] = new Material();
        }
    }

    mtlFile.close();
    return materials;
}
