#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#define HASH_SIZE 73
#define STEP_SIZE 1
#define PROBING_TRIES 10

typedef struct hash_s hash_t;
struct hash_s {
        char *value;
        hash_t *next;
};

int (*hash_func)(hash_t hash[HASH_SIZE], char *key);
void (*print_colision_map)(hash_t hash[HASH_SIZE]);
