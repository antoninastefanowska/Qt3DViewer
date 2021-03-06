#include "model.hpp"

Model::Model()
{
    texture = NULL;
}

Model::~Model()
{
    glDeleteBuffers(1, &verticesHandle);
    glDeleteBuffers(1, &normalsHandle);
    glDeleteBuffers(1, &uvHandle);
    glDeleteBuffers(1, &randomColorsHandle);
    glDeleteBuffers(1, &ambientHandle);
    glDeleteBuffers(1, &diffuseHandle);
    glDeleteBuffers(1, &specularHandle);
    glDeleteBuffers(1, &emissionHandle);

    delete texture;
}

void Model::init()
{
    initializeOpenGLFunctions();

    createModel();
    generateRandomColors();
}

void Model::loadDataToBuffers(vector<Vertex> &vertices)
{
    map<Vertex, unsigned int> verticesOut;
    vector<vec3> verticesData, normalsData, ambientData, diffuseData, specularData, emissionData;
    vector<vec2> uvData;
    vector<unsigned int> indicesData;

    indicesData.reserve(vertices.size());

    clock_t start, end;
    start = clock();
    for (Vertex vertex : vertices)
    {
        int foundIndex = vertex.getSimilarVertexIndexFast(verticesOut);
        if (foundIndex != -1)
            indicesData.push_back((unsigned int)foundIndex);
        else
        {
            verticesData.push_back(vertex.getPosition());
            normalsData.push_back(vertex.getNormal());
            uvData.push_back(vertex.getUV());
            ambientData.push_back(vertex.getMaterial()->getAmbient());
            diffuseData.push_back(vertex.getMaterial()->getDiffuse());
            specularData.push_back(vertex.getMaterial()->getSpecular());
            emissionData.push_back(vertex.getMaterial()->getEmission());

            unsigned int index = (unsigned int)verticesData.size() - 1;
            verticesOut[vertex] = index;
            indicesData.push_back(index);
        }
    }
    end = clock();
    cout << "Czas indeksowania: " << ((double)(end - start)) / CLOCKS_PER_SEC << "s" << endl;

    indicesNumber = indicesData.size();
    vertexNumber = verticesData.size();

    glGenBuffers(1, &verticesHandle);
    glBindBuffer(GL_ARRAY_BUFFER, verticesHandle);
    glBufferData(GL_ARRAY_BUFFER, verticesData.size() * sizeof(vec3), &verticesData[0], GL_STATIC_DRAW);

    glGenBuffers(1, &normalsHandle);
    glBindBuffer(GL_ARRAY_BUFFER, normalsHandle);
    glBufferData(GL_ARRAY_BUFFER, normalsData.size() * sizeof(vec3), &normalsData[0], GL_STATIC_DRAW);

    glGenBuffers(1, &uvHandle);
    glBindBuffer(GL_ARRAY_BUFFER, uvHandle);
    glBufferData(GL_ARRAY_BUFFER, uvData.size() * sizeof(vec2), &uvData[0], GL_STATIC_DRAW);

    glGenBuffers(1, &ambientHandle);
    glBindBuffer(GL_ARRAY_BUFFER, ambientHandle);
    glBufferData(GL_ARRAY_BUFFER, ambientData.size() * sizeof(vec3), &ambientData[0], GL_STATIC_DRAW);

    glGenBuffers(1, &diffuseHandle);
    glBindBuffer(GL_ARRAY_BUFFER, diffuseHandle);
    glBufferData(GL_ARRAY_BUFFER, diffuseData.size() * sizeof(vec3), &diffuseData[0], GL_STATIC_DRAW);

    glGenBuffers(1, &specularHandle);
    glBindBuffer(GL_ARRAY_BUFFER, specularHandle);
    glBufferData(GL_ARRAY_BUFFER, specularData.size() * sizeof(vec3), &specularData[0], GL_STATIC_DRAW);

    glGenBuffers(1, &emissionHandle);
    glBindBuffer(GL_ARRAY_BUFFER, emissionHandle);
    glBufferData(GL_ARRAY_BUFFER, normalsData.size() * sizeof(vec3), &emissionData[0], GL_STATIC_DRAW);

    glGenBuffers(1, &indicesHandle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesHandle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesData.size() * sizeof(unsigned int), &indicesData[0], GL_STATIC_DRAW);
}

void Model::generateRandomColors()
{
    vector<vec3> colorsData;
    colorsData.reserve(vertexNumber);
    srand(time(NULL));

    for (int i = 0; i < vertexNumber; i++)
    {
        double r1 = ((double)rand() / RAND_MAX), r2 = ((double)rand() / RAND_MAX), r3 = ((double)rand() / RAND_MAX);
        colorsData.push_back(vec3(r1, r2, r3));
    }

    glGenBuffers(1, &randomColorsHandle);
    glBindBuffer(GL_ARRAY_BUFFER, randomColorsHandle);
    glBufferData(GL_ARRAY_BUFFER, colorsData.size() * sizeof(vec3), &colorsData[0], GL_STATIC_DRAW);
}

void Model::draw()
{
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, verticesHandle);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, normalsHandle);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, randomColorsHandle);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnableVertexAttribArray(3);
    glBindBuffer(GL_ARRAY_BUFFER, uvHandle);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnableVertexAttribArray(4);
    glBindBuffer(GL_ARRAY_BUFFER, ambientHandle);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnableVertexAttribArray(5);
    glBindBuffer(GL_ARRAY_BUFFER, diffuseHandle);
    glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnableVertexAttribArray(6);
    glBindBuffer(GL_ARRAY_BUFFER, specularHandle);
    glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnableVertexAttribArray(7);
    glBindBuffer(GL_ARRAY_BUFFER, emissionHandle);
    glVertexAttribPointer(7, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    if (texture != NULL)
        texture->draw();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesHandle);
    glDrawElements(GL_TRIANGLES, indicesNumber, GL_UNSIGNED_INT, (void*)0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);
    glDisableVertexAttribArray(4);
    glDisableVertexAttribArray(5);
    glDisableVertexAttribArray(6);
    glDisableVertexAttribArray(7);
}

void Model::createHandles(ShaderProgram* shaderProgram)
{
    if (texture != NULL)
        texture->createHandles(shaderProgram);
}

void Model::switchTexture(string filename)
{
    if (texture != NULL)
        texture->loadTexture(filename);
}

void Model::calculateNormals(vector<Vertex> &vertices, vector<Triangle> &triangles)
{
    for (Vertex &vertex : vertices)
    {
        vec3 normal = vec3(0.0f);
        for (Triangle triangle : triangles)
        {
            if (triangle.contains(vertex))
                normal += triangle.getNormal();
        }
        normal = normalize(normal);
        vertex.setNormal(normal);
    }
}
