#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#define HASH_SIZE 73

typedef struct hash_s hash_t;
struct hash_s {
        char *value;
        hash_t *next;
};
hash_t hash[HASH_SIZE];

void ini_hash(void){
        int i;
        for(i=0; i<HASH_SIZE; i++){
                hash[i].value = NULL;
        }
}

int find_magic(char *key){
        int magic_key = 0;
        int i;
        for(i=0; i<strlen(key); i++){
                magic_key += (unsigned int) key[i];
        }
        return magic_key;
}

void describe_hash(void){
        int i;
        for(i=0; i<HASH_SIZE; i++){
                printf("Position %d: ", i);
                hash_t *h = &hash[i];
                while(h && h->value){
                        printf("+");
                        h = h->next;
                }
                printf("\n");
        }
}

int hashfy(char *key){
        /* find magic */
        int hashed_key = find_magic(key);
        int hash_position = hashed_key % HASH_SIZE;

        hash_t *h = &hash[hash_position];
        hash_t *p = NULL;

        if(h->value == NULL){
                h->value = malloc(sizeof(char)*(strlen(key)+1));
                strcpy(h->value, key);
        }
        else if(strncmp(h->value, key, strlen(key)) != 0){
                p = h;
                h = h->next;
                while((h != NULL)){
                        if (strncmp(h->value, key, strlen(key)) == 0) break;
                        p = h;
                        h = h->next;
                }
                
                if(h == NULL || strcmp(h->value, key) != 0){
                        h = malloc(sizeof(hash_t));
                        if(p) p->next = h;
                        h->value = malloc(sizeof(char)*(strlen(key)+1));
                        strcpy(h->value, key);
                }

        }
        return 0;
}

int main(void){
        printf("Welcome, this hash does linear hashing\n");
        printf("Hash size is %d\n", HASH_SIZE);

        int fp;
        if((fp = open("words", O_RDONLY)) < 0){
                printf("could not open dictionary file.\n");
                exit(-1);
        }

        /* get file contents */
        char buffer[512];
        char word[25];
        int word_pos = 0;
        while(read(fp, buffer, 512)){
                int buffer_pos;
                for(buffer_pos=0; buffer_pos<512; buffer_pos++){
                        char ch = buffer[buffer_pos];
                        if((ch > 65 && ch < 90) || (ch > 97 && ch < 122)){
                                word[word_pos++] = ch;
                                word[word_pos] = '\0';
                        }
                        else if(strlen(word) > 0){
                                word_pos = 0;
                                hashfy(word);

                                word[0] = '\0';
                        }   
                }
        }

        describe_hash();
        return 0;
}
