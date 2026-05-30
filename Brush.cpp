#include "Brush.h"

#include "Terminal.h"

Brush::Brush() {
    _char = " ";
    _color = WHITE;
    _shade = SHADE_4;
}

void Brush::paint() {
    terminal.set_bg_color(_color);
    switch (_shade) {
        case SHADE_1:
            terminal.set_txt_color(WHITE);
            break;
        case SHADE_2:
            terminal.set_txt_color(WHITE);
            break;
        case SHADE_3:
            terminal.set_txt_color(WHITE);
            break;
        case SHADE_4:
            terminal.set_txt_color(WHITE);
            break;
        case SHADE_5:
            terminal.set_txt_color(BLACK);
            break;
        case SHADE_6:
            terminal.set_txt_color(BLACK);
            break;
        case SHADE_7:
            terminal.set_txt_color(BLACK);
            break;
    }
    terminal.put_char(_char);
}

void Brush::change_color(const ANSI_colors color) {
    _color = color;
}

void Brush::change_shade(const shades shade) {
    _shade = shade;
    switch (shade) {
        case SHADE_1:
            _char = "▓";
            break;
        case SHADE_2:
            _char = "▒";
            break;
        case SHADE_3:
            _char = "░";
            break;
        case SHADE_4:
            _char = " ";
            break;
        case SHADE_5:
            _char = "░";
            break;
        case SHADE_6:
            _char = "▒";
            break;
        case SHADE_7:
            _char = "▓";
            break;
    }
}
