#include <stdio.h>
#include <stdlib.h>

int leftRocketOffsetGlobal, rightRocketOffsetGlobal;
#define width 32
#define height 16


void printField(int ballX, int ballY, int rocketLeft, int rocketRight);
void getInput();
int getLeftRocketOffset(char key);
int getRightRocketOffset(char key);
int getRocketY(int rocketY, int offsetY);
int getBallCoordX(int ballOld, int ball);
int getBallCoordY(int ballOld, int ball);
int getBallXFromWall(int ballXOld, int ballX);
int getBallYFromWall(int ballYOld, int ballY);
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

    int ballXOld = 17, ballYOld = 6;

    printField(ballX, ballY, rocketLeft, rocketRight);

    while (1) {
        int leftRocketOffset, rightRocketOffset;

        getInput();


        leftRocketOffset = leftRocketOffsetGlobal;
        rightRocketOffset = rightRocketOffsetGlobal;

        int updatedLeftRocketY = getRocketY(rocketLeft, leftRocketOffset);
        int updatedRightRocketY = getRocketY(rocketRight, rightRocketOffset);
        int updatedBallX, updatedBallY;

        if (ballY == 0 || ballY == 14) {
            updatedBallX = getBallXFromWall(ballXOld, ballX);
            updatedBallY = getBallYFromWall(ballYOld, ballY);
        } else {
            updatedBallX = getBallCoordX(ballXOld, ballX);
            updatedBallY = getBallCoordY(ballYOld, ballY);
        }

        ballXOld = ballX;
        ballYOld = ballY;

        ballX = updatedBallX;
        ballY = updatedBallY;

        rocketLeft = updatedLeftRocketY;
        rocketRight = updatedRightRocketY;

        system("cls");

        printField(ballX, ballY, rocketLeft, rocketRight);
    }
}


void getInput() {
    char keyPressed = getchar();

    int leftRocketOffset = 0, rightRocketOffset = 0;

    if (keyPressed == ('A' || 'a') || keyPressed == ('Z' || 'z')) {
        leftRocketOffset = getLeftRocketOffset(keyPressed);

    } else if (keyPressed == ('K' || 'k') || keyPressed == ('M' || 'm')) {
        rightRocketOffset = getRightRocketOffset(keyPressed);

    }/* else {  // Удали это и различие в чем будет ---------------------
        if (keyPressed == ('A' || 'a') || keyPressed == ('Z' || 'z')) {
            leftRocketOffset = getLeftRocketOffset(keyPressed);
        } else {
            rightRocketOffset = getRightRocketOffset(keyPressed);
        }
    }*/ // до сюда ------------------------------------------------------

    leftRocketOffsetGlobal = leftRocketOffset;
    rightRocketOffsetGlobal = rightRocketOffset;
}

int getLeftRocketOffset(char key) {
    int move = 0;

    if (key == 'A' || key == 'a') {
        move = -1;
    } else if (key == ('Z' || 'z')) {
        move = 1;
    } else {
        move = 0;
    }

    return move;
}

int getRightRocketOffset(char key) {
    int move = 0;

    if (key == ('K' || 'k')) {
        move = -1;
    } else if (key == ('M' || 'm')) {
        move = 1;
    } else {
        move = 0;
    }

    return move;
}

int getRocketY(int rocketY, int offsetY) {
    int updatedRocketY = rocketY + offsetY;
    int move = 0;

    if (updatedRocketY < 0) {
        move = 0;
    } else if (updatedRocketY > 12) {
        move = 12;
    } else {
        move = updatedRocketY;
    }

    return move;
}

int getBallCoordX(int ballOld, int ball) {
    int offset = ball - ballOld;
    int updatedBall = ball + offset;

    int move;

    if (updatedBall < 0) {
        move = 0;
    } else if (updatedBall > 30) {
        move = 30;
    } else {
        move = updatedBall;
    }

    return move;
}

int getBallCoordY(int ballOld, int ball) {
    int move;

    int offset = ball - ballOld;
    int updatedBall = ball + offset;

    if (updatedBall < 0) {
        move = 0;
    } else if (updatedBall > 14) {
        move = 14;
    } else {
        move = updatedBall;
    }

    return move;
}

int getBallXFromWall(int ballXOld, int ballX) {
    int offset = ballX - ballXOld;

    return ballX + offset;
}

int getBallYFromWall(int ballYOld, int ballY) {
    int offset = ballYOld - ballY;

    return ballY + offset;
}

