#include "particle.h"

// METHODS for parcle fluids
// Smoothed Particle Hydrodynamics (SPH)
// Marker and Cell (MAC)
//      http://plaza.ufl.edu/ebrackear/
//      https://cg.informatik.uni-freiburg.de/intern/seminar/gridFluids_fluid_flow_for_the_rest_of_us.pdf

float dragFactor = 0.999f;

void checkEdgeCollisions(std::vector<Particle>& particles, float deltaTime)
{
        for (auto& particle: particles)
        {
                if (particle.position.x - particle.radius < -4.0f || particle.position.x + particle.radius > 4.0f)
                {
                        particle.velocity.x *= -0.70f; // invert x velo
                }
                if (particle.position.y < (-3.0f + particle.radius) || particle.position.y > (3.0 - particle.radius))
                {
                        particle.velocity.y *= -0.70f; // invert y velo
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





