
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

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

void handle_input(int *dx, int *dy) {
    int ch = getch();
    switch (ch) {
            case KEY_UP:    
                *dx = 0;
                *dy = -1;
            break;
            case KEY_DOWN:  
                *dx = 0;
                *dy = 1;
            break;
            case KEY_LEFT:  
                *dx = -1;
                *dy = 0;
            break;
            case KEY_RIGHT: 
                *dx = 1;
                *dy = 0;
            break;
    }
}

void draw(int x, int y){
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

    mvprintw(HEIGHT + 1, 0, "Score: %d", snake_length - 1);
    
    refresh();
}

void show_start_screen(){
    clear();
    mvprintw(HEIGHT / 2 - 2, WIDTH / 2 - 4, "S N A K E");
    mvprintw(HEIGHT / 2,     WIDTH / 2 - 7, "Press any key to start");
    refresh();
    nodelay(stdscr, FALSE);
    getch();
    nodelay(stdscr, TRUE);
}

int show_game_over_screen(int score){
    clear();
    mvprintw(HEIGHT / 2 - 2, WIDTH / 2 - 4, "GAME OVER");
    mvprintw(HEIGHT / 2,     WIDTH / 2 - 5, "Score: %d", score);
    mvprintw(HEIGHT / 2 + 2, WIDTH / 2 - 9, "Press R to play again or Q to quit");
    refresh();
    nodelay(stdscr, FALSE);
    while(1){
        int ch = getch();
        if(ch == 'r' || ch == 'R') { nodelay(stdscr, TRUE); return 1; }
        if(ch == 'q' || ch == 'Q') { nodelay(stdscr, TRUE); return 0; }
    }
}

void reset_game(int *x, int *y, int *dx, int *dy){
    *x = WIDTH / 2;
    *y = HEIGHT / 2;
    snake_length = 1;
    *dx = 0;
    *dy = 0;
    snake_x[0] = *x;
    snake_y[0] = *y;
    spawn_food();
}

int main(){
    int x = WIDTH / 2;
    int y = HEIGHT / 2;
    int dx = 0;
    int dy = 0;

    srand(time(NULL));
    spawn_food();

    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    
    while(1){

        reset_game(&x, &y, &dx, &dy);
        show_start_screen();
        int game_over = 0;
        while(!game_over){
        handle_input(&dx, &dy);
        x += dx;
        y += dy;
        //moves the body with the head
        for(int i = snake_length - 1; i > 0; i--) {
            snake_x[i] = snake_x[i-1];
            snake_y[i] = snake_y[i-1];
        }
        
        snake_x[0] = x;
        snake_y[0] = y;

        //ends game after hitting the wall (still needs to check for hitting itself)
        if (x <= 0 || x >= WIDTH-1 || y <= 0 || y >= HEIGHT-1){
            game_over = 1;
            break;
        }

        //spawns food after increases length
        if (x == food_x && y == food_y) {
            snake_length++;
            spawn_food();
        }
        
        for(int i = 1; i < snake_length; i++){
            if(x == snake_x[i] && y == snake_y[i]){
                game_over = 1;
                break;
            }
        }
        if(!game_over){
            draw(x, y);
            napms(150); 
        }
    }
        if(!show_game_over_screen(snake_length - 1))
            break;
}
    
    
    endwin();
    return 0; 
}
