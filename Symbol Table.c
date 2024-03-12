#include<stdio.h>
#include<stdlib.h>

typedef struct Symbol_Table_tag
{
	//26 English alphabets
	char variable_name[26];
} Symbol_Table;

typedef struct Node_tag
{
	//For a Scope
	Symbol_Table s;
	Node *next;
} Node;

typedef struct Symbol_Table_Collection_tag
{
	//Insertion and Deletion at lptr(points to current scope)
	Node *lptr;
} Symbol_Table_Collection;

Symbol_Table_Collection Sym_c;

void main()
{
	FILE* fptr = fopen("data.txt", "r");
    if (fptr == NULL) 
    {
        printf("no such file.");
        
    }
    else
    {
    	do
    	{
    		ch=fgetc(fptr);
    		i=0;
    		print=assign=0;
    		while(ch!=' ')
    		{
    			command[i]=ch;
    			i++;
    		}
    		if(strcmp(command,"begins")==0)
    		{
    			Create_Current_Scope();
    			assign=print=0;
    		}
    		else if(strcmp(command,"ends")==0)
    		{
    			assign=print=0;
    			Delete_Current_Scope();
   		 	}
   	 		else if(strcmp(command,"assign")==0)
    		{
    			print =0;
    			assign=1;
    		}
    		else if(strcmp(command,"print")==0)
    		{
    			print=1;
    			assign=0;
    		}
    		else
    		{
    			if(assign==1)
    			{
    				Insert_At_Current_Scope(command);
    			}
    			else if(print==1)
    			{
    				print_val=Get_Value_from_Current_Scope(hash(command[0]));
    				printf("%d",print_val);
    			}
    		}
    	}while(ch!=EOF);
   	}
}

