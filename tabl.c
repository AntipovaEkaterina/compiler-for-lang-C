#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHTAB_SIZE 71
#define HASHTAB_MUL  31

struct listnode
{
    char *key;
    int value;
    
    struct listnode *next;
};
struct listnode *hashtab[HASHTAB_SIZE];

unsigned int hashtab_hash(char *key)
{
    unsigned int h = 0;
    char *p;
    for (p = key; *p != '\0'; p++)
    {
        h = h * HASHTAB_MUL + (unsigned int)*p;
    }
    return h % HASHTAB_SIZE;
}
//иницализация хэш-таблицы
void hashtab_init(struct listnode **hashtab)
{
    int i;
    for (i = 0; i < HASHTAB_SIZE; i++)
    {
        hashtab[i] = NULL;
    }
}
//добавление эл-та в хэш-таблицу
void hashtab_add(struct listnode **hashtab,char *key, int value)
{
    struct listnode *node;
    int index = hashtab_hash(key);
    //вставка в начало списка
    node = malloc(sizeof(*node));
    if (node != NULL) 
    {
        node->key = key;
        node->value = value;
        node->next = hashtab[index];
        hashtab[index] = node;
    }
}
//поиск эл-та
struct listnode *hashtab_lookup(struct listnode **hashtab, char *key)
{
    int index;
    struct listnode *node;
    index = hashtab_hash(key);
    for (node = hashtab[index]; node != NULL; node = node->next)
    {
        if (strcmp(node->key, key) == 0) 
        {
            return node;
        }
    }
return NULL;
}
//удаление
void hashtab_delete(struct listnode **hashtab,char *key)
{
    int index;
    struct listnode *p, *prev = NULL;
    index = hashtab_hash(key);
    for (p = hashtab[index]; p != NULL; p = p->next)
    {
        if (strcmp(p->key, key) == 0) 
        {
            if (prev == NULL)
                hashtab[index] = p->next;
            else
                prev->next = p->next;
            free(p);
            
            return;
        }
        prev = p;
    }
}
int main()
{
    //поиск 
    struct listnode *node;
    hashtab_init(hashtab);
    hashtab_add(hashtab, "Tigr", 2300);
    hashtab_add(hashtab, "Slon", 190);
    hashtab_add(hashtab, "Volk", 0);
    node = hashtab_lookup(hashtab, "Volk");
    printf("Node: %s, %d\n", node->key, node->value);
    return 0;
    //удаление 
    /*hashtab_delete(hashtab, "Slon");
    node = hashtab_lookup(hashtab, "Slon");
    if (node != NULL) 
    {
        printf("Node: %s, %d\n", node->key, node->value);
    } else {
        printf("Key 'Slon' not found\n");
    }
    return 0;*/
}
