#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct hash_node_tag
{
	//Variable names
	char var_name[10];

	//Variable val
	int variable_val;

	struct hash_node_tag *next;

} hash_node;
//Structure for Symbol_Table(Hash Table)for a Given Scope
typedef struct Symbol_Table_tag
{
	//Modulus 10
	hash_node *h[5];

} Symbol_Table;

//Node in a Singly Linked list(with data = Symbol_Table)
typedef struct Node_tag
{
	//For a Scope
	Symbol_Table s;
	struct Node_tag *next;
} Node;

//Wrapper to eclare Singly linked list of Symbol Tables(Scopes)
typedef struct Symbol_Table_Collection_tag
{
	//Insertion and Deletion at lptr(points to current scope)
	Node *lptr;
} Symbol_Table_Collection;

//Declaring the Symbol Table as Global
Symbol_Table_Collection Sym_c;

//Initialise the lptr(of linked list) to NULL(initially no Symbol Tables)
void Init_Symbol_Table_Collection()
{
	//No Scopes
	Sym_c.lptr=NULL;
}

//Auxillary Function to Create a Node
Node* Create_Node()
{
	return((Node*)malloc(sizeof(Node)));
}

//Intialise the Symbol Table
void Init(Symbol_Table *sptr)
{
	//Initialise vaiable values with 0
	//All of the variables *not* declared at start
	for(int i=0;i<5;i++)
	{
		(sptr)->h[i]=NULL;	
	}
}

//Create Scope i.e Insert a Symbol Table in the list
void Create_Current_Scope()
{
	Node *nptr=NULL;

	//Create a Node
	nptr=Create_Node();
	nptr->next=NULL;

	//Intialise the Symbol Table to be Inserted
	Init(&(nptr->s));

	//Insert at start

	if(Sym_c.lptr==NULL)
	{
		//If list is empty
		Sym_c.lptr=nptr;
	}
	else
	{
		//If list not empty
		nptr->next=Sym_c.lptr;
		Sym_c.lptr=nptr;
	}

	printf("\nCreated a New scope\n");
}

//Delete the current scope(to which lptr points to)
void Delete_Current_Scope()
{
	//Point to the beginning of the list
	Node *ptr=Sym_c.lptr;

	if(Sym_c.lptr==NULL)
	{
		//If list Empty(Error!!)
		printf("\nERROR : No 'begin' matches with the 'end' here");
	}
	else
	{
		//Delete at Start
		Sym_c.lptr=Sym_c.lptr->next;
		free(ptr);

		printf("\nDeleted Current scope\n");
	}
	
}

hash_node* Create_Hash_Node()
{
	return(malloc(sizeof(hash_node)));
}

//Hash function
int hash(char name[])
{
	int key,sum=0;
	int len=strlen(name);

	for(int i=0;i<len;i++)
	{
		sum=sum+(int)name[i];
	}
	key=sum%5;

	return key;
}

//Add the variable details in Symbol Table(Current Scope)
void Insert_At_Current_Scope(char name[],int val)
{
	int key=hash(name);
	//printf("Key= %d ",key);
	hash_node *ptr=Sym_c.lptr->s.h[key];

	if(Sym_c.lptr!=NULL)
	{
		if(ptr==NULL)
		{
			//printf("Here");
			ptr=Create_Hash_Node();
			strcpy(ptr->var_name,name);
			ptr->variable_val=val;
			ptr->next=NULL;

			Sym_c.lptr->s.h[key]=ptr;

		}
		else{
			//Check if variable already declared or not

			while((ptr!=NULL)&&(strcmp(ptr->var_name,name)!=0))
			{
				//printf("Here");
				ptr=ptr->next;
			}

			if(ptr!=NULL)
			{
				printf("\nRedeclaration of the variable\n");
			}
			else 
			{
				ptr=Create_Hash_Node();
				strcpy(ptr->var_name,name);
				ptr->variable_val=val;

				//Insert at Start
				ptr->next=Sym_c.lptr->s.h[key];
				Sym_c.lptr->s.h[key]=ptr;
			}
		}
	}
	else
	{
		printf("\nPlease define a scope\n");
	}
	
}
int get_val(char name[])
{
	Node *ptr=Sym_c.lptr;
	int key=hash(name);
	hash_node *hptr=Sym_c.lptr->s.h[key];

	while(ptr!=NULL)
	{
		//Search for the variable
		while((hptr!=NULL)&&(strcmp(hptr->var_name,name)!=0))
		{
			//printf("Here");
			hptr=hptr->next;
		}

		if(hptr!=NULL)
		{
			//Found
			printf("Ha");
			break;
		}
		else
		{
			printf("\nPrevious Scope to be Searched\n");
			ptr=ptr->next;
		}
	}
	if((hptr!=NULL))
	{
		return (hptr->variable_val);
	}
	else
	{
		printf("\nThe variable %s does not exist\n",name);
		return 0;
	}
}



void main()
{
	Init_Symbol_Table_Collection();
	char str[10]=" ";
	int i=0,val=0;
    
Create_Current_Scope();
Insert_At_Current_Scope("a",1);
Insert_At_Current_Scope("b",2);
Create_Current_Scope();
Insert_At_Current_Scope("a",3);
Insert_At_Current_Scope("c",4);
printf("b = %d",get_val("b"));//=> prints value 2
Create_Current_Scope();
Insert_At_Current_Scope("c",5);
printf("b = %d",get_val("b"));
printf("a = %d",get_val("a"));
printf("c = %d",get_val("c"));
Delete_Current_Scope();
printf("a = %d",get_val("a")); //=> prints value 3
printf("c = %d",get_val("c"));
Delete_Current_Scope();
printf("c = %d",get_val("c"));//=> prints value 1
Delete_Current_Scope();
}

