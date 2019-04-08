#ifndef CYLINDER_HPP
#define CYLINDER_HPP

#include "model.hpp"

class Cylinder : public Model
{
private:
    int n;
    float radius, height;

public:
    Cylinder();
    Cylinder(int n, float radius, float height);

    void generateVertices();

    void changeN(int dn);
    void changeRadius(float dradius);
    void changeHeight(float dHeight);
};

#endif // CYLINDER_HPP
