#include "Terminal.h"
#include "Utils.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <regex>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

Terminal terminal;

Terminal::Terminal() {
    tcgetattr(STDIN_FILENO, &_old_terminal_config);
    _new_terminal_config = _old_terminal_config;
    
    _new_terminal_config.c_lflag = _new_terminal_config.c_lflag & ~ICANON; // Sets ICANON bits in new_terminal to 0
    _new_terminal_config.c_lflag = _new_terminal_config.c_lflag & ~ECHO; // Sets ECHO bits in new_terminal to 0
    
    // Blocks until 1 char is read
    _new_terminal_config.c_cc[VMIN] = 1;
    _new_terminal_config.c_cc[VTIME] = 0;
    
    tcsetattr(STDIN_FILENO, TCSANOW, &_new_terminal_config);
    
    winsize win{};
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
    
    _terminal_width = win.ws_col;
    _terminal_height = win.ws_row;
    _cursor_bound_left = 1;
    _cursor_bound_right = _terminal_width;
    _cursor_bound_top = 1;
    _cursor_bound_bottom = _terminal_height;
    _cursor_type = CURSOR_BOX_BLINK;
    _txt_color = TXT_WHITE;
    _bg_color = BG_BLACK;
    _cursor_x_pos = 1;
    _cursor_y_pos = 1;
    _stored_cursor_x_pos = 1;
    _stored_cursor_y_pos = 1;
    _filename = "canvas.wave";
    std::string blank_space = (static_cast<std::string>(TXT_WHITE) + static_cast<std::string>(BG_BLACK) + " ");
    _filebuffer.assign(_terminal_width * _terminal_height, blank_space);
    
    put_cursor(1, 1);
    std::cout <<CLEAR_SCREEN <<std::flush;
    
}

Terminal::~Terminal() {
    put_cursor(1, 1);
    std::cout 
        <<CURSOR_BAR_BLINK 
        <<TXT_WHITE 
        <<BG_BLACK 
        <<CLEAR_SCREEN
        << std::flush;
    put_cursor(1, 1);
    tcsetattr(STDIN_FILENO, TCSANOW, &_old_terminal_config);
}

void Terminal::put_cursor(const int x, const int y) {
    if (x > _cursor_bound_right || x < _cursor_bound_left) {
        return;
    }
    if (y > _cursor_bound_bottom || y < _cursor_bound_top) {
        return;
    }

    _cursor_x_pos = x;
    _cursor_y_pos = y;
    std::cout <<"\033[" <<y <<";" <<x <<"H" <<std::flush;
}

void Terminal::move_cursor(const char dir, const int amount) {
    switch (dir) {
        case 'u':
            put_cursor(_cursor_x_pos, _cursor_y_pos - amount);
            break;
        case 'd':
            put_cursor(_cursor_x_pos, _cursor_y_pos + amount);
            break;
        case 'l':
            put_cursor(_cursor_x_pos - amount, _cursor_y_pos);
            break;
        case 'r':
            put_cursor(_cursor_x_pos + amount, _cursor_y_pos);
            break;
        default:
            break;
    }
}

void Terminal::hide_cursor() {
    std::cout <<HIDE_CURSOR <<std::flush;
    put_cursor(_cursor_x_pos, _cursor_y_pos);
}
void Terminal::show_cursor() {
    std::cout <<SHOW_CURSOR <<std::flush;
    put_cursor(_cursor_x_pos, _cursor_y_pos);
}
void Terminal::save_cursor_pos() {
    _stored_cursor_x_pos = _cursor_x_pos;
    _stored_cursor_y_pos = _cursor_y_pos;
    std::cout <<SAVE_CURSOR_POS <<std::flush;
    put_cursor(_cursor_x_pos, _cursor_y_pos);
}
void Terminal::load_cursor_pos() {
    _cursor_x_pos = _stored_cursor_x_pos;
    _cursor_y_pos = _stored_cursor_y_pos;
    std::cout <<LOAD_CURSOR_POS <<std::flush;
    put_cursor(_cursor_x_pos, _cursor_y_pos);
}

char Terminal::get_char() {
    char c;
    if (read(STDIN_FILENO, &c, 1) != 1) {
        return '\0';
    }

    if (c == '\33') {
        char c2;
        read(STDIN_FILENO, &c2, 1);
        if (c2 != '[') {
            return '\0';
        }
        char c3;
        read(STDIN_FILENO, &c3, 1);
        switch (c3) {
            case 'A':
                move_cursor('u');
                break;
            case 'B':
                move_cursor('d');
                break;
            case 'C':
                move_cursor('r');
                break;
            case 'D':
                move_cursor('l');
                break;
            default:
                break;
        }
        return '\0';
    }
    return c;
}

void Terminal::print(const std::string &str) {
    _cout(str);
    move_cursor('r', _visible_width_utf8(str));
}

// void Terminal::put_char(const std::string &c) {
//     std::cout
//     <<_cursor_type
//     <<_txt_color
//     <<_bg_color
//     <<c
//     <<std::flush;
//     put_cursor(_cursor_x_pos, _cursor_y_pos);
// }

void Terminal::_cout(const std::string &str) {
    std::cout
        <<_cursor_type
        <<_txt_color
        <<_bg_color
        <<str
        <<std::flush;

    int i = 0;
    for (int j = 0; j < str.size(); j += _char_len_utf8(str[j])) {
        const int k = (_cursor_x_pos -1 +i) + (_cursor_y_pos -1) * _terminal_width;
        int len = _char_len_utf8(str[j]);
        std::string full_char = str.substr(j, len);
        _filebuffer[k] = (_cursor_type + _txt_color + _bg_color + full_char);
        i++;
    }
}

void Terminal::set_cursor_bounds(const int t, const int b, const int l, const int r) {
    if (t < 1 || b > _terminal_height || l < 1 || r > _terminal_width) {
        return;
    }
    _cursor_bound_left = l;
    _cursor_bound_right = r;
    _cursor_bound_top = t;
    _cursor_bound_bottom = b;
}


void Terminal::set_txt_color(const ANSI_colors color) {
    switch (color) {
    case BLACK:
        _txt_color = TXT_BLACK;
        break;
    case RED:
        _txt_color = TXT_RED;
        break;
    case GREEN:
        _txt_color = TXT_GREEN;
        break;
    case YELLOW:
        _txt_color = TXT_YELLOW;
        break;
    case BLUE:
        _txt_color = TXT_BLUE;
        break;
    case MAGENTA:
        _txt_color = TXT_MAGENTA;
        break;
    case CYAN:
        _txt_color = TXT_CYAN;
        break;
    case WHITE:
        _txt_color = TXT_WHITE;
        break;
    case ALT_BLACK:
        _txt_color = TXT_ALT_BLACK;
        break;
    case ALT_RED:
        _txt_color = TXT_ALT_RED;
        break;
    case ALT_GREEN:
        _txt_color = TXT_ALT_GREEN;
        break;
    case ALT_YELLOW:
        _txt_color = TXT_ALT_YELLOW;
        break;
    case ALT_BLUE:
        _txt_color = TXT_ALT_BLUE;
        break;
    case ALT_MAGENTA:
        _txt_color = TXT_ALT_MAGENTA;
        break;
    case ALT_CYAN:
        _txt_color = TXT_ALT_CYAN;
        break;
    case ALT_WHITE:
        _txt_color = TXT_ALT_WHITE;
        break;
    }
}

void Terminal::set_bg_color(const ANSI_colors color) {
    switch (color) {
        case BLACK:
            _bg_color = BG_BLACK;
            break;
        case RED:
            _bg_color = BG_RED;
            break;
        case GREEN:
            _bg_color = BG_GREEN;
            break;
        case YELLOW:
            _bg_color = BG_YELLOW;
            break;
        case BLUE:
            _bg_color = BG_BLUE;
            break;
        case MAGENTA:
            _bg_color = BG_MAGENTA;
            break;
        case CYAN:
            _bg_color = BG_CYAN;
            break;
        case WHITE:
            _bg_color = BG_WHITE;
            break;
    case ALT_BLACK:
        _bg_color = BG_ALT_BLACK;
        break;
    case ALT_RED:
        _bg_color = BG_ALT_RED;
        break;
    case ALT_GREEN:
        _bg_color = BG_ALT_GREEN;
        break;
    case ALT_YELLOW:
        _bg_color = BG_ALT_YELLOW;
        break;
    case ALT_BLUE:
        _bg_color = BG_ALT_BLUE;
        break;
    case ALT_MAGENTA:
        _bg_color = BG_ALT_MAGENTA;
        break;
    case ALT_CYAN:
        _bg_color = BG_ALT_CYAN;
        break;
    case ALT_WHITE:
        _bg_color = BG_ALT_WHITE;
        break;
    }
}

window_size Terminal::get_window_size() const {
    return window_size{
        .width = _terminal_width,
        .height = _terminal_height
    };
}
cursor_pos Terminal::get_cursor_pos() const {
    return cursor_pos{
        .x = _cursor_x_pos,
        .y = _cursor_y_pos
    };
}

void Terminal::save_terminal() {
    std::ofstream file(_filename, std::ios::trunc);
    file 
        <<"WAVE-PAINT-CLI CANVAS FILE" <<std::endl
        <<_terminal_width <<std::endl
        <<_terminal_height <<std::endl;
    for (int i = 0; i < _filebuffer.size(); ++i) {
        file <<_filebuffer[i] <<",";
    }
    file.close();
}

void Terminal::load_terminal() {
    std::ifstream file(_filename);
    std::string header;
    std::getline(file, header);
    if (header != "WAVE-PAINT-CLI CANVAS FILE") {
        return;
    }
    
    std::cout <<CURSOR_BOX_BLINK <<TXT_WHITE <<BG_BLACK <<CLEAR_SCREEN <<std::flush;
    
    std::getline(file, header);
    _terminal_width = std::stoi(header);
    std::getline(file, header);
    _terminal_height = std::stoi(header);
    
    std::string blank_space = (static_cast<std::string>(TXT_WHITE) + static_cast<std::string>(BG_BLACK) + " ");
    _filebuffer.assign(_terminal_width * _terminal_height, blank_space);
    std::string str;
    int i = 0;
    while (std::getline(file, str, ',')) {
        _filebuffer[i++] = str;
    }
    file.close();
    
    for (int i = 1; i <= _terminal_height; ++i) {
        for (int j = 1; j <= _terminal_width; ++j) {
            put_cursor(j, i);
            const int index = (j -1) + (i -1) * _terminal_width;
            std::cout
                <<_filebuffer[index]
                <<std::flush;
        }
    }
    put_cursor(1, 1);
}


// 0% human-written method
int Terminal::_visible_width_utf8(const std::string &str) {
    int width = 0;
    for (const unsigned char c : str) {
        if ((c & 0xC0) != 0x80) {
            ++width;
        }
    }
    return width;
}
// 0% human-written method
int Terminal::_char_len_utf8(unsigned char c) {
    if ((c & 0x80) == 0x00) return 1;
    if ((c & 0xE0) == 0xC0) return 2;
    if ((c & 0xF0) == 0xE0) return 3;
    if ((c & 0xF8) == 0xF0) return 4;
    return 1;
}

void Terminal::_scrub_save() {
    static const std::vector<std::string> unwanted = {
        CURSOR_BOX_BLINK,
        CURSOR_BAR_BLINK,
        HIDE_CURSOR,
        SHOW_CURSOR,
        SAVE_CURSOR_POS,
        LOAD_CURSOR_POS,
    };
    static const std::regex cursor_pos_reg("\033\\[[0-9]+;[0-9]+H");
    
    for (auto &x : _filebuffer) {
        for (auto &y : unwanted) {
            auto pos = x.find(y);
            if (pos != std::string::npos) {
                x.erase(pos, y.size());
            }
        }
        x = std::regex_replace(x, cursor_pos_reg, "");
    }
}
