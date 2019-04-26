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

public:
    LoadedModel(string filename);
    void createModel();
};

#endif // LOADEDMODEL_HPP
