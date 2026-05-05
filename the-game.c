
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 20
#define HEIGHT 20

int food_x;
int food_y;

int snake_x[100];
int snake_y[100];
int snake_length = 1;

void spawn_food(){
    food_x = (rand() % (WIDTH - 2) + 1);
    food_y = (rand() % (HEIGHT - 2) + 1);
}

void handle_input(int *x, int *y) {
    int ch = getch();
    switch (ch) {
            case KEY_UP:    (*y)--; 
            break;
            case KEY_DOWN:  (*y)++; 
            break;
            case KEY_LEFT:  (*x)--; 
            break;
            case KEY_RIGHT: (*x)++; 
            break;
    }
}

void print(int x, int y){
    clear();

    for(int i = 0; i < WIDTH; i++) {
        mvprintw(0, i, "#");
        mvprintw(HEIGHT - 1, i, "#");
    }
    for(int i = 0; i< HEIGHT; i++){
        mvprintw(i, 0, "#");
        mvprintw(i, WIDTH - 1, "#");
    }

    for(int i = 1; i < snake_length; i++) {
        mvprintw(snake_y[i], snake_x[i], "o");
    }

    mvprintw(y, x, "0");

    mvprintw(food_y, food_x, "*");

    refresh();
}

int main(){
    int x = WIDTH / 2;
    int y = HEIGHT / 2;

    srand(time(NULL));
    spawn_food();

    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    while(1){
        handle_input(&x, &y);
        //moves the body with the head
        for(int i = snake_length - 1; i > 0; i--) {
            snake_x[i] = snake_x[i-1];
            snake_y[i] = snake_y[i-1];
        }
        //spawns food after increases length
        if (x == food_x && y == food_y) {
            snake_length++;
            spawn_food();
        }
        
        snake_x[0] = x;
        snake_y[0] = y;
        
        print(x, y);

        //ends game after hitting the wall (still needs to check for hitting itself)
        if (x <= 0 || x >= WIDTH-1 || y <= 0 || y >= HEIGHT-1)
            break;
    }
        
        napms(100);


        
    }

    endwin();
    return 0; 
}
