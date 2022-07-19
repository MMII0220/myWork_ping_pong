#include <stdio.h>


#define width 31
#define height 11

void printGame(int bX, int bY);

int main() {
    int ballX = 15, ballY = 5;
    int rocketY = 15, rocketX = 1;
    
    printGame(ballX, ballY);
    
    return 0;
}

void printGame(int bX, int bY) {
    for (int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++) {
            if (x == 0 || x == height - 1) {
                printf("-");
            } else if (y == bX && x == bY) {
                printf("o");
            }/* else if() {
                printf(|);
            }*/ else if ((x != 0 && y == 0) || (y == width - 1)) {
                printf("|");
            }  else if(x != 0 && y != 0 && x != height - 1 && y != width - 1) {
                printf(" ");
            }  
        }
        printf("\n");
    }
}
