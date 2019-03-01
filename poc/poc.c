#include <stdio.h>

int distance(void *a, void *b)
{
	return a - b;
}

#define PRINT_FIELD_LOC(s, f) printf("%d\t%s\n", distance((void*) &s.f, (void*) &s), #f)

struct allFunctionPointers {
        int (*allFunctionPointersFieldOne)();
	int (*allFunctionPointersFieldTwo)();
};
struct notAllFunctionPointers {
	int (*notAllFunctionPointersFieldOne)();
	int notAllFunctionPointersFieldTwo;
};
struct notautoselect {
	int (*test1)();
	int (*test2)();
}__attribute__((no_randomize_layout));

struct norand {
	int tomato;
	char potato;
	double lettuce;
	int computer;
};

struct mystruct {
	char *first;
	char *second;
}__attribute__((no_randomize_layout)) __attribute__((randomize_layout));
struct autoselecttest {
        int (*test1)();
	int (*test2)();
};
struct autotestfail {
	int (*test1)();
	int test2;
};
struct notautoselect {
	int (*test1)();
	int (*test2)();
}__attribute__((no_randomize_layout));
int distance(void *a, void *b)
{
	return a - b;
}

int main(void)
{
	struct mystruct m;
	struct allFunctionPointers a;
	struct notautoselect n;
	struct notAllFunctionPointers f;
	
	m.first = "I'm the first!";
	m.second = "and I'm the second!";
	m.third = "third!!!";

	f.notAllFunctionPointersFieldOne = NULL;
	f.notAllFunctionPointersFieldTwo = 1;
	a.allFunctionPointersFieldOne = NULL;
	a.allFunctionPointersFieldTwo = NULL;
	n.test1 = NULL;
	n.test2 = NULL;

	PRINT_FIELD_LOC(m, first);
	PRINT_FIELD_LOC(m, second);
	PRINT_FIELD_LOC(m, third);

	//Does NOT randomize layout due to struct not being all function pointers
	//Contents should NOT be randomized
	printf("Not All Function Pointers Struct Field One: %i\n", &f.notAllFunctionPointersFieldOne);
	printf("Not All Function Pointers Struct Field Two: %i\n", &f.notAllFunctionPointersFieldTwo);

	//Randomizes layout due to being all function pointers
	//Contents should be randomized
	printf("All Function Pointers Struct Field One: %i\n", &a.allFunctionPointersFieldOne);
	printf("All Function Pointers Struct Field Two: %i\n", &a.allFunctionPointersFieldTwo);
	
	PRINT_FIELD_LOC(f, notAllFunctionPointersFieldOne);
	PRINT_FIELD_LOC(f, notAllFunctionPointersFieldTwo);
	PRINT_FIELD_LOC(a, allFunctionPointersFieldOne);
	PRINT_FIELD_LOC(a, allFunctionPointersFieldTwo);

	struct perf p;

	p.a = 0;
	p.b = 'a';
	p.m = m;
	p.potato = 0;
	p.hi = NULL;

	PRINT_FIELD_LOC(p, a);
	PRINT_FIELD_LOC(p, b);
	PRINT_FIELD_LOC(p, c);
	PRINT_FIELD_LOC(p, m);
	//PRINT_FIELD_LOC(p, potato);
	PRINT_FIELD_LOC(p, hi);

	struct norand r;

	PRINT_FIELD_LOC(r, tomato);
	PRINT_FIELD_LOC(r, potato);
	PRINT_FIELD_LOC(r, lettuce);
	PRINT_FIELD_LOC(r, computer);

	struct autoselecttest a;
	struct notautoselect n;
	struct autotestfail f;
	f.test1 = NULL;
	f.test2 = 1;
	a.test1 = NULL;
	a.test2 = NULL;
	n.test1 = NULL;
	n.test2 = NULL;
	m.first = "I'm the first!";
	m.second = "and I'm the second!";
        printf("Autofail test: %i\n", &f.test1);
	printf("Autofail test: %i\n", &f.test2);
	printf("Auto test: %i\n", &a.test1);
	printf("Auto test: %i\n", &a.test2);
	printf("%d first\n", distance((void*)&m.first, (void*)&m));
	printf("%d second\n", distance((void*)&m.second, (void*)&m));
	return 0;
}
