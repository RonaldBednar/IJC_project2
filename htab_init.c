// htab_init.c
// IJC-DU2 - b)
// Ronald Bednár <xbednar00>
// 25.4.2024, FIT - VUT
// preložené: Apple clang version 15.0.0

#include <stdlib.h>
#include <stdio.h>
#include "htab.h"
#include "htab_private.h"

// Konštruktor: vytvorí hashovaciu tabuľku s počtom položiek n.
htab_t *htab_init(size_t n) {
    htab_t *table = malloc(sizeof(htab_t));
    if (table == NULL) {
        fprintf(stderr, "Error allocating memory!\n");
        return NULL;
    }

    table->arr_ptr = malloc(n * sizeof(struct htab_item *));
    if (table->arr_ptr == NULL) {
        fprintf(stderr, "Error allocating memory!\n");
        free(table);
        return NULL;
    }

    table->size = 0;
    table->arr_size = n;

    for (size_t i = 0; i < n; i++) {
        table->arr_ptr[i] = NULL;
    }

    return table;
}
