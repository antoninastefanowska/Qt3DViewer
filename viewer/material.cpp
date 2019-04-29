#include "material.hpp"

Material::Material()
{
    ambient = vec3(0.0f);
    diffuse = vec3(0.0f);
    specular = vec3(0.0f);
    emission = vec3(0.0f);
}

Material::Material(vec3 ambient, vec3 diffuse, vec3 specular, vec3 emission)
{
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->emission = emission;
}

Material::~Material()
{
    //delete texture;
}

void Material::setTexture(Texture* texture)
{
    this->texture = texture;
}

vec3 Material::getAmbient()
{
    return ambient;
}

void Material::setAmbient(vec3 ambient)
{
    this->ambient = ambient;
}

vec3 Material::getDiffuse()
{
    return diffuse;
}

void Material::setDiffuse(vec3 diffuse)
{
    this->diffuse = diffuse;
}

vec3 Material::getSpecular()
{
    return specular;
}

void Material::setSpecular(vec3 specular)
{
    this->specular = specular;
}

vec3 Material::getEmission()
{
    return emission;
}

void Material::setEmission(vec3 emission)
{
    this->emission = emission;
}
