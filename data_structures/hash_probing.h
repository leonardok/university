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

int (*magic)(char *key, int step);
void (*print_colision_map)(hash_t hash[HASH_SIZE]);
void (*register_colision)(int position);
