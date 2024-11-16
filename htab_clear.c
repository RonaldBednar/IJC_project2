// htab_clear.c
// IJC-DU2 - b)
// Ronald Bednár <xbednar00>
// 25.4.2024, FIT - VUT
// preložené: Apple clang version 15.0.0

#include "htab.h"
#include "htab_private.h"
#include <stdlib.h>

// Zruší všetky položky v hash tabuľke
void htab_clear(htab_t *t) {
    if (t == NULL) return;

    // Prechádza všetky záznamy v hash tabuľke
    for (size_t i = 0; i < t->arr_size; i++) {
        struct htab_item *current_item = t->arr_ptr[i];
        while (current_item != NULL) {
            struct htab_item *next_item = current_item->next;

            // Uvoľní pamäť alokovanú pre key
            free((void *)current_item->pair.key);

            // Uvoľní pamäť pre aktuálny záznam
            free(current_item);

            // Presunie sa na ďalší záznam
            current_item = next_item;
        }

        // po prevedení sa ukazovateľ v poli nastaví na NULL
        t->arr_ptr[i] = NULL;
    }
    t->size = 0;

}
