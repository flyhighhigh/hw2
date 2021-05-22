#ifndef MAIN_H
#define MAIN_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include<sys/time.h>
#define TRUE 1
#define FALSE 0

enum{
    ll,arr,bs,bst,hash
};
typedef struct node Node;
struct node{
    char* str;
    Node* left;
    Node* right;
    Node* next;
};

int opt[5];
int opt_cnt;
int data_cnt;
int query_cnt;
int data_hash[(int)1e6];
char **data_const;
char **query_const;

char **data_arr;
char **data_bs;
Node* ll_head;
Node* bst_head;
Node** hash_table;

void create();
unsigned int hash_func(int,char*);
void arr_build();
void arr_query();
void bs_build();
void bs_query();
void bs_find(int,int,char*);
void ll_build();
void ll_query();
Node* newnode(char*);
void bst_build();
void bst_findend(Node*,char*);
void bst_query();
void hash_build();
void hash_query();

char name[5][10]={"ll","arr","bs","bst","hash"};
typedef void (*Fptr)();
Fptr build_func[5]={ll_build,arr_build,bs_build,bst_build,hash_build};
Fptr query_func[5]={ll_query,arr_query,bs_query,bst_query,hash_query};

#endif