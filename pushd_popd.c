/*Implement pushd and popd Linux commands in C programming.

Conditions:
- Program must be compiled and executed in Linux environment
- Parogram should accept command-line arguments only
- Pre-build Linux applications such as ls, mkdir, etc, and pre-build functions like
system(), popen() should not be used in your application  */

typedef struct Node {
    char directory[1024];
    struct Node* next;
} Node;

Node* head = NULL;

void pushd(const char* dir) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    if (realpath(dir, new_node->directory) == NULL) {
        perror("Invalid directory");
        free(new_node);
        exit(EXIT_FAILURE);
    }

    new_node->next = head;
    head = new_node;

    if (chdir(new_node->directory) != 0) {
        perror("Failed to change directory");
        exit(EXIT_FAILURE);
    }

    printf("Directory pushed: %s\n", new_node->directory);
}

void popd() {
    if (head == NULL) {
        fprintf(stderr, "Directory stack is empty\n");
        return;
    }

    Node* temp = head;
    head = head->next;

    if (chdir(head != NULL ? head->directory : getenv("HOME")) != 0) {
        perror("Failed to change directory");
        exit(EXIT_FAILURE);
    }

    printf("Directory popped: %s\n", temp->directory);
    free(temp);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [pushd <dir> | popd]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[1], "pushd") == 0) {
        if (argc != 3) {
            fprintf(stderr, "Usage: %s pushd <dir>\n", argv[0]);
            exit(EXIT_FAILURE);
        }
        pushd(argv[2]);
    } else if (strcmp(argv[1], "popd") == 0) {
        popd();
    } else {
        fprintf(stderr, "Unknown command: %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    return 0;
}
