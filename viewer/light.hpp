#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

using glm::vec3;
using glm::vec4;
using glm::mat4;
using glm::translate;

class Light
{
private:
    vec3 position;

public:
    Light();
    Light(vec3 position);

    vec3 getPosition();

    void translateX(float distance);
    void translateY(float distance);
    void translateZ(float distance);
};

#endif // LIGHT_HPP
