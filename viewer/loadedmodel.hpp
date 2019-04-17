#ifndef LOADEDMODEL_HPP
#define LOADEDMODEL_HPP

#include "model.hpp"

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
