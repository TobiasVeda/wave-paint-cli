#include "Process.h"
#include "Keymap.h"
#include "Terminal.h"

Process::Process() {
    _brush = new Brush();
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
            _brush->change_color(Keymap::key_to_color(c));
            draw_menu_background();
            draw_shade_options();
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
        if (Keymap::is_save_key(c)) {
            terminal.save_terminal();
            continue;
        }
        if (Keymap::is_load_key(c)) {
            terminal.load_terminal();
            draw_menu();
            continue;
        }
    }
}

void Process::unlock() const {
    terminal.save_cursor_pos();
    auto winsize = terminal.get_window_size();
    terminal.set_cursor_bounds(1, winsize.height, 1, winsize.width);
}

void Process::lock() const {
    auto winsize = terminal.get_window_size();
    terminal.set_cursor_bounds(3, winsize.height -1, 1, winsize.width);
    terminal.load_cursor_pos();
}

void Process::draw_menu() const {
    draw_menu_background();
    draw_color_options();
    draw_shade_options();
    terminal.put_cursor(1, 3);
    draw_coords();
    draw_save_options();
}


void Process::draw_menu_background() const {
    unlock();
    terminal.set_bg_color(BLACK);
    terminal.put_cursor(1, 1);
    auto winsize = terminal.get_window_size();
    
    for (int i = 1; i < 3; ++i) {
        terminal.put_cursor(1, i);
        for (int j = 1; j <= winsize.width; ++j) {
            if (j == 1 || (j >= 18 && j <= 19) || (j >= 34 && j <= winsize.width -7) || j == winsize.width) {
                _brush->paint();
            }
            terminal.move_cursor('r');
        }
    }

    terminal.put_cursor(1, winsize.height);
    for (int i = 1; i <= winsize.width; ++i) {
        if (i < winsize.width -10 || i == winsize.width) {
            _brush->paint();
        }
        terminal.move_cursor('r');
    }
    
    terminal.set_txt_color(BLACK);
    terminal.put_cursor(2, winsize.height);
    terminal.set_bg_color(WHITE);
    terminal.print("q:quit");
    lock();
}

void Process::draw_color_options() const {
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

void Process::draw_shade_options() const {
    unlock();
    terminal.put_cursor(20, 1);  
    terminal.set_bg_color(_brush->current_color());
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

void Process::draw_coords() const {
    unlock();
    terminal.set_txt_color(BLACK);
    terminal.set_bg_color(WHITE);
    auto pos = terminal.get_cursor_pos();
    std::string x = "x:" + std::to_string(pos.x);
    std::string y = "y:" + std::to_string(pos.y -2);
    auto winsize = terminal.get_window_size();
    
    terminal.put_cursor(winsize.width-10, winsize.height);
    terminal.print("          ");
    terminal.put_cursor(winsize.width-10, winsize.height);
    terminal.print(x);
    terminal.put_cursor(winsize.width-5, winsize.height);
    terminal.print(y);
    lock();
}

void Process::draw_save_options() const {
    unlock();
    auto winsize = terminal.get_window_size();
    terminal.put_cursor(winsize.width-6, 1);
    terminal.set_txt_color(BLACK);
    terminal.set_bg_color(WHITE);
    terminal.print("s:save");
    terminal.put_cursor(winsize.width-6, 2);
    terminal.print("l:load");
    lock();
}
