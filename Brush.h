#ifndef WAVE_BRUSH_H
#define WAVE_BRUSH_H

#include <string>

#include "Utils.h"

class Brush {
private:
    std::string _char;
    ANSI_colors _color;
    shades _shade;
public:
    Brush();
    void paint();
    void change_color(ANSI_colors color);
    void change_shade(shades shade);
};



#endif //WAVE_BRUSH_H