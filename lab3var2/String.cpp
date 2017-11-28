#include "String.h"

//CONSTRUCTORS HERE
cString::cString() {
	//printf("Void constructor\n");
	data = NULL;
	length = 0;
}

cString::cString(const char *psz) {
	//printf("Copy from char* constructor\n");
	length = 0;
	data = NULL;//This issigment is important
	const char *ptr = psz;
	if (ptr != NULL) {
		while (*(ptr++) != '\0') length++;
		data = new char[length];
		memcpy(data, psz, sizeof(char) * length);
	}
}

cString::cString(const cString& stringsrc) {
	//printf("Copy from cString constructor\n");
	length = stringsrc.length;
	data = NULL;//This issigment is important
	if (length != 0)
		data = new char[length];
	if (stringsrc.data != NULL) //when data = Null length = 0, right behaviour of 
					//memcpy(0, 0, 0) is not guaranteed
		memcpy(data, stringsrc.data, sizeof(char) * length);
}
//DESTRUCTOR
cString::~cString() {
	//printf("DESTRUCTOR CALLED: ");
	this->Empty();//calls Empty Method, cause destructor and Empty do the same in this class
}
//METHODS HERE
int cString::Getlength() const {
	return length;
}

bool cString::Isempty() const {
	if (Getlength() == 0) return true;
	return false;
}

void cString::Empty() {
	//printf("Empty called, deleting:");
	length = 0;
	delete[]data;
	data = NULL;//now it looks like it was created with basic constructor
}

void cString::SetAt(int nindex, char ch) {
	if (ch == '\0') {
		throw std::runtime_error("Invalid argument");
	}

	if (nindex < 0) nindex = length + nindex; // -1 is last symbol, 0 is first, 1 is second one
	if (nindex >= length || nindex < 0) {
		throw std::runtime_error("Out of range");
		return;
	}
	//Here we know exactly, that given index is correct
	data[nindex] = ch;
}

int cString::Compare(const cString& s) const {
	//if s has no data, length = 0, so, there is no reason to check, 
	//whether data pointers are equal to NULL
	//we will use .NET String.Compare method logic: 
	// - two empty strings are equal
	// - any string > empty string
	int i = 0;
	while (i < length &&  i < s.length) {
		if (data[i] != s.data[i])
			return (int)(data[i] - s.data[i]);
		i++;
	}
	//firts symbols are equal, but (this) string is longer
	if (length > s.length) return 1;
	//first symbols are equal, but s string is longer
	if (s.length > length) return -1;
	//strings are equal
	return 0;
}

int cString::Find(char ch) const {
	int res = 0;
	while (res < length) {
		if (data[res] == ch) return res;
		res++;
	}
	return -1;
}

int cString::Find(char *pszsub) const {
	if (pszsub == NULL || *pszsub == '\0') {
		throw std::runtime_error("Invalid argument");
	}
	int res = 0;
	bool found = false;
	int i;

	while (res < length) {
		if (data[res] == pszsub[0]) {
			found = true;
			i = 0;
			while (pszsub[++i] != '\0') {//If we find mathing for the first pszsub element,
										//we check, whether all other elements of strings are
										//equal and set flag found value
				if (data[res + i] != pszsub[i]) {
					found = false;
					break;
				}
			}
			if (found) return res;
		}
		res++;
	}

	return -1;
}

void cString::Print() {
	for (int i = 0; i < length; i++)
		printf("%c", data[i]);
}

cString& cString::operator +=(const cString& string) {
	if (string.length == 0) return *this;
	//we will create a new array, copy both data there and assign this->data to new array
	char *data2;
	
	data2 = new char[length + string.length];
	//we can add smt to empty string, so
	if (data != NULL) 
		memcpy(data2, data, sizeof(char) * length);
	memcpy(data2 + length, string.data, sizeof(char) * string.length);
	length += string.length;
	delete[]data;
	data = data2;
	return *this;
}

cString cString::Mid(int nfirst, int ncount) const {
	cString temp;

	if (ncount == 0 || nfirst + ncount >= length)
		ncount = length - nfirst;
	if (nfirst < 0 || ncount < 0)
		return temp;

	temp.length = ncount;
	temp.data = new char[ncount];
	while (ncount-- > 0) {
		temp.data[ncount] = data[nfirst + ncount];
	}

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
	if (stringsrc.length == 0) return *this;

	length = stringsrc.length;
	data = new char[length];
	memcpy(data, stringsrc.data, sizeof(char) * length);

	return *this;
}

const cString& cString::operator =(const unsigned char* psz) {
	Empty();

	const unsigned char *ptr = psz;
	if (ptr != NULL) {
		while (*(ptr++) != '\0') length++;
		data = new char[length];
		memcpy(data, psz, sizeof(char) * length);
	}

	return *this;
}

char cString::operator [](int indx) {
	if (indx >= length || indx < 0) {
		throw std::runtime_error("Out of range");
	}
	//Here we know exactly, that given index is correct
	return data[indx];
}

cString cString::operator +(const cString& string) {
cString temp;
	//ÑHEATS: ON
	temp += (*this);
	temp += string;
	//CHEATS: OFF
	return temp;
}