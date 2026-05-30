#include "Process.h"

#include "Keymap.h"
#include "Terminal.h"

Process::Process() {
    _brush = new Brush();
    auto winsize = terminal.get_window_size();
    _width = winsize.width;
    _height = winsize.height;
    terminal.put_cursor(1, 3);
}

Process::~Process() {
    delete _brush;
}

void Process::start() {
    for (char c = terminal.get_char(); !Keymap::is_quit_key(c); c = terminal.get_char()) {
        if (c == '\0') {
            draw_coords();
            continue;
        }
        if (Keymap::is_color_key(c)) {
            ANSI_colors color = Keymap::key_to_color(c);
            _brush->change_color(color);
            draw_menu_background();
            draw_shade_options(color);
            continue;
        }
        if (Keymap::is_shade_key(c)) {
            _brush->change_shade(Keymap::key_to_shade(c));
            draw_menu_background();
            continue;
        }
        if (Keymap::is_paint_key(c)) {
            _brush->paint();
            continue;
        }
    }
}

void Process::unlock() {
    terminal.save_cursor_pos();
    terminal.set_cursor_bounds(1, _height, 1, _width);
}

void Process::lock() {
    terminal.set_cursor_bounds(3, _height -1, 1, _width);
    terminal.load_cursor_pos();
}

void Process::draw_menu() {
    draw_menu_background();
    draw_color_options();
    draw_shade_options(WHITE);
    terminal.put_cursor(1, 3);
    draw_coords();
}


void Process::draw_menu_background() {
    unlock();
    terminal.set_bg_color(BLACK);
    terminal.put_cursor(1, 1);
    
    for (int i = 1; i < 3; ++i) {
        terminal.put_cursor(1, i);
        for (int j = 1; j <= _width; ++j) {
            if (j == 1 || (j >= 18 && j <= 19) || j >= 34) {
                _brush->paint();
            }
            terminal.move_cursor('r');
        }
    }

    terminal.put_cursor(1, _height);
    for (int i = 1; i <= _width; ++i) {
        if (i < _width -10 || i == _width) {
            _brush->paint();
        }
        terminal.move_cursor('r');
    }
    
    terminal.set_txt_color(BLACK);
    terminal.put_cursor(2, _height);
    terminal.set_bg_color(WHITE);
    terminal.print("q:quit");
    lock();
}

void Process::draw_color_options() {
    unlock();
    terminal.put_cursor(2, 1);
    
    terminal.set_txt_color(WHITE);
    terminal.set_bg_color(RED);
    terminal.print("r ");
    terminal.set_bg_color(GREEN);
    terminal.print("g ");
    terminal.set_bg_color(BLUE);
    terminal.print("b ");
    terminal.set_txt_color(BLACK);
    terminal.set_bg_color(WHITE);
    terminal.print("w ");
    terminal.set_txt_color(WHITE);
    terminal.set_bg_color(CYAN);
    terminal.print("c ");
    terminal.set_bg_color(MAGENTA);
    terminal.print("m ");
    terminal.set_bg_color(YELLOW);
    terminal.print("y ");
    terminal.set_bg_color(BLACK);
    terminal.print("k ");
    
    terminal.put_cursor(2, 2);
    terminal.set_txt_color(WHITE);

    terminal.set_txt_color(WHITE);
    terminal.set_bg_color(ALT_RED);
    terminal.print("R ");
    terminal.set_bg_color(ALT_GREEN);
    terminal.print("G ");
    terminal.set_bg_color(ALT_BLUE);
    terminal.print("B ");
    terminal.set_txt_color(BLACK);
    terminal.set_bg_color(ALT_WHITE);
    terminal.print("W ");
    terminal.set_txt_color(WHITE);
    terminal.set_bg_color(ALT_CYAN);
    terminal.print("C ");
    terminal.set_bg_color(ALT_MAGENTA);
    terminal.print("M ");
    terminal.set_bg_color(ALT_YELLOW);
    terminal.print("Y ");
    terminal.set_bg_color(ALT_BLACK);
    terminal.print("K ");
    
    lock();
}

void Process::draw_shade_options(ANSI_colors colors) {
    unlock();
    terminal.put_cursor(20, 1);
    terminal.set_bg_color(colors);
    terminal.set_txt_color(WHITE);
    terminal.print("▓▓▒▒░░  ");
    terminal.set_txt_color(BLACK);
    terminal.print("░░▒▒▓▓");
    
    terminal.put_cursor(20, 2);
    terminal.set_bg_color(WHITE);
    terminal.set_txt_color(BLACK);
    terminal.print("1 2 3 4 5 6 7 ");
    lock();
}

void Process::draw_coords() {
    unlock();
    terminal.set_txt_color(BLACK);
    terminal.set_bg_color(WHITE);
    auto pos = terminal.get_cursor_pos();
    std::string x = "x:" + std::to_string(pos.x);
    std::string y = "y:" + std::to_string(pos.y -2);
    
    terminal.put_cursor(_width-10, _height);
    terminal.print("          ");
    terminal.put_cursor(_width-10, _height);
    terminal.print(x);
    terminal.put_cursor(_width-5, _height);
    terminal.print(y);
    lock();
}
