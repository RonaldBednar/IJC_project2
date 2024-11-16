// htab_erase.c
// IJC-DU2 - b)
// Ronald Bednár <xbednar00>
// 25.4.2024, FIT - VUT
// preložené: Apple clang version 15.0.0

#include "htab.h"
#include "htab_private.h"
#include <stdlib.h>
#include <string.h>

// Vymaže záznam zo zadaného kľúčom z hash tabuľky
bool htab_erase(htab_t *t, htab_key_t key) {
    if (t == NULL || key == NULL) return false;

    size_t index = htab_hash_function(key) % t->arr_size;
    struct htab_item **ptr = &t->arr_ptr[index];

    while (*ptr != NULL) {
        if (strcmp((*ptr)->pair.key, key) == 0) {
            struct htab_item *to_remove = *ptr; // Záznam, ktorý sa má odstrániť
            *ptr = to_remove->next;

            free((void *)to_remove->pair.key);
            free(to_remove); // Uvoľnenie pamäte

            t->size--; // Dekrementuje veľkosť hash tabuľky
            return true;
        }
        ptr = &(*ptr)->next;
    }

    return false; // Sem sa funkcia dostane ak daný kľúč neexistuje
}
