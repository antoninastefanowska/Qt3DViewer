#include "translateanimation.hpp"

TranslateAnimation::TranslateAnimation(vec3 startPosition, vec3 endPosition, unsigned int duration)
{
    this->startPosition = startPosition;
    this->endPosition = endPosition;
    this->duration = duration;
    currentStep = 0;
    paused = false;
}

mat4 TranslateAnimation::calculateFrameMatrix()
{
    vec3 currentPosition = startPosition + vec3(currentStep) * (endPosition - startPosition) / vec3(duration);
    mat4 currentTransformationMatrix = translate(mat4(1.0f), currentPosition);
    currentStep++;
    return currentTransformationMatrix;
}
