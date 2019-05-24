#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

using glm::vec3;
using glm::mat4;

class Animation
{
protected:
    unsigned int currentStep, duration;
    bool paused;

public:
    bool isFinished();
    void restart();
    void pause();
    void resume();

    virtual mat4 calculateFrameMatrix() = 0;
};

#endif // ANIMATION_HPP
