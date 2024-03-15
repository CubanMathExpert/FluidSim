#include "particle.h"

float dragFactor = 0.999f;

void checkEdgeCollisions(Particle& particle, float deltaTime)
{
    if (particle.position.x - particle.radius < -4.0f || particle.position.x + particle.radius > 4.0f)
    {
            particle.velocity.x *= -1.0f; // invert x velo
    }
    if (particle.position.y < (-3.0f + particle.radius) || particle.position.y > (3.0 - particle.radius))
    {
            particle.velocity.y *= -1.0f; // invert x velo
    }
}

void updateParticles(Particle& particle, float deltaTime)
{
        // euler implicite method
        particle.velocity.x *= dragFactor;
        particle.velocity += gravity * deltaTime;
        particle.position += particle.velocity * deltaTime;
}



