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