#ifndef CYLINDER_HPP
#define CYLINDER_HPP

#include "model.hpp"
#include "triangle.hpp"

class Cylinder : public Model
{
private:
    int n;
    float radius, height;

    void loadDataToBuffers(vector<vec3> verticesData, vector<vec3> normalsData, vector<vec2> uvData);

public:
    Cylinder();
    Cylinder(int n, float radius, float height);

    void createModel();

    void changeN(int n);
    void changeRadius(float radius);
    void changeHeight(float height);
};

#endif // CYLINDER_HPP
