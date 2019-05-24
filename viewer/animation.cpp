#include "animation.hpp"

void Animation::restart()
{
    currentStep = 0;
}

bool Animation::isFinished()
{
    return (currentStep >= duration);
}

void Animation::pause()
{
    paused = true;
}

void Animation::resume()
{
    paused = false;
}
