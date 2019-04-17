#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <glm/glm.hpp>
#include <QOpenGLFunctions>

using glm::vec2;
using glm::vec3;

class Vertex
{
private:
    vec3 position, normal;
    vec2 uv;

public:
    Vertex();
    Vertex(vec3 position);

    vec3 getPosition();

    vec3 getNormal();
    void setNormal(vec3 normal);

    void calculateUVPlanar(float scale);
    void calculateUVCylindrical(float scale);

    vec2 getUV();
    void setUV(vec2 uv);
};

#endif // VERTEX_HPP
