#ifndef TABL_H
#define TABL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AST.h"

#define HASHTAB_SIZE 71
#define HASHTAB_MUL  31

enum Base_Type
{
    function = 1,
    array,
    variable
};

enum Type
{
    Void,
    Char,
    Int 
};
//int size = 8;
struct listnode
{
    char *key;//наименование id 
    int value; //хэш-ключ
    enum Base_Type base_type;
    enum Type type;
    int offset; //смещение в стеке
    int size; 
    int count_el; //кол-во эл-в. для массива
    struct listnode *hashkoll; //для решения коллизий
    struct listnode *next;  //переход к след узлу
};

struct Id_Table
{
    struct listnode *hashtab[HASHTAB_SIZE];
    struct Id_Table *next;
    int level;
};

int hashtab_hash(char *key);

void hashtab_init(struct listnode **hashtab);
void hashtab_add(struct listnode **hashtab,char *key, int value, int base_type, int type);
void hashtab_delete(struct listnode **hashtab,char *key);

struct listnode *hashtab_lookup(struct listnode **hashtab, char *key);
struct Id_Table *Id_Table_Init (int level);
struct listnode *Find_in_all_table(struct Id_Table *Table, char *key);

#endif
