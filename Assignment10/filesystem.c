/*
    Compile: make filesystem
    Run: ./filesystem
    Compile & run: make filesystem && ./filesystem
*/

#include "base.h"

typedef enum {
    NT_DIR,
    NT_FILE,
} NodeType;

#define MAX_NAME_LEN 63

typedef struct Node Node;
typedef struct Entry Entry;

// An entry in a directory. A directory is a linked list of entries.
struct Entry {
    Node* node;
    Entry* next;
};

// A node of the file system. Can either be a directory or a regular file.
struct Node {
    char name[MAX_NAME_LEN + 1];
    NodeType type;
    union {
        struct {
            Entry* entries; // list of directory entries
        } dir;
        struct {
            void* contents; // any binary data of the given length
            int length;
        } file;
    };
};

Entry* new_entry(Node* node, Entry* next) {
    require_not_null(node);
    Entry* entry = xmalloc(sizeof(Entry));
    entry->node = node;
    entry->next = next;
    return entry;
}

Node* new_node(char* name) {
    require_not_null(name);
    require("name not too long", strlen(name) <= MAX_NAME_LEN);
    Node* node = xmalloc(sizeof(Node));
    strncpy(node->name, name, MAX_NAME_LEN);
    node->name[MAX_NAME_LEN] = '\0';
    return node;
}

Node* new_file(char* name) {
    // TODO: implement (a)
    return NULL;
}

Node* new_directory(char* name) {
    // TODO: implement (a)
    return NULL;
}

// Inserts a new node into a directory.
// Ensures that the list of nodes remains sorted by their names.
void insert_into_directory(Node* directory, Node* new_node) {
    return; // TODO: remove
    require_not_null(directory);
    require_not_null(new_node);
    require("target is a directory", directory->type == NT_DIR);
    require("name not empty", *new_node->name != '\0');
    // TODO: implement (b)
}

// Recursively prints the files and directories in a node.
void print_node(Node* node, char* prefix) {
    if (node == NULL) return;
    require_not_null(prefix);
    int prefix_length;
    switch(node->type) {
    case NT_FILE:
        printf("%s%s\n", prefix, node->name);
        break;
    case NT_DIR:
        prefix_length = strlen(prefix) + strlen(node->name) + 2; // + slash + termination
        char new_prefix[prefix_length];
        snprintf(new_prefix, prefix_length, "%s%s/", prefix, node->name);
        for (Entry* entry = node->dir.entries; entry != NULL; entry = entry->next) {
            print_node(entry->node, new_prefix);
        }
        // print directory name, if directory is empty
        if (node->dir.entries == NULL) {
            printf("%s\n", new_prefix);
        }
        break;
    }
}

// Recursively frees the node.
void free_node(Node* node) {
    // TODO: implement (c)
}

// Tries to find a node in the entries of a directory.
Node* find_entry(Node* directory, char* name) {
    require_not_null(directory);
    require("is directory", directory->type == NT_DIR);
    for (Entry* entry = directory->dir.entries; entry != NULL; entry = entry->next) {
        if (strcmp(entry->node->name, name) == 0) {
            return entry->node;
        }
    }
    return NULL;
}

// Tries to find a node in the entries of a directory.
// Only matches the first n characters of name.
Node* find_entry_n(Node* directory, char* name, int n) {
    require_not_null(directory);
    require("is directory", directory->type == NT_DIR);
    for (Entry* entry = directory->dir.entries; entry != NULL; entry = entry->next) {
        if (strncmp(entry->node->name, name, n) == 0) {
            return entry->node;
        }
    }
    return NULL;
}

// Tries to find a node that corresponds to the given path, starting at the
// given root node.
Node* find_node(Node* root, char* path) {
    if (root == NULL) return NULL;
    require_not_null(path);
    // skip slashes at front
    while (*path == '/') path++;
    // if empty, return root
    if (*path == '\0') return root;
    // find path separator
    char* slash = strchr(path, '/');
    if (slash == NULL) {
        // TODO: implement (d)
        return NULL;
    } else {
        // TODO: implement (d)
        return NULL;
    }
}

// Appends length bytes from buffer to file. Returns true iff the data could
// actually be written.
bool write_file(Node* file, void* buffer, int length) {
    if (file == NULL || buffer == NULL || length <= 0) return true;
    if (file->type != NT_FILE) return false;
    int old_length = file->file.length;
    int new_length = old_length + length;
    char* p = xmalloc(new_length);
    if (old_length > 0) {
        assert("contents exists", file->file.contents != NULL);
        memcpy(p, file->file.contents, old_length);
        free(file->file.contents);
    }
    memcpy(p + old_length, buffer, length);
    file->file.contents = p;
    file->file.length = new_length;
    return true;
}

// Reads the contents of the file into buffer. If the file is larger than
// buffer, only the first length bytes are read. Returns the number of bytes
// read.
int read_file(Node* file, void* buffer, int length) {
    if (file == NULL || buffer == NULL || length <= 0) return 0;
    if (file->type != NT_FILE) return 0;
    int file_length = file->file.length;
    int n = file_length < length ? file_length : length;
    assert("contents exists", file->file.contents != NULL);
    memcpy(buffer, file->file.contents, n);
    return n;
}

int file_length(Node* file) {
    if (file == NULL) return 0;
    if (file->type == NT_FILE) return file->file.length;
    return 0;
}

int main(void) {
    report_memory_leaks(true); 

    // create a filesystem
    Node* root = new_directory("");

    // insert some directories and files
    Node* test_file = new_file("test.txt");
    insert_into_directory(root, test_file);
    insert_into_directory(root, new_file("hello.c"));
    insert_into_directory(root, new_file("world.c"));

    Node* home = new_directory("home");

    Node* user = new_directory("user");
    insert_into_directory(user, new_file("image.jpg"));
    Node* config_file = new_file("config.cfg");
    insert_into_directory(user, config_file);
    insert_into_directory(user, new_file("game.exe"));

    Node* todos = new_directory("TODO");
    insert_into_directory(user, todos);

    insert_into_directory(home, user);
    insert_into_directory(root, home);

    Node* system = new_directory("system");
    insert_into_directory(system, new_file("8_configuration.txt"));
    insert_into_directory(system, new_file("4_processes.txt"));

    Node* secret = new_directory("secret");
    Node* flag_file = new_file("flag.txt");
    insert_into_directory(secret, flag_file);
    Node* pin_file = new_file("pin.dat");
    insert_into_directory(secret, pin_file);

    insert_into_directory(root, system);
    insert_into_directory(system, secret);

    insert_into_directory(root, new_file("archive.a"));

    // output the filesystem's contents
    print_node(root, "");

    // make sure we can extract the contained nodes again
    test_equal_b(find_node(root, "") == root, true);
    test_equal_b(find_node(root, "/") == root, true);
    test_equal_b(find_node(root, "//") == root, true);
    test_equal_b(find_node(root, "x") == NULL, true);
    test_equal_b(find_node(root, "/test.txt") == test_file, true);
    test_equal_b(find_node(root, "/x/test.txt") == test_file, false);
    test_equal_b(find_node(root, "test.txt") == test_file, true);
    test_equal_b(find_node(root, "/test.txt/test.txt") == test_file, false);
    test_equal_b(find_node(root, "/test.txt/") == NULL, true);
    test_equal_b(find_node(root, "/system/secret/flag.txt") == flag_file, true);
    test_equal_b(find_node(root, "/home/user/config.cfg") == config_file, true);
    test_equal_b(find_node(root, "/home/user/config.cfg/test") == NULL, true);
    test_equal_b(find_node(root, "/home/user") == user, true);
    test_equal_b(find_node(root, "/home/user/") == user, true);
    test_equal_b(find_node(root, "/home/home/user") == user, false);
    test_equal_b(find_node(root, "/home/home") == NULL, true);
    test_equal_b(find_node(root, "home/home") == NULL, true);
    test_equal_b(find_node(root, "//home///user////") == user, true);
    test_equal_b(find_node(root, "/system/secret") == secret, true);
    test_equal_b(find_node(root, "/system/secret/") == secret, true);
    test_equal_b(find_node(root, "/system/secrets/") == NULL, true);
    test_equal_b(find_node(root, "/system/secret/does_not_exist") == NULL, true);
    test_equal_b(find_node(root, "/test.txt/") == NULL, true);
    test_equal_b(find_node(root, "/doesnot.exist") == NULL, true);
    test_equal_b(find_node(root, "/also/does/not/exist") == NULL, true);
    test_equal_b(find_node(root, "/world.c/invalid") == NULL, true);

    // test writing to and reading from files
    test_equal_b(write_file(test_file, "hello", 5), true);
    char buffer[64] = {0}; // zero-initialized buffer
    test_equal_i(read_file(test_file, buffer, 64), 5);
    test_equal_s(buffer, "hello");

    test_equal_b(write_file(test_file, " world", 6), true);
    test_equal_i(read_file(test_file, buffer, 64), 11);
    test_equal_s(buffer, "hello world");
    test_equal_i(file_length(test_file), 11);

    int pin = 1234;
    test_equal_b(write_file(pin_file, &pin, sizeof(int)), true);
    int x = 0;
    test_equal_i(read_file(pin_file, &x, sizeof(int)), 4);
    test_equal_i(x, 1234);
    test_equal_i(file_length(pin_file), 4);

    free_node(root);
    return 0;
}
