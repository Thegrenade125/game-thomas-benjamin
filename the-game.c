
#include <ncurses.h>
#include <stdlib.h>



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
        mvprintw(i, WIDTH - 1, "#")
}

        mvprintw(y, x, "0");

    refresh();
}

int main (){



    return 0; 
}