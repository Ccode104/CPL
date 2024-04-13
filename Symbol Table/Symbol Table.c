#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Structure for Symbol_Table(Hash Table)for a Given Scope
typedef struct Symbol_Table_tag
{
	//26 English alphabets(26 vars)
	char variable_val[26];

	//Shows if declared(alloc[i]=='y' if declared)
	char alloc[26];

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
	for(int i=0;i<26;i++)
	{
		(sptr)->variable_val[i]='0';
		(sptr)->alloc[i]='n';	
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

//Add the variable details in Symbol Table(Current Scope)
void Insert_At_Current_Scope(char ch,char val)
{
	if(Sym_c.lptr!=NULL)
	{
		//Check if variable already declared or not
		if(((Sym_c.lptr)->s.alloc[(int)(ch-'a')])!='y')
		{
			//If not yet
			((Sym_c.lptr)->s.variable_val[(int)(ch-'a')])=val;
			((Sym_c.lptr)->s.alloc[(int)(ch-'a')])='y';
			printf("\nAssigned %c to %c at pos %d\n",ch,val,(int)(ch-'a'));
		}
		else
		{
			printf("\nRedeclaration of the variable\n");
		}
	}
	else
	{
		printf("\nPlease define a scope Please\n");
	}
	
}
char get_val(char ch)
{
	Node *ptr=Sym_c.lptr;
	while(ptr!=NULL)
	{
		if(ptr->s.alloc[(int)(ch-'a')]=='n')
		{
			printf("\nPrevious Scope to be Searched\n");
			ptr=ptr->next;
		}
		else
		{
			break;
		}
	}
	if(ptr!=NULL)
	{
		return (ptr->s.variable_val[(int)(ch-'a')]);
	}
	else
	{
		printf("\nThe variable %c does not exist\n",ch);
		return '\0';
	}
}



void main()
{
	Init_Symbol_Table_Collection();
	char ch,val,str[100];
	int i=0;
	FILE* fptr = fopen("data.txt", "r");
    if (fptr == NULL) 
    {
        printf("no such file.");
        
    }
    else
    {
    	while(feof(fptr)!=1)
    	{
    		strcpy(str," ");
    		fscanf(fptr,"%s",str);
    		//printf("\n%s",str);
    		if(strcmp(str,"begin")==0)
    		{
    			Create_Current_Scope();
    		}
    		else if(strcmp(str,"end")==0)
    		{
    			Delete_Current_Scope();
   		 	}
   	 		else if(strcmp(str,"assign")==0)
    		{
    			ch=fgetc(fptr);
    			//printf("ch=%c",ch);
    			ch=fgetc(fptr);
    			//printf("ch=%c",ch);
    			val=fgetc(fptr);
    			//printf("val=%c",val);
    			val=fgetc(fptr);
    			//printf("val=%c",val);
    			
    			Insert_At_Current_Scope(ch,val);
    		}
    		else if(strcmp(str,"print")==0)
    		{
    			ch=fgetc(fptr);
    			ch=fgetc(fptr);
    			//printf("\nprint %c",ch);
    			if(get_val(ch)!='\0')
    			{
    				printf("\n%c=%c",ch,get_val(ch));
    			}
    		}
    		
    	}
   	}
}

