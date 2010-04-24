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
                        hash_func = &hashfy_linear_probing;
                        print_colision_map = &linear_colision_map;
                        break;
                case 'q':
                        hash_func = &quadratic_probing_hashfy;
                        print_colision_map = &quadratic_colision_map;
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
                                int pos = hash_func(hash, word);
                                printf("position %d -> '%s'\n",pos, hash[pos].value);
                                word[0] = '\0';
                        }
                }
        }

        printf("======================\n");
        print_colision_map(hash);
        return 0;
}
