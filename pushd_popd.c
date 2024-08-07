/*Implement pushd and popd Linux commands in C programming.

Conditions:
- Program must be compiled and executed in Linux environment
- Parogram should accept command-line arguments only
- Pre-build Linux applications such as ls, mkdir, etc, and pre-build functions like
system(), popen() should not be used in your application  */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_DIRS 100
#define MAX_PATH_LEN 1024

char *dir_stack[MAX_DIRS];
int top = -1;

void pushd(const char *dir) {
    if (top >= MAX_DIRS - 1) {
        fprintf(stderr, "Directory stack overflow\n");
        return;
    }
    char *cwd = (char *)malloc(MAX_PATH_LEN);
    if (getcwd(cwd, MAX_PATH_LEN) == NULL) {
        perror("getcwd");
        free(cwd);
        return;
    }
    dir_stack[++top] = cwd;
    if (chdir(dir) != 0) {
        perror("chdir");
        top--;
        free(cwd);
    }
}

void popd() {
    if (top < 0) {
        fprintf(stderr, "Directory stack underflow\n");
        return;
    }
    char *dir = dir_stack[top--];
    if (chdir(dir) != 0) {
        perror("chdir");
    }
    free(dir);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command> [directory]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "pushd") == 0) {
        if (argc != 3) {
            fprintf(stderr, "Usage: %s pushd <directory>\n", argv[0]);
            return 1;
        }
        pushd(argv[2]);
    } else if (strcmp(argv[1], "popd") == 0) {
        popd();
    } else {
        fprintf(stderr, "Unknown command: %s\n", argv[1]);
        return 1;
    }

    return 0;
}
