// htab_size.c
// IJC-DU2 - b)
// Ronald Bednár <xbednar00>
// 25.4.2024, FIT - VUT
// preložené: Apple clang version 15.0.0

#include "htab.h"
#include "htab_private.h"

// Počet záznamov (prvkov) v tabuľke
size_t htab_size(const htab_t * t) {
    return t->size;
}
