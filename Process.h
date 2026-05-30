#ifndef WAVE_MAIN_H
#define WAVE_MAIN_H

#include "Brush.h"

class Process {
private:
    
    Brush *_brush;
    
public:
    Process();
    ~Process();
    
    void start();
    
    void draw_menu() const;
    
private:
    void draw_menu_background() const;
    void draw_color_options() const;
    void draw_shade_options() const;
    void draw_coords() const;
    void draw_save_options() const;
    
    void unlock() const;
    void lock() const;
};


#endif //WAVE_MAIN_H