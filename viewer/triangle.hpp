#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "vertex.hpp"

class Triangle
{
private:
    Vertex v1, v2, v3;
    vec3 normal;
public:
    Triangle();
    Triangle(Vertex v1, Vertex v2, Vertex v3);
    void calculateNormal();
    vec3 getNormal();
    bool contains(Vertex v);
};


#endif // TRIANGLE_HPP
