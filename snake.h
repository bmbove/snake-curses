#include <vector>


class Snake{

    public:
        Snake(){
            heading = 0;
            new_apple(); 
            Cell new_snake;
            new_snake.x = 10;
            new_snake.y = 10;

            head.x = new_snake.x;
            head.y = new_snake.y;

            tail.x = new_snake.x;
            tail.y = new_snake.y;

            body.push_back(new_snake);
        };
        struct Cell{
            int x;
            int y;
        };
        void move_snake();
        std::vector<Cell> body;
        Cell apple;
        Cell head;
        Cell tail;
        bool hit_detect();
        bool change_dir(int new_head);
        int heading;

    private:
        bool apple_detect();
        void new_apple();
        int rand_int(int r_min, int r_max);
};
