#include "particle.h"

// METHODS for parcle fluids
// Smoothed Particle Hydrodynamics (SPH)
// Marker and Cell (MAC)
//      http://plaza.ufl.edu/ebrackear/
//      https://cg.informatik.uni-freiburg.de/intern/seminar/gridFluids_fluid_flow_for_the_rest_of_us.pdf

float dragFactor = 0.999f;

//------------------- UPDATE FULL SIM --------------------------------------------------------

void update_simulation(std::vector<Particle>& particles, float dt)
{
    check_wall_collisions(particles, dt);
    //update_particle(particles, dt);
}

void update_particle(std::vector<Particle>& particles, float dt)
{
    for (Particle& particle : particles)
    {
    // euler implicit method : xf = xi + v * deltaTime
        particle.position = particle.position + particle.velocity * dt; // update the position
        particle.velocity = particle.velocity + gravity * dt; 
        //glm::vec2 pressure_force = calculate_pressure_force(particle, particles);
        //glm::vec2 pressure_acceleration = pressure_force / particle.density;
        //particle.velocity +=  pressure_acceleration * dt;
    }
}
//----------------------------- PRESSURE ----------------------------------------------------------

//----------------------------- DENSITY ----------------------------------------------------------

float poly6kernel(float h, float r)
{
    float volume = 315 / (64 * PI * pow(h, 9));
    float value = std::max(0.0f, h * h - r * r); // this ensures that if the distance of particles is higher than smoothing radius we return 0
    return volume * pow(value, 3);
}

void computeDensity(std::vector<Particle>& particles)
{
    // we will not take into consideration the mass of the particles since we have assumed it is = 1
    for (auto& p : particles)
    {
        float result = 0;
        for (const auto& neighbor: particles)
        {
            if (&p != &neighbor)
            {
                float r = glm::length(neighbor.position - p.position);
                result += poly6kernel(smoothing_radius, r);
            }
        }
        p.density = result;
    }
}

//---------------------------- CHECK COLLISIONS --------------------------------------------------------------------------

void check_wall_collisions(std::vector<Particle>& particles, float deltaTime)
{

    // TODO FIX THIS COLLISION BY CHECKING NEXT POSITION AND IF
    // IT IS PAST THE WALL THEN JUST MAKE IT HIT THE WALL.
    for (Particle& particle: particles)
    {
        glm::vec2 new_position = particle.position + particle.velocity * (deltaTime * 1);
        // collision on x axis for edge of vp
        if (new_position.x < (-4.0f + particle.radius))
        {
            particle.position.x = -4.0f + particle.radius; // bring back particle into the screen if the predicted position is beyond the screen (stuck)
            particle.velocity.x *= -0.3f; // invert y velo and loss of energy
        }
        if (new_position.x > (4.0f - particle.radius))
        {
            particle.position.x = 4.0f - particle.radius;
            particle.velocity.x *= -0.3f;
        }
        // collision on y axis for edge of vp
        if (new_position.y < (-3.0f + particle.radius))
        {
            particle.position.y = -3.0f + particle.radius;
            particle.velocity.y *= -0.3f; 
        }
        if (new_position.y > (3.0 - particle.radius))
        {
            particle.position.y = 3.0f - particle.radius;
            particle.velocity.y *= -0.3f;
        }
            
    }
        
}

void handle_collisions(std::vector<Particle>& particles)
{
    // handle the collision with edges
    check_wall_collisions(particles, 0.0f);

}



void initializeParticles(std::vector<Particle>& particles, int num_particles)
{
    int spawn_length = static_cast<int>(std::sqrt(num_particles));
    glm::vec2 offset =  glm::vec2(-3.0f, 2.5f);
    
    int dx = 0;
    int dy = 0;

    for (Particle& p : particles)
    {
        if (dx == spawn_length)
        {
            dy--;
            dx = 0;
        }
        // generate initial position and velocity
        p.position.x = 3.0f * p.radius * dx + offset.x;
        p.position.y = 3.0f * p.radius * dy + offset.y;
        dx++;
    }
}










