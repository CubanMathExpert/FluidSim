#ifndef MYSTRUCT_H
#define MYSTRUCT_H

#include <glm/glm.hpp>

struct Particle
{
    glm::vec3 position;
    glm::vec3 velocity;
    const float radius = 0.05f;
    const int segments = 20;

    bool isStuck; // used later maybe
};

// physics of the particle
void checkEdgeCollisions(Particle particle, float deltaTime);


#endif // MYSTRUCT_H