#include "model.hpp"

Model::Model() { }

void Model::init()
{
    initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    light = new Light(vec3(0.0f, 0.0f, 0.0f));
    texture = new Texture();
    texture->init();
    texture->loadTexture("checkered.bmp");

    generateVertices();
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
    switchShaderProgram("positionshader");
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
    colorsData.reserve(vertexNumber);
    srand(time(NULL));

    for (int i = 0; i < vertexNumber; i++)
    {
        float r1 = ((double)rand() / RAND_MAX), r2 = ((double)rand() / RAND_MAX), r3 = ((double)rand() / RAND_MAX);
        colorsData.push_back(vec3(r1, r2, r3));
    }

    glGenBuffers(1, &colorsID);
    glBindBuffer(GL_ARRAY_BUFFER, colorsID);
    glBufferData(GL_ARRAY_BUFFER, colorsData.size() * sizeof(vec3), &colorsData[0], GL_STATIC_DRAW);
}

void Model::loadVerticesData(vector<vec3> verticesData, vector<vec3> normalsData, vector<vec2> uvData)
{
    glGenBuffers(1, &verticesID);
    glBindBuffer(GL_ARRAY_BUFFER, verticesID);
    glBufferData(GL_ARRAY_BUFFER, verticesData.size() * sizeof(vec3), &verticesData[0], GL_STATIC_DRAW);

    glGenBuffers(1, &normalsID);
    glBindBuffer(GL_ARRAY_BUFFER, normalsID);
    glBufferData(GL_ARRAY_BUFFER, normalsData.size() * sizeof(vec3), &normalsData[0], GL_STATIC_DRAW);

    glGenBuffers(1, &uvID);
    glBindBuffer(GL_ARRAY_BUFFER, uvID);
    glBufferData(GL_ARRAY_BUFFER, uvData.size() * sizeof(vec2), &uvData[0], GL_STATIC_DRAW);
}

void Model::frame()
{
    ShaderProgram* currentShaderProgram = shaderPrograms[currentShaderProgramName];

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(currentShaderProgram->getProgramID());

    glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(viewID, 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(projectionID, 1, GL_FALSE, &projection[0][0]);

    glUniform3f(lightPositionID, light->getPosition().x, light->getPosition().y, light->getPosition().z);

    glBindTexture(GL_TEXTURE_2D, texture->getTextureDataID());
    glUniform1i(textureID, 0);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, verticesID);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, normalsID);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, colorsID);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnableVertexAttribArray(3);
    glBindBuffer(GL_ARRAY_BUFFER, uvID);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glDrawArrays(GL_TRIANGLES, 0, vertexNumber);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);
}

Light* Model::getLight()
{
    return light;
}

Texture* Model::getTexture()
{
    return texture;
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

    modelID = glGetUniformLocation(currentShaderProgram->getProgramID(), "model");
    viewID = glGetUniformLocation(currentShaderProgram->getProgramID(), "view");
    projectionID = glGetUniformLocation(currentShaderProgram->getProgramID(), "projection");
    lightPositionID = glGetUniformLocation(currentShaderProgram->getProgramID(), "lightPosition");
    textureID = glGetUniformLocation(currentShaderProgram->getProgramID(), "textureSampler");
}

void Model::switchTexture(string filename)
{
    texture->loadTexture(filename);
}

void Model::reloadCurrentShaderProgram()
{
    ShaderProgram* currentShaderProgram = shaderPrograms[currentShaderProgramName];
    glDeleteProgram(currentShaderProgram->getProgramID());
    delete currentShaderProgram;
    loadShaderProgram(currentShaderProgramName);
    switchShaderProgram(currentShaderProgramName);
}

void Model::changePerspectiveRatio(float ratio)
{
    projection = perspective(radians(45.0f), ratio, 0.1f, 100.0f);
}

void Model::scaleTexture(float factor)
{
    texture->setScale(factor);
    generateVertices();
}

void Model::cleanUp()
{
    for (pair<string, ShaderProgram*> shaderPair : shaderPrograms)
    {
        GLuint shaderProgramID = shaderPair.second->getProgramID();
        glDeleteProgram(shaderProgramID);
        delete shaderPair.second;
    }
    shaderPrograms.clear();

    glDeleteBuffers(1, &verticesID);
    glDeleteBuffers(1, &normalsID);
    glDeleteBuffers(1, &uvID);
    glDeleteBuffers(1, &colorsID);
    glDeleteTextures(1, &textureID);

    delete texture;
    delete light;
}
