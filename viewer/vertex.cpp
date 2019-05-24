#include "vertex.hpp"

Vertex::Vertex() { }

Vertex::Vertex(vec3 coords)
{
    this->position = coords;
    this->normal = vec3(0.0f);
    this->uv = vec2(0.0f);
}

bool Vertex::operator<(Vertex that) const
{
    return memcmp((void*)this, (void*)&that, sizeof(Vertex))>0;
}

bool Vertex::operator==(Vertex that) const
{
    return (this->position == that.position &&
            this->normal == that.normal &&
            this->uv == that.uv);
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

Material* Vertex::getMaterial()
{
    return material;
}

void Vertex::setMaterial(Material* material)
{
    this->material = material;
}

int Vertex::getSimilarVertexIndexFast(map<Vertex, unsigned int> &vertices)
{
    map<Vertex, unsigned int>::iterator it = vertices.find(*this);
    if (it == vertices.end())
        return -1;
    else
       return it->second;
}

int Vertex::getSimilarVertexIndexSlow(vector<Vertex> &vertices)
{
    for (unsigned int i = 0; i < vertices.size(); i++)
        if (*this == vertices[i])
            return i;
    return -1;
}
