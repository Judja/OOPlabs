#include "String.h"

//CONSTRUCTORS HERE
cString::cString() {
	printf("Void constructor\n");
	top = NULL;
}

cString::cString(const char *psz) {
	printf("Copy from char* constructor\n");
	top = new Node;
	Node *ptr;
	ptr = top;
	while (*psz != '\0') {
		ptr->value = *psz;
		psz++;
		printf("%c", ptr->value);
		ptr->next = new Node;
		ptr = ptr->next;
	}
	printf("%s\n", "\\0");
	ptr->next = NULL;
	ptr->value = '\0';
}

cString::cString(const cString& stringsrc) {
	printf("Copy from cString constructor\n");
	top = new Node;
	Node *ptr, *ptrs;
	ptrs = stringsrc.top;
	ptr = top;
	while (ptrs->next != NULL) {
		ptr->value = ptrs->value;
		printf("%c", ptr->value);
		ptr->next = new Node;
		ptr = ptr->next;
		ptrs = ptrs->next;
	}
	printf("%s\n", "\\0");
	ptr->next = NULL;
	ptr->value = '\0';

}
//DESTRUCTOR
cString::~cString() {
	printf("DESTRUCTOR CALLED: ");
	this->Empty();
}
//METHODS HERE
int cString::Getlength() const {
	if (top == NULL) return 0;
	int res = 0;
	Node *ptr = top;
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
		res++;
	}
	return res;
}

bool cString::Isempty() const {
	if (Getlength() == 0) return true;
	return false;
}

void cString::Empty() {
	printf("Empty called, deleting:");
	Node *ptr;
	while (top != NULL) {
		ptr = top;
		top = top->next;
		printf(" %c", ptr->value);
		delete ptr;
	}
	printf("\n");
}

void cString::SetAt(int nindex, char ch) {
	if (ch == '\0') {
		printf("Do not break my programm\n");
		return;
	}
	Node *ptr = top;
	int len = Getlength();
	if (nindex < 0) nindex = len + nindex; // -1 is last symbol, 0 is first, 1 is second one
	if (nindex >= len || nindex < 0) {
		printf("And how should it work with wrong indexes?\n");
		return;
	}
	//Here we know exactly, that given index is correct
	while (nindex != 0) {
		nindex--;
		ptr = ptr->next;
	}
	ptr->value = ch;
}

int cString::Compare(const cString& s) const {

}
