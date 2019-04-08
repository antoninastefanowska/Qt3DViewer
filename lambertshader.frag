#version 330 core

in vec3 normal;
in vec3 lightVector;

out vec3 color;

void main()
{
        const vec3 materialColor = vec3(1.0, 0.0, 0.0);
        const vec3 lightColor = vec3(1.0);

        vec3 n = normalize(normal);
        vec3 l = normalize(lightVector);

        float cosTheta = clamp(dot(n, l), 0.0, 1.0);

        color = materialColor * lightColor * cosTheta;
}
