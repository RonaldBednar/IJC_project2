// htab_find.c
// IJC-DU2 - b)
// Ronald Bednár <xbednar00>
// 25.4.2024, FIT - VUT
// preložené: Apple clang version 15.0.0

#include "htab.h"
#include "htab_private.h"
#include <string.h>

// Nájde záznam zo zadaného kľúčom z hash tabuľky
htab_pair_t *htab_find(const htab_t *t, htab_key_t key) {
    // Vypočíta hash value daného kľúča
    size_t index = htab_hash_function(key) % t->arr_size;
    
    // Ukazovateľ na prvú položku bucketu
    struct htab_item *ptr = t->arr_ptr[index];
    
    // Prechádza celý chain na danom indexe
    while (ptr != NULL) {
        if (strcmp(key, ptr->pair.key) == 0) {
            // Ak nájde zhodu, vráti pointer na pair
            return &ptr->pair;
        }
        
        ptr = ptr->next;
    }
    
    // Sem sa funkcia dostane ak daný kľúč nenájde
    return NULL;
}
