#ifndef CUBE_HPP
#define CUBE_HPP

#include "model.hpp"
#include "triangle.hpp"

class Cube : public Model
{
private:
    void createFace(vec3 v1, vec3 v2, vec3 v3, vec3 v4, vector<Vertex> &vertices, vector<Triangle> &triangles, Material* material);

public:
    Cube();

    void createModel();
};

#endif // CUBE_HPP
