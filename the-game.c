
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 20
#define HEIGHT 20

int food_x;
int food_y;

void spawn_food(){
    food_x = (rand() % (WIDTH - 2) + 1);
    food_y = (rand() % (HEIGHT - 2)) + 1);
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

    mvprintw(y, x, "0");

    mvprintw(food_y, ood_x, "*");

    refresh();
}

int main(){
    int x = WIDTH / 2;
    int y = HEIGHT / 2;

    srand(time(NULL));
    spawn_food();

    intiscr();
    neocho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    while(1){
        print(x, y);
        handle_input(&x, &y);
        napms(100);
    }

    endwin();
    return 0; 
}
