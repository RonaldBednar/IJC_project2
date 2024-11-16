// htab_bucket_count.c
// IJC-DU2 - b)
// Ronald Bednár <xbednar00>
// 25.4.2024, FIT - VUT
// preložené: Apple clang version 15.0.0

#include "htab.h"
#include "htab_private.h"

// Vráti počet prvkov poľa (.arr_size).
size_t htab_bucket_count(const htab_t * t) {
    return t->arr_size;
}
