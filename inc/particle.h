#ifndef MYSTRUCT_H
#define MYSTRUCT_H

#include <glm/glm.hpp>

const glm::vec2 gravity = glm::vec2(0.0f, -9.81f);
#define PI 3.141592653589793f


struct Particle
{
    glm::vec2 position;
    glm::vec2 velocity;
    const float radius = 0.01f;
    const int segments = 20;

    bool isStuck; // used later maybe

};

    // physics of the particle
    void checkEdgeCollisions(Particle& particle, float deltaTime);
    void updateParticles(Particle& Particle, float deltaTime);


#endif // MYSTRUCT_H