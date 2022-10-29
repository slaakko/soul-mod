module if_;

void bar()
{
}

void bazz()
{
}

void foo()
{
	int x = 1;
	if (x)
	{
		bar();
	}
	else
	{
		bazz();
	}
}

int main()
{
	foo();
	return 0;
}
