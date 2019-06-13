#include"tabl.h"

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
   // int size = 8;
    int i;
    for (i = 0; i < HASHTAB_SIZE; i++)
    {
        hashtab[i] = NULL;
    }
}

struct Id_Table *Id_Table_Init (int level)
{
   // int size = 8;
    struct Id_Table *Table = (struct Id_Table*) calloc (1, sizeof (struct Id_Table));
    Table->level = level;
    hashtab_init(Table->hashtab);
    return Table;
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
        node->size = 8;
        node->offset = 0;
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

