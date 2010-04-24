#include "hash_probing.h"
#include "hash_probing_linear.h"
#include "hash_probing_quadratic.h"

void show_usage(char *cmd){
        printf("Usage is: %s [-l|-q]\n", cmd);
        exit(-1);
}

void ini_hash(hash_t *hash){
        int i;
        for(i=0; i<HASH_SIZE; i++){
                hash[i].value = NULL;
        }
}

int hashfy(hash_t hash[HASH_SIZE], char *key){
        int hashed_key, hash_position;
        hash_t *h, *p;
        int i;

        for(i=0;i<PROBING_TRIES;i++){
                hashed_key = magic(key, i);
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

                        printf("  passou\n");
                        register_colision(hash_position);
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


int main(int argc, char **argv){
        printf("argc is %d", argc);
        if(argc < 2){
                show_usage(argv[0]);
        }
        hash_t hash[HASH_SIZE];
        ini_hash(hash);

        printf("Welcome, this multi hash testing app\n");
        printf("Hash size is %d\n", HASH_SIZE);

        printf("Chosen Hash was '%s'\n", argv[1]);

        int fp;
        if((fp = open("words", O_RDONLY)) < 0){
                printf("could not open dictionary file.\n");
                exit(-1);
        }

        switch(argv[1][1]){
                case 'l':
                        magic = &linear_find_magic;
                        print_colision_map = &linear_colision_map;
                        register_colision  = &linear_register_colision;
                        break;
                case 'q':
                        magic = &quadratic_find_magic;
                        print_colision_map = &quadratic_colision_map;
                        register_colision  = &quadratic_register_colision;
                        break;
                default: show_usage(argv[0]);;
        }

        /* get file contents */
        char buffer[512];
        char word[40]; 
        int word_pos = 0;
        int read_size = 0;
        while((read_size = read(fp, buffer, 512))){
                int buffer_pos;
                for(buffer_pos=0; buffer_pos<read_size; buffer_pos++){
                        char ch = buffer[buffer_pos];
                        if((ch != 46 || ch != 44) && 
                          ((ch >= 48 && ch <= 57) || 
                           (ch >= 65 && ch <= 90) ||
                           (ch >= 97 && ch <= 122)||
                           (ch == 39 || ch == 45)
                          )){
                                word[word_pos++] = ch;
                                word[word_pos] = '\0';
                        }
                        else if(strlen(word) > 0){
                                word_pos = 0;
                                int pos = hashfy(hash, word);
                                printf("position %d -> '%s'\n",pos, hash[pos].value);
                                word[0] = '\0';
                        }
                }
        }

        printf("======================\n");
        print_colision_map(hash);
        return 0;
}
