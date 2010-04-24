#include "hash_probing.h"
#include "hash_probing_linear.h"

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
                for(j=0;j<linear_hash_colisions[i];j++){
                        printf("-");
                        linear_total_colisions++;
                }
                printf("\n");
        }
        printf("Total of colisions were: %d\n", linear_total_colisions);
}

void linear_register_colision(int position){
        linear_hash_colisions[position]++;
}

int linear_find_magic(char *key, int step){
        int i;

        int magic_key = step;
        for(i=0; i<strlen(key); i++){
                magic_key += (unsigned int) key[i];
        }
        return magic_key;
}
