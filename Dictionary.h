//
// Created by jplop on 05/02/2023.
//

#ifndef HASH_TABLE_DICTIONARY_H
#define HASH_TABLE_DICTIONARY_H

#include <stdlib.h>
#include <stdio.h>

typedef struct dictionary Dictionary;

Dictionary* new_dictionary(int (*hash)(void*), int (*eql)(void *, void *));
void* set(Dictionary *d, void *k, void *v);
void* get(Dictionary *d, void *k);
int key_exists(Dictionary *d, void *k);

#endif //HASH_TABLE_DICTIONARY_H
