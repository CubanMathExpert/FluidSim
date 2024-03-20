#ifndef MYSTRUCT_H
#define MYSTRUCT_H

#include <glm/glm.hpp>
#include <vector>

const glm::vec2 gravity = glm::vec2(0.0f, -9.81f);
#define PI 3.141592653589793f



struct Particle
{
    glm::vec2 position;
    glm::vec2 velocity;
    const float mass = 1.0f;
    const float radius = 0.2f;
    const int segments = 6;

    bool isStuck; // used later maybe
};

    // physics of the particle
    void checkEdgeCollisions(std::vector<Particle>& particles, float deltaTime);
    void updateParticles(Particle& particle, float deltaTime);


#endif // MYSTRUCT_H