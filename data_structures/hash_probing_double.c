#include "hash_probing.h"
#include "hash_probing_double.h"

void double_colision_map(hash_t hash[HASH_SIZE]){
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
                for(j=0;j<double_hash_colisions[i];j++){
                        printf("-");
                        double_total_colisions++;
                }
                printf("\n");
        }
        printf("Total of colisions were: %d\n", double_total_colisions);
}

void double_register_colision(int position){
        double_hash_colisions[position]++;
}


int double_find_magic(char *key, int step){
        /* first hash: ASCII value of the char
         * second hash: ASCII value of the char times position
         *              inside the string backwards
        **/
        int magic_key_1 = 0;
        int magic_key_2 = 0;
        int str_sz = strlen(key);
        int i;
        for(i=0; i<str_sz; i++){
                magic_key_1 += (unsigned int) key[i];
                magic_key_2 += (unsigned int) key[i] & step;
        }

        return (magic_key_1 + magic_key_2);
}

