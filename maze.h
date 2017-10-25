#ifndef _MAZE_H
#define _MAZE_H

namespace csis3700
{
    class maze
    {
    public:
        maze(int n, int w, int h);
        void generate_maze();
        void draw_maze();
        void mark(int r, int c);
        void unmark(int r, int c);
        bool valid(int r, int c);
        bool unvisited(int r, int c);
        bool isEnd(int r, int c);
        bool traverse(int r, int c);

    private:
        int **grid;
        int row;
        int col;
        int width;
        int height;
        double box_width;
        double box_height;
        double x_position;
        double y_position;
        const int start_maze = 8;
        const int end_maze = 9;
        const int wall = 0;
        const int hallway = 1;
        const int on_path = 2;
        const int dead_end = 3;
    };
}
#endif // _MAZE_H
