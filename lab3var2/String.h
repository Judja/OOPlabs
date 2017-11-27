#pragma once
/*!
* file: StringList.h
* StringList class declaration
* written: 26/11/2017
* Copyright (c) 2017 by D. Fedorchenko
*/
#pragma once
#include <string.h>
#include <stdio.h>

struct Node {
	char value;
	Node *next;
};

class cString {
public:
	//constructors/destructor
	cString();
	cString(const char *psz);//takes c-string ("abs") as argument
	cString(const cString& stringsrc);//takes another cString object as argument

	~cString();

	//methods
	int Getlength() const; //Counts and returns a width of string without '\0'
	bool Isempty()const;//returns true if length == 0
	void Empty();//Empties string, deleting all elements from memory
	void SetAt(int nindex, char ch);//Sets element with given index value to ch, my little change: nindex can be <0
	int Compare(const cString& s) const;//compares two strings, returns > 0 if "calling" string is greater 
	int Find(char ch) const;//Looks for a character, returns it's index, or returns -1
	int Find(char *pszsub) const;//Looks for substring

	cString Mid(int nfirst, int ncount = 0) const; //returns substring of characters with indexes from nfirst to nfirst + ncount
	cString Left(int ncount) const;//returns first ncount characters
	cString Right(int ncount) const;//returns last ncount characters

	//operators
	cString& operator =(const cString& stringsrc);
	const cString& operator =(const unsigned char* psz);
	char operator [](int indx);//can access by index, cannot change value

	cString operator +(const cString& string);
	cString& operator +=(const cString& string);
	//
	void Print();
private:
	//put your own data members here
	Node *top;
};

