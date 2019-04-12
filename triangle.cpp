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

    edge1 = v2.getPosition() - v1.getPosition();
    edge2 = v3.getPosition() - v1.getPosition();

    normal = cross(edge1, edge2);
    normal = normalize(normal);
}

vec3 Triangle::getNormal()
{
    return normal;
}

bool Triangle::contains(Vertex v)
{
    if (v1.getPosition() == v.getPosition() || v2.getPosition() == v.getPosition() || v3.getPosition() == v.getPosition())
        return true;
    else
        return false;
}
