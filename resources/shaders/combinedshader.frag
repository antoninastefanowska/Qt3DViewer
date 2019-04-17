#version 330 core

in vec3 normal;
in vec3 lightVector;
in vec2 uv;

out vec3 color;

uniform sampler2D textureSampler;

void main()
{
    vec3 material = texture2D(textureSampler, uv).rgb;
    vec3 ambient = material * vec3(0.2);

    const vec3 lightColor = vec3(1.0);
    const vec3 specular = vec3(0.8);

    vec3 n = normalize(normal);
    vec3 l = normalize(lightVector);

    float cosTheta = clamp(dot(n, l), 0.0, 1.0);

    color = cosTheta * material * lightColor + ambient;
    color += pow(cosTheta, 100) * specular;
}
