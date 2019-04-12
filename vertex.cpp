#include "vertex.hpp"

Vertex::Vertex() { }

Vertex::Vertex(vec3 coords)
{
    this->position = coords;
    this->normal = vec3(0.0f);
}

vec3 Vertex::getPosition()
{
    return position;
}

vec3 Vertex::getNormal()
{
    return normal;
}

void Vertex::setNormal(vec3 normal)
{
    this->normal = normal;
}
