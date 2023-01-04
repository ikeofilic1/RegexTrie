#ifndef _NEWTRIE
#define _NEWTRIE

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define BRDTH (32)
// This makes lowercase and uppercase ascii letters coincede in same position
//TODO: change to bounds checking instead
#define IDX(x) (((x+128))%BRDTH) //hack till w_char support

typedef struct trie Trie;

struct trie
{
    int8_t keys[BRDTH];
    uint8_t size;
    // Or just use this all the time
    uint16_t capacity;
    Trie **nodes;
};

void add_word(Trie*, char*);
int find_word(Trie*, char*);
void add_regex(Trie*, char*);
void free_trie(Trie*);
void print_trie_dfs(Trie*);
Trie *new_trie();

#endif
