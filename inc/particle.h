#ifndef MYSTRUCT_H
#define MYSTRUCT_H

#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>    


const glm::vec2 gravity = glm::vec2(0.0f, -9.81f);
#define PI 3.141592653589793f
const float smoothing_radius = 0.03f;
#define gravity glm::vec2(0.0f, -9.81f)
const int num_particles = 1000;


struct Particle
{
    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 acceleration = gravity;

    // important values to calculate forces
    float pressure = 0;
    float density = 0;
    float density0 = 1000; 

    const float mass = 1.0f;
    const float radius = 0.05f;
    const int segments = 6;

    std::vector<Particle> neighbors;


};

    // physics of the particle
    // collisions
    void check_wall_collisions(std::vector<Particle>& particles, float deltaTime);
    void handle_collisions(std::vector<Particle>& particles);
\
    // movement
    void update_particle(std::vector<Particle>& particles, float dt);
    void update_simulation(std::vector<Particle>& particles, float dt);

    // intial spawner
    void initializeParticles(std::vector<Particle>& particles, int num_particles);
    


    ////////////////////////////////////
    // TODO grid functions

    // SPH
    /*
        - Neighbor search
        - Density / Pressure
        - Forces (pressure, viscosity, gravity, external forces)
        - New velocity, New position
    */
   //void searchNeighbors(std::vector<Particle> particles);



#endif // MYSTRUCT_H