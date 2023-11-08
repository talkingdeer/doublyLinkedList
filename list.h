#pragma once

#include <iostream>

template <class T>
class DList
{
	struct DListNode
   {
      T value;
      DListNode *next, *prev;
      DListNode() { next = prev = nullptr; }
      void LinkNext(DListNode *p) { next = p; if (p) p->prev = this; }
      void LinkPrev(DListNode *p) { prev = p; if (p) p->next = this; }
   };
	size_t size;
	DListNode *first, *last;

public:

   DList() { size = 0; first = last = nullptr; }
   ~DList();
   void clear();
   void PushLast(const T &x);
   void PushFront(const T &x);
   
   T getValue(int N);
   
   void Remove(DListNode* list);

   int Size() const { return size; } 
 
   template <class P>
   friend std::ostream & operator<<(std::ostream & os, const DList<P> & list);
   
   bool operator==(const DList<T> & list);
   DList<T> operator=(const DList<T> & list);

};
                                                          
template <class T>
std::ostream & operator<<(std::ostream & os, const DList<T> & list)
 {
    typename DList<T>::DListNode *p;
    std::cout << "[" << list.Size() << "] ";
    for (p  = list.first; p; p = p->next) {
       std::cout << " " << p->value ;
    }
    std::cout << '\n';
    return os;
}

template <class T>
void DList<T>::clear()
{
    DListNode *p = first;
    while (first) {
        p = first;
        first = first->next;
        delete p;
    }
	size = 0;
}

template <class T>
DList<T>::~DList()
 {
    DListNode *p = first;
    while (first) {
        p = first;
        first = first->next;
        delete p;
    }
 }

template <class T> 
void DList<T>::PushLast(const T &x)
{
    DListNode *p = new DListNode;
    p->value = x;
    ++size;
    if (last == nullptr) {
       first = last = p;
    } else {
       last->LinkNext(p);
       last = p;
    }
}

template <class T> 
void DList<T>::PushFront(const T &x)
{
    DListNode *p = new DListNode;
    p->value = x;
    ++size;
    if (first == 0) {
       last = first = p;
    } else {
       first->LinkPrev(p);
       first = p;
    }
}

template <class T>
T DList<T>::getValue(int N){
	DListNode* p = first;
	while(N--){p = p -> next;}
	return p -> value;
}

template <class T> 
bool DList<T>::operator==(const DList<T> & list)
{
	DListNode* p = first;
	DListNode* q = list.first;
    if(size != list.Size()) return false;
	do{
		if(p->value != q->value) return false;
		p = p -> next;
		q = q -> next;
	} while(p != nullptr || q != nullptr);
	return true;
}

template <class T> 
DList<T> DList<T>::operator=(const DList<T> & list)
{
	if(&list == this) return *this;
	DListNode* p = list.first;
	this->clear();
	while(p != nullptr)
	{
		this->PushLast(p->value);
		p = p -> next;											
	}
    return *this;
}