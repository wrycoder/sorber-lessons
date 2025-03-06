

#include "hashtable.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 4096


uint64_t hash(const char *data, size_t length) {
    uint64_t hash_value = 0;
    for (int i=0; i < length; i++) {
        hash_value += data[i];
        hash_value = hash_value * data[i];
    }
    return hash_value;
}

#define FNV_PRIME 0x100000001b3
#define FNV_OFFSET 0xcbf29ce48422325UL

uint64_t hash_fnv1(const char *data, size_t length) {
    uint64_t hash_value = FNV_OFFSET;
    for (int i=0; i < length; i++) {
        hash_value *= FNV_PRIME;
        hash_value ^= data[i];
    }
    return hash_value;
}

uint64_t hash_fnv1a(const char *data, size_t length) {
    uint64_t hash_value = FNV_OFFSET;
    for (int i=0; i < length; i++) {
        hash_value ^= data[i];
        hash_value *= FNV_PRIME;
    }
    return hash_value;
}




void generate_random_word(char *buffer, size_t length) {
    for (size_t i=0; i < length-1; i++) {
        buffer[i] = 'a' + (rand() % 26);
    }
    buffer[length-1] = 0;
}

void mycleanup(void *p) {
    printf("destroying %p\n",p);
    free(p);
}

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("usage: %s <wordlist filename> <num guesses>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *filename = argv[1];
    uint32_t num_guesses = atol(argv[2]);

    const int tablesize = (1<<20);
    hash_table *table = hash_table_create(tablesize, hash_fnv1, NULL);


    FILE *fp = fopen(filename, "r");
    char buffer[MAX_LINE];
    uint32_t numwords = 0;
    while (!feof(fp) && fgets(buffer, MAX_LINE, fp) != NULL) {
        buffer[strcspn(buffer, "\n\r")] = 0;
        char *newentry = malloc(strlen(buffer)+1);
        strcpy(newentry, buffer);
        hash_table_insert(table, newentry, newentry);
        numwords++;
    }
    fclose(fp);
    printf("Loaded %d words into the table.\n", numwords);
    printf("\t...with %lu collisions\n",hash_table_collisions(table));

    //hash_table_print(table);
    
    //now make guesses
    uint32_t good_guesses = 0;
    const int shortest_guess = 2;
    const int longest_guess = 15;
    for (uint32_t i=0; i < num_guesses; i++) {
        generate_random_word(buffer, shortest_guess + (rand() % (longest_guess-shortest_guess)));
        if (hash_table_lookup(table, buffer)) {
            good_guesses++;
        }
    }
    printf("%u out of %u guesses were in the table\n", good_guesses, num_guesses);
    hash_table_destroy(table);
}