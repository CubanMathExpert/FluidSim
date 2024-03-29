#ifndef MYSTRUCT_H
#define MYSTRUCT_H

#include <glm/glm.hpp>
#include <vector>
#include <iostream>


const glm::vec2 gravity = glm::vec2(0.0f, -9.81f);
const float cutoffDistance = 0.1f;
#define PI 3.141592653589793f
const int num_particles = 5;


struct Particle
{
    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 acceleration = glm::vec2(0.0f, 0.0f);

    // important values to calculate forces
    float pressure = 0;
    float density = 0;
    float density0 = 1000; 

    const float mass = 1.0f;
    const float radius = 0.05f;
    const int segments = 6;

};

    // physics of the particle
    // collisions
    void check_wall_collisions(std::vector<Particle>& particles, float deltaTime);
    bool check_collision(Particle& p1, Particle& p2);
    void handle_collisions(std::vector<Particle>& particles);
    void solve_particle_overlap(Particle& p1, Particle& p2);
    void solve_collision(Particle& p1, Particle& p2);
    void naive_p_p_interaction(std::vector<Particle>& particles);
\
    // movement
    void update_particle(std::vector<Particle>& particles, float dt);
    void update_simulation(std::vector<Particle>& particles, float dt);
    void lennard_jones_force(std::vector<Particle>& particles);
    

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