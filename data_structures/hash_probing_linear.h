/* global variables */
int linear_hash_colisions[HASH_SIZE];
int linear_total_colisions;

/* function prototypes */
void linear_colision_map(hash_t hash[HASH_SIZE]);
void linear_register_colision(int position);
int  linear_find_magic(char *key, int step);
