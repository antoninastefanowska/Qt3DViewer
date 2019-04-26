#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <iostream>

#include <glm/glm.hpp>
#include <QOpenGLFunctions>

using namespace std;

using glm::vec2;
using glm::vec3;

class Vertex
{
private:
    vec3 position, normal;
    vec2 uv;

    bool isSimilar(Vertex vertex);

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

    int getSimilarVertexIndex(vector<Vertex> vertices);
};

#endif // VERTEX_HPP
