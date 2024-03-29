#ifndef MYSTRUCT_H
#define MYSTRUCT_H

#include <glm/glm.hpp>
#include <vector>
#include <iostream>


const glm::vec2 gravity = glm::vec2(0.0f, -9.81f);
const float cutoffDistance = 0.1f;
#define PI 3.141592653589793f
const int num_particles = 500;


struct Particle
{
    glm::vec2 position;
    glm::vec2 velocity;
    float pressure = 0;
    float density = 0;
    float density0 = 1000; 
    const float mass = 1.0f;
    const float radius = 0.05f;
    const int segments = 6;

};

    // physics of the particle
    void checkWallCollisions(std::vector<Particle>& particles, float deltaTime);
    void updateParticles(Particle& particle, float deltaTime);
    void naiveCollisionCheck(std::vector<Particle>& particles);
    

    // SPH
    /*
        - Neighbor search
        - Density / Pressure
        - Forces (pressure, viscosity, gravity, external forces)
        - New velocity, New position
    */
   //void searchNeighbors(std::vector<Particle> particles);



#endif // MYSTRUCT_H