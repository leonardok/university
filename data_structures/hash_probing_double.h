/* global variables */
int double_hash_colisions[HASH_SIZE];
int double_total_colisions;

/* function prototypes */
void double_colision_map(hash_t hash[HASH_SIZE]);
void double_register_colision(int position);
int  double_find_magic(char *key, int step);
