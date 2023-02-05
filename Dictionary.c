//
// Created by jplop on 05/02/2023.
//

#include "Dictionary.h"
#define HASH_TABLE_SIZE 1000000

typedef struct item
{
   void *key;
   void *value;
   struct item *next;
} Item;

struct dictionary
{
    int (*Hash)(void*);
    int (*Equal)(void*, void*);

    Item *hash_table[HASH_TABLE_SIZE];
};

Dictionary* new_dictionary(int (*hash)(void*), int (*eql)(void *, void *))
{
    Dictionary *d = calloc(1, sizeof(Dictionary));
    d->Hash = hash;
    d->Equal = eql;
    return d;
}

Item* new_item(void* key, void* value)
{
    Item *i = calloc(1, sizeof (Item));
    i->key = key;
    i->value = value;
    return i;
}

void* set(Dictionary* d, void* key, void* value)
{
    int hash_code = d->Hash(key) % HASH_TABLE_SIZE;
    if(d->hash_table[hash_code] == NULL)
    {
        d->hash_table[hash_code] = new_item(key, value);
        return key;
    }
    // aqui ya ocurrió una de dos cosas
    // 1: O el usuario quiere re-asignar una llave
    // 2: la llave es nueva pero ocurrio una colision.
    printf("TENEMOS UNA COLISION!!!\n");
    Item *current = d->hash_table[hash_code];
    while (!d->Equal(current->key, key))
    {
        if(current->next == NULL)
        {
            // 2: la llave es nueva, pero comparte hash_code con otras llaves
            current->next = new_item(key, value);
            return key;
        }
        current = current->next;
    }
    // 1: El usuario quiere reasignar la llave
    current->value = value;
    return key;
}

void* get(Dictionary* d, void* key)
{
    int hash_code = d->Hash(key) % HASH_TABLE_SIZE;
    if(d->hash_table[hash_code] == NULL)
        exit(EXIT_FAILURE);
    Item *current = d->hash_table[hash_code];
    while (!d->Equal(current->key, key))
    {
        if(current->next == NULL)
            exit(EXIT_FAILURE);
        current = current->next;
    }
    return current->value;
}

int key_exists(Dictionary *d, void *k)
{
    int hash_code = d->Hash(k) % HASH_TABLE_SIZE;
    if(d->hash_table[hash_code] == NULL)
    {
        return 0;
    }
    Item *current = d->hash_table[hash_code];
    while (!d->Equal(current->key, k))
    {
        if(current->next == NULL)
        {
            return 0;
        }
        current = current->next;
    }
    return 1;
}

