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
	cString(const char *psz);
	cString(const cString& stringsrc);

	~cString();

	//methods
	int Getlength() const;
	bool Isempty()const;
	void Empty();
	void SetAt(int nindex, char ch);//a little change: nindex can be <0
	int Compare(const cString& s) const;
	int Find(char ch) const;
	int Find(char *pszsub) const;

	cString Mid(int nfirst, int ncount) const;
	cString Left(int ncount) const;
	cString Right(int ncount) const;

	//operators
	cString& operator =(const cString& stringsrc);
	const cString& operator =(const unsigned char* psz);
	char operator [](int indx);

	cString operator +(const cString& string);
	cString& operator +=(const cString& string);
	//
	void Print();
private:
	//put your own data members here
	Node *top;
};

