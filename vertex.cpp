#include "vertex.hpp"

Vertex::Vertex() { }

Vertex::Vertex(vec3 coords)
{
    this->position = coords;
    this->normal = vec3(0.0f);
    this->uv = vec2(0.0f);
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

void Vertex::calculateUVPlanar()
{
    uv.x = 0.5 * position.x;
    uv.y = 0.5 * position.y;
}

void Vertex::calculateUVCylindrical()
{
    GLfloat phi;

    phi = atan2(position.y, position.x);
    uv.x = 0.5 * phi;
    uv.y = 0.5 * position.z;
}

vec2 Vertex::getUV()
{
    return uv;
}

void Vertex::setUV(vec2 uv)
{
    this->uv = uv;
}
