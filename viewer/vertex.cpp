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

void Vertex::calculateUVPlanar(float scale)
{
    uv.x = scale * position.x;
    uv.y = scale * position.y;
}

void Vertex::calculateUVCylindrical(float scale)
{
    GLfloat phi;

    phi = atan2(position.y, position.x);
    uv.x = scale * phi;
    uv.y = scale * position.z;
}

vec2 Vertex::getUV()
{
    return uv;
}

void Vertex::setUV(vec2 uv)
{
    this->uv = uv;
}

bool Vertex::isSimilar(Vertex vertex)
{
    if (distance(this->position, vertex.position) < 0.01f && distance(this->normal, vertex.normal) < 0.01f && distance(this->uv, vertex.uv) < 0.01f)
        return true;
    else
        return false;
}

int Vertex::getSimilarVertexIndex(vector<Vertex> vertices)
{
    for (unsigned int i = 0; i < vertices.size(); i++)
    {
        if (isSimilar(vertices[i]))
            return i;
    }
    return -1;
}
