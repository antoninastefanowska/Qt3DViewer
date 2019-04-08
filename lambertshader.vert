#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexNormal_modelspace;

out vec3 normal;
out vec3 lightVector;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPosition;

void main()
{
        gl_Position = projection * view * model * vec4(vertexPosition_modelspace, 1);

        vec4 vertexPosition_modelviewspace = view * model * vec4(vertexPosition_modelspace, 1);
        lightVector = vec3(lightPosition - vertexPosition_modelviewspace);
        normal = vertexNormal_modelspace;
}
