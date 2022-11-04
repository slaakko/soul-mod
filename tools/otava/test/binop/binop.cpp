import std.core;

void add()
{
	int b = 1;
	int c = 2;
	int a = b + c;
}

void sub()
{
	int b = 1;
	int c = 2;
	int a = b - c;
}

void imul()
{
	int b = 2;
	int c = 3;
	int a = b * c;
}

void umul()
{
	uint32_t b = 2;
	uint32_t c = 3;
	uint32_t a = b * c;
}

void idiv()
{
	int b = 8;
	int c = 2;
	int a = b / c;
}

void udiv()
{
	uint32_t b = 8;
	uint32_t c = 2;
	uint32_t a = b / c;
}

void mod()
{
	int b = 8;
	int c = 3;
	int a = b % c;
}

void and()
{
	int b = 7;
	int c = 3;
	int a = b & c;
}

void or()
{
	int b = 1;
	int c = 2;
	int a = b | c;
}

void xor()
{
	int b = 7;
	int c = 2;
	int a = b ^ c;
}

void shl()
{
	int b = 1;
	int c = 2;
	int a = b << c;
}

void shr()
{
	int b = 8;
	int c = 2;
	int a = b >> c;
}

void equal()
{
	int a = 1;
	int b = 1;
	bool result = a == b;
}

void notEqual()
{
	int a = 1;
	int b = 2;
	bool result = a != b;
}

void less()
{
	int a = 1;
	int b = 2;
	bool result = a < b;
}

void greater()
{
	int a = 2;
	int b = 1;
	bool result = a > b;
}

void lessEqual()
{
	int a = 1;
	int b = 2;
	bool result = a <= b;
}

void greaterEqual()
{
	int a = 2;
	int b = 1;
	bool result = a >= b;
}

void disjunction()
{
	bool a = false;
	bool b = true;
	bool result = a || b;
}

void conjunction()
{
	bool a = true;
	bool b = true;
	bool result = a && b;
}

int main()
{
	add();
	sub();
	imul();
	umul();
	idiv();
	udiv();
	mod();
	and();
	or();
	xor();
	shl();
	shr();
	equal();
	notEqual();
	less();
	greater();
	lessEqual();
	greaterEqual();
	disjunction();
	conjunction();
	return 0;
}
