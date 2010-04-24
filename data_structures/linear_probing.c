#include "hash_probing.h"

/* global variables */
int hash_linear_colisions[HASH_SIZE];
int linear_total_colisions;

void linear_colision_map(hash_t hash[HASH_SIZE]){
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
                for(j=0;j<hash_linear_colisions[i];j++){
                        printf("-");
                        linear_total_colisions++;
                }
                printf("\n");
        }
        printf("Total of colisions were: %d\n", linear_total_colisions);
}

int linear_find_magic(char *key, int step){
        int i;

        int magic_key = step;
        for(i=0; i<strlen(key); i++){
                magic_key += (unsigned int) key[i];
        }
        return magic_key;
}

int hashfy_linear_probing(hash_t hash[HASH_SIZE], char *key){
        int hashed_key, hash_position;
        hash_t *h, *p;
        int i;

        for(i=0;i<PROBING_TRIES;i++){
                hashed_key = linear_find_magic(key, i);
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

                        hash_linear_colisions[hash_position]++;
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


