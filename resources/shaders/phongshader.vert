#version 330 core

layout(location = 0) in vec3 vertexPositionLoaded;
layout(location = 1) in vec3 vertexNormalLoaded;

out vec3 normal;
out vec3 lightVector;

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
}
