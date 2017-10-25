#include "maze.h"
#include <cstdlib>
#include <iostream>
#include <time.h>
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_primitives.h"

namespace csis3700
{
maze::maze(int n, int w, int h)
{
    row = n;
    col = n;
    width = w;
    height = h;
    box_width = width / row;
    box_height = height / col;
    x_position = 0;
    y_position = 0;
}

void maze::generate_maze()
{
    srand (time(NULL));
    int rdm;
    grid = new int* [row];
    for(int i = 0; i < row; i++)
    {
        grid[i] = new int[col];
    }

    for(int r = 0; r < row; r++)
    {
        for(int c = 0; c < col; c++)
        {
            rdm = rand() % 5 + 1;
            if(r == 0 && c == 0) // Start and End are hallways
            {
                grid[r][c] = start_maze;
            }
            else if (r == row-1 && c == col-1)
            {
                grid[r][c] = end_maze;
            }
            else if (rdm == 5)
            {
                grid[r][c] = wall;
            }
            else
            {
                grid[r][c] = hallway;
            }

        }

    }
}

void maze::draw_maze()
{
    al_clear_to_color(al_map_rgb(255,255,255));

    for(int r = 0; r < row; r++)
    {
        for(int c = 0; c < col; c++)
        {
            if(grid[r][c] == start_maze)
            {
                al_draw_filled_rectangle(x_position, y_position, x_position + box_width, y_position + box_height, al_map_rgb(0,0,255));
                x_position += box_width;
                if (x_position >= width)
                    x_position = 0;
            }
            else if (grid[r][c] == end_maze)
            {
                al_draw_filled_rectangle(x_position, y_position, x_position + box_width, y_position + box_height, al_map_rgb(0,0,255));
                x_position += box_width;
                if (x_position >= width)
                    x_position = 0;
            }
            else if (grid[r][c] == wall)
            {
                al_draw_filled_rectangle(x_position, y_position, x_position + box_width, y_position + box_height, al_map_rgb(0,0,0));
                x_position += box_width;
                if (x_position >= width)
                    x_position = 0;
            }
            else if (grid[r][c] == hallway)
            {
                al_draw_filled_rectangle(x_position, y_position, x_position + box_width, y_position + box_height, al_map_rgb(255,255,255));
                x_position += box_width;
                if (x_position >= width)
                    x_position = 0;
            }
            else if (grid[r][c] == on_path)
            {
                al_draw_filled_rectangle(x_position, y_position, x_position + box_width, y_position + box_height, al_map_rgb(0,255,0));
                x_position += box_width;
                if (x_position >= width)
                    x_position = 0;
            }
            else
            {
                al_draw_filled_rectangle(x_position, y_position, x_position + box_width, y_position + box_height, al_map_rgb(255,0,0));
                x_position += box_width;
                if (x_position >= width)
                    x_position = 0;
            }
        }
        y_position += box_height;
        if(y_position >= height)
            y_position = 0;

        //al_flip_display();
    }
    al_flip_display();
}

void maze::mark(int r, int c)
{
    grid[r][c] = on_path;
}

void maze::unmark(int r, int c)
{
    grid[r][c] = dead_end;
}

bool maze::valid(int r, int c)
{
    if(r < 0 || c < 0)
    {
        return false;
    }
    else if (r >= row || c >= col)
    {
        return false;
    }
    return true;
}

bool maze::unvisited(int r, int c)
{
    if (grid[r][c] == start_maze || grid[r][c] == hallway || grid[r][c] == end_maze)
        return true;
    else
        return false;
}

bool maze::isEnd(int r, int c)
{
    return (grid[r][c] == grid[row-1][col-1]);
}

bool maze::traverse(int r, int c)
{
    draw_maze();
    bool done = false;
    if (valid(r,c) && unvisited(r,c))
    {
        mark(r,c);

        if (isEnd(r,c))
        {
            done = true;
        }
        else
        {
            done = traverse(r+1,c);// try down

            if (!done)
            {
                done = traverse(r,c+1); // try right
            }
            if (!done)
            {
                done = traverse(r-1,c); // try up
            }
            if (!done)
            {
                done = traverse(r,c-1); // try left
            }
        }
        if (!done)
        {
            unmark(r,c);

        }
    }
    return done;
}
}

