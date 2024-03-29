#include "particle.h"

// METHODS for parcle fluids
// Smoothed Particle Hydrodynamics (SPH)
// Marker and Cell (MAC)
//      http://plaza.ufl.edu/ebrackear/
//      https://cg.informatik.uni-freiburg.de/intern/seminar/gridFluids_fluid_flow_for_the_rest_of_us.pdf

float dragFactor = 0.999f;

void update_simulation(std::vector<Particle>& particles, float dt)
{
    lennard_jones_force(particles);
    handle_collisions(particles);
    update_particle(particles, dt);
}

void handle_collisions(std::vector<Particle>& particles)
{
    // handle the collision with edges
    check_wall_collisions(particles, 0.0f);

    // naive implementation for now
    //naive_p_p_interaction(particles);
}

bool check_collision(Particle& p1, Particle& p2)
{
    // distance between two particles
    glm::vec2 dist = p1.position - p2.position;
    float d2 = glm::dot(dist, dist);

    //check if there is a collision
    if (d2 < 4.0f * p1.radius * p2.radius) return true;
    else return false;
}

void solve_collision(Particle& p1, Particle& p2)
{
    // Calculate combined mass
    float combinedMass = p1.mass + p2.mass;

    // Calculate final velocity
    glm::vec2 finalVelocity = (p1.mass * p1.velocity + p2.mass * p2.velocity) / combinedMass;

    // Set final velocity for both particles
    p1.velocity = finalVelocity;
    p2.velocity = finalVelocity;
}

void solve_particle_overlap(Particle& p1, Particle& p2)
{
    glm::vec2 dist = p1.position - p2.position;
    float r2 = glm::dot(dist, dist);

    if (r2 < 4.0f * p1.radius * p2.radius)
    {
        float dx = p2.position.x - p1.position.x;
        float dy = p2.position.y - p1.position.y;
        float d = sqrt(r2);

        float overlap = d -(2.0f * p1.radius);

        float dirX = dx / d;
        float dirY = dy / d;

        float dispX = dirX * overlap / 2.0f;
        float dispY = dirY * overlap / 2.0f;

        p1.position.x += dispX;
        p1.position.y += dispY;
        p2.position.x -= dispX;
        p2.position.y -= dispY;
    }
    
}

void naive_p_p_interaction(std::vector<Particle>& particles)
{
    // naive implementation for now
    for (Particle& p1 : particles)
    {
        for (Particle& p2 : particles)
        {
            if (p1.position != p2.position)
            {
                if (check_collision(p1, p2))
                {
                    solve_particle_overlap(p1,p2);
                    solve_collision(p1, p2);
                }
            }
        }
    }
}




void check_wall_collisions(std::vector<Particle>& particles, float deltaTime)
{

    // TODO FIX THIS COLLISION BY CHECKING NEXT POSITION AND IF
    // IT IS PAST THE WALL THEN JUST MAKE IT HIT THE WALL.
    for (Particle& particle: particles)
    {
        // collision on x axis for edge of vp
        if (particle.position.x < (-4.0f + particle.radius))
        {
            particle.position.x = -4.0f + particle.radius; // bring back particle into the screen if the predicted position is beyond the screen (stuck)
            particle.velocity.x *= -0.1f; // invert y velo and loss of energy
        }
        if (particle.position.x > (4.0f - particle.radius))
        {
            particle.position.x = 4.0f - particle.radius;
            particle.velocity.x *= -0.1f;
        }
        // collision on y axis for edge of vp
        if (particle.position.y < (-3.0f + particle.radius))
        {
            particle.position.y = -3.0f + particle.radius;
            particle.velocity.y *= -0.1f; 
        }
        if (particle.position.y > (3.0 - particle.radius))
        {
            particle.position.y = 3.0f - particle.radius;
            particle.velocity.y *= -1.0f;
        }
            
    }
        
}
// naive implementation of it no grid yet
void lennard_jones_force(std::vector<Particle>& particles)
{
    // control parameters
    int k1 = 1;
    int k2 = 1;
    int m = 4;
    int n = 2;

    for (Particle& p1 : particles)
    {
        for (Particle& p2 : particles)
        {
            glm::vec2 dist = p1.position - p2.position;
            float d = glm::distance(p1.position, p2.position);
            std::cout << k1/pow(d, m) - k2/pow(d, n) << std::endl;

            if (p1.position != p2.position)
            {
                p1.acceleration += float((k1 / pow(d, m)) - (k2 / pow(d, n))) * dist / d;
            }
        }
        //std::cout << p1.acceleration.x << " " << p1.acceleration.y << std::endl;
    }
}

void update_particle(std::vector<Particle>& particles, float dt)
{
    for (Particle& particle : particles)
    {
    // euler implicit method : xf = xi + v * deltaTime
        particle.position = particle.position + particle.velocity * dt; // update the position
        particle.velocity = particle.velocity + particle.acceleration * dt;            
    }
}








