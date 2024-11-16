// htab_lookup_add.c
// IJC-DU2 - b)
// Ronald Bednár <xbednar00>
// 25.4.2024, FIT - VUT
// preložené: Apple clang version 15.0.0

#include "htab.h"
#include "htab_private.h"
#include <string.h>
#include <stdlib.h>

// Hľadá záznam v hashovacej tabuľke a pridá ho, ak sa v nej nenachádza.
htab_pair_t *htab_lookup_add(htab_t *t, htab_key_t key) {
    if (t == NULL || key == NULL) {
        return NULL;
    }

    size_t idx = htab_hash_function(key) % t->arr_size;
    struct htab_item **ptr = &(t->arr_ptr[idx]);

    while (*ptr != NULL) {
        if (strcmp((*ptr)->pair.key, key) == 0) {
            return &((*ptr)->pair);
        }
        ptr = &((*ptr)->next);
    }

    struct htab_item *new_item = malloc(sizeof(struct htab_item));
    if (new_item == NULL) {
        return NULL;
    }

    new_item->pair.key = strdup(key);
    new_item->pair.value = 0;
    new_item->next = NULL;

    *ptr = new_item;

    t->size++;

    return &(new_item->pair);
}
