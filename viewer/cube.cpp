#include "cube.hpp"

Cube::Cube() { }

void Cube::createModel()
{
    vector<Triangle> triangles;
    vector<Vertex> vertices;

    Material* material = new Material();
    texture = new Texture();
    texture->init();
    texture->loadTexture("checkered.png");

    vertices.reserve(36);
    triangles.reserve(12);

    createFace(vec3(0, 0, 0), vec3(1, 0, 0), vec3(1, 1, 0), vec3(0, 1, 0), vertices, triangles, material);
    createFace(vec3(0, 0, 0), vec3(1, 0, 0), vec3(1, 0, 1), vec3(0, 0, 1), vertices, triangles, material);
    createFace(vec3(0, 0, 0), vec3(0, 1, 0), vec3(0, 1, 1), vec3(0, 0, 1), vertices, triangles, material);

    createFace(vec3(1, 1, 1), vec3(0, 1, 1), vec3(0, 0, 1), vec3(1, 0, 1), vertices, triangles, material);
    createFace(vec3(1, 1, 1), vec3(0, 1, 1), vec3(0, 1, 0), vec3(1, 1, 0), vertices, triangles, material);
    createFace(vec3(1, 1, 1), vec3(1, 0, 1), vec3(1, 0, 0), vec3(1, 1, 0), vertices, triangles, material);

    calculateNormals(vertices, triangles);
    loadDataToBuffers(vertices);
    delete material;
}

void Cube::createFace(vec3 v1, vec3 v2, vec3 v3, vec3 v4, vector<Vertex> &vertices, vector<Triangle> &triangles, Material* material)
{
    Vertex vertex1, vertex2, vertex3, vertex4;

    vertex1 = Vertex(v1);
    vertex1.calculateUVPlanar(1.0f);
    vertex1.setMaterial(material);

    vertex2 = Vertex(v2);
    vertex2.calculateUVPlanar(1.0f);
    vertex2.setMaterial(material);

    vertex3 = Vertex(v3);
    vertex3.calculateUVPlanar(1.0f);
    vertex3.setMaterial(material);

    vertex4 = Vertex(v4);
    vertex4.calculateUVPlanar(1.0f);
    vertex4.setMaterial(material);

    vertices.push_back(vertex1);
    vertices.push_back(vertex2);
    vertices.push_back(vertex3);
    vertices.push_back(vertex3);
    vertices.push_back(vertex4);
    vertices.push_back(vertex1);

    triangles.push_back(Triangle(vertex1, vertex2, vertex3));
    triangles.push_back(Triangle(vertex3, vertex4, vertex1));
}
