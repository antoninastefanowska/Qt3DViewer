#include "rotateanimation.hpp"

RotateAnimation::RotateAnimation(float startAngle, float endAngle, vec3 axisVector, unsigned int duration)
{
    this->startAngle = startAngle;
    this->endAngle = endAngle;
    this->duration = duration;
    this->axisVector = axisVector;
    currentStep = 0;
    paused = false;
}

mat4 RotateAnimation::calculateFrameMatrix()
{
    float currentAngle = startAngle + currentStep * (endAngle - startAngle) / duration;
    mat4 currentTransformationMatrix = rotate(mat4(1.0f), radians(currentAngle), axisVector);
    currentStep++;
    return currentTransformationMatrix;
}
