#ifndef WAVE_MAIN_H
#define WAVE_MAIN_H

#include "Brush.h"

class Process {
private:
    
    Brush *_brush;
    
    int _width; // helpers
    int _height; // helpers
    
public:
    Process();
    ~Process();
    
    void start();
    
    void draw_menu();
    
private:
    void draw_menu_background();
    void draw_color_options();
    void draw_shade_options(ANSI_colors colors);
    void draw_coords();
    
    void unlock();
    void lock();
};


#endif //WAVE_MAIN_H