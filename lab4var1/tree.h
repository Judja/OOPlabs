#pragma once
/*!
* file: tree.h
* CBinTree and CTreeNode classes declaration
* written: 02/12/2017
* Copyright (c) 2017 by D. Fedorchenko
*/
#pragma warning(disable : 4996)

#include <stdlib.h>
#include <stdio.h>
#include <string>

using namespace std;

class CTreeNode {
private:
	int m_Bookid;
	string m_Author;
	string m_Title;
	int m_Year;
	int m_Quantity;
	//Tree data
	unsigned char height;

public:
	CTreeNode();
	CTreeNode(CTreeNode& k);
	CTreeNode(int id, string a, string t, int y, int q);
	void print();
	CTreeNode* left;
	CTreeNode* right;
	friend class CBinTree;
};

class CBinTree {
private:
	CTreeNode* root;
	CTreeNode* insert(CTreeNode* p, CTreeNode& k);//inserts books to tree
	CTreeNode* remove(CTreeNode* p, int k);//removes book with given id
	CTreeNode* findTitle(CTreeNode* p, const string& title);//finds a book with given title
	void printByAuthor(CTreeNode* p, const string& title);//prints all authors books
	//"internal" tree's methods
	unsigned char height(CTreeNode* p);
	int bfactor(CTreeNode* p);
	void fixheight(CTreeNode* p);
	CTreeNode* rotateright(CTreeNode* p);
	CTreeNode* rotateleft(CTreeNode* q);
	CTreeNode* balance(CTreeNode* p);
	CTreeNode* findmin(CTreeNode* p);
	CTreeNode* removemin(CTreeNode* p);
public:
	CBinTree();
	CBinTree(char* file);
	CTreeNode* GetRoot();
	void Insert(CTreeNode& k);//uses insert to add a book
	void Remove(int id);//uses remove to remove a book
	void PrintByAuthor(string author);//...
	int Find(string title);
};