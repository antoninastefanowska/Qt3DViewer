#version 330 core

layout(location = 0) in vec3 vertexPositionLoaded;
layout(location = 2) in vec3 vertexColorLoaded;

out vec3 vertexColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(vertexPositionLoaded, 1);
    vertexColor = vertexColorLoaded;
}
