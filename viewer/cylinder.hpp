#ifndef CYLINDER_HPP
#define CYLINDER_HPP

#include "model.hpp"
#include "triangle.hpp"

class Cylinder : public Model
{
private:
    int n;
    float radius, height, uvScale;

public:
    Cylinder();
    Cylinder(int n, float radius, float height);

    void createModel();
    void completeDrawing();
    //void completeHandles();

    void changeN(int n);
    void changeRadius(float radius);
    void changeHeight(float height);
    void changeUVScale(float scale);
};

#endif // CYLINDER_HPP
