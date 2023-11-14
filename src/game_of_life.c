#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define W 80
#define H 25

void title();
int input(int grid[][W]);
void next(int grid[][W], int grid2[][W]);
int no_lives(int grid[][W]);
void output(int grid[][W], WINDOW *win);
int no_match(int grid[][W], int new_grid[][W]);
int neighbour_check(int grid[][W], int y, int x);
void cpGrid(int grid[][W], int grid2[][W]);

int main() {
    int grid[H][W];
    int new_grid[H][W];
    input(grid);
    WINDOW *win;
    win = initscr();
    nodelay(win, TRUE);
    noecho();
    cpGrid(grid, new_grid);

    output(grid, win);
    while (1) {
        char ch = getch();
        if (ch == 'q') {
            return 0;
        }
        output(new_grid, win);
        next(grid, new_grid);
        usleep(100000);
        cpGrid(new_grid, grid);
        int co = no_lives(new_grid);
        if (co) {
            co = no_match(new_grid, grid);
        }
    }
    return 0;
}
int input(int grid[][W]) {
    int cell;
    int retval = 0;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (scanf("%d", &cell) == 1) {
                if (cell == 0 || cell == 1) {
                    grid[i][j] = cell;
                } else {
                    retval = 0;
                }
            }
        }
    }
    return retval;
}

void output(int grid[H][W], WINDOW *win) {
    wclear(win);
    title();
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (grid[i][j] == 1) {
                printw("o");
            } else {
                printw(" ");
            }
        }
        printw("\n");
    }
}

void next(int grid[][W], int grid2[][W]) {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            int n = neighbour_check(grid, i, j);
            if ((n < 2 || n > 3)) {
                grid2[i][j] = 0;
            } else if (n == 3) {
                grid2[i][j] = 1;
            }
        }
    }
}

int neighbour_check(int grid[][W], int y, int x) {
    int count = 0;
    for (int i = y - 1; i <= y + 1; i++) {
        for (int j = x - 1; j <= x + 1; j++) {
            count += grid[(i + H) % H][(j + W) % W];
        }
    }
    return count - grid[y][x];
}

void cpGrid(int grid[][W], int grid2[][W]) {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            grid2[i][j] = grid[i][j];
        }
    }
}

int no_lives(int grid[][W]) {
    int counter = 0;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (grid[i][j] == 1) {
                counter += 1;
            }
        }
    }
    return counter;
}

int no_match(int grid[][W], int new_grid[][W]) {
    int counter = 0;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (grid[i][j] != new_grid[i][j]) {
                counter = 1;
            }
        }
    }
    return counter;
}

void title() {
    printw(
        "*****  *   *  *****      ****    ****   *       *  *****      ****   *****     *      *****  *****  "
        "*****\n");
    printw(
        "  *    *   *  *         *       *    *  * *   * *  *         *    *  *         *        *    *      "
        "* \n");
    printw(
        "  *    *****  ***       *  ***  ******  *   *   *  ***       *    *  ***       *        *    ***    "
        "***\n");
    printw(
        "  *    *   *  *         *    *  *    *  *       *  *         *    *  *         *        *    *      "
        "*\n");
    printw(
        "  *    *   *  *****      ****   *    *  *       *  *****      ****   *         *****  *****  *      "
        "*****\n");
    printw(
        "____________________________________________________________________________________________________"
        "_____\n");
}
