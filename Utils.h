#ifndef WAVE_UTILS_H
#define WAVE_UTILS_H

#define CLEAR_SCREEN "\033[2J"

#define CURSOR_BOX_BLINK "\033[1 q"
#define CURSOR_BAR_BLINK "\033[5 q"

#define HIDE_CURSOR "\x1B[?25l"
#define SHOW_CURSOR "\x1B[?25h"
#define SAVE_CURSOR_POS "\x1B[s"
#define LOAD_CURSOR_POS "\x1B[u"

#define TXT_BLACK "\033[30m"
#define TXT_RED "\033[31m"
#define TXT_GREEN "\033[32m"
#define TXT_YELLOW "\033[33m"
#define TXT_BLUE "\033[34m"
#define TXT_MAGENTA "\033[35m"
#define TXT_CYAN "\033[36m"
#define TXT_WHITE "\033[37m"

#define TXT_ALT_BLACK "\033[0;90m"
#define TXT_ALT_RED "\033[0;91m"
#define TXT_ALT_GREEN "\033[0;92m"
#define TXT_ALT_YELLOW "\033[0;93m"
#define TXT_ALT_BLUE "\033[0;94m"
#define TXT_ALT_MAGENTA "\033[0;95m"
#define TXT_ALT_CYAN "\033[0;96m"
#define TXT_ALT_WHITE "\033[0;97m"

#define BG_BLACK "\033[40m"
#define BG_RED "\033[41m"
#define BG_GREEN "\033[42m"
#define BG_YELLOW "\033[43m"
#define BG_BLUE "\033[44m"
#define BG_MAGENTA "\033[45m"
#define BG_CYAN "\033[46m"
#define BG_WHITE "\033[47m"

#define BG_ALT_BLACK "\033[0;100m"
#define BG_ALT_RED "\033[0;101m"
#define BG_ALT_GREEN "\033[0;102m"
#define BG_ALT_YELLOW "\033[0;103m"
#define BG_ALT_BLUE "\033[0;104m"
#define BG_ALT_MAGENTA "\033[0;105m"
#define BG_ALT_CYAN "\033[0;106m"
#define BG_ALT_WHITE "\033[0;107m"

enum ANSI_colors {
    BLACK,    ALT_BLACK,
    RED,      ALT_RED, 
    GREEN,    ALT_GREEN,
    YELLOW,   ALT_YELLOW,
    BLUE,     ALT_BLUE,
    MAGENTA,  ALT_MAGENTA,
    CYAN,     ALT_CYAN,
    WHITE,    ALT_WHITE
};

enum shades {
    SHADE_1,  // ▓ WHITE
    SHADE_2,  // ▒ WHITE
    SHADE_3,  // ░ WHITE
    SHADE_4,  //
    SHADE_5,  // ░ BLACK
    SHADE_6,  // ▒ BLACK
    SHADE_7   // ▓ BLACK
};


#endif //WAVE_UTILS_H