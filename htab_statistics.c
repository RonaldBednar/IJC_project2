// htab_statistics.c
// IJC-DU2 - b)
// Ronald Bednár <xbednar00>
// 25.4.2024, FIT - VUT
// preložené: Apple clang version 15.0.0

#include "htab.h"
#include "htab_private.h"
#include <stdio.h>
#include <stdint.h>

void htab_statistics(const htab_t *t) {
    if (t == NULL || t->arr_size == 0) {
        fprintf(stderr, "Hash table is empty or uninitialized.\n");
        return;
    }

    size_t min_length = SIZE_MAX; // Najväčšia možná hodnota
    size_t max_length = 0;
    size_t total_items = 0;
    size_t non_empty_buckets = 0;

    for (size_t i = 0; i < t->arr_size; i++) {
        size_t chain_length = 0;
        for (struct htab_item *item = t->arr_ptr[i]; item != NULL; item = item->next) {
            chain_length++;
        }

        if (chain_length > 0) non_empty_buckets++;

        if (chain_length < min_length) min_length = chain_length;
        if (chain_length > max_length) max_length = chain_length;

        total_items += chain_length;
    }

    double avg_length;
    if (non_empty_buckets > 0) {
        avg_length = (double)total_items / non_empty_buckets;
    } else {
        avg_length = 0;
    }

    fprintf(stderr, "min: %zu, max: %zu, avg: %f", min_length, max_length, avg_length);
}
