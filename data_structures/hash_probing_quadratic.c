#include "hash_probing.h"
#include "hash_probing_quadratic.h"

/* global variables */
int quadratic_hash_colisions[HASH_SIZE];
int quadratic_total_colisions;

void quadratic_colision_map(hash_t hash[HASH_SIZE]){
        int i;
        for(i=0; i<HASH_SIZE; i++){
                printf("Position %d: ", i);
                int j;
                //if(hash[i].value) printf("+");
                hash_t *h = &hash[i];
                while(h && h->value){
                        printf("+");
                        h = h->next;
                }
                for(j=0;j<quadratic_hash_colisions[i];j++){
                        printf("-");
                        quadratic_total_colisions++;
                }
                printf("\n");
        }
        printf("Total of colisions were: %d\n", quadratic_total_colisions);
}

int quadratic_find_magic(char *key, int step, int c1, int c2){
        int magic_key = 0;
        int i;
        for(i=0; i<strlen(key); i++){
                magic_key += (unsigned int) key[i];
        }

        /* add modifier */
        magic_key += (c1 * step) + (c2 * step * step);

        return magic_key;
}

int quadratic_probing_hashfy(hash_t hash[HASH_SIZE], char *key){
        int hashed_key, hash_position;
        hash_t *h, *p;
        int i;
        int c1 = 1; int c2 = 2;

        for(i=0;i<PROBING_TRIES;i++){
                hashed_key = quadratic_find_magic(key, i, c1, c2);
                hash_position = hashed_key % (HASH_SIZE);
                h = &hash[hash_position];
                p = NULL;

                if(!h->value){
                        h->value = malloc(sizeof(char)*(strlen(key)+1));
                        strcpy(h->value, key);
                        h->next = NULL;
                        return hash_position;
                }
                else {
                        printf("  comp %d:'%s' <- '%s'\n", hash_position, h->value, key);
                        /* if same value admit is not a colision */
                        if(strncmp(h->value, key, strlen(key)) == 0){
                                printf("same word!\n");
                                return 0;
                        }

                        quadratic_hash_colisions[hash_position]++;
                }
                printf("  probing\n");
        }

        /* could not put it by probing, so chain it */
        while(h && h->value){
                if (strncmp(h->value, key, strlen(key)) == 0) return 0;
                p = h;
                h = h->next;
        }
        h = malloc(sizeof(hash_t));
        h->value = malloc(sizeof(char)*(strlen(key)+1));
        h->next = NULL;
        p->next = h;
        strcpy(h->value, key);
        printf("inserted word %s\n", key);

        return 0;
}


