#include "Keymap.h"

bool Keymap::is_color_key(const char c) {
    return (
        c == 'k' || c== 'r' || c == 'g' || c == 'y' || c == 'b' || c == 'm' || c == 'c' || c == 'w' ||
        c == 'K' || c== 'R' || c == 'G' || c == 'Y' || c == 'B' || c == 'M' || c == 'C' || c == 'W'
        );
}

bool Keymap::is_shade_key(const char c) {
    const auto uc = static_cast<unsigned char>(c);
    const int n = uc - '0';
    return (n >= 1 && n <=7);
}

bool Keymap::is_paint_key(const char c) {
    return c == ' ';
}

bool Keymap::is_quit_key(const char c) {
    return c == 'q';
}

ANSI_colors Keymap::key_to_color(const char c) {
    switch (c) {
        case 'k':
            return BLACK;
        case 'r':
            return RED;
        case 'g':
            return GREEN;
        case 'y':
            return YELLOW;
        case 'b':
            return BLUE;
        case 'm':
            return MAGENTA;
        case 'c':
            return CYAN;
        case 'w':
            return WHITE;
        case 'K':
            return ALT_BLACK;
        case 'R':
            return ALT_RED;
        case 'G':
            return ALT_GREEN;
        case 'Y':
            return ALT_YELLOW;
        case 'B':
            return ALT_BLUE;
        case 'M':
            return ALT_MAGENTA;
        case 'C':
            return ALT_CYAN;
        case 'W':
            return ALT_WHITE;
        default:
            return WHITE;
    }
}

shades Keymap::key_to_shade(char c) {
    switch (c) {
        case '1':
            return SHADE_1;
        case '2':
            return SHADE_2;
        case '3':
            return SHADE_3;
        case '4':
            return SHADE_4;
        case '5':
            return SHADE_5;
        case '6':
            return SHADE_6;
        case '7':
            return SHADE_7;
        default:
            return SHADE_4;
    }
}
