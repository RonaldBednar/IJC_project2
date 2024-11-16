// htab_for_each.c
// IJC-DU2 - b)
// Ronald Bednár <xbednar00>
// 25.4.2024, FIT - VUT
// preložené: Apple clang version 15.0.0

#include "htab.h"
#include "htab_private.h"

// Použije zadanú funkciu na každý záznam v hash tabuľke
void htab_for_each(const htab_t *t, void (*f)(htab_pair_t *data)) {
    if (t == NULL || f == NULL) return;

    // Prechádza všetkými bucketmi v tabuľke
    for (size_t i = 0; i < t->arr_size; i++) {
        for (struct htab_item *item = t->arr_ptr[i]; item != NULL; item = item->next) {
            f(&item->pair); // Aplikuje funkciu 'f' na každý prvok
        }
    }
}
