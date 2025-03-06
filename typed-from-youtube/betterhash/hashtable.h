#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>


typedef uint64_t hashfunction (const char*, size_t);
typedef void cleanupfunction(void *);
typedef struct _hash_table hash_table;

hash_table *hash_table_create(uint32_t size, hashfunction *hf, cleanupfunction *cf);
void hash_table_destroy(hash_table *ht);
void hash_table_print(hash_table *ht);
bool hash_table_insert(hash_table *ht, const char *key, void *obj);
void *hash_table_lookup(hash_table *ht, const char *key);
void *hash_table_delete(hash_table *ht, const char *key);

uint64_t hash_table_collisions(hash_table *ht);

#endif