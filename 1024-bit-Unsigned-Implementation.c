/*CPL Assignment 1
Name of student: Abhishek Prashant Chandurkar
BT22CSE104
*/

#include<stdio.h>
#include<string.h>

//1024 bit data type for unsigned integers
typedef struct num
{
	unsigned int binary[32];
} int_1024;

//Prints the 1024 bit number in binary format
void printNum(int_1024);

//Initialises the 1024 bit number to 0
void init(int_1024 *);

//Adds two 1024 bit nos
int_1024 add(int_1024,int_1024);

//Modify a bit in the 1024 bit number
unsigned int store(unsigned int,unsigned int,unsigned int);

//Access a bit in the 1024 bit number
unsigned int access(unsigned int,unsigned int);

//Multiplies two 1024 bit number
int_1024 mul(int_1024,int_1024);

//Calculates the parameter which can be used to calculate the number of bits in 1024 bit number
void no_of_digits(int_1024,unsigned int*,unsigned int*);

//Converts Decimal number to binary format(to store in the int_1024 data type)
int_1024 binary(char *);

//Multiply the number by 2(Left shift the binary number)
int_1024 leftshift(int_1024);

//Substract two 1024 bit number
int_1024 sub(int_1024,int_1024);

//Add two numbers in string format
void add_str(char*,char*,char*);

//Print the number as a string
void print_as_str(int_1024);

// function to reverse a string(Use this in case strrev not available)
void strrev(char *);

//Driver code
void main()
{
	char ch1[309],ch2[309];//String to take the input
	
	int_1024 num1,num2;//1024 bit nos
	
	unsigned int i,len;
	
	printf("\n Size of BigInt data type implemented is %ld\n",sizeof(int_1024));
	
	//Initialise to 0
	init(&num1);
	init(&num2);
	
	//INPUT 1
	printf("\nEnter the first number\t");
	scanf("%s",ch1);

	//Reverse the string
	strrev(ch1);

	//Padding 0s to make it a 308 digit number
	i=0;
	len=strlen(ch1);
	while(i<308)
	{
		strcat(ch1,"0");
		i++;
	}
	

	//Convert input 1 to 1024 bit number
	num1=binary(ch1);

	//INPUT 2
	printf("\nEnter the second number\t");
	scanf("%s",ch2);

	//Reverse the string
	strrev(ch2);

	//Padding 0s to make it a 308 digit number
	i=0;
	len=strlen(ch2);
	while(i<308)
	{
		strcat(ch2,"0");
		i++;
	}

	//Convert input to 1024 bit number
	num2=binary(ch2);

	printf("\n");
	//Print the output
	print_as_str(num1);

	printf("\n");
	//Print the output
	print_as_str(num2);

	printf("\nSubstraction\n");
	print_as_str(sub(num1,num2));
	
	printf("\nAddition\n");
	print_as_str(add(num1,num2));

	

	printf("\nMultiplication\n");
	print_as_str(mul(num1,num2));



	

}
void init(int_1024 *num)
{	
	for(int i=0;i<32;i++)
		num->binary[i]=0;
}
void printNum(int_1024 num)
{
	for(int i=31;i>=0;i--)
	{
		for(int j=31;j>=0;j--)
		{
			printf("%d",access(num.binary[i],j));
		}
		printf("\n");
	}
}
int_1024 binary(char *ch)
{
	int_1024 p,b,num;
	unsigned int len=308;
	unsigned int n=0;

	init(&b);
	init(&p);
	init(&num);

	for(int k=0;k<len;k++)
	{
		init(&p);
		init(&b);
		n=ch[k]-'0'; //Convert char to integer
		b.binary[0]=n; //Store in Least Significant 32-bit array 
		
		for(int z=0;z<k;z++)
		{	
			init(&p);
			b=leftshift(b);
			p=add(p,b);
			b=leftshift(b);
			b=leftshift(b);
			p=add(p,b);
			b=p;
		}
		num=add(num,b);
	}
	return num;
}

void no_of_digits(int_1024 b,unsigned int *lim_i,unsigned int *lim_j)
{
	*lim_i=0;
	*lim_j=0;
	for(int i=0;i<32;i++)
	{
		for(int j=0;j<32;j++)
		{
			if(access(b.binary[i],j)==1)
			{
				*lim_i=i;
				*lim_j=j;
			}
		}
	}
}
int_1024 leftshift(int_1024 b)
{
	int_1024 cy;
	init(&cy);

	for(int i=31;i>0;i--)
	{
		cy.binary[0]=access(b.binary[i-1],31);
		b.binary[i]=b.binary[i]<<1;
		b.binary[i]=b.binary[i]+cy.binary[0];
	}
	b.binary[0]<<=1;

	return b;
}
int_1024 mul(int_1024 b1,int_1024 b2)
{
	/*Multiply two binary nos*/
	int_1024 b,t;
	unsigned int flag=0,lim_k=0,lim_l=0,prod=1;

	init(&b);
	
	no_of_digits(b2,&lim_k,&lim_l);

	for(int k=0;k<=lim_k;k++)
	{
		for(int l=0;l<=lim_l;l++)
		{
			if(access(b2.binary[k],l)==1)
				{
					b=add(b,b1);
				}
			b1=leftshift(b1);
		}
	}

	
	return b;
}


unsigned int access(unsigned int num,unsigned int j)
{
	return((num >> j) & 1);
}

unsigned int store(unsigned int num,unsigned int j,unsigned int val)
{
	return ((num | (val << j)));
}

int_1024 add(int_1024 b1,int_1024 b2)
{
	int_1024 b;
	unsigned int carry=0,sum=0;
	init(&b);

	for(int i=0;i<32;i++)
	{
		for(int j=0;j<32;j++)
		{
			sum=access(b1.binary[i],j)+access(b2.binary[i],j)+carry;
			if(sum==2)
			{
				carry=1;
				sum=0;
			}
			else if(sum==3)
			{
				carry=1;
				sum=1;

			}
			else if((sum==1)||(sum==0))
			{
				carry=0;

			}
			b.binary[i]=store(b.binary[i],j,sum);
		}
	}
	if(carry==1)
	{
		printf("/***** OVERFLOW ******/");
	}
	
	return b;
}
int_1024 sub(int_1024 b1,int_1024 b2)
{
	int_1024 b;
	init(&b);
	int borrow=0,res=0;
	int temp;

	for(int i=0;i<32;i++)
	{
		for(int j=0;j<32;j++)
		{
			//b1.binary[i]=store(b1.binary[i],j,access(b1.binary[i],j)-borrow);
			temp=access(b1.binary[i],j)-borrow;
			if(temp<(int)access(b2.binary[i],j))
			{
				res=(int)access(b1.binary[i],j) + 2 - (int)access(b2.binary[i],j)-borrow;
				b.binary[i]=store(b.binary[i],j,res);
				borrow=1;
			}
			else{
				res=(int)access(b1.binary[i],j) - (int)access(b2.binary[i],j)-borrow;
				b.binary[i]=store(b.binary[i],j,res);
				borrow=0;
			}
		}
		
	}
	if(borrow==1)
		{
			printf(" Negative answer ");
		}
	return b;
}

void strrev(char* str)
{
    // if the string is empty
    if (!str) {
        return;
    }
    // pointer to start and end at the string
    int i = 0;
    int j = strlen(str) - 1;

    // reversing string
    while (i < j) {
        char c = str[i];
        str[i] = str[j];
        str[j] = c;
        i++;
        j--;
    }
}
void add_str(char* str1,char* str2,char *str)
{
	char result[308];
	unsigned long int carry=0,a=0,b=0,sum=0;
	

	for(int i=0;i<308;i++)
	{
		result[i]='0';
	}

	for(int i=0;i<308;i++)
	{	
		a=0;
		b=0;
		sum=0;
		a=str1[i]-'0';
		b=str2[i]-'0';

		sum=a+b+carry;
		if(sum>=10)
		{
			carry=1;
			sum=sum-10;
		}
		else
		{
			carry=0;
		}
		result[i]=sum+'0';
	}
	if(carry==1)
	{
		printf("Overflow");
	}
	else{
		strcpy(str,result);
	}
	

}

void print_as_str(int_1024 num)
{
	char str[308],val[308],res[308];
	unsigned int i=0;
	
	//Inititialise the string
	for(int i=0;i<308;i++)
	{
		str[i]='0';
		val[i]='0';
	}
	
	val[0]='1';

	for(int i=0;i<32;i++)
	{
		for(int j=0;j<32;j++)
		{	
			
			if(access(num.binary[i],j))
			{
				add_str(str,val,str);
			}
			if((i==31)&&(j==31))
			{
				//Do not accumulate value
			}
			else{
				add_str(val,val,val);
			
			}
		}
	}
	strrev(str);
	i=0;
	while(str[i]=='0')
		i++;
	printf("\n%s\n",str+i);
	
}