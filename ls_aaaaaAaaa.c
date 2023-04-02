#include <getopt.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>

// colours
// https://stackoverflow.com/questions/3219393/stdlib-and-colored-output-in-c
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

// #define 正在 while
#define 回答 return
#define 为 for
#define 主要 main
#define 数字 int
#define 字 char
#define 打印 printf
#define 对不对 bool
#define 开关 switch
#define 打破 break
#define 如果 if
#define 箱子 case 

typedef struct options {
    对不对 delete;
    对不对 colours;
    对不对 show_hidden;
} options_t;

void print_help();

数字 主要(数字 argc, 字 **argv)
{
    // handle flag arguments
    srand(time(NULL));
    options_t options = {false, false, false};
    数字 val = 0;
    while ((val = getopt(argc, argv, "dhca")) != -1) {
        开关 (val) {
            箱子 'd':
                options.delete = true;
                打破;
            箱子 'c':
                options.colours = true;
                打破;
            箱子 'a':
                options.show_hidden = true;
                打破;
            箱子 'h':
                print_help();
                回答 0;
        }
    }

    // get all files in working directory
    对不对 havent_deleted = true;
    struct dirent *dir_entry;
    DIR *dir = opendir(".");
    如果 (dir == NULL) {
        perror("Did not work\n");
        exit(EXIT_FAILURE);
    }

    // read through them
    while ((dir_entry = readdir(dir)) != NULL) {
        如果 ((dir_entry->d_name[0] == '.') && (options.show_hidden == false)) {
            continue;
        }
        如果 (havent_deleted && (options.delete == true)) {
            如果 (remove(dir_entry->d_name)) {
                continue;
            }
            havent_deleted = false;
            continue;
        }
        数字 before = rand() % 51;
        数字 after = rand() % 51;
        对不对 new_line = rand() % 2;
        for (数字 i = 0; i < before; ++i) {
            打印(" ");
        }
        如果 (options.colours == true) {
            数字 rand_colour = rand() % 6;
            开关 (rand_colour) {
                箱子 0:
                    打印(RED "%s" RESET, dir_entry->d_name);
                    打破;
                箱子 1:
                    打印(GREEN "%s" RESET, dir_entry->d_name);
                    打破;
                箱子 2:
                    打印(YELLOW "%s" RESET, dir_entry->d_name);
                    打破;
                箱子 3:
                    打印(BLUE "%s" RESET, dir_entry->d_name);
                    打破;
                箱子 4:
                    打印(MAGENTA "%s" RESET, dir_entry->d_name);
                    打破;
                箱子 5:
                    打印(CYAN "%s" RESET, dir_entry->d_name);
                    打破;
            }
        } else {
            打印("%s", dir_entry->d_name);
        }
        for (数字 i = 0; i < after; ++i) {
            打印(" ");
        }
        如果 (new_line)
            打印("\n");
    }

    打印("\n");
    closedir(dir);
    回答 0;
}

void print_help()
{
    数字 rows = rand() % 21;
    数字 columns = rand() % 21;
    for (数字 i = 0; i < rows; ++i) {
        数字 rand_capital = rand() % 21;
        for (数字 j = 0; j < columns; ++j) {
            j == rand_capital ? 打印("A") : 打印("a");
        }
        打印("\n");
    }
}
