#include <iostream>
#include "particle.h"

// vp dimensions they go from -4 to 4 and -3 to 3

struct Grid
{
    // grid dimensions
    const float cell_size = 0.2;
    const int width = static_cast<int>(8 / cell_size);
    const int height = static_cast<int>(6 / cell_size);

    // initialize the grid
    std::vector<std::vector<std::vector<Particle*>>> cells;


    // functions

    // find neighbors for all particles and keep updating 
    void set_neighbors(std::vector<Particle>& particles)
    {
        //int counter = 0;
        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                for (Particle* p1: cells[i][j])
                {
                    for (Particle* p2: cells[i][j])
                    {
                        if (p1->position != p2->position)
                        {
                            //counter++;
                        }
                        
                    }
                }
            }
        }
        //std::cout << counter << std::endl;
    }

    // set the sizes for the grid 
    void create_grid()
    {
        cells.resize(width); // Resize the outer vector to have a size equal to grid.width
        for (int i = 0; i < width; ++i) 
        {
            cells[i].resize(height); // Resize each inner vector to have a size equal to grid.height
        }
    }

    void update_grid(std::vector<Particle>& particles)
    {
        //clear_grid();
        cells.clear();
        create_grid();

        for (Particle& p : particles)
        {
            // check in which cell the particle is
            int cell_x = static_cast<int>((p.position.x + 4) / cell_size);
            int cell_y = static_cast<int>((p.position.y + 3) / cell_size);

            // correct overshooting the value of the cell (sometimes the particle gets pushed outside de window)
            if (cell_x > width - 1) cell_x = width - 1;
            if (cell_y > height - 1) cell_y = height - 1;
            if (cell_x < 0) cell_x = 0;
            if (cell_y < 0) cell_y = 0;

            // insert particle in the cell 
            cells[cell_x][cell_y].push_back(&p);
        }        

    }

    //clear the grid at every iteration
    void clear_grid() 
    {
        for (int i = 0; i < width; ++i) 
        {
            for (int j = 0; j < height; ++j) 
            {
                cells[i][j].clear();
            }
        }
    
    }

    // print grid to the terminal
    void print_grid()
    {
        for (int i = height - 1; i >= 0; i--)
        {
            for (int j = 0; j < width; j++)
            {
                std::cout <<  "|" << cells[j][i].size() << "|";
            }
            std::cout << std::endl;
        }
        std::cout << "\033[2J";
    }

};

// other fuctions for use on grid



