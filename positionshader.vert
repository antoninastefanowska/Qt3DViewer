#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;

out vec3 vertexPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(vertexPosition_modelspace, 1);
    vertexPosition = vertexPosition_modelspace;
}
