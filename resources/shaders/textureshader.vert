#version 330 core

layout(location = 0) in vec3 vertexPositionLoaded;
layout(location = 3) in vec2 vertexUVLoaded;

out vec2 uv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(vertexPositionLoaded, 1);
    uv = vertexUVLoaded;
}
