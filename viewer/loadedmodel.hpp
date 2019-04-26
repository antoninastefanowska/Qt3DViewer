#ifndef LOADEDMODEL_HPP
#define LOADEDMODEL_HPP

#include "model.hpp"
#include "material.hpp"
#include "vertex.hpp"

#include <QFile>
#include <QTextStream>
#include <QString>

class LoadedModel : public Model
{
private:
    static const string BASE_PATH;
    string filename;
    GLuint indicesHandle, kaHandle, kdHandle, ksHandle, keHandle;
    vector<unsigned short> indices;

    void loadDataToBuffers(vector<vec3> verticesData, vector<vec3> normalsData, vector<vec2> uvData);

public:
    LoadedModel(string filename);
    void createModel();
    void completeHandles();
    void completeDrawing();
};

#endif // LOADEDMODEL_HPP
