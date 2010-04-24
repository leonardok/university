#define C1 1
#define C2 2

/* global variables */
int quadratic_hash_colisions[HASH_SIZE];
int quadratic_total_colisions;

/* function prototypes */
void quadratic_colision_map(hash_t hash[HASH_SIZE]);
void quadratic_register_colision(int position);
int  quadratic_find_magic(char *key, int step);
