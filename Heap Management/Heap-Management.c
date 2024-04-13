/*BT22CSE104 Abhishek Prashant Chandurkar
CPL Assignment 2 */

#define SIZE_OF_HEAP 100
#include<stdio.h>
#include<stdlib.h>


typedef struct heap_tag
{
	char byte[SIZE_OF_HEAP];
	unsigned int lptr; //free list
} heap;

void init(heap *h)
{
	unsigned int *ptr;
	char *curr=h->byte;
	

	ptr=(unsigned int*)h->byte;

	for(int i=0;i<SIZE_OF_HEAP;i++)
	{
		h->byte[i]=0;
	}//Set Heap vals to 0

	//Initial Metadata
	*ptr=SIZE_OF_HEAP;
	
	curr=curr+4;
	ptr=(unsigned int*)curr;
	*ptr=101;

	h->lptr=0;

}
char* malloc_h(unsigned int size,heap *h)
{
	char *ptr=NULL;//For traversal
	char *prev=ptr;//For prev to ptr
	unsigned int *s;//Store the size of block pointed by ptr
	unsigned int *n;//Store index of next of free block to ptr
	unsigned int *ps;//Store the size of the free block before alloc
	int flag=0;//To break the loop on success 

	size=size+8;//Include size of metadata(8 bytes)

	if(h->lptr==101)
	{
		//Empty free list
		printf("\nMalloc Failure due to full heap\n");
	}
	else{
		//Set ptr to start of free list
		
		ptr=&(h->byte[h->lptr]);

		//First fit
		do
		{
			s=(unsigned int*)ptr;//Get size
			if((*s)>=size)
			{
				flag=1;//Found the block to allocate
				n=(unsigned int*)(ptr+4);//Get index of next block
			}
			else
			{
				//Move forward
				prev=ptr;
				n=(unsigned int*)(ptr+4);//Get index of next block
				if((*n)!=101)
				{
					//Not the last free block
					ptr=&(h->byte[(*n)]);
				}
			}
		}while((*n!=101)&&(flag==0));
	}

	//Termination due to No block of sufficient size found
	if((*n==101)&&(flag==0))
	{
		//External Fragmentation
		printf("\nMalloc Failure due to External Fragmentation\n");
	}
	else if((*n==101)&&(flag==1))
	{
		//Only one free block in heap
		//Set h->lptr 

		(h->lptr)=((ptr)-(h->byte))+size;

		//Get size of first block in free list(to be modified)
		ps=(unsigned int*)(&(h->byte[h->lptr]));
		*ps=(*s)-size;
		
		//Get next block index and set to NULL(101)	
		n=(unsigned int*)(&(h->byte[(h->lptr)+4]));
		*n=101;//Set the next pointer of only free block in the list to NULL(101)
		
		*s=size;//Size of alloc block set
		}
	else{

		if(ptr-(h->byte)==h->lptr)
		{
			//First block in free list
			(h->lptr)=((ptr)-(h->byte))+size;

			ps=(unsigned int*)(h->byte+(h->lptr));
			*ps=(*s)-size;
	
			*s=size;
		}
		else
		{
			if(*s-size>8)
			{
				//Set size of split free node
				ps=(unsigned int*)(ptr+size);
				*ps=(*s)-size;

				//Set next pointer(index val) of split free node
				n=(unsigned int*)(ptr+size+4);
				*n=*(ptr+4);
			
				//Set prev next pointer to split free node
				*(prev+4)=(ptr-h->byte)+size;
				*s=size;
			}
			else{
				//No split in free node
				*s=size;
				*(prev+4)=*(ptr+4);
			}
		}
	}
    
	return (ptr+8);
}

void free_h(char *ptr,heap *h)
{
	unsigned int *curr_s=NULL;//size of current free block
	unsigned int *prev_s=NULL;//size of prev free block
	unsigned int *ptr_s,*prev_n,*curr_n,*ptr_n;
	char *curr,*prev=NULL;

	if(h->lptr==101)
	{
		//Empty free list
		h->lptr=((ptr-(h->byte)-8));
	}
	else{

		//Set curr at start of free list
		curr=&(h->byte[h->lptr]);

		while(((ptr-(h->byte))-8)>(curr-(h->byte)))
		{
			//ptr comes after curr

			prev=curr;
			curr_n=(unsigned int*)(curr+4);
			if(*(curr_n)!=101)
			{
				//Goto next free block
				curr=(&(h->byte[*(curr_n)]));
			}
			else
				break;
		}
		if(prev!=NULL)
		{
			if((ptr-prev)!=(*prev))
			{
				//prev and ptr not adjacent
				//Insert ptr between prev and curr
				ptr_n=(unsigned int*)(ptr-4);
				prev_n=(unsigned int*)(prev+4);
				*(ptr_n)=curr-(h->byte);
				*(prev_n)=ptr-(h->byte);
			}
			else{
				//prev and ptr adjacent
				//Merge prev and ptr
				prev_n=(unsigned int*)(prev+4);
				*(prev_n)=curr-(h->byte);

				prev_s=(unsigned int*)(prev);
				ptr_s=(unsigned int*)(ptr);
				*prev_s+=*ptr_s;//Accumulate the size
			}
	
			if(curr-prev==(*(prev+4)))
			{
				//prev and curr adjacent
				prev_s=(unsigned int*)(prev);
				curr_s=(unsigned int*)(curr);
				*prev_s+=*curr_s;//Accumulate the size

				prev_n=(unsigned int*)(prev+4);
				curr_n=(unsigned int*)(curr+4);
				*(prev_n)=*(curr_n);
	 		}
	 		
        }
        else{
        	//prev is NULL
        	//If insert at start 
        	ptr_n=(unsigned int*)(ptr-4);
        	*(ptr_n)=(h->lptr);
        	
        	ptr_s=(unsigned int*)(ptr-8);

        	//Check for merge case
        	if((curr-h->byte)==(*ptr_s))
        	{
        		*ptr_s+=*((unsigned int*)curr);
        	}

 
		    h->lptr=(ptr-(h->byte))-8;
		    
        }
		
	}
}

void main()
{
	heap h;//Create a virtual heap 
	init(&h);//Initialise the heap as all vals to 0 and metadata:size=100,next=101

	//Create the pointers of some primitive data types
	char *c;
	int *n,n1;
	float *f,f1;

	
	//Malloc char
	c=(char*)malloc_h(1,&h);
	*c='v';

	//Access them print the vals
	
	printf("\nValue of char = %c",*c);
	
	
	//Free char
	free_h(c,&h);
	
	//Malloc int
	n=(int*)malloc_h(sizeof(int),&h);
	*n=1000;

	printf("\nValue of integer = %d",*(n));
	
	
	//Free the int
	free_h((char*)n,&h);
	
	
	//Malloc float
	f=(float*)malloc_h(sizeof(float),&h);
	*f=1.23;

	printf("\nValue of float = %f",*f);
	free_h((char*)f,&h);	
	
	//After all are freed the values still prevail
	printf("\nValue of integer after free %d",*(n));
	printf("\nValue of char after free %c",*c);
	printf("\nValue of float after free %f",*f);

	f1=1.23;
	printf("\nExpected garbage value of integer %d\n",*((int*)&f1));

}