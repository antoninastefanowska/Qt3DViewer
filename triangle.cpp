#include "triangle.hpp"

Triangle::Triangle() { }

Triangle::Triangle(Vertex v1, Vertex v2, Vertex v3)
{
    this->v1 = v1;
    this->v2 = v2;
    this->v3 = v3;

    calculateNormal();
}

void Triangle::calculateNormal()
{
    vec3 edge1, edge2;

    edge1 = v2.getCoords() - v1.getCoords();
    edge2 = v3.getCoords() - v1.getCoords();

    normal = cross(edge1, edge2);
    normal = normalize(normal);
}

vec3 Triangle::getNormal()
{
    return normal;
}

bool Triangle::contains(Vertex v)
{
    if (v1.getCoords() == v.getCoords() || v2.getCoords() == v.getCoords() || v3.getCoords() == v.getCoords())
        return true;
    else
        return false;
}
