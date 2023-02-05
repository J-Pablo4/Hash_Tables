#include <stdio.h>
#include <string.h>
#include "Dictionary.h"

int string_equals(void *a, void *b)
{
    return strcmp(a, b) == 0;
}
// http://www.cse.yorku.ca/~oz/hash.html
int hash_string(void *s)
{
    int hash = 5381;
    char *str = s;
    char c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}

int main() {
    Dictionary *dict = new_dictionary(hash_string, string_equals);
    set(dict, "Hola", "Hello");
    set(dict, "Hola", "Hullo!");
    set(dict, "Mundo", "World");
    set(dict, "beber", "drink");
    set(dict, "tomar", "drink");
    printf("%s\n", get(dict, "Hola"));
    printf("%s\n", get(dict, "Mundo"));
    printf("%s\n", get(dict, "tomar"));

    if(key_exists(dict, "Hola"))
    {
        printf("Si existe!!!!\n");
    }
    if(!key_exists(dict, "SUEJO"))
    {
        printf("No existe\n");
    }
    return 0;
}
