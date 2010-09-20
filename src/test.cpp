#include <list>
#include <cstdlib>
#include <iostream>
#include <skiplist.h>
#include <skipqueue.h>
#include <skipstack.h>
#include <initializer_list>

template <class C,class I,class T>
static int qtester(const std::initializer_list<T> il){
	unsigned count = 0;

	C cg,ccg;
	cg.push(il);
	std::cout << "<< operator-----------" << std::endl << cg << std::endl
		<< "<< operator ends------" << std::endl;
	if(cg.size() != il.size()){
		std::cerr << "Expected " << il.size() << " size." << std::endl;
		return -1;
	}
	/*
	if(cg.size()){
		std::cout << "Index 0: " << cg[0] << std::endl;
		if(cg.size() > 1){
			std::cout << "Index " << (il.size() - 1) << ": " << cg[il.size() - 1] << std::endl;
		}
	}
	*/
	std::cout << "Base elements...";
	for(I i = cg.begin() ; i != cg.end() ; ++i){
		std::cout << *i << " ";
		++count;
	}
	std::cout << std::endl;
	std::cout << "Iterated over " << count << " elements." << std::endl;
	if(count != il.size()){
		std::cerr << "Expected " << il.size() << " elements." << std::endl;
		return -1;
	}
	C dg = cg; // test copy constructor
	ccg = cg; // test object assignment
	std::cout << "Popping base...";
	for(unsigned z = 0 ; z < count ; ++z){
		std::cout << cg.front() << " ";
		cg.pop();
	}
	std::cout << std::endl;

	count = 0;
	std::cout << "Copy elements...";
	for(I i = dg.begin() ; i != dg.end() ; ++i){
		std::cout << *i << " ";
		++count;
	}
	std::cout << std::endl;
	std::cout << "Iterated over " << count << " elements." << std::endl;
	if(count != il.size()){
		std::cerr << "Expected " << il.size() << " elements." << std::endl;
		return -1;
	}

	std::cout << "Popping copy...";
	for(unsigned z = 0 ; z < count ; ++z){
		std::cout << dg.front() << " ";
		dg.pop();
	}
	std::cout << std::endl;

	count = 0;
	std::cout << "Copy elements...";
	for(I i = ccg.begin() ; i != ccg.end() ; ++i){
		std::cout << *i << " ";
		++count;
	}
	std::cout << std::endl;
	std::cout << "Iterated over " << count << " elements." << std::endl;
	if(count != il.size()){
		std::cerr << "Expected " << il.size() << " elements." << std::endl;
		return -1;
	}

	std::cout << "Popping assigned...";
	for(unsigned z = 0 ; z < count ; ++z){
		std::cout << ccg.front() << " ";
		ccg.pop();
	}
	std::cout << std::endl;
	return 0;
}

template <class C,class I,class T>
static int mtester(){
	const std::initializer_list<int> zl = {};
	const std::initializer_list<int> ml = {1911};
	const std::initializer_list<int> il = {1, 2, 3, 4, 2010, 9, 8, 7, 6, 5};

	if(qtester<C,I,T>(zl)){
		return -1;
	}
	if(qtester<C,I,T>(ml)){
		return -1;
	}
	if(qtester<C,I,T>(il)){
		return -1;
	}
	return 0;
}

int main(void){
	std::cout << "Performing deque tests (problem 1)..." << std::endl;
	if(mtester<Skiplist<int>,Skiplist<int>::iterator,int>()){
		std::cerr << "Error during skiplist tests!" << std::endl;
		return EXIT_FAILURE;
	}
	if(mtester<Skipqueue<int>,Skipqueue<int>::iterator,int>()){
		std::cerr << "Error during skipqueue tests!" << std::endl;
		return EXIT_FAILURE;
	}
	if(mtester<Skipstack<int>,Skipstack<int>::iterator,int>()){
		std::cerr << "Error during skipstack tests!" << std::endl;
		return EXIT_FAILURE;
	}
	std::cout << "All tests succeeded!" << std::endl;
	return EXIT_SUCCESS;
}

/*
int main(void){
	const std::initializer_list<int> il = {0, 1, 2, 3, 4, 9, 8, 7, 6};

	std::cout << "Performing deque tests (problem 1)..." << std::endl;
	if(tester<casagrande<int>,casagrande<int>::const_iterator,int>(il)){
		std::cerr << "Error during deque tests!" << std::endl;
		return EXIT_FAILURE;
	}
	std::cout << std::endl << "Performing queue tests (problem 2)..." << std::endl;
	if(tester<casaqueue<int>,casaqueue<int>::const_iterator,int>(il)){
		std::cerr << "Error during queue tests!" << std::endl;
		return EXIT_FAILURE;
	}
	std::cout << std::endl << "Performing stack tests (problem 3)..." << std::endl;
	if(tester<casastack<int>,casastack<int>::const_iterator,int>(il)){
		std::cerr << "Error during stack tests!" << std::endl;
		return EXIT_FAILURE;
	}
	std::cout << "All tests succeeded!" << std::endl;
	return EXIT_SUCCESS;
}
*/
