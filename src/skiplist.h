#ifndef SRC_SKIPLIST
#define SRC_SKIPLIST

#include <stdexcept>
#include <initializer_list>

#include <iostream>

template <class T>
class Skipnode { // FIXME make internal to Skiplist?

private:
T obj;
Skipnode<T> **ptrs;

public:
Skipnode(int level,const T& obj){
	ptrs = new Skipnode<T> *[level + 1];
	do{
		ptrs[level] = 0;
	}while(level--);
	this->obj = obj;
}

~Skipnode(){
	delete[] ptrs;
}

T& operator*(){
	return obj;
}

Skipnode<T> *ptrat(int level){
	return ptrs[level];
}

Skipnode<T> **lnptrat(int level){
	return &ptrs[level];
}

friend std::ostream& operator<<(std::ostream& out,const Skipnode& sn){
	return out << sn.obj;
}

};

template <class T>
class Skiplist {

class SkipIterator{
public:
SkipIterator(Skipnode<T> *p) : sn(p) {}
~SkipIterator() {}

SkipIterator& operator=(const SkipIterator& other){
	sn = other.sn;
	return *this;
}

bool operator==(const SkipIterator& other) const {
	return sn == other.sn;
}

bool operator!=(const SkipIterator& other) const {
	return sn != other.sn;
}

SkipIterator& operator++(){
	if(sn != NULL){
		sn = sn->ptrat(0);
	}
	return *this;
}

T& operator*() const {
	return **sn;
}

T* operator->(){
	return &*(Skiplist<T>::SkipIterator)*this;
}

private:
Skipnode<T> *sn;
};

private:
size_t nodes;
Skipnode<T> *head;
Skipnode<T> **link;

static void destroy(Skipnode<T> *head){
	Skipnode<T> *sn;

	while( (sn = head) ){
		head = sn->ptrat(0);
		delete sn;
	}
}

public:
Skiplist(){
	nodes = 0;
	head = 0;
	link = &head;
}

~Skiplist(){
	destroy(head);
}

// Copy constructor
Skiplist(const Skiplist& src){
	nodes = 0;
	head = 0;
	link = &head;
	for(iterator i = src.begin() ; i != src.end() ; ++i){
		push(*i);
	}
}

static const int levels = 1; // FIXME decay to linked list

Skiplist& operator=(const Skiplist& src){
	Skipnode<T> *sn;
	Skipnode<T> *ohead = 0;
	Skipnode<T> **olink = &ohead;

	try{
		for(sn = src.head ; sn ; sn = sn->ptrat(0)){
			Skipnode<T> *tmp = new Skipnode<T>(levels,**sn);
			*olink = tmp;
			olink = tmp->lnptrat(0);
		}
	}catch(...){
		destroy(ohead);
		throw;
	}
	destroy(head);
	head = ohead;
	link = &head;
	nodes = 0;
	return *this;
}

size_t size(){
	return nodes;
}

typedef SkipIterator iterator;
typedef const SkipIterator const_iterator;

iterator begin(){
	return iterator(head);
}

const_iterator begin() const {
	return const_iterator(head);
}

iterator end(){
	return iterator(0);
}

const_iterator end() const {
	return const_iterator(0);
}

T& operator[](const int idx){
	iterator i = begin();
	int x = idx;

	while(i != end() && x--){
		++i;
	}
	if(i == end()){
		throw std::range_error("out-of-bounds");
	}
	return *i;
}

T& pop_back(){
	Skipnode<T> **prev;

	if(*(prev = &head) == 0){
		throw std::range_error("underflow");
	}
	while((*prev)->ptrat(0)){
		prev = (*prev)->lnptrat(0);
	}
	link = prev;
	T& ret = ***prev;
	delete(*prev);
	*prev = 0;
	--nodes;
	return ret;
}

T& pop_front(){
	Skipnode<T> **prev,*tmp;

	if(*(prev = &head) == 0){
		throw std::range_error("underflow");
	}
	link = prev;
	T& ret = ***prev;
	tmp = *prev;
	*prev = (*prev)->ptrat(0);
	delete(tmp);
	--nodes;
	return ret;
}

void push_back(const T& ref){
	Skipnode<T> *sn = new Skipnode<T>(levels,ref);
	*link = sn; // FIXME
	link = sn->lnptrat(0);
	++nodes;
}

void push_back(const std::initializer_list<T> il){
	const T *cil;

	for(cil = il.begin() ; cil != il.end() ; ++cil){
		push_back(*cil);
	}
}

void push_front(const T& ref){
	Skipnode<T> *sn = new Skipnode<T>(levels,ref);
	if((*sn->lnptrat(0) = head) == 0){
		link = sn->lnptrat(0);
	}
	head = sn;
	++nodes;
}

void push_front(const std::initializer_list<T> il){
	const T *cil;

	for(cil = il.end() ; cil != il.begin() ; --cil){
		push_front(*cil);
	}
}

T& pop(){
	return pop_back();
}

void push(const T& ref){
	return push_front(ref);
}

void push(const std::initializer_list<T> il){
	return push_front(il);
}

friend std::ostream&  operator<<(std::ostream&  out,const Skiplist& sl){
	Skipnode<T> *sn;

	for(sn = sl.head ; sn ; sn = sn->ptrat(0)){
		if(sn != sl.head){
			out << ", ";
		}
		out << *sn;
	}
	return out;
}

};

#endif
