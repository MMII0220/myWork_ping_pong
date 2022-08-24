#include <stdio.h>
#include <stdlib.h>

#define width 32
#define height 16

void printField(int ballX,int ballY, int rocketLeft, int rocketRight);


int main() {
    int ballX = 16, ballY = 7;
    int rocketLeft = 6, rocketRight = 6;

    printField(ballX, ballY, rocketLeft, rocketRight);
    return 0;
}

void printField(int ballX,int ballY, int rocketLeft, int rocketRight) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 || i == height - 1) {
                printf("-");
            } else if (j == 0 || j == width -1) {
                printf("|");
            } else if (i == ballY && j == ballX) {
                printf("o");
            } else if (j == 1 && (i >= rocketLeft && i <= rocketLeft + 2)) {
                printf("|");
            } else if (j == 30 && (i >= rocketRight && i <= rocketRight + 2)) {
                printf("|");
            } else if (i != 0 && j != 0 && j != width - 1 && i != height - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
}




