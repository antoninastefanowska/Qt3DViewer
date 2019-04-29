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

    vector<Vertex> loadOBJ(string filename);
    map<string, Material*> loadMTL(string filename);

public:
    LoadedModel(string filename);
    void createModel();
};

#endif // LOADEDMODEL_HPP
