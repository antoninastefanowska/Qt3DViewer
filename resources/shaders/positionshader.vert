#version 330 core

layout(location = 0) in vec3 vertexPositionLoaded;

out vec3 vertexPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(vertexPositionLoaded, 1);
    vertexPosition = vertexPositionLoaded;
}
