int foo(int b)
{
	int a=b;
	if(a==1)
		return 2;
	else
		return a;
}
int main()
{
	int a,b;
	a=4;
	b=foo(a);

	return b;
}