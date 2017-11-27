#include "String.h"

//CONSTRUCTORS HERE
cString::cString() {
	//printf("Void constructor\n");
	top = NULL;
}

cString::cString(const char *psz) {
	//printf("Copy from char* constructor\n");
	top = new Node;
	Node *ptr;
	ptr = top;
	while (*psz != '\0') {
		ptr->value = *psz;
		psz++;
		//printf("%c", ptr->value);
		ptr->next = new Node;
		ptr = ptr->next;
	}
	ptr->next = NULL;
	ptr->value = '\0';
}

cString::cString(const cString& stringsrc) {
	//printf("Copy from cString constructor\n");
	top = new Node;
	Node *ptr, *ptrs;
	ptrs = stringsrc.top;
	ptr = top;
	while (ptrs->next != NULL) {
		ptr->value = ptrs->value;
		//printf("%c", ptr->value);
		ptr->next = new Node;
		ptr = ptr->next;
		ptrs = ptrs->next;
	}
	ptr->next = NULL;
	ptr->value = '\0';

}
//DESTRUCTOR
cString::~cString() {
	//printf("DESTRUCTOR CALLED: ");
	this->Empty();//calls Empty Method, cause destructor and Empty do the same in this class
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
	//printf("Empty called, deleting:");
	Node *ptr;
	while (top != NULL) {
		ptr = top;
		top = top->next;
		//printf(" %c", ptr->value);
		delete ptr;
	}
	//printf("\n");
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
	Node *ptr, *ptrs;

	ptr = top;
	ptrs = s.top;

	while (ptr != NULL && ptrs != NULL) {
		if (ptr->value != ptrs->value)
			return (int)(ptr->value - ptrs->value);

		ptr = ptr->next;
		ptrs = ptrs->next;
	}
	//firts symbols are equal, but (this) string is longer
	if (ptr != NULL) return 1;
	//first symbols are equal, but s string is longer
	if (ptrs != NULL) return -1;
	//strings are equal
	return 0;
}

int cString::Find(char ch) const {
	int res = 0;
	Node *ptr = top;
	while (ptr != NULL) {
		if (ptr->value == ch) return res;
		ptr = ptr->next;
		res++;
	}
	return -1;
}

int cString::Find(char *pszsub) const {
	if (pszsub == NULL || *pszsub == '\0') return -1;
	int res = 0;
	Node *ptr = top, *ptr2;
	bool found = false;
	int i;

	while (ptr != NULL) {
		if (ptr->value == pszsub[0]) {
			found = true;
			i = 0;
			ptr2 = ptr->next;
			while (pszsub[++i] != '\0') {//If we find mathing for the first pszsub element,
										//we check, whether all other elements of strings are
										//equal and set flag found value
				if (ptr2->value != pszsub[i]) {
					found = false;
					break;
				}
				ptr2 = ptr2->next;
			}
			if (found) return res;
		}
		ptr = ptr->next;
		res++;
	}

	return -1;
}

void cString::Print() {
	Node *ptr = top;
	if (ptr == NULL) return;
	while (ptr->next != NULL) {
		printf("%c", ptr->value);
		ptr = ptr->next;
	}
}

cString& cString::operator +=(const cString& string) {
	Node *ptr, *ptrs = string.top;
	if (ptrs == NULL || ptrs->next == NULL) return *this;
	if (top == NULL) {
		top = new Node;
		top->next = NULL;
	}
	ptr = top;
	while (ptr->next != NULL)
		ptr = ptr->next;

	while (ptrs->next != NULL) {
		ptr->value = ptrs->value;
		ptrs = ptrs->next;
		ptr->next = new Node;
		ptr = ptr->next;
	}
	ptr->next = NULL;
	ptr->value = '\0';

	return *this;
}

cString cString::Mid(int nfirst, int ncount) const {
	cString temp("");
	Node *ptrs = top, *ptr;
	temp.top = new Node;
	ptr = temp.top;
	int len = Getlength();

	if (ncount == 0 || nfirst + ncount >= len)
		ncount = len - nfirst;
	if (nfirst < 0 || ncount < 0)
		return temp;

	while (nfirst-- > 0)
		ptrs = ptrs->next;
	while (ncount-- > 0) {
		ptr->value = ptrs->value;
		ptr->next = new Node;
		ptr = ptr->next;
		ptrs = ptrs->next;
	}

	ptr->next = NULL;
	ptr->value = '\0';

	return temp;
}

cString cString::Left(int ncount) const {
	int len = Getlength();
	if (ncount > len) ncount = len;
	return Mid(0, ncount);
}

cString cString::Right(int ncount) const {
	int len = Getlength();
	if (ncount > len) ncount = len;

	return Mid(len - ncount, ncount);
}

cString& cString::operator =(const cString& stringsrc) {
	Empty();
	Node *ptr, *ptrs = stringsrc.top;
	if (ptrs == NULL) return *this;
	top = new Node;
	ptr = top;

	while (ptrs->next != NULL) {
		ptr->value = ptrs->value;
		ptrs = ptrs->next;
		ptr->next = new Node;
		ptr = ptr->next;
	}

	ptr->value = '\0';
	ptr->next = NULL;

	return *this;
}

const cString& cString::operator =(const unsigned char* psz) {
	Empty();
	top = new Node;
	Node *ptr;
	ptr = top;
	while (*psz != '\0') {
		ptr->value = *psz;
		psz++;
		ptr->next = new Node;
		ptr = ptr->next;
	}
	ptr->next = NULL;
	ptr->value = '\0';

	return *this;
}

char cString::operator [](int indx) {
	Node *ptr = top;
	int len = Getlength();
	if (indx >= len || indx < 0) {
		printf("And how should it work with wrong indexes?\n");
		return '0';
	}
	//Here we know exactly, that given index is correct
	while (indx != 0) {
		indx--;
		ptr = ptr->next;
	}
	return ptr->value;
}

cString cString::operator +(const cString& string) {
cString temp;
	//ÑHEATS: ON
	temp += (*this);
	temp += string;
	//CHEATS: OFF
	return temp;
}
