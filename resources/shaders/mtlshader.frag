#version 330 core

in vec3 normal;
in vec3 lightVector;
in vec2 uv;

in vec3 ambientColor;
in vec3 diffuseColor;
in vec3 specularColor;
in vec3 emitColor;

out vec3 color;

uniform sampler2D textureSampler;
uniform vec3 lightColor;

void main()
{
    vec3 texture = texture2D(textureSampler, uv).rgb;
    vec3 material = diffuseColor + texture;
    vec3 ambient = ambientColor * material * vec3(0.2);
    vec3 specular = specularColor * material;
    vec3 emit = emitColor;

    vec3 n = normalize(normal);
    vec3 l = normalize(lightVector);

    float cosTheta = clamp(dot(n, l), 0.0, 1.0);

    color = cosTheta * material * lightColor + ambient + pow(cosTheta, 100) * specular + emit;
}
