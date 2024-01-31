#include "Particle.h"
#include <stdlib.h>

void initializeParticles(std::vector<Particle>& particles, int nbParticles, float xPos, float yPos) {
    for (int i = 0; i < nbParticles; i++)
    {
        Particle particle; //Create particle obj   
        //float randomXPosition = xPos + rand() % 50;
        //float randomYPosition = yPos + rand() % 50; 

        //Give inital values to each of the properties 
        particle.position = glm::vec3(xPos, yPos, 0.0f);
        particle.color = glm::vec4(0.25f, 0.5f, 0.75f, 1.0f);
        particle.velocity = glm::vec3(0.0f, 0.0f, 0.0f);
        particle.radius = 10.0f;
    }
    
}

void updateParticles(std::vector<Particle>& particles, float deltaTime) {
    for (auto& particle : particles)
    {
        //Update particle position based on velocity (if velo 10 than every second he gains 10 units in that direction)
        particle.position += particle.velocity * deltaTime;
    }
    
}