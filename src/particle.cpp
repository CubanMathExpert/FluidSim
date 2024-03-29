#include "particle.h"

// METHODS for parcle fluids
// Smoothed Particle Hydrodynamics (SPH)
// Marker and Cell (MAC)
//      http://plaza.ufl.edu/ebrackear/
//      https://cg.informatik.uni-freiburg.de/intern/seminar/gridFluids_fluid_flow_for_the_rest_of_us.pdf

float dragFactor = 0.999f;

void checkWallCollisions(std::vector<Particle>& particles, float deltaTime)
{
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

void updateParticles(Particle& particle, float deltaTime)
{

        
        // euler implicite method
        particle.position += particle.velocity * deltaTime;
        particle.velocity += gravity * deltaTime;
        particle.velocity.x *= dragFactor;
}

// just a regular O(n2) collision check
void naiveCollisionCheck(std::vector<Particle>& particles)
{
    for (Particle& particle1: particles)
    {
        //particleData(particles);
        for (Particle& particle2: particles)
        {
            // don't check particle with herself
            if (particle1.position != particle2.position)
            {
                // distance between two particles
                glm::vec2 distanceVect = particle1.position - particle2.position;
                float d2 = glm::dot(distanceVect, distanceVect);

                // collision detected
                if (d2 < 4.0f * particle1.radius * particle2.radius)
                {
                    // change velocity of particles
                    particle1.velocity = particle1.velocity - glm::dot(particle1.velocity - particle2.velocity, particle1.position - particle2.position) / d2 * distanceVect;
                    particle2.velocity = particle2.velocity - glm::dot(particle2.velocity - particle1.velocity, particle2.position - particle1.position) / d2 * (-1.0f * distanceVect);
                        
                    // this code separates the particles when they're overlapping
                    float dx = particle2.position.x - particle1.position.x;
                    float dy = particle2.position.y - particle1.position.y;
                    float d = sqrt(d2);

                    float overlap = d - (2.0f * particle1.radius);
                        
                    float dirX = dx / d;
                    float dirY = dy / d;

                    float dispX = dirX * overlap / 2.0f;
                    float dispY = dirY * overlap / 2.0f;

                    particle1.position.x += dispX;
                    particle1.position.y += dispY;
                    particle2.position.x -= dispX;
                    particle2.position.y -= dispY; 

                }
            }
        }
    }
}





