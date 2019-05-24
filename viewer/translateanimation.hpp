#ifndef TRANSLATEANIMATION_HPP
#define TRANSLATEANIMATION_HPP

#include "animation.hpp"

class TranslateAnimation : public Animation
{
private:
    vec3 startPosition, endPosition;

public:
    TranslateAnimation(vec3 startPosition, vec3 endPosition, unsigned int duration);

    mat4 calculateFrameMatrix();
};

#endif // TRANSLATEANIMATION_HPP
