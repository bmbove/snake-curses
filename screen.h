#include <curses.h>

class Screen{
    public:
        Screen(){
            initscr();
            start_color();
            cbreak();
            noecho();
            curs_set(0);
            keypad(stdscr, true);
            init_pair(1, COLOR_YELLOW, COLOR_BLACK);
            init_pair(2, COLOR_RED, COLOR_BLACK);
            init_pair(3, COLOR_GREEN, COLOR_BLACK);
            init_pair(4, COLOR_BLUE, COLOR_BLACK);
            init_pair(5, COLOR_WHITE, COLOR_BLACK);
            refresh();

            int h, w;
            getmaxyx(stdscr, h, w);
            win = newwin(h, w, 0, 0);
            Screen::redraw();
            nodelay(stdscr, true);
        };
        void destroy();
        void redraw(bool reset=true);
        void clear();
        int get();
        void print(char ch, int x, int y, int col);

    private:
        WINDOW* win;
        int cur_line;
};
