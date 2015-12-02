#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include "snake.h"
#include "screen.h"
using namespace std;

bool redraw(Screen &screen, Snake &snake){

    for(int i=0; i < 40; i++){
        for(int j=0; j < 30; j++){
            if(i == 0 || i == 39)
                screen.print('|', i, j, 2);
            else if(j == 0 || j == 29)
                screen.print('-', i, j, 2);
            else
                screen.print(' ', i, j, 2);
        }
    }

    snake.move_snake();

    screen.print('@', snake.apple.x, snake.apple.y, 1);
    for(unsigned int i=0; i < snake.body.size(); i++){
        screen.print('#', snake.body[i].x, snake.body[i].y, 4);
    }
    screen.print('0', snake.head.x, snake.head.y, 3);

    char msg[30];
    snprintf(msg, 20, "%-10s%9d", "Score", (int)snake.body.size() - 1);
    for(unsigned int i=0; i < 19; i++){
        screen.print(msg[i], 5+i, 33, 5);
    }

    if(snake.heading == 0){
        snprintf(msg, 30, "Use Arrow Keys to Start");
        for(unsigned int i=0; i < 23; i++){
            screen.print(msg[i], 5+i, 29, 5);
        }
    }


    screen.redraw();

    if(snake.hit_detect()){
        snprintf(msg, 11, "Game Over!");
        for(int i=0; i < 10; i++){
            screen.print(msg[i], 12 + i, 15, 2);
        }
        screen.redraw();
        usleep(1500000);
        return false;
    }

    return true;
}

int main(){

    srand(time(NULL));
    Snake snake = Snake();
    Screen screen;
    clock_t last = clock();
    clock_t now = clock();
    int new_head;
    float time_c = 1.0;
    bool play = true;

    redraw(screen, snake);

    while(play){
        now = clock();
        int size = snake.body.size();
        time_c = 0.5 * pow(2.71828, (-size * 0.046));
        if(((float)(now - last) / CLOCKS_PER_SEC) > time_c){
            last = clock();
            play = redraw(screen, snake);
        }
        
        new_head = screen.get();
        if(new_head != ERR){
            if(new_head == 'q'){
                break;
            }
            if(snake.change_dir(new_head)){
                play = redraw(screen, snake);
                last = clock();
            }
        }
        screen.redraw();
    }

    screen.clear();

    screen.destroy();

    return 0;
}
