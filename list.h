#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <list>
#include <chrono>
using namespace std;
#include "exception.h"

enum IterPosition
{
	atNode = 0,
	atBeg = 1,
	atEnd = 2
};

class Element
{
	int value;
	int row;
	int column;
	
public:
	Element(){}
	Element(const Element &x){
		this -> value = x.value;
		this -> row = x.row;
		this -> column = x.column;
	}
	Element(double x, int m, int n){
		value = x;
		row = m;
		column = n;
	}
	int getRow(){return row;};
	int getColumn(){return column;};
	int getValue(){return value;};
	void swapRowColumn() {int c; c = row; row = column; column = c;};
	void addValue(int val){value += val;};
	
	bool operator==(const Element &element){
		if(value == element.value && row == element.row && column == element.column) return true;
		return false;
	}
	
	bool operator!=(const Element &element){
		return !(*this == element);
	}
};

template <typename P>
class DList
{
	struct DListNode
	{
		P element;
		DListNode *next, *prev;
		DListNode()
		{
			next = prev = nullptr;
		}
		DListNode(const P &x)
		{
			this -> element = x;
			next = prev = nullptr;
		}
		void linkNext(DListNode *p)
		{
			next = p;
			if (p) p->prev = this;
		}

		void linkPrev(DListNode *p)
		{
			prev = p;
			if (p) p->next = this;
		}
	};
	
	DListNode *first, *last;
	size_t size;
	
public:
	class Iterator
	{
		friend class DList ;
		DList *pList;
		DListNode * currentNode;
		int itpos;
		Iterator(DList *p, DListNode *pos, int b)
		{
			pList = p;
			currentNode = pos;
			itpos = b;
		}

		public:
			Iterator()
			{
				currentNode = nullptr;
				itpos = atBeg | atEnd;
			}

		Iterator(const Iterator &i)
		{ 		*this = i;
		}

		Iterator &operator=(const Iterator &i)
		{
			pList = i.pList;
			currentNode = i.currentNode;
			itpos = i.itpos;
			return * this;
		}
		int getPos() {return this -> itpos;};
		bool operator!=(const Iterator &i);
		bool operator==(const Iterator &i);
		Iterator &operator++();
		Iterator &operator--();
		P &operator*()
		{
			return currentNode->element;
		}
	};

	Iterator begin()
	{
		return Iterator(this, first, (first) ? atNode : atEnd);
	}

	Iterator end()
	{
		return Iterator(this, nullptr, atEnd);
	}

	Iterator rbegin()
	{
		return Iterator(this, last, (last) ? atNode : atBeg);
	}

	Iterator rend()
	{
		return Iterator(this, nullptr, atBeg);
	}

	class ConstIterator
	{
		friend class DList ;
		const DList *pList;
		const DListNode * currentNode;
		int itpos;
		ConstIterator(const DList *p, const DListNode *pos, int b)
		{
			pList = p;
			currentNode = pos;
			itpos = b;
		}

		public:
			ConstIterator();
		ConstIterator(const ConstIterator &i);
		ConstIterator &operator=(const ConstIterator &i);
		bool operator!=(const ConstIterator &i) const;
		bool operator==(const ConstIterator &i) const;
		ConstIterator &operator++();
		ConstIterator &operator--();
		const P &operator* ()const;
	};

	ConstIterator cbegin();
	ConstIterator cend();
	ConstIterator crbegin();
	ConstIterator crend();
	
	bool removeAt(Iterator & i);
	bool addAt(Iterator & i, P & x);
	
	DList();
	DList(const DList<P> &list);
	~DList();
	
	DListNode* getFirst(){return first;}
	DListNode* getLast(){return last;}
	int getSize(){return size;};
	int find(int k, int t);
	void clear();
	void push_front(const P &x);
	void push_back(const P &x);
	DList<P> transpose();
	
	bool operator==(const DList<P> &list);
	DList<P> operator=(const DList<P> &list);
	DList<P> operator+=(const DList<P> &list);
	DList<P> operator+(const DList<P> &list);
	DList<P> multiply(const DList<P> &list, int row_size, int column_size);
};

template <typename T>
class Matrix
{
	T matrix;
	int row_size;
	int column_size;
	
public:
	Matrix();
	Matrix(T matr, int m, int n);
	
	Matrix<T> transpose();
	
	bool operator==(const Matrix<T> &matr);
	Matrix<T> operator=(const Matrix<T> &matr);
	Matrix<T> operator+=(const Matrix<T> &matr);
	Matrix<T> operator+(const Matrix<T> &matr);
	Matrix<T> operator*=(const Matrix<T> &matr);
	Matrix<T> operator*(const Matrix<T> &matr);
	
	template <class S>
	friend ostream &operator<<(ostream &os, Matrix<S> &matr);
	template <class S>
	friend ifstream &operator>>(ifstream &f, Matrix<S> &matr);
};
	

template <class P>
DList<P>::DList()
{	
	first = last = nullptr;
	size = 0;
}

template <class P>
DList<P>::DList(const DList<P> &list)
{
	DListNode * p;
	first = last = nullptr;
	size = 0;
	for (p = list.first; p != nullptr; p = p->next)
	{
		this->push_back(p->element);
	}
}

template <class P>
DList<P>::~DList()
{
	DListNode *p = first;
	while (first)
	{
		p = first;
		first = first->next;
		delete p;
	}
}

template <class P>
void DList<P>::push_front(const P &x)
{
	DListNode *p = new DListNode;
	p->element = x;
	++size;
	if (first == 0)
	{
		last = first = p;
	}
	else
	{
		first->linkPrev(p);
		first = p;
	}
}

template <class P>
void DList<P>::push_back(const P &x)
{	
	DListNode *p = first;
	while(p){
		p = p -> next;
	}
	p = new DListNode;
	p->element = x;
	++size;
	if (last == 0)
	{
		first = last = p;
	}
	else
	{
		last->linkNext(p);
		last = p;
	}
}

template <class P>
void DList<P>::clear()
{
	DListNode * p;
	while (first)
	{
		p = first;
		first = first->next;
		delete p;
	}
	last = nullptr;
	size = 0;
}

template <class P>
int DList<P>::find(int k, int t)
{
	DListNode* p = first;
	while(p)
	{
		if(k == p -> element.getRow() && t == p -> element.getColumn()){
			return p -> element.getValue();
		}
		p = p -> next;
	}
	return 0;
}

template <class P>
DList<P> DList<P>::transpose()
{
	DListNode *p = first;
	int k;
	while(p){
		p->element.swapRowColumn();
		p = p -> next;
	}
	return *this;
}

template <class P>
bool DList<P>::operator==(const DList<P> &list)
{
	DListNode *p = first;
	DListNode *q = list.first;
	if (size != list.size) return false;
	do { if (p->element != q->element) return false;
		p = p->next;
		q = q->next;
	} while (p != nullptr || q != nullptr);
	return true;
}

template <class P>
DList<P> DList<P>::operator=(const DList<P> &list)
{
	if (this != &list)
	{
		DListNode * p;
		this->clear();
		for (p = list.first; p != nullptr; p = p->next)
		{
			this->push_back(p->element);
		}
	}
	return * this;
}

template <class P>
DList<P> DList<P>::operator+=(const DList<P> &list)
{
	DListNode *p = list.first;
	DListNode *q;
	while(p){
		q = first;
		while(q)
		{
			if(p -> element.getRow() == q -> element.getRow() && p -> element.getColumn() == q -> element.getColumn()){
				q -> element.addValue(p -> element.getValue());
				break;
			}
			q = q -> next;
		}
		if(!q)
		{
			Element e(p -> element.getValue(), p -> element.getRow(), p -> element.getColumn());
			this -> push_back(e);
		}
		p = p -> next;
	}
	return * this;
}

template <class P>
DList<P> DList<P>::operator+(const DList<P> &list)
{	
	this += &list;
	return *this;
}

template <class P>
DList<P> DList<P>::multiply(const DList<P> &list, int row_size, int column_size)
{
	DList<P> a;
	int val;
	int i, j, k;
	DListNode *p;
	DListNode *q;
	for(i = 0; i < row_size; i++){
		for(j = 0; j < column_size; j++){
			val = 0;
			for(k = 0; k < row_size; k++){
				for(p = first; p != nullptr; p = p -> next){
					if(p -> element.getRow() == i && p -> element.getColumn() == k) break;
				}
				if(!p) break;
				for(q = list.first; q != nullptr; q = q -> next){
						if(q -> element.getRow() == k && q ->  element.getColumn() == j) break;
					}
				if(!q) break;
				val += (p -> element.getValue()) * (q -> element.getValue());
			}
			if(val){
				P e(val, i, j);
				a.push_back(e);
			}
		}
	}
	*this = a;
	return a;
}

template <class T>
Matrix<T>::Matrix(){
		row_size = 0;
		column_size = 0;
	}

template <class T>
Matrix<T>::Matrix(T matr, int m, int n){
		matrix = matr;
		row_size = m;
		column_size = n;
	}

template <class T>	
ifstream &operator>>(ifstream &f, Matrix<T> &matr)
{
	int q;
	f >> matr.row_size >> matr.column_size;
	for (int k = 0; k < matr.row_size; k++)
	{
		for (int p = 0; p < matr.column_size; p++)
		{	
			if(!f.good()) throw myException("Wrong file data.\n", EC_FILE);
			f >> q;
			Element t(q, k, p);
			if (q) matr.matrix.push_back(t);
		}
	}
	return f;
}

template <class T>
ostream &operator<<(ostream &os, Matrix<T> &matr)
{
	int k, t;
	int q;
	for (k = 0; k < matr.row_size; k++)
	{
		for (t = 0; t < matr.column_size; t++)
		{
			if(q = matr.matrix.find(k, t)) cout << q << ' ';
			else cout << "0 ";
		}

		cout << endl;
	}
	cout << endl;
	return os;
}

template <class T>
bool Matrix<T>::operator==(const Matrix<T> &matr){
	if(row_size != matr.row_size || column_size != matr.column_size) return false;
	return matrix == matr.matrix;
}

template <class T>
Matrix<T> Matrix<T>::operator=(const Matrix<T> &matr)
{
	row_size = matr.row_size;
	column_size = matr.column_size;
	matrix = matr.matrix;
	return *this;
}

template <class T>
Matrix<T> Matrix<T>::operator+=(const Matrix<T> &matr)
{
	if(row_size != matr.row_size || column_size != matr.column_size) throw myException("Can't add matrix because of different size.\n", EC_MATRIX);
	matrix += matr.matrix;
	return *this;
}

template <class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &matr)
{
	*this += matr;
	return *this;
}

template <class T>
Matrix<T> Matrix<T>::operator*=(const Matrix<T> &matr)
{
	if(row_size != matr.row_size || column_size != matr.column_size) throw myException("Can't add matrix because of different size.\n", EC_MATRIX);
	matrix.multiply(matr.matrix, row_size, column_size);
	return *this;
}

template <class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &matr)
{
	*this *= matr;
	return *this;
}
	
template <class T>
Matrix<T> Matrix<T>::transpose()
{
	int c;
	c = row_size;
	row_size = column_size;
	column_size = c;
	for(auto i = matrix.begin(); i != matrix.end(); ++i)
		(*i).swapRowColumn();
	return *this;
}

template <class P>
bool DList<P>::removeAt(Iterator & i)
{
	if (i == end() || i == rend()) return false;
	DListNode *p = i.currentNode;
	if (p->prev == nullptr && p->next == nullptr)
	{
		i.itpos = atBeg | atEnd;
		i.currentNode = nullptr;
		first = last = nullptr;
		delete p;
		size--;
		return true;
	}
	if (p->prev == nullptr)
	{
		i.itpos = atBeg;
		i.currentNode = p->next;
		i.currentNode->prev = nullptr;
		first = i.currentNode;
	}
	else
	if (p->next == nullptr)
	{
		i.itpos = atEnd;
		i.currentNode = p->prev;
		i.currentNode->next = nullptr;
		last = i.currentNode;
	}
	else
	{
		p->prev->linkNext(p->next);
		i.currentNode = p->next;
	}
	delete p;
	size--;
	return true;
}

template <class P>
bool DList<P>::addAt(Iterator & i, P & x)
{
	DListNode *p = new DListNode(x);
	if (i.itpos == atBeg | atEnd){
		i.currentNode = p;
		first = last = i.currentNode;
		size++;
		return true;
	}
	if (i.currentNode -> prev == nullptr)
	{
		p -> next = i.currentNode;
		i.currentNode -> prev = p;
		i.currentNode = i.currentNode -> prev;
		first = i.currentNode;
		i.itpos = atNode;
	}
	else
	{
		p -> next = i.currentNode;
		i.currentNode -> prev -> next = p;
	}
	size++;
	return true;
}

template <class P>
bool DList<P>::Iterator::operator!=(const Iterator &i)
{
	if (pList != i.pList) return true;
	if (currentNode != i.currentNode) return true;
	if (itpos != i.itpos) return true;
	return false;
}

template <class P>
bool DList<P>::Iterator::operator==(const Iterator &i)
{
	if (pList != i.pList) return false;
	if (currentNode != i.currentNode) return false;
	if (itpos != i.itpos) return false;
	return true;
}

template <class P>
typename DList<P>::Iterator &DList<P>::Iterator::operator++()
{
	if (currentNode)
	{
		currentNode = currentNode->next;
		if (currentNode == nullptr) itpos = atEnd;
	}
	return * this;
}

template <class P>
typename DList<P>::Iterator &DList<P>::Iterator::operator--()
{
	if (currentNode)
	{
		currentNode = currentNode->prev;
		if (currentNode == nullptr) itpos = atBeg;
	}
	return * this;
}