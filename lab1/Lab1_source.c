/************************************************************************
*file: Lab1_source.c
*synopsis: The argz functions use malloc/realloc to allocate/grow argz vectors, and so any argz
* vector creating using these functions may be freed by using free; conversely, any argz
* function that may grow a string expects that string to have been allocated using malloc
* (those argz functions that only examine their arguments or modify them in place will work
* on any sort of memory). All argz functions that do memory allocation have a return type
* of error_t, and return 0 for success, and ENOMEM if an allocation error occurs.
* These functions are declared in the include file "argz.h".
*related files: none
*author: Denys Fedorchenko
*written: 24/09/2017
*last modified: 24/10/2017
************************************************************************/

#include "Lab1_header.h"

/*
The argz_create_sep function converts the null-terminated string string into an
argz vector (returned in argz and argz len) by splitting it into elements at every
occurrence of the character sep.
*/
error_t argz_create_sep(const char *string, int sep, char **argz, size_t *argz_len) {
	int len;

	if (string == NULL) return ERROR;
	
	len = strlen(string) + 1;//+1 for '\0' in the end
	if (len <= 1) return ERROR;

	*argz = malloc(sizeof(char)*len);
	if (*argz == NULL) return ERROR;

	for (int i = 0; i < len; i++) {
		if (string[i] == sep)
			(*argz)[i] = '\0';
		else
			(*argz)[i] = string[i];
	}
	(*argz_len) = len;
	return OK;
}

//Returns the number of elements in the argz vector.
//We use argz_next function - this allows argz_count not to know details about argz vector
size_t argz_count(const char *argz, size_t arg_len) {
	int count = 0;
	for (char *entry = argz; entry; entry = argz_next(argz, arg_len, entry))
		count++;
	return count;
}

//The argz_add function adds the string str to the end of the argz vector // *argz, and updates *argz and *argz_len accordingly.
error_t argz_add(char **argz, size_t *argz_len, const char *str) {
	int new_length;
	
	if (*argz == NULL || str == NULL) return ERROR;
	new_length = strlen(str);
	if (*argz_len == 0 || new_length == 0) return ERROR;
	
	new_length += *argz_len + 1; // +1 for last '\0' in str

	*argz = (char *)realloc(*argz, new_length * sizeof(char));
	
	for (int i = *argz_len; i < new_length; i++) 
		(*argz)[i] = str[i - *argz_len];
	
	*argz_len = new_length;

	return OK;
}

/*If entry points to the beginning of one of the elements in the argz vector *argz, the argz_delete function will remove this entry and reallocate *argz, modifying *argz and *argz_len accordingly. Note that as destructive argz functions usually reallocate their argz argument, pointers into argz vectors such as entry will then become invalid.
*/
void argz_delete(char **argz, size_t *argz_len, char *entry) {
	int entlen, elemlen;
	char *temp, *iter = NULL;
	
	if (entry == NULL) return;

	entlen = strlen(entry);
	while ((iter = argz_next(*argz, *argz_len, iter))){
		if (strncmp(iter, entry, entlen) == 0) {
			elemlen = strlen(iter) + 1; //+1 for '\0'
			temp = malloc((*argz_len - elemlen) * sizeof(char));

			for (int i = 0; i < iter - *argz; i++)
				temp[i] = (*argz)[i];
			for (int i = iter - *argz + elemlen; i < *argz_len; i++)
				temp[i - elemlen] = (*argz)[i];

			free(*argz);
			(*argz) = temp;
			(*argz_len) -= elemlen;

			return;
		}
	}
}

/*
The argz_insert function inserts the string entry into the argz vector *argz at a point just before the existing element pointed to by before, reallocating *argz and updating *argz and *argz_len. If before is 0, entry is added to the end instead (as if by argz_add). Since the first element is in fact the same as *argz, passing in *argz as the value of before will result in entry being inserted at the beginning.
*/
error_t argz_insert(char **argz, size_t *argz_len, char *before, const char *entry) {
	char *iter = NULL, *temp;
	int entlen, n;
	
	if (before == NULL || entry == NULL) return ERROR;

	entlen = strlen(entry);
	if (entlen < 1) return ERROR;
	entlen += 1; // +1 for '\0'

	while ((iter = argz_next(*argz, *argz_len, iter))) {
		if (strcmp(iter, before) == 0) {
			temp = malloc(sizeof(char) * (*argz_len + entlen));
			n = (int)(iter - (*argz));
			for (int i = 0; i < n; i++)
				temp[i] = (*argz)[i];
			for (int i = 0; i < entlen; i++)
				temp[i + n] = entry[i];
			for (int i = n; i < *argz_len; i++)
				temp[i + entlen] = (*argz)[i];
			
			free(*argz);
			(*argz) = temp;
			(*argz_len) += entlen;
			return OK;
		}
	}

	return ERROR;
}

/*
The argz_next function provides a convenient way of iterating over the elements in the argz vector argz. It returns a pointer to the next element in argz after the element entry, or 0 if there are no elements following entry. If entry is 0, the first element of argz is returned.
This behavior suggests two styles of iteration:
char *entry = 0;
while ((entry = argz_next (argz, argz_len, entry)))
action;
(the double parentheses are necessary to make some C compilers shut up about what they consider a questionable while-test) and:
char *entry;
for (entry = argz; entry; entry = argz_next (argz, argz_len, entry))
action;
Note that the latter depends on argz having a value of 0 if it is empty (rather than a pointer to an empty block of memory); this invariant is maintained for argz vectors created by the functions here.
*/
char * argz_next(char *argz, size_t argz_len, const char *entry) {
	if (entry == NULL)
		return argz;
	for (; entry - argz < argz_len-1; entry++) {
		if (*entry == '\0')
			return entry + 1;
	}
	return NULL;
}

/*
Replace the string str in argz with string with, reallocating argz as
necessary.
*/
error_t argz_replace(char **argz, size_t *argz_len, const char *str, const char *with){
	char *temp;
	int withlen, slen, i, j, index;

	if (str == NULL || with == NULL) return ERROR;
	slen = strlen(str);
	if (slen == 0) return ERROR;//its OK for *with to have 0 length. It'll delete a part of the argz-string
	withlen = strlen(with);

	for (i = 0; i < *argz_len - slen; i++) {
		if ((*argz)[i] == str[0]) {
			index = i;
			for (j = 1; j < slen; j++) {
				if ((*argz)[i + j] != str[j]) {
					index = -1;
					break;
				}
			}
			if (index > -1) {
				if (withlen == slen) {
					for (i = 0; i < slen; i++)
						(*argz)[i + index] = with[i];
				}
				else {
					temp = malloc((*argz_len + withlen - slen) * sizeof(char));
					for (i = 0; i < index; i++) 
						temp[i] = (*argz)[i];
					for (i = 0; i < withlen; i++)
						temp[i + index] = with[i];
					withlen -= slen;
					for (i = index + slen; i < *argz_len; i++)
						temp[i + withlen] = (*argz)[i];

					free(*argz);
					(*argz_len) += withlen;
					(*argz) = temp;
				}

				return OK;
			}
		}
	}

	return ERROR;
}
/*prints argz vector */
void argz_print(const char *argz, size_t argz_len) {
	for (int i = 0; i < argz_len; i++)
		printf("%c", argz[i]);
	printf("\n");
}
