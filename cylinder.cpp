#include "cylinder.hpp"

Cylinder::Cylinder() { }

Cylinder::Cylinder(int n, float radius, float height)
{
    this->n = n;
    this->radius = radius;
    this->height = height;
}


void Cylinder::generateVertices()
{
    float angle = radians((float)360 / n);

    vector<vec3> verticesData, normalsData;
    vector<vec2> uvData;
    vector<Triangle> triangles;
    vector<Vertex> vertices;

    vertexNumber = n * 12;

    verticesData.reserve(vertexNumber);
    normalsData.reserve(vertexNumber);
    uvData.reserve(vertexNumber);
    vertices.reserve(vertexNumber);
    triangles.reserve(n * 4);

    GLfloat prevX = radius, prevY = 0.0f;
    for (int i = 0; i < n; i++)
    {
        vec3 v1, v2, v3, v4, v5, v6;
        for (int k = 0; k < 2; k++)
        {
            Vertex vertex1, vertex2, vertex3;
            GLfloat z = k ? -height / 2.0f : height / 2.0f;

            v1.x = v1.y = 0.0f;
            v1.z = z;
            vertex1 = Vertex(v1);
            vertex1.calculateUVPlanar();
            vertices.push_back(vertex1);

            v2.x = prevX;
            v2.y = prevY;
            v2.z = z;
            vertex2 = Vertex(v2);
            vertex2.calculateUVPlanar();
            vertices.push_back(vertex2);

            v3.x = i == n - 1 ? radius : v2.x * cos(angle) - v2.y * sin(angle);
            v3.y = i == n - 1 ? 0.0f : v2.x * sin(angle) + v2.y * cos(angle);
            v3.z = z;
            vertex3 = Vertex(v3);
            vertex3.calculateUVPlanar();
            vertices.push_back(vertex3);
            triangles.push_back(Triangle(vertex1, vertex2, vertex3));

            v4.x = v2.x;
            v4.y = v2.y;
            v4.z = z;
            vertex1 = Vertex(v4);
            vertex1.calculateUVCylindrical();
            vertices.push_back(vertex1);

            v5.x = v3.x;
            v5.y = v3.y;
            v5.z = z;
            vertex2 = Vertex(v5);
            vertex2.calculateUVCylindrical();
            vertices.push_back(vertex2);

            v6.x = k ? v3.x : v2.x;
            v6.y = k ? v3.y : v2.y;
            v6.z = -z;
            vertex3 = Vertex(v6);
            vertex3.calculateUVCylindrical();
            vertices.push_back(vertex3);
            triangles.push_back(Triangle(vertex1, vertex2, vertex3));
        }
        prevX = v3.x;
        prevY = v3.y;
    }

    for (Vertex vertex : vertices)
    {
        vec3 normal = vec3(0.0f);
        for (Triangle triangle : triangles)
        {

            if (triangle.contains(vertex))
                normal += triangle.getNormal();
        }
        normal = normalize(normal);
        vertex.setNormal(normal);

        normalsData.push_back(vertex.getNormal());
        verticesData.push_back(vertex.getPosition());
        uvData.push_back(vertex.getUV());
    }

    loadVerticesData(verticesData, normalsData, uvData);
}

void Cylinder::changeN(int n)
{
    this->n = n;
    generateVertices();
    generateColors();
}

void Cylinder::changeRadius(float radius)
{
    this->radius = radius;
    generateVertices();
}

void Cylinder::changeHeight(float height)
{
    this->height = height;
    generateVertices();
}
