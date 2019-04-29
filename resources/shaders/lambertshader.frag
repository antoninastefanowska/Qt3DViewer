#version 330 core

in vec3 normal;
in vec3 lightVector;

out vec3 color;

uniform vec3 lightColor;

void main()
{
    const vec3 material = vec3(1.0, 0.0, 0.0);
    vec3 ambient = material * vec3(0.2);

    vec3 n = normalize(normal);
    vec3 l = normalize(lightVector);

    float cosTheta = clamp(dot(n, l), 0.0, 1.0);

    color = cosTheta * material * lightColor + ambient;
}
