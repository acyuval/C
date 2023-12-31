#include <stdio.h>

#define ROWS 8
#define COLS 8

int floodFill(int screen[ROWS][COLS], int x, int y, int oldColor, int newColor) {
    if (x < 0 || x >= ROWS || y < 0 || y >= COLS) {
        printf("\nOUTSIDE!\n");
        return 0;
    }
    if (screen[x][y] != oldColor || screen[x][y] == newColor) {
        return 1; 
    }

    screen[x][y] = newColor;

    floodFill(screen, x + 1, y, oldColor, newColor);  // Right
    floodFill(screen, x - 1, y, oldColor, newColor);  // Left
    floodFill(screen, x, y + 1, oldColor, newColor);  // Down
    floodFill(screen, x, y - 1, oldColor, newColor);  // Up
}

// Function to print the screen
void printScreen(int screen[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", screen[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int screen[ROWS][COLS] = {
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 0, 1, 1, 1}
    };

    printf("Original Screen:\n");
    printScreen(screen);

    int x = 6, y = 6;  // Seed point
    int oldColor = 0;
    int newColor = 1;  // New color to fill

    floodFill(screen, x, y, oldColor, newColor);

    printf("\nScreen after Flood Fill:\n");
    printScreen(screen);

    return 0;
}
