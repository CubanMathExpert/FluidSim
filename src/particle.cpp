#include "particle.h"

// METHODS for parcle fluids
// Smoothed Particle Hydrodynamics (SPH)
// Marker and Cell (MAC)
//      http://plaza.ufl.edu/ebrackear/
//      https://cg.informatik.uni-freiburg.de/intern/seminar/gridFluids_fluid_flow_for_the_rest_of_us.pdf

float dragFactor = 0.999f;

void update_simulation(std::vector<Particle>& particles, float dt)
{
    handle_collisions(particles);
    update_particle(particles, dt);
    update_densities(particles);
}

void update_particle(std::vector<Particle>& particles, float dt)
{
    for (Particle& particle : particles)
    {
    // euler implicit method : xf = xi + v * deltaTime
        particle.position = particle.position + particle.velocity * dt; // update the position
        particle.velocity = particle.velocity + gravity * dt; 
        calculate_density(particle, particles); 
        calculate_pressure(particles);
        calculatePressureForce(particles);
        //glm::vec2 pressure_force = calculate_pressure_force(particle, particles);
        //glm::vec2 pressure_acceleration = pressure_force / particle.density;
        //particle.velocity +=  pressure_acceleration * dt;
    }
}

void handle_collisions(std::vector<Particle>& particles)
{
    // handle the collision with edges
    check_wall_collisions(particles, 0.0f);

}

// density
float smoothing_kernel(float r, float d)
{
    float volume = PI * pow(r, 8) / 4;
    float value = std::max(0.0f , r * r - d * d);
    return value * value * value / volume;
}

float smoothing_kernel_derivative(float r, float d)
{
    if (d >= r) return 0;
    float f = r * r  - d * d;
    float scale = -24 / (PI * pow(r, 8));
    return scale * d * f * f;
}

float calculate_density(Particle& p, std::vector<Particle>& particles)
{
    float density = 0;
    for (Particle& neightbor_p : particles)
    {
        float d = glm::length(neightbor_p.position - p.position);
        float influence = smoothing_kernel(smoothing_radius, d);
        density += neightbor_p.mass * influence;
    }
    return density;
}

void calculatePressureForce(std::vector<Particle>& particles) 
{
    for (auto& particle : particles) 
    {
        glm::vec2 pressureForce(0.0f);
        for (const auto& neighbor : particles) 
        {
            if (&particle != &neighbor) 
            {
                glm::vec2 direction = glm::normalize(particle.position - neighbor.position);
                float distance = glm::distance(particle.position, neighbor.position);
                float r = particle.radius;
                float d = distance;
                
                float kernel_derivative = smoothing_kernel_derivative(r, d);
                pressureForce += direction * ((particle.pressure + neighbor.pressure) / (2.0f * neighbor.density)) * kernel_derivative;
            }
        }
        particle.acceleration -= pressureForce / particle.density;
    }
}

void calculate_pressure(std::vector<Particle>& particles)
{
    const float stiffness = 1000.0f;
    for (Particle& p : particles)
    {
        p.pressure = convert_dens2pressure(p.density);
    }

}

void update_densities(std::vector<Particle>& particles)
{
    for (Particle& p : particles)
    {
        p.density = calculate_density(p, particles);
    }
}

float convert_dens2pressure(float density)
{
    float target_density = 2.75f;
    float pressure_multiplier = 0.5f;
    
    float dens_error =  density - target_density;
    float pressure = dens_error * pressure_multiplier;
    return pressure;
}

glm::vec2 calculate_pressure_force(Particle& p, std::vector<Particle>& particles)
{
    glm::vec2 pressure_force = glm::vec2(0.0f);

    for (Particle& neighbor_p : particles)
    {
        if (&p != &neighbor_p)
        {
            float d = glm::length(neighbor_p.position - p.position);
            glm::vec2 direction = (neighbor_p.position - p.position) / d;
            float slope = smoothing_kernel_derivative(smoothing_radius, d);
            float density = neighbor_p.density;
            pressure_force += -convert_dens2pressure(density) * direction * slope * neighbor_p.mass / density;
        }
    }

    return pressure_force;
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
            particle.velocity.x *= -0.3f; // invert y velo and loss of energy
        }
        if (particle.position.x > (4.0f - particle.radius))
        {
            particle.position.x = 4.0f - particle.radius;
            particle.velocity.x *= -0.3f;
        }
        // collision on y axis for edge of vp
        if (particle.position.y < (-3.0f + particle.radius))
        {
            particle.position.y = -3.0f + particle.radius;
            particle.velocity.y *= -0.3f; 
        }
        if (particle.position.y > (3.0 - particle.radius))
        {
            particle.position.y = 3.0f - particle.radius;
            particle.velocity.y *= -0.3f;
        }
            
    }
        
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










