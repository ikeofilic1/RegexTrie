#include "trie.h"

Trie *new_trie() {
    Trie *new = malloc(sizeof(Trie));
    assert(new && "Could not allocate memory for new trie");
    
    new->size = 0;    
    new->nodes = malloc(4*sizeof(Trie*));
    new->capacity = (new->nodes)?4:0;
          
    memset(new->keys, -1, BRDTH);

    return new;
}

void add_node(Trie *nd, int idx) {
    #define _nd (nd->nodes) 
    unsigned int sz = (nd->size)++;
    
    if (sz == nd->capacity) {
        nd->capacity *= 2;
        _nd = realloc(_nd, 2*sz*sizeof(void*));
        assert(_nd && "add_node: Could not allocate memory for trie node");
        //printf("sz: %d <=> mallocd: %ld\n", sz, mallocd_size(_nd));
    }
    nd->keys[idx] = sz;
    _nd[sz] = new_trie();

    #undef _nd
}

int find_word(Trie *root, char *word) {
    if (root == NULL) return 0;
    int sz = strlen(word);

    Trie *curr = root;
    for (int i = 0; i < sz; ++i) {
        if (curr->keys[IDX(word[i])] == -1) return 0;

        else if (IDX(word[i]) != IDX('@')) 
            curr = curr->nodes[curr->keys[IDX(word[i])]];
    }

    if (curr->keys[IDX('@')] != BRDTH+1) 
        return 0;
    else return 1;
}

void add_word (Trie* root, char* word) {
    if (root == NULL) return;
    int sz = strlen(word);

    Trie *curr = root;
    for (int i = 0; i < sz; ++i)
    {   
        //upper and lower-case maps to same index coincidentally
        if (curr->keys[IDX(word[i])] == -1) {
            add_node(curr, IDX(word[i]));
        }
        if (IDX(word[i]) != IDX('@'))  curr = curr->nodes[curr->keys[IDX(word[i])]];
    }

    curr->keys[IDX('@')] = BRDTH+1;
}

void add_regex(Trie* root, char* word) {
    add_word(root, word);

    Trie *cur = root;
    int sz = strlen(word);

    for (int i = 0; i < sz; ++i) {
        if (i) {
            if (IDX(word[i-1]) != IDX('@'))
                cur = cur->nodes[cur->keys[IDX(word[i-1])]]; //only if words have @
        }

        if (IDX(word[i]) != IDX('@')) { //only if words have @
            if (cur->keys[IDX('?')] == -1)
                add_node(cur, IDX('?'));
            add_regex(cur->nodes[cur->keys[IDX('?')]], word+i+1); 
        }
    }
}

void free_trie(Trie* root) {
    //if (!root) return;
    
    int sz = root->size;
    for (int i = 0; i < sz; ++i) {
        free_trie(root->nodes[i]);
    }
    
    if (root->nodes == NULL) puts("It was NULL!!\n");
    free(root->nodes);
    free(root);
}

void dfs_helper(Trie *root, char** sofar, int *cap, int lv) {
    if (lv == *cap) {
        (*cap) *= 2;
        *sofar = realloc(*sofar, ((*cap)+1)*sizeof(char));
    }

    for (int i = 0; i < BRDTH; ++i) {
        if (root->keys[i] != -1) {
            if (i == IDX('@')) {
                sofar[0][lv] = '\0';
                printf("%s\n", *sofar);
            }   
            else{
                sofar[0][lv] = '?'+i;
                dfs_helper(root->nodes[root->keys[i]], sofar, cap, lv+1);
            }
        }
    }
}

void print_trie_dfs(Trie* root) {
    if (!root) return;
    int cap = 5;
    char *x = malloc((cap+1)*sizeof(char));
    dfs_helper(root, &x, &cap, 0);
    free(x);
}
