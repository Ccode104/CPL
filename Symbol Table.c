#include<stdio.h>
#include<stdlib.h>

typedef struct Hash_Table_tag
{
	char variable_name[26];
} Hash_Table;

typedef struct Node_tag
{
	Hash_Table h;
} Node;

typedef struct Symbol_Table_tag
{
	Node *lptr;
} Symbol_Table;

