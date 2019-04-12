#include "model.hpp"

Model::Model() { }

void Model::init()
{
    initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    generateVertices();
    generateColors();

    model = mat4(1.0f);
    view = lookAt(
        vec3(0, 0, 15),
        vec3(0, 0, 0),
        vec3(0, 1, 0)
    );
    projection = perspective(radians(45.0f), 1.0f, 0.1f, 100.0f);

    light = new Light(vec3(0.0f, 0.0f, 0.0f));

    loadAllShaders();
    switchShader(POSITION_SHADER);
}

void Model::loadAllShaders()
{
    ShaderProgram* shaderProgram = new ShaderProgram();
    shaderProgram->init();

    shaderProgram->loadShader("randomshader.vert", GL_VERTEX_SHADER);
    shaderProgram->loadShader("randomshader.frag", GL_FRAGMENT_SHADER);
    shaderProgram->linkProgram();
    shaderPrograms[RANDOM_SHADER] = shaderProgram;

    shaderProgram = new ShaderProgram();
    shaderProgram->init();
    shaderProgram->loadShader("positionshader.vert", GL_VERTEX_SHADER);
    shaderProgram->loadShader("positionshader.frag", GL_FRAGMENT_SHADER);
    shaderProgram->linkProgram();
    shaderPrograms[POSITION_SHADER] = shaderProgram;

    shaderProgram = new ShaderProgram();
    shaderProgram->init();
    shaderProgram->loadShader("normalshader.vert", GL_VERTEX_SHADER);
    shaderProgram->loadShader("normalshader.frag", GL_FRAGMENT_SHADER);
    shaderProgram->linkProgram();
    shaderPrograms[NORMAL_SHADER] = shaderProgram;

    shaderProgram = new ShaderProgram();
    shaderProgram->init();
    shaderProgram->loadShader("lambertshader.vert", GL_VERTEX_SHADER);
    shaderProgram->loadShader("lambertshader.frag", GL_FRAGMENT_SHADER);
    shaderProgram->linkProgram();
    shaderPrograms[LAMBERT_SHADER] = shaderProgram;
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

void Model::loadVerticesData(vector<vec3> verticesData, vector<vec3> normalsData)
{
    glGenBuffers(1, &verticesID);
    glBindBuffer(GL_ARRAY_BUFFER, verticesID);
    glBufferData(GL_ARRAY_BUFFER, verticesData.size() * sizeof(vec3), &verticesData[0], GL_STATIC_DRAW);

    glGenBuffers(1, &normalsID);
    glBindBuffer(GL_ARRAY_BUFFER, normalsID);
    glBufferData(GL_ARRAY_BUFFER, normalsData.size() * sizeof(vec3), &normalsData[0], GL_STATIC_DRAW);
}

void Model::frame()
{
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(currentShaderProgram->getProgramID());

    glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(viewID, 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(projectionID, 1, GL_FALSE, &projection[0][0]);

    glUniform3f(lightPositionID, light->getPosition().x, light->getPosition().y, light->getPosition().z);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, verticesID);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, normalsID);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, colorsID);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glDrawArrays(GL_TRIANGLES, 0, vertexNumber);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}

Light* Model::getLight()
{
    return light;
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

void Model::switchShader(ShaderType shaderType)
{
    currentShaderProgram = shaderPrograms[shaderType];

    modelID = glGetUniformLocation(currentShaderProgram->getProgramID(), "model");
    viewID = glGetUniformLocation(currentShaderProgram->getProgramID(), "view");
    projectionID = glGetUniformLocation(currentShaderProgram->getProgramID(), "projection");
    lightPositionID = glGetUniformLocation(currentShaderProgram->getProgramID(), "lightPosition");
}

void Model::changePerspectiveRatio(float ratio)
{
    projection = perspective(radians(45.0f), ratio, 0.1f, 100.0f);
}
