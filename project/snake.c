#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 20
#define HEIGHT 10

int headX, headY;
int foodX, foodY;
int score;
char map[HEIGHT][WIDTH];

void initGame() {
    srand((unsigned)time(NULL));
    headX = WIDTH / 2;
    headY = HEIGHT / 2;

    foodX = rand() % WIDTH;
    foodY = rand() % HEIGHT;

    score = 0;
}

void draw() {
    system("cls");  // VS Code 的终端能正常清屏

    printf("得分：%d\n", score);

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == headY && j == headX)
                printf("O");   // 蛇头
            else if (i == foodY && j == foodX)
                printf("*");   // 食物
            else
                printf(".");
        }
        printf("\n");
    }
}

void update(char dir) {
    if (dir == 'w') headY--;
    else if (dir == 's') headY++;
    else if (dir == 'a') headX--;
    else if (dir == 'd') headX++;

    // 撞墙
    if (headX < 0 || headX >= WIDTH || headY < 0 || headY >= HEIGHT) {
        printf("你撞墙了，游戏结束！\n");
        exit(0);
    }

    // 吃食物
    if (headX == foodX && headY == foodY) {
        score++;
        foodX = rand() % WIDTH;
        foodY = rand() % HEIGHT;
    }
}

int main() {
    initGame();

    while (1) {
        draw();
        printf("请输入方向（w上 s下 a左 d右）：");

        char c;
        scanf(" %c", &c); // 输入方向

        update(c);
    }

    return 0;
}
