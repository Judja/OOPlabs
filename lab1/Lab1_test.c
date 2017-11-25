/***********************************************************************
*file: Lab1_test.c
*synopsis: The argz functions use malloc/realloc to allocate/grow argz vectors, *and so any argz vector creating using these functions may be freed by using *free; conversely, any argz function that may grow a string expects that string *to have been allocated *using malloc those argz functions that only examine *their arguments or modify them in place *will work on any sort of memory). All *argz functions that do memory allocation have a return type of error_t, and
*return 0 for success, and ENOMEM if an allocation error occurs.
* These functions are declared in the include file "argz.h".
*related files: none
*author: Denys Fedorchenko
*created: 24/09/2017
*last modified: 25/10/2017
************************************************************************/
#include "Lab1_header.h"

int main() {
	char *const string = "SHELL=/bin/bash:usr=monty:PWD=/bin/monty:LANG=en_US.UTF-8";
	char *argz = 0, *iter = NULL;
	int argz_len;
	
	argz_create_sep(string, 58/*ASCII for : */, &argz, &argz_len);
	argz_print(argz, argz_len);

	argz_delete(&argz, &argz_len, "PWD");
	argz_replace(&argz, &argz_len, "bash", "");
	argz_add(&argz, &argz_len, "food=borshch");
	argz_print(argz, argz_len);

	iter = argz_next(argz, argz_len, iter);
	iter = argz_next(argz, argz_len, iter);
	argz_insert(&argz, &argz_len, iter, "dog=boxer");
	argz_print(argz, argz_len);

	printf("argz_count = %d\n", argz_count(argz, argz_len));
	system("pause");

	return 0;
}
