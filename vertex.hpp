#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <glm/glm.hpp>

using glm::vec3;

class Vertex
{
private:
    vec3 coords, normal;
public:
    Vertex();
    Vertex(vec3 coords);
    vec3 getCoords();
    vec3 getNormal();
    void setNormal(vec3 normal);
};

#endif // VERTEX_HPP
