#ifndef ROTATEANIMATION_HPP
#define ROTATEANIMATION_HPP

#include "animation.hpp"

using glm::radians;

class RotateAnimation : public Animation
{
private:
    float startAngle, endAngle;
    vec3 axisVector;

public:
    RotateAnimation(float startAngle, float endAngle, vec3 axisVector, unsigned int duration);

    mat4 calculateFrameMatrix();
};

#endif // ROTATEANIMATION_HPP
