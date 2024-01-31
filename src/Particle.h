#pragma once

#include <glm/glm.hpp>
#include <vector>

struct Particle {
    glm::vec3 position; // in 3d I guess that would be a vec4
    glm::vec3 velocity; // same thing for this
    glm::vec4 color; //Color is given by a vec4
    float radius;
};

//function declarations
void initializeParticles(std::vector<Particle>& particles, int nbParticles, float xPos, float yPos);
/*
    intialize the vector containing all the Particle objects and give the amount of particles to be instantiated
*/
void updateParticles(std::vector<Particle>& particles, float deltaTime);
/*
    same vector containing all the particles, but now we add the time factor so that we get a real-time update of the particles
    position
    velocity
    (color if needed)
*/
