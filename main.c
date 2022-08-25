#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int leftRocketOffsetGlobal, rightRocketOffsetGlobal;
// #define width 32
// #define height 16
#define width 81
#define height 26


int getLeftRocketOffset(char key);

int getRightRocketOffset(char key);

int getRocketY(int rocketY, int offsetY);

int getBallCoordX(int ballOld, int ball);

int getBallCoordY(int ballOld, int ball);

int getBallXFromWall(int ballXOld, int ballX);

int getBallYFromWall(int ballYOld, int ballY);

int getBallXFromRocket(int ballXOld, int ballX);

int getBallYFromRocket(int ballYOld, int ballY);

void getInput();

void printField(int ballX, int ballY, int rocketLeft, int rocketRight, int leftPlayerScore, int rightPlayerScore);

void Play();


int main() {
    Play();

    return 0;
}

// Создаем Поле
void printField(int ballX, int ballY, int rocketLeft, int rocketRight, int leftPlayerScore, int rightPlayerScore) {
    printf("Score: \n\t %d - %d\n\n", leftPlayerScore, rightPlayerScore);

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
            } else if (j == width - 3 && (i >= rocketRight && i <= rocketRight + 2)) {
                printf("|");
            } else if (i != 0 && j != 0 && j != width - 1 && i != height - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
}


void Play() {  // Вся наша игра
    int ballX = 40, ballY = 12;
    int rocketLeft = 10, rocketRight = 10;

    int ballXOld = 41, ballYOld = 11;

    int leftPlayerScore = 0, rightPlayerScore = 0;

    printField(ballX, ballY, rocketLeft, rocketRight, leftPlayerScore, rightPlayerScore);

    int leftRocketOffset, rightRocketOffset;

    int updatedLeftRocketY;
    int updatedRightRocketY;

    int updatedBallX, updatedBallY;

    while (leftPlayerScore < 12 && rightPlayerScore < 12) {
        getInput();

        leftRocketOffset = leftRocketOffsetGlobal;
        rightRocketOffset = rightRocketOffsetGlobal;

        updatedLeftRocketY = getRocketY(rocketLeft, leftRocketOffset);
        updatedRightRocketY = getRocketY(rocketRight, rightRocketOffset);

        if (ballY == 0 && ballX == 1 &&
        updatedLeftRocketY == 0) {  // if left racket and ball in the top left corner
            updatedBallX = 2;
            updatedBallY = 1;
        } else if (ballY == (height - 2) && ballX == 1 &&
        updatedLeftRocketY == (height - 4)) {  // if left racket and ball in the bottom left corner
            updatedBallX = 2;
            updatedBallY = height - 3;
        } else if (ballY == 0 && ballX == (width - 3) &&
        updatedRightRocketY == 0) {  // if right racket and ball in the top right corner
            updatedBallX = width - 3;
            updatedBallY = 1;
        } else if (ballY == height - 2 && ballX == (width - 3) &&
        updatedRightRocketY == (height - 4)) {  // if right racket and ball in the bottom right corner
            updatedBallX = width - 3;
            updatedBallY = height - 3;
        } else if (ballY == 0 || ballY == height - 2) {  // Отражение от стены
            updatedBallX = getBallXFromWall(ballXOld, ballX);
            updatedBallY = getBallYFromWall(ballYOld, ballY);
        } else if (ballX == 2 && (ballY >= updatedLeftRocketY && ballY <= updatedLeftRocketY + 2)) {  // Отражение от левой ракетки
            updatedBallX = getBallXFromRocket(ballXOld, ballX);
            updatedBallY = getBallYFromRocket(ballYOld, ballY);
        } else if (ballX == (width - 2) && (ballY >= updatedRightRocketY && ballY <= updatedRightRocketY + 2)) {  // Отражение от правой ракетки
            updatedBallX = getBallXFromRocket(ballXOld, ballX);
            updatedBallY = getBallYFromRocket(ballYOld, ballY);
        } else {  // При любом случае условия, мяч сдвигается
            updatedBallX = getBallCoordX(ballXOld, ballX);
            updatedBallY = getBallCoordY(ballYOld, ballY);
        }

        ballXOld = ballX;
        ballYOld = ballY;

        ballX = updatedBallX;
        ballY = updatedBallY;

        rocketLeft = updatedLeftRocketY;
        rocketRight = updatedRightRocketY;

        if (ballX == 1 || ballX == width - 2) {
            // Вернем все местоположения по-умочанию
            ballX = 40, ballY = 12;
            rocketLeft = 10, rocketRight = 10;

            if (ballX == 1) {  // Если Гол забил правый игрок
                rightPlayerScore++;

                ballXOld = 41;  // Мяч полетит влево при старте
                ballYOld = 11;
            } else {  // Если Гол забил левый игрок
                leftPlayerScore++;

                ballXOld = 39;;  // Мяч полетит вправо при старте
                ballYOld = 13;
            }

            system("cls");

            printf("\t\tGoal!!!\n\n");
            sleep(1);
        }

        system("cls");

        printField(ballX, ballY, rocketLeft, rocketRight, leftPlayerScore, rightPlayerScore);
    }

    if (leftPlayerScore == 12) {
        printf("Congratulation!\nPlayer 1 won!");
    } else if (rightPlayerScore == 12) {
        printf("Congratulation!\nPlayer 2 won!");
    }

    printf("Game Over!");
}


void getInput() {  // Меняем местоположения наших ракеток
    char keyPressed;
    keyPressed = getchar();

    int leftRocketOffset = 0, rightRocketOffset = 0;

    if (keyPressed == 'A' || keyPressed == 'Z' || keyPressed == 'a' || keyPressed == 'z') {
        leftRocketOffset = getLeftRocketOffset(keyPressed);
    } else if (keyPressed == 'K' || keyPressed == 'M' || keyPressed == 'k' || keyPressed == 'm') {
        rightRocketOffset = getRightRocketOffset(keyPressed);
    }

    leftRocketOffsetGlobal = leftRocketOffset;
    rightRocketOffsetGlobal = rightRocketOffset;
}


int getLeftRocketOffset(char key) {  // Двигаем левую ракетку вверх|вниз
    int move = 0;

    if (key == 'A' || key == 'a') {
        move = -1;
    } else if (key == 'Z' || key == 'z') {
        move = 1;
    } else {
        move = 0;
    }

    return move;
}

int getRightRocketOffset(char key) {  // Двигаем правую ракетку вверх|вниз
    int move = 0;

    if (key == 'K' || key == 'k') {
        move = -1;
    } else if (key == 'M' || key == 'm') {
        move = 1;
    } else {
        move = 0;
    }

    return move;
}

int getRocketY(int rocketY, int offsetY) {  // Если наша ракетка выходит за поле
    int updatedRocketY = rocketY + offsetY;
    int move = 0;

    if (updatedRocketY < 1) {
        move = 1;
    } else if (updatedRocketY > (height - 4)) {
        move = height - 4;
    } else {
        move = updatedRocketY;
    }

    return move;
}

int getBallCoordX(int ballOld, int ball) {  // Двигаем наш мяч по ось X
    int offset = ball - ballOld;
    int updatedBall = ball + offset;

    int move;

    if (updatedBall < 0) {
        move = 0;
    } else if (updatedBall > (width - 2)) {
        move = width - 2;
    } else {
        move = updatedBall;
    }

    return move;
}

int getBallCoordY(int ballOld, int ball) {  // Двигаем наш мяч по ось Y
    int move;

    int offset = ball - ballOld;
    int updatedBall = ball + offset;

    if (updatedBall < 1) {
        move = 1;
    } else if (updatedBall > (height - 1)) {
        move = height - 1;
    } else {
        move = updatedBall;
    }

    return move;
}

int getBallXFromWall(int ballXOld, int ballX) {  // Отражения от стены по ось X
    int offset = ballX - ballXOld;

    return ballX + offset;
}

int getBallYFromWall(int ballYOld, int ballY) {  // Отражения от стены по ось Y
    int offset = ballYOld - ballY;

    return ballY + offset;
}

int getBallXFromRocket(int ballXOld, int ballX) {  // Отражения от ракетки по ось X
    int offset = ballXOld - ballX;

    return ballX + offset;
}

int getBallYFromRocket(int ballYOld, int ballY) {  // Отражения от ракетки по ось Y
    int offset = ballY - ballYOld;

    return ballY + offset;
}
