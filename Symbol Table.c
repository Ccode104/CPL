#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct Symbol_Table_tag
{
	//26 English alphabets
	char variable_val[26];
} Symbol_Table;

typedef struct Node_tag
{
	//For a Scope
	Symbol_Table s;
	struct Node_tag *next;
} Node;

typedef struct Symbol_Table_Collection_tag
{
	//Insertion and Deletion at lptr(points to current scope)
	Node *lptr;
} Symbol_Table_Collection;

Symbol_Table_Collection Sym_c;

void Init_Symbol_Table_Collection()
{
	//No Scopes
	Sym_c.lptr=NULL;
}



Node* Create_Node()
{
	return((Node*)malloc(sizeof(Node)));
}

void Init(Symbol_Table *sptr)
{
	//Initialise with 0
	for(int i=0;i<26;i++)
	{
		(sptr)->variable_val[i]='0';
	}
	//printf("\nInitialised New Scope to %c \n",(sptr)->variable_val[25]);
}
void Create_Current_Scope()
{
	Node *nptr;
	nptr=Create_Node();
	nptr->next=NULL;

	//Put -1
	Init(&(nptr->s));

	if(Sym_c.lptr==NULL)
	{
		Sym_c.lptr=nptr;
	}
	else
	{
		nptr->next=Sym_c.lptr;
		Sym_c.lptr=nptr;
	}
	printf("\nCreated a New scope\n");
}
void Delete_Current_Scope()
{
	Node *ptr=Sym_c.lptr;

	if(Sym_c.lptr==NULL)
	{
		//Empty
	}
	else{
		Sym_c.lptr=Sym_c.lptr->next;
		free(ptr);
	}
	printf("\nDeleted Current scope\n");
}
void Insert_At_Current_Scope(char ch,char val)
{
	((Sym_c.lptr)->s.variable_val[(int)(ch-'a')])=val;
	printf("\nAssigned %c to %c at pos %d\n",ch,val,(int)(ch-'a'));
}
char get_val(char ch)
{
	Node *ptr=Sym_c.lptr;
	while(ptr!=NULL)
	{
		if(ptr->s.variable_val[(int)(ch-'a')]=='0')
		{
			printf("\nPrevious Scope Searched\n");
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
    			printf("\n%c=%c",ch,get_val(ch));
    		}
    		
    	}
   	}
}

