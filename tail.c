// tail.c
// IJC-DU2 - a)
// Ronald Bednár <xbednar00>
// 25.4.2024, FIT - VUT
// preložené: Apple clang version 15.0.0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 2047

typedef struct {
    char **buffer;
    int size;
    int start;
    int count;
} cbuf;

// Funckia poslúži na overenie platnosti argumemtu n
int is_all_digits(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit((unsigned char)str[i])) {
            return 0; // Vráti 0 ak niektorý zo zankov nie je číslo
        }
    }

    return 1; // Všetky znaky sú čislom
}

// Vytvorenie circular bufferu
cbuf* cbuf_create(int n) {
    if (n == 0) {
        return NULL;
    }

    cbuf *cb = malloc(sizeof(cbuf));
    if (cb == NULL) {
        fprintf(stderr, "Error allocating memory!\n");
        return NULL;
    }

    cb->buffer = malloc(sizeof(char*) * n);
    if (cb->buffer == NULL) {
        free(cb);
        fprintf(stderr, "Error allocating memory!\n");
        return NULL;
    }

    for (int i = 0; i < n; i++)
        cb->buffer[i] = NULL;

    cb->size = n;
    cb->start = 0;
    cb->count = 0;
    return cb;
}

// Uvoľnenie circular bufferu
void cbuf_free(cbuf *cb) {
    if (cb != NULL) {
        for (int i = 0; i < cb->size; i++)
            free(cb->buffer[i]);
        free(cb->buffer);
        free(cb);
    }
}

// Vloženie riadku do circular bufferu
void cbuf_put(cbuf *cb, const char *line) {
    int index = (cb->start + cb->count) % cb->size;

    if (cb->buffer[index] != NULL) {
        free(cb->buffer[index]);
    }
    cb->buffer[index] = strdup(line);

    if (cb->count < cb->size)
        cb->count++;
    else
        cb->start = (cb->start + 1) % cb->size;
}

// Získanie riadku z circular bufferu
void cbuf_get(cbuf *cb) {
    int index = cb->start;
    for (int i = 0; i < cb->count; i++) {
        printf("%s", cb->buffer[index]);
        index = (index + 1) % cb->size;
    }
    //printf("\n");
}

int main(int argc, char **argv) {
    int n = 10; // default hodnota (počet riadkov)
    char *filename = NULL;
    FILE *fp = stdin;

    // Zpracovanie argumentov
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0) {
            if (i + 1 < argc && is_all_digits(argv[i + 1])) {
                n = atoi(argv[i + 1]);
                if (n < 0) {
                    fprintf(stderr, "Error: Line count argument must be an non-negative integer\n");
                    return 1;
                }
                i++; // Preskočí následujúce čislo za -n
            } else {
                fprintf(stderr, "Error: Argument '-n' must be followed by non-negative integer.\n");
                return 1;
            }

        } else if (filename == NULL) {
            filename = argv[i];
        } else {
            fprintf(stderr, "Error: Unexpected argument or multiple files specified\n");
            return 1;
        }
    }

    if (filename != NULL) {
        fp = fopen(filename, "r");
        if (fp == NULL) {
            fprintf(stderr, "Error: Failed to open specified file\n");
            return 1;
        }
    }

    cbuf *cb = cbuf_create(n);
    if (cb == NULL && n > 0) return 1;

    if (cb) {
        char line[MAX_LINE_LENGTH + 2];
        while (fgets(line, sizeof(line), fp) != NULL) {
            if (strlen(line) > MAX_LINE_LENGTH) {
                fprintf(stderr, "Warning: Line length exceeds the limit\n");
                line[MAX_LINE_LENGTH] = '\n';
                line[MAX_LINE_LENGTH + 1] = '\0';
            }
            cbuf_put(cb, line);
        }

        cbuf_get(cb);
        cbuf_free(cb);
    }

    if (fp != stdin) fclose(fp);
    return 0;
}
