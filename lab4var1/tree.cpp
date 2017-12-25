#include "tree.h"

CTreeNode::CTreeNode() {
	m_Bookid = 1;
	m_Author = "Empty";
	m_Title = "Empty";
	m_Year = 0;
	m_Quantity = 0;
	height = 1;
	left = NULL;
	right = NULL;
}
//if we use smt likr this 	CTreeNode Test(*(tree.GetRoot()));
//for empty tree, &k will be NULL
//in this case, we throw exception, cause we do not need "Empty" nodes in our tree
CTreeNode::CTreeNode(CTreeNode& k) {
	if (&k == NULL) throw std::runtime_error("Invalid argument for node copy constructor");
	m_Bookid = k.m_Bookid;
	m_Author = k.m_Author;
	m_Title = k.m_Title;
	m_Year = k.m_Year;
	m_Quantity = k.m_Quantity;
	height = 1;
	left = NULL;
	right = NULL;
}

CTreeNode::CTreeNode(int id, string a, string t, int y, int q) {
	m_Bookid = id;
	m_Author = a;
	m_Title = t;
	m_Year = y;
	m_Quantity = q;
	height = 1;
	left = NULL;
	right = NULL;
}

void CTreeNode::print() {
	if(this)
		printf("ID: %d, Author: %s, Title: %s, Year: %d, Quantity: %d\n", m_Bookid, m_Author.c_str(), m_Title.c_str(), m_Year, m_Quantity);
}
//-----------------------
//TREE
CBinTree::CBinTree() {
	root = NULL;
}
//.csv file parsing
CBinTree::CBinTree(char *file) {
	root = NULL;
	FILE *csvFile = NULL;
	char buf[256], buf2[20];
	CTreeNode node;
	int j, k;

	csvFile = fopen(file, "r");

	if (csvFile != NULL) {//if csvFile == NULL => we just get empty tree with root == NULL
		while (!feof(csvFile)) {
			fgets(buf, 255, csvFile);
			j = -1;
			k = 0;
			while (buf[++j] != ';') {
				buf2[k++] = buf[j];
			}
			buf2[k] = '\0';
			k = atoi(buf2);
			node.m_Bookid = k;

			k = 0;
			while (buf[++j] != ';') {
				buf2[k++] = buf[j];
			}
			buf2[k] = '\0';
			node.m_Author = buf2;

			k = 0;
			while (buf[++j] != ';') {
				buf2[k++] = buf[j];
			}
			buf2[k] = '\0';
			node.m_Title = buf2;

			k = 0;
			while (buf[++j] != ';') {
				buf2[k++] = buf[j];
			}
			buf2[k] = '\0';
			k = atoi(buf2);
			node.m_Year = k;

			k = 0;
			while (buf[++j] <= '9' && buf[j] >= '0') {
				buf2[k++] = buf[j];
			}
			buf2[k] = '\0';
			k = atoi(buf2);
			node.m_Quantity = k;

			Insert(node);
		}
	}
}

CTreeNode* CBinTree::GetRoot() {
	return root;
}

unsigned char CBinTree::height(CTreeNode* p) {
	return p ? p->height : 0;
}

int CBinTree::bfactor(CTreeNode* p) {
	return height(p->right) - height(p->left);
}

void CBinTree::fixheight(CTreeNode* p) {
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	p->height = (hl>hr ? hl : hr) + 1;
}

CTreeNode* CBinTree::rotateright(CTreeNode* p) {
	CTreeNode* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

CTreeNode* CBinTree::rotateleft(CTreeNode* q) {
	CTreeNode* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

CTreeNode* CBinTree::balance(CTreeNode* p) {
	fixheight(p);
	if (bfactor(p) == 2)
	{
		if (bfactor(p->right) < 0)
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if (bfactor(p) == -2)
	{
		if (bfactor(p->left) > 0)
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p;
}

void CBinTree::Insert(CTreeNode& k) {
	root = insert(root, k);
}

CTreeNode* CBinTree::insert(CTreeNode* p, CTreeNode& k) {
	if (!p) return new CTreeNode(k);
	if (k.m_Bookid < p->m_Bookid)
		p->left = insert(p->left, k);
	else if (k.m_Bookid == p->m_Bookid)
		p->m_Quantity += k.m_Quantity;
	else
		p->right = insert(p->right, k);
	return balance(p);
}

CTreeNode* CBinTree::findmin(CTreeNode* p) {
	return p->left ? findmin(p->left) : p;
}

CTreeNode* CBinTree::removemin(CTreeNode* p) {
	if (p->left == 0)
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}
//------
void CBinTree::Remove(int id) {
	root = remove(root, id);
}

CTreeNode* CBinTree::remove(CTreeNode* p, int k) {
	if (!p) return 0;
	if (k < p->m_Bookid)
		p->left = remove(p->left, k);
	else if (k > p->m_Bookid)
		p->right = remove(p->right, k);
	else //  k == p->m_Bookid
	{
		CTreeNode* q = p->left;
		CTreeNode* r = p->right;
		delete p;
		if (!r) return q;
		CTreeNode* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
	return balance(p);
}

int CBinTree::Find(string title) {
	CTreeNode *p = findTitle(root, title);

	if (p) {
		printf("We have %d Book(s) with title \"%s\" in Library\n", p->m_Quantity, p->m_Title.c_str());
		return p->m_Bookid;
	}
	printf("There is no book with title \"%s\" in Library\n", title.c_str());
	return -1; 
}

CTreeNode* CBinTree::findTitle(CTreeNode* p, const string& title) {
	CTreeNode * q = NULL;
	if (p == NULL) return NULL;
	if (p->m_Title.compare(title) == 0) return p;

	q = findTitle(p->left, title);
	return (q) ? q : findTitle(p->right, title);
}

void CBinTree::PrintByAuthor(string author) {
	printf("\nLooking for all %s's Books:\n", author.c_str());
	printByAuthor(root, author);
	printf("==================================================\n\n");
}

void CBinTree::printByAuthor(CTreeNode* p, const string& author) {
	if (p == NULL) return;
	if (p->m_Author.compare(author) == 0) p->print();
	
	printByAuthor(p->left, author);
	printByAuthor(p->right, author);
}