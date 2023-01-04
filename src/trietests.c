#include "trie.h"

char *trim(char *word) {
    int x = strlen(word)-1;
    if (x >= 0 && word[x] == '\n') word[x] = '\0';
    return word;
}

void add_words_from_file(Trie *head, FILE *fp) {
    char *line = NULL;
    size_t size = 0;
    while (getline(&line, &size, fp) != -1)
    {
        //printf("%s", line);
        add_word(head, trim(line));
    }
    free(line);    
}

int main(int argc, char **argv) {
    Trie *head = new_trie();

    if (argc == 1) {
        printf("Usage: %s files...\n", argv[0]);
        exit(1);
    }

    for (int i = 1; i < argc; ++i) {
        FILE *f = fopen(argv[i], "r");
        if (!f) {
            fprintf(stderr, "In option \"%s\":\n", argv[i]);
            perror("An error occurred while opening file");
            continue;
        }
        add_words_from_file(head, f);
        fclose(f);
    }

    char *line = NULL;
    size_t val = 0;
    do{
        if (line) {
            printf("Word: %s", line);
            printf("%s\n\n", find_word(head, trim(line))?"found":"not found");
        }
        printf("Enter word to find: ");
    } while (getline(&line, &val, stdin) > 1);
    
    free(line);
    //print_trie_dfs(head);
    free_trie(head);
    return 0;
}
