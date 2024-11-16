// htab_free.c
// IJC-DU2 - b)
// Ronald Bednár <xbednar00>
// 25.4.2024, FIT - VUT
// preložené: Apple clang version 15.0.0

#include "htab.h"
#include "htab_private.h"
#include <stdlib.h>

// Deštruktor - uvoľní všetky záznamy v hash tabuľky a uvoľní pamäť.
void htab_free(htab_t *t) {
    if (t == NULL) return;

    htab_clear(t); 
    free(t->arr_ptr);
    free(t);
}
