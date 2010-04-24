#include "hash_probing.h"
#include "hash_probing_quadratic.h"

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

void quadratic_register_colision(int position){
        quadratic_hash_colisions[position]++;
}

int quadratic_find_magic(char *key, int step){
        int magic_key = 0;
        int i;
        for(i=0; i<strlen(key); i++){
                magic_key += (unsigned int) key[i];
        }

        /* add modifier */
        magic_key += (C1 * step) + (C2 * step * step);

        return magic_key;
}
