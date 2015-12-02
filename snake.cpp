#include <curses.h>
#include <stdlib.h>
#include "snake.h"

bool Snake::change_dir(int new_head){

    bool small = false;
    int cur = heading;

    if(body.size() == 1)
        small = true;

    switch(new_head){
        case KEY_DOWN:
            if(cur != 1 || small){
                heading = 3;
                return true;
            }
            break;
        case KEY_RIGHT:
            if(cur != 4 || small){
                heading = 2;
                return true;
            }
            break;
        case KEY_UP:
            if(cur != 3 || small){
                heading = 1;
                return true;
            }
            break;
        case KEY_LEFT:
            if(cur != 2 || small){
                heading = 4;
                return true;
            }
            break;
        default:
            return false;
            break;
    }
    return false;
}


void Snake::move_snake(){

    switch(heading){
        case 1:
            head.y--;
            break;
        case 2:
            head.x++;
            break;
        case 3:
            head.y++;
            break;
        case 4:
            head.x--;
            break;
        case 0:
            break;
    }


    if(heading != 0){
        body.push_back(head);

        if(heading != 0){
            if(!apple_detect()){
                for(unsigned int i=0; i < body.size(); i++){
                    if(body[i].x == tail.x && body[i].y == tail.y){
                        tail.x = body[i+1].x;
                        tail.y = body[i+1].y;
                        body.erase(body.begin()+i);
                    }
                }
            }
            else{
                new_apple();
            }
        }
    }
}

int Snake::rand_int(int r_min, int r_max){
    return r_min + (rand() % (r_max - r_min + 1));
}

bool Snake::hit_detect(){

    int count = 0;

    for(unsigned int i=0; i < body.size(); i++){

        // hit a side wall
        if(body[i].x == 0 || body[i].x == 39)
            return true;

        // hit a top/bottom wall
        if(body[i].y == 0 || body[i].y == 29)
            return true;

        for(unsigned int j=0; j < body.size(); j++){
            if(body[i].x == body[j].x && body[i].y == body[j].y)
                count++;

            // hit it's own body
            if(count > 1)
                return true;
        }
        count = 0;
    }
    
    return false;
}

bool Snake::apple_detect(){

    if(head.x == apple.x && head.y == apple.y)
        return true;
    else
        return false;
}

void Snake::new_apple(){

    bool nope;
    Cell new_apple;
    new_apple.x = rand_int(1, 38);
    new_apple.y = rand_int(1, 28);

    while(true){
        nope = false;
        for(unsigned int i=0; i < body.size(); i++){
            if(body[i].x == new_apple.x && body[i].y == new_apple.y)
                nope = true;
        }
        if(!nope){
            apple = new_apple;
            break;
        }
        else{
            new_apple.x = rand_int(1, 38);
            new_apple.y = rand_int(1, 28);
        }
    }
}
