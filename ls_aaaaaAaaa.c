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
// #define 回答 return
// #define 主要 main
// #define 数字 int
// #define 字 char

typedef struct options {
    bool delete;
    bool colours;
    bool show_hidden;
} options_t;

void print_help();

int main(int argc, char **argv)
{
    // handle flag arguments
    srand(time(NULL));
    options_t options = {false, false, false};
    int val = 0;
    while ((val = getopt(argc, argv, "dhca")) != -1) {
        switch (val) {
            case 'd':
                options.delete = true;
                break;
            case 'c':
                options.colours = true;
                break;
            case 'a':
                options.show_hidden = true;
                break;
            case 'h':
                print_help();
                return 0;
        }
    }

    // get all files in working directory
    bool havent_deleted = true;
    struct dirent *dir_entry;
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("Did not work\n");
        exit(EXIT_FAILURE);
    }

    // read through them
    while ((dir_entry = readdir(dir)) != NULL) {
        if ((dir_entry->d_name[0] == '.') && (options.show_hidden == false)) {
            continue;
        }
        if (havent_deleted && (options.delete == true)) {
            if (remove(dir_entry->d_name)) {
                continue;
            }
            havent_deleted = false;
            continue;
        }
        int before = rand() % 51;
        int after = rand() % 51;
        bool new_line = rand() % 2;
        for (int i = 0; i < before; ++i) {
            printf(" ");
        }
        if (options.colours == true) {
            int rand_colour = rand() % 6;
            switch (rand_colour) {
                case 0:
                    printf(RED "%s" RESET, dir_entry->d_name);
                    break;
                case 1:
                    printf(GREEN "%s" RESET, dir_entry->d_name);
                    break;
                case 2:
                    printf(YELLOW "%s" RESET, dir_entry->d_name);
                    break;
                case 3:
                    printf(BLUE "%s" RESET, dir_entry->d_name);
                    break;
                case 4:
                    printf(MAGENTA "%s" RESET, dir_entry->d_name);
                    break;
                case 5:
                    printf(CYAN "%s" RESET, dir_entry->d_name);
                    break;
            }
        } else {
            printf("%s", dir_entry->d_name);
        }
        for (int i = 0; i < after; ++i) {
            printf(" ");
        }
        if (new_line)
            printf("\n");
    }

    printf("\n");
    closedir(dir);
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
