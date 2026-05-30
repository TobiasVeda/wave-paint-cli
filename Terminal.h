#ifndef WAVE_TERMINAL_H
#define WAVE_TERMINAL_H

#include <string>
#include <termios.h>
#include "Utils.h"

struct window_size{
    int width;
    int height;
};
struct cursor_pos{
    int x;
    int y;
};

class Terminal {
private:
    termios _old_terminal_config;
    termios _new_terminal_config;
    
    int _terminal_width;
    int _terminal_height;
    int _cursor_bound_left;
    int _cursor_bound_right;
    int _cursor_bound_top;
    int _cursor_bound_bottom;
    
    std::string _cursor_type;
    std::string _txt_color;
    std::string _bg_color;
    
    int _cursor_x_pos;
    int _cursor_y_pos;
    int _stored_cursor_x_pos;
    int _stored_cursor_y_pos;
    
    bool _has_file;
    std::string _filename;
    
public:
    Terminal();
    ~Terminal();
    
    void put_cursor(int x, int y); // Bound limited
    void move_cursor(char dir, int amount = 1); // Bound limited
    
    void hide_cursor();
    void show_cursor();
    void save_cursor_pos();
    void load_cursor_pos();
    
    void put_char(std::string c); // Doesn't move cursor
    char get_char(); // Moves cursor on arrow keys then returns \0
    void print(const std::string &str); // Moves cursor
    
    void set_cursor_bounds(int t, int b, int l, int r);
    
    void set_txt_color(ANSI_colors color);
    void set_bg_color(ANSI_colors color);
    
    window_size get_window_size() const;
    cursor_pos get_cursor_pos() const;
    
private:
    void _cout(auto... args);
    int _visible_width_utf8(const std::string &str);
};
extern Terminal terminal;

#endif //WAVE_TERMINAL_H