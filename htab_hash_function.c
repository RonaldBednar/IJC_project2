// htab_hash_function.c
// IJC-DU2 - b)
// Ronald Bednár <xbednar00>
// 25.4.2024, FIT - VUT
// preložené: Apple clang version 15.0.0

#include <stdint.h>
#include "htab.h"

// Rozptylovacia (hash) funkcia pre reťazce - varianta sdbm
// Zdroj: http://www.cse.yorku.ca/~oz/hash.html

size_t htab_hash_function(const char *str) {
  uint32_t h = 0;   // musí mať 32 bitov
  const unsigned char *p;
  for (p = (const unsigned char *)str; *p != '\0'; p++) {
    h = 65599 * h + *p;
  }
  return h;
}
