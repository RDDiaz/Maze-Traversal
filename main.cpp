#include "maze.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "time.h"

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_primitives.h"

using namespace csis3700;
using namespace std;

//const float FPS = 60;

const size_t WIDTH=800;
const size_t HEIGHT=600;


int main(int argc, char **argv)
{
    /// ALLEGRO INITIALIZERS
    srand(time(NULL));

    if(!al_init())
    {
        cerr << "Failed to initialize allegro!" << endl;
        exit(1);
    }

    if(!al_init_image_addon())
    {
        cerr << "Failed to initialize al_init_image_addon!" << endl;
        exit(1);
    }

    if(!al_install_mouse())
    {
        cerr << "Failed to install mouse." << endl;
        exit(1);
    }

    if(!al_install_keyboard())
    {
        cerr << "Failed to install keyboard." << endl;
        exit(1);
    }

    // This option causes the display to wait for VSYNC before flipping
    // pages. This can help to avoid tearing. Comment this out if you
    // are having refresh problems.
    al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_REQUIRE);

    ALLEGRO_DISPLAY *display = al_create_display(WIDTH, HEIGHT);
    if(!display)
    {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return EXIT_FAILURE;
    }

//    ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
//    if(!timer)
//    {
//        al_show_native_message_box(display, "Error", "Error", "Failed to create timer!",
//                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
//        al_destroy_display(display);
//        return EXIT_FAILURE;
//    }

    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    if(!event_queue)
    {
        al_show_native_message_box(display, "Error", "Error", "Failed to create event queue!",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return EXIT_FAILURE;
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));
    //al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    //al_start_timer(timer);


    al_init_primitives_addon();

    //double time = 0;
    bool redraw = true;

    ALLEGRO_EVENT ev;
    do
    {
        al_wait_for_event(event_queue, &ev);

//        if(ev.type == ALLEGRO_EVENT_TIMER)
//        {
//            redraw = true;
//        }


        if(redraw && al_is_event_queue_empty(event_queue))
        {
            redraw = false;
            //time += 1/FPS;

            int size;
            string file_name = "maze.txt";
            ifstream in(file_name.c_str());

            if(in.good())
            {
                while(in >> size)
                {
                    // File read to size
                }
            }
            else
            {
                cout << "Unable to open file!";
            }

            maze M(size,WIDTH,HEIGHT);

            bool finish = false;

            ALLEGRO_EVENT ev;

            al_wait_for_event(event_queue, &ev);

            al_wait_for_event(event_queue, &ev);
            M.generate_maze();
            M.draw_maze();
            finish = M.traverse(0,0);

            al_rest(3);

        }
    }
    while(ev.type != ALLEGRO_EVENT_DISPLAY_CLOSE);


    //al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);


    return EXIT_SUCCESS;
}
