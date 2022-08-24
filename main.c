#include <stdio.h>
#include <stdlib.h>

#define width 32
#define height 16

void printField(int ballX,int ballY, int rocketLeft, int rocketRight);
int ballMovementY(int ballY);
int ballMovementX(int ballX);
int leftRocketMovement(int rocketLeft, char key);
int rightRocketMovement(int rocketRight, char key);
void play();


int main() {
    play();

    return 0;
}


void printField(int ballX, int ballY, int rocketLeft, int rocketRight) {
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


void play() {
    int ballX = 16, ballY = 7;
    int rocketLeft = 6, rocketRight = 6;

    printField(ballX, ballY, rocketLeft, rocketRight);

    while (1) {
        char keyPressed;
        keyPressed = getchar();

        if (keyPressed == 'X') {
            printf("Game Stopped!");
            break;
        } else {
            ballX = ballMovementX(ballX);
            ballY = ballMovementY(ballY);

            rocketLeft = leftRocketMovement(rocketLeft, keyPressed);
            rocketRight = rightRocketMovement(rocketRight, keyPressed);

            system("cls");

            printField(ballX, ballY, rocketLeft, rocketRight);
        }
    }
}


int ballMovementX(int ballX) {
    ballX -= 1;

    return ballX;
}

int ballMovementY(int ballY) {
    ballY += 1;

    return ballY;
}

int leftRocketMovement(int rocketLeft, char key) {
    if (key == 'W') {
        rocketLeft -= 1;
    } else if (key == 'S') {
        rocketLeft += 1;
    }

    return rocketLeft;
}

int rightRocketMovement(int rocketRight, char key) {
    if (key == 'E') {
        rocketRight -= 1;
    } else if (key == 'D') {
        rocketRight += 1;
    }

    return rocketRight;
}






