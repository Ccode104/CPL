void Init_Symbol_Table_Collection()
{
	//No Scopes
	c.lptr=NULL;
}

Node* Create_Node()
{
	return((Node*)malloc(sizeof(Node)));
}

void Init(Symbol_Table**spptr)
{
	//Initialise with Empty Characters
	for(int i=0;i<26;i++)
	{
		strcpy((*spptr)->variable_name," ");
	}
}
void Create_Current_Scope()
{
	Node *nptr;
	nptr=Create_Node();

	//Put Empty characters
	Init(&(nptr->s));
	if(Sym_c.lptr==NULL)
	{
		Sym.lptr=nptr;
	}
	else{
		nptr->next=Sym_c.lptr;
		Sym_c.lptr=nptr;
	}
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
}
void Insert_At_Current_Scope(char *str,char *val)
{
	Sym_c.lptr->s[hash(str)]=val[0]-'0';
}