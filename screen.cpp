#include "screen.h"

void Screen::redraw(bool reset){
    refresh();
    wrefresh(win);
    if(reset)
        cur_line = 0;
}

void Screen::destroy(){
    endwin();
    delwin(win);
}

void Screen::clear(){
    werase(win);
    Screen::redraw();
}

int Screen::get(){
    return getch();
}

void Screen::print(char ch, int x, int y, int col){
    wattron(win, COLOR_PAIR(col));
    mvwaddch(win, y, x, ch);
    wattroff(win, COLOR_PAIR(col));
}
