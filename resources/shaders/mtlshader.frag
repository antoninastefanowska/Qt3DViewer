#version 330 core

in vec3 normal;
in vec3 lightVector;
in vec2 uv;

out vec3 color;

uniform sampler2D textureSampler;
uniform vec3 ka;
uniform vec3 kd;
uniform vec3 ks;
uniform vec3 ke;

void main()
{
    vec3 texture = texture2D(textureSampler, uv).rgb;
    vec3 material = kd * texture;
    vec3 ambient = ka * texture * vec3(0.2);
    vec3 specular = ks * texture;

    const vec3 lightColor = vec3(1.0);

    vec3 n = normalize(normal);
    vec3 l = normalize(lightVector);

    float cosTheta = clamp(dot(n, l), 0.0, 1.0);

    color = cosTheta * material * lightColor + ambient;
    color += pow(cosTheta, 100) * specular;
}
