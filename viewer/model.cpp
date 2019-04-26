#include "model.hpp"

Model::Model() { }

void Model::init()
{
    initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    light = new Light(vec3(0.0f, 0.0f, 0.0f));
    light->init();
    material = new Material();
    material->init();

    createModel();
    generateColors();

    model = mat4(1.0f);
    view = lookAt(
        vec3(0, 0, 15),
        vec3(0, 0, 0),
        vec3(0, 1, 0)
    );
    projection = perspective(radians(45.0f), 1.0f, 0.1f, 100.0f);

    loadShaderProgram("positionshader");
    loadShaderProgram("randomshader");
    loadShaderProgram("normalshader");
    loadShaderProgram("lambertshader");
    loadShaderProgram("phongshader");
    loadShaderProgram("textureshader");
    loadShaderProgram("combinedshader");
    loadShaderProgram("mtlshader");
    switchShaderProgram("positionshader");
}

void Model::loadDataToBuffers(vector<Vertex> vertices)
{
    vector<Vertex> verticesOut;
    vector<vec3> verticesData, normalsData;
    vector<vec2> uvData;
    vector<unsigned short> indicesData;

    indicesData.reserve(vertices.size());

    for (Vertex vertex : vertices)
    {
        int foundIndex = vertex.getSimilarVertexIndex(verticesOut);
        if (foundIndex != -1)
            indicesData.push_back(foundIndex);
        else
        {
            verticesData.push_back(vertex.getPosition());
            normalsData.push_back(vertex.getNormal());
            uvData.push_back(vertex.getUV());
            verticesOut.push_back(vertex);
            indicesData.push_back((unsigned short)verticesOut.size() - 1);
        }
    }
    indicesNumber = indicesData.size();

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
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesData.size() * sizeof(unsigned short), &indicesData[0], GL_STATIC_DRAW);

}

void Model::loadShaderProgram(string name)
{
    ShaderProgram* shaderProgram = new ShaderProgram();
    shaderProgram->init();
    shaderProgram->loadShader(name + ".vert", GL_VERTEX_SHADER);
    shaderProgram->loadShader(name + ".frag", GL_FRAGMENT_SHADER);
    shaderProgram->linkProgram();
    shaderPrograms[name] = shaderProgram;
}

void Model::generateColors()
{
    vector<vec3> colorsData;
    colorsData.reserve(indicesNumber);
    srand(time(NULL));

    for (int i = 0; i < indicesNumber; i++)
    {
        float r1 = ((double)rand() / RAND_MAX), r2 = ((double)rand() / RAND_MAX), r3 = ((double)rand() / RAND_MAX);
        colorsData.push_back(vec3(r1, r2, r3));
    }

    glGenBuffers(1, &colorsHandle);
    glBindBuffer(GL_ARRAY_BUFFER, colorsHandle);
    glBufferData(GL_ARRAY_BUFFER, colorsData.size() * sizeof(vec3), &colorsData[0], GL_STATIC_DRAW);
}

void Model::draw()
{
    ShaderProgram* currentShaderProgram = shaderPrograms[currentShaderProgramName];

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(currentShaderProgram->getProgramHandle());

    glUniformMatrix4fv(modelMatrixHandle, 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(viewMatrixHandle, 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(projectionMatrixHandle, 1, GL_FALSE, &projection[0][0]);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, verticesHandle);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, normalsHandle);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, colorsHandle);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnableVertexAttribArray(3);
    glBindBuffer(GL_ARRAY_BUFFER, uvHandle);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    light->draw();
    material->draw();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesHandle);
    glDrawElements(GL_TRIANGLES, indicesNumber, GL_UNSIGNED_SHORT, (void*)0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);
}

Light* Model::getLight()
{
    return light;
}

Material* Model::getMaterial()
{
    return material;
}

void Model::rotateX(float angle)
{
    model = rotate(model, radians(angle), vec3(1.0f, 0.0f, 0.0f));
}

void Model::rotateY(float angle)
{
    model = rotate(model, radians(angle), vec3(0.0f, 1.0f, 0.0f));
}

void Model::rotateZ(float angle)
{
    model = rotate(model, radians(angle), vec3(0.0f, 0.0f, 1.0f));
}

void Model::translateX(float distance)
{
    model = translate(model, vec3(distance, 0.0f, 0.0f));
}

void Model::translateY(float distance)
{
    model = translate(model, vec3(0.0f, distance, 0.0f));
}

void Model::translateZ(float distance)
{
    model = translate(model, vec3(0.0f, 0.0f, distance));
}

void Model::switchShaderProgram(string name)
{
    ShaderProgram* currentShaderProgram = shaderPrograms[name];
    currentShaderProgramName = name;

    modelMatrixHandle = glGetUniformLocation(currentShaderProgram->getProgramHandle(), "model");
    viewMatrixHandle = glGetUniformLocation(currentShaderProgram->getProgramHandle(), "view");
    projectionMatrixHandle = glGetUniformLocation(currentShaderProgram->getProgramHandle(), "projection");

    light->createHandles(currentShaderProgram);
    material->createHandles(currentShaderProgram);
}

void Model::reloadCurrentShaderProgram()
{
    ShaderProgram* currentShaderProgram = shaderPrograms[currentShaderProgramName];
    glDeleteProgram(currentShaderProgram->getProgramHandle());
    delete currentShaderProgram;
    loadShaderProgram(currentShaderProgramName);
    switchShaderProgram(currentShaderProgramName);
}

void Model::changePerspectiveRatio(float ratio)
{
    projection = perspective(radians(45.0f), ratio, 0.1f, 100.0f);
}

void Model::cleanUp()
{
    for (pair<string, ShaderProgram*> shaderPair : shaderPrograms)
    {
        GLuint shaderProgramID = shaderPair.second->getProgramHandle();
        glDeleteProgram(shaderProgramID);
        delete shaderPair.second;
    }
    shaderPrograms.clear();

    glDeleteBuffers(1, &verticesHandle);
    glDeleteBuffers(1, &normalsHandle);
    glDeleteBuffers(1, &uvHandle);
    glDeleteBuffers(1, &colorsHandle);

    delete material;
    delete light;
}
