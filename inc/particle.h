#ifndef MYSTRUCT_H
#define MYSTRUCT_H

#include <glm/glm.hpp>
#include <vector>

const glm::vec3 gravity = glm::vec3(0.0f, -9.81f, 0.0f);
#define PI 3.141592653589793f



struct Particle
{
    glm::vec3 position;
    glm::vec3 velocity;
    const float radius = 0.03f;
    const int segments = 6;

    bool isStuck; // used later maybe
};

    // physics of the particle
    void checkEdgeCollisions(std::vector<Particle>& particles, float deltaTime);
    void updateParticles(Particle& particle, float deltaTime);


#endif // MYSTRUCT_H