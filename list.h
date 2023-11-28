#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <list>
using namespace std;
#include "exception.h"

extern int M, N;

enum IterPosition
{
	atNode = 0,
	atBeg = 1,
	atEnd = 2
};

template < class T>
	class DList
	{
		struct DListNode
		{
			T value;
			int row;
			int column;
			DListNode *next, *prev;
			DListNode()
			{
				next = prev = nullptr;
			}
			DListNode(const T &x, const int &m, const int &n)
			{
				this -> value = x;
				this -> row = m;
				this -> column = n;
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
				friend class DList<T> ;
				DList<T> *pList;
				DListNode * currentNode;
				int itpos;
				Iterator(DList<T> *p, DListNode *pos, int b)
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
				T &operator*()
				{
					return currentNode->value;
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
			friend class DList<T> ;
			const DList<T> *pList;
			const DListNode * currentNode;
			int itpos;
			ConstIterator(const DList<T> *p, const DListNode *pos, int b)
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
			const T &operator* ()const;
		};

		ConstIterator cbegin();
		ConstIterator cend();
		ConstIterator crbegin();
		ConstIterator crend();

		DList();
		DList(const T &x, const int &m, const int &n);
		DList(const DList &list);
		~DList();

		void clear();
		T getValue(int n);
		void pushFront(const T &x, const int &m, const int &n);
		void pushLast(const T &x, const int &m, const int &n);
		DList<T> transpose();
		int getSize() const { return size;}

		bool removeAt(Iterator & i);
		bool addAt(Iterator & i, T & x, int & n, int & m);
		
		bool operator==(const DList<T> &list);
		DList<T> operator=(const DList<T> &list);
		DList<T> operator+=(const DList<T> &list);
		DList<T> operator+(const DList<T> &list);
		DList<T> operator*=(const DList<T> &list);
		DList<T> operator*(const DList<T> &list);

		template < class P>
			friend ostream &operator<<(ostream &os, const DList<P> &list);

		template < class P>
			friend ifstream &operator>>(ifstream &f, DList<P> &list);
	};
	
template < class T>
	ifstream &operator>>(ifstream &f, DList<T> &list)
	{
		int q;
		for (int k = 0; k < M; k++)
		{
			for (int p = 0; p < N; p++)
			{
				f >> q;
				if (q) list.pushLast(q, k, p);
			}
		}
		return f;
	}

template < class T>
	ostream &operator<<(ostream &os, const DList<T> &list)
	{
		typename DList<T>::DListNode * p;
		cout << "[" << list.getSize() << "]";
		int k, t;
		for (p = list.first; p; p = p -> next)
		{
			cout << ' ' << p -> value;
		}
		cout << endl;
		for (k = 0; k < M; k++)
		{
			for (t = 0; t < N; t++)
			{
				p = list.first;
				while(p){
					if(k == p -> row && t == p -> column){
						cout << p->value << ' ';
						break;
					}
					p = p -> next;
				}
				if(!p) cout << "0 ";
			}

			cout << endl;
		}
		cout << endl;
		return os;
	}

template < class T>
	DList<T>::~DList()
	{
		DListNode *p = first;
		while (first)
		{
			p = first;
			first = first->next;
			delete p;
		}
	}
	
template < class T>
	DList<T>::DList(const DList &list)
	{
		DListNode * p;
		first = last = nullptr;
		size = 0;
		for (p = list.first; p != nullptr; p = p->next)
		{
			this->pushLast(p->value, p->row, p->column);
		}
	}

template < class T>
	DList<T>::DList()
	{
		size = 0;
		first = last = nullptr;
	}

template < class T>
	void DList<T>::pushFront(const T &x, const int &m, const int &n)
	{
		if((m > M - 1) || (n > N - 1)) throw myException("Can't add the element due to matrix size.\n", EC_MATRIX);
		DListNode *p = new DListNode;
		p->value = x;
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

template < class T>
	void DList<T>::pushLast(const T &x, const int &m, const int &n)
	{
		if((m > M - 1) || (n > N - 1)) throw myException("Can't add the element due to matrix size.\n", EC_MATRIX);
		DListNode *p = first;
		while(p){
			if(m == p -> row && n == p -> column) throw myException("You are trying to add an element that already exists.\n", EC_MATRIX);
			p = p -> next;
		}
		p = new DListNode;
		p->value = x;
		p->row = m;
		p->column = n;
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
	
/*void swap(int* a, int* b){
	int* c;
	*c = *a;
	*a = *b;
	*b = *c;
}
	
template < class T>
	DList<T> DList<T>::transpose()
	{
		DListNode *p = first;
		int k;
		while(p){
			swap(&(p -> row), &(p -> column));
			p = p -> next;
		}
		return *this;
		swap(&M, &N);
	}*/

template < class T>
	T DList<T>::getValue(int n)
	{
		DListNode *p = first;
		while (n--)
		{
			p = p->next;
		}

		return p->value;
	}

template < class T>
	void DList<T>::clear()
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

	
template < typename T>
	DList<T> DList<T>::operator=(const DList &list)
	{
		if (this != &list)
		{
			DListNode * p;
			this->clear();
			for (p = list.first; p != nullptr; p = p->next)
			{
				this->pushLast(p->value, p->row, p->column);
			}
		}
		return * this;
	}

template < class T>
	bool DList<T>::operator==(const DList<T> &list)
	{
		DListNode *p = first;
		DListNode *q = list.first;
		if (size != list.getSize()) return false;
		do { 	if (p->value != q->value) return false;
			p = p->next;
			q = q->next;
		} while (p != nullptr || q != nullptr);
		return true;
	}
	
template < class T>
	DList<T> DList<T>::operator+=(const DList<T> &list)
	{
		DListNode *p = list.first;
		DListNode *q;
		while(p){
			q = first;
			while(q){
				if(p -> row == q -> row && p -> column == q -> column){
					q -> value += p -> value;
					break;
				}
				q = q -> next;
			}
			if(!q) this -> pushLast(p -> value, p -> row, p -> column);
			p = p -> next;
		}
		return *this;
	}
	
template < class T>
	DList<T> DList<T>::operator+(const DList<T> &list)
	{
		*this += list;
		return *this;
	}
	
template < class T>
	DList<T> DList<T>::operator*=(const DList<T> &list)
	{
		DList<T> a;
		T val;
		int i, j, k;
		DListNode *p;
		DListNode *q;
		for(i = 0; i < M; i++){
			for(j = 0; j < N; j++){
				val = 0;
				for(k = 0; k < M; k++){
					for(p = first; p != nullptr; p = p -> next){
						if(p -> row == i && p -> column == k) break;
					}
					if(!p) break;
					for(q = list.first; q != nullptr; q = q -> next){
							if(q -> row == k && q -> column == j) break;
						}
					if(!q) break;
					val += (p -> value) * (q -> value);
				}
				if(val) a.pushLast(val, i, j);
			}
		}
		*this = a;
		return a;
	}
	
template < class T>
	DList<T> DList<T>::operator*(const DList<T> &list)
	{
		*this *= list;
		return *this;
	}
	
template < class T>
	bool DList<T>::removeAt(Iterator & i)
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
	
template < class T>
	bool DList<T>::addAt(Iterator & i, T & x, int & n, int & m)
	{
		DListNode *p = new DListNode(x, n, m);
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

template < class T>
	bool DList<T>::Iterator::operator!=(const Iterator &i)
	{
		if (pList != i.pList) return true;
		if (currentNode != i.currentNode) return true;
		if (itpos != i.itpos) return true;
		return false;
	}

template < class T>
	bool DList<T>::Iterator::operator==(const Iterator &i)
	{
		if (pList != i.pList) return false;
		if (currentNode != i.currentNode) return false;
		if (itpos != i.itpos) return false;
		return true;
	}

template < class T>
	typename DList<T>::Iterator &DList<T>::Iterator::operator++()
	{
		if (currentNode)
		{
			currentNode = currentNode->next;
			if (currentNode == nullptr) itpos = atEnd;
		}
		return * this;
	}

template < class T>
	typename DList<T>::Iterator &DList<T>::Iterator::operator--()
	{
		if (currentNode)
		{
			currentNode = currentNode->prev;
			if (currentNode == nullptr) itpos = atBeg;
		}
		return * this;
	}