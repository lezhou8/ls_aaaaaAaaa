#include <getopt.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>

// #define 正在 while
// #define 回答 return
// #define 主要 main
// #define 数字 int
// #define 字 char

typedef struct options {
    bool delete;
} options_t;

void print_help();

int main(int argc, char **argv)
{
    options_t options = {false};
    int val = 0;
    srand(time(NULL));
    while ((val = getopt(argc, argv, "dh"))) {
        switch (val) {
            case 'd':
                options.delete = true;
                break;
            case 'h':
                print_help();
                return 0;
        }
    }
    return 0;
}

void print_help()
{
    int rows = rand() % 21;
    int columns = rand() % 21;
    for (int i = 0; i < rows; ++i) {
        int rand_capital = rand() % 21;
        for (int j = 0; j < columns; ++j) {
            j == rand_capital ? printf("A") : printf("a");
        }
        printf("\n");
    }
}
