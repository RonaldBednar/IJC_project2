// io.c
// IJC-DU2 - b)
// Ronald Bednár <xbednar00>
// 25.4.2024, FIT - VUT
// preložené: Apple clang version 15.0.0

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

// Funkcia načíta jedno slovo zo súboru f do zadaného poľa znakov a vracia jeho dĺžku
// Pri dlhých slovách načíta max-1 znakov a zbytok preskočí
int read_word(char *s, int max, FILE *f) {
    int c, len = 0;
    bool too_long = false;
    static bool warning_printed = false;

    while ((c = fgetc(f)) != EOF && isspace(c));

    if (c == EOF) {
        return EOF;
    }

    do {
        if (len < max-1) {
            s[len++] = c;
        } else {
            if (!too_long) {
                too_long = true;
                if (!warning_printed) {
                    fprintf(stderr, "Warning: Word length exceeds maximum of %d characters. Truncating.\n", max-1);
                    warning_printed = true;  // Zabráni opakovanému výpisu varovania
                }
            }
        }
    } while ((c = fgetc(f)) != EOF && !isspace(c));

    s[len] = '\0';
    return len;
}
