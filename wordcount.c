// wordcount.c
// IJC-DU2 - b)
// Ronald Bednár <xbednar00>
// 25.4.2024, FIT - VUT
// preložené: Apple clang version 15.0.0

#include "htab.h"
#include "io.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_WORD_LENGTH 256
#define HTAB_SIZE 100000


void print_word_count(htab_pair_t *data) {
    printf("%s\t%d\n", data->key, data->value);
}

int main() {
    htab_t *table = htab_init(HTAB_SIZE);  // Initialize the hash table with a suitable size
    if (table == NULL) {
        fprintf(stderr, "Error allocating memory!\n");
        return EXIT_FAILURE;
    }

    char word[MAX_WORD_LENGTH + 1];
    while (read_word(word, MAX_WORD_LENGTH, stdin) != EOF) {
        // Lookup the word in the hash table or add it if it does not exist
        htab_pair_t *item = htab_lookup_add(table, word);
        if (item == NULL) {
            fprintf(stderr, "Error allocating memory!\n");
            htab_free(table);
            return EXIT_FAILURE;
        }
        item->value++;
    }

    // Print all words and their counts using htab_for_each
    htab_for_each(table, print_word_count);

    // Free the hash table
    htab_free(table);
    return EXIT_SUCCESS;
}


