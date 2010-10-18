/**
 * @file   adaptative_huffman.h
 * @Author Leonardo Korndorfer (leokorndorfer@gmail.com)
 * @date   September, 2010
 *
 * @brief  This file has complement stuff
 *
 * Detailed description of file.
 */


#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__

#define NYT  -1
#define NODE 0
#define LEAF 1

typedef struct structure_huffman_tree type_ahuffman_tree;
struct  structure_huffman_tree 
{
    char value;
    int  weight;
    
    type_ahuffman_tree *parent;
    type_ahuffman_tree *l_child;
    type_ahuffman_tree *r_child;
};


int ahuffman_begin_tree(char *);
int ahuffman_rotate_tree(void);
int ahuffman_new_node(char c, int times, type_ahuffman_tree **);
int ahuffman_write_encoded(void);
int ahuffman_encode(char *);

#endif
