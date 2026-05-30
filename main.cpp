#include "Process.h"

int main() {
    
    auto *a = new Process();
    a->draw_menu();
    
    a->start();

    delete a;
}
