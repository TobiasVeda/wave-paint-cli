#ifndef WAVE_KEYMAPS_H
#define WAVE_KEYMAPS_H
#include "Utils.h"


class Keymap {
public:
    static bool is_color_key(char c);
    static bool is_shade_key(char c);
    static bool is_paint_key(char c);
    static bool is_quit_key(char c);
    static bool is_save_key(char c);
    static bool is_load_key(char c);
    static ANSI_colors key_to_color(char c);
    static shades key_to_shade(char c);
};


#endif //WAVE_KEYMAPS_H