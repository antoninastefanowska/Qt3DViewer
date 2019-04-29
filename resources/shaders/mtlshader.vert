#version 330 core

layout(location = 0) in vec3 vertexPositionLoaded;
layout(location = 1) in vec3 vertexNormalLoaded;
layout(location = 3) in vec2 vertexUVLoaded;
layout(location = 4) in vec3 vertexAmbientLoaded;
layout(location = 5) in vec3 vertexDiffuseLoaded;
layout(location = 6) in vec3 vertexSpecularLoaded;
layout(location = 7) in vec3 vertexEmissionLoaded;

out vec3 normal;
out vec3 lightVector;
out vec2 uv;
out vec3 ambientColor;
out vec3 diffuseColor;
out vec3 specularColor;
out vec3 emitColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPosition;

void main()
{
    gl_Position = projection * view * model * vec4(vertexPositionLoaded, 1);

    vec3 vertexPosition = vec3(view * model * vec4(vertexPositionLoaded, 1));
    lightVector = vec3(view * vec4(lightPosition, 1)) - vertexPosition;
    normal = vec3(view * model * vec4(vertexNormalLoaded, 1));
    uv = vertexUVLoaded;

    ambientColor = vertexAmbientLoaded;
    diffuseColor = vertexDiffuseLoaded;
    specularColor = vertexSpecularLoaded;
    emitColor = vertexEmissionLoaded;
}
