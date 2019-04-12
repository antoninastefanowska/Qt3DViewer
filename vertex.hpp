#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <glm/glm.hpp>

using glm::vec3;

class Vertex
{
private:
    vec3 position, normal;
public:
    Vertex();
    Vertex(vec3 position);
    vec3 getPosition();
    vec3 getNormal();
    void setNormal(vec3 normal);
};

#endif // VERTEX_HPP
