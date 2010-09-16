#include <list>
#include <cstdlib>
#include <iostream>
#include <casaqueue.h>
#include <casastack.h>
#include <casagrande.h>
#include <initializer_list>

template <class C,class I,class T> static int
tester(const std::initializer_list<T> il){
	unsigned count = 0;

	C cg,ccg;
	cg.push(il);
	for(I i = cg.begin() ; i != cg.end() ; ++i){
		std::cout << "Element #" << count << ": " << *i << std::endl;
		++count;
	}
	std::cout << "Iterated over " << count << " elements." << std::endl;
	if(count != il.size()){
		std::cerr << "Expected " << il.size() << " elements." << std::endl;
		return -1;
	}
	C dg = cg; // test copy constructor
	count = 0;
	for(I i = dg.begin() ; i != dg.end() ; ++i){
		std::cout << "Element #" << count << ": " << *i << std::endl;
		++count;
	}
	std::cout << "Iterated over " << count << " elements." << std::endl;
	if(count != il.size()){
		std::cerr << "Expected " << il.size() << " elements." << std::endl;
		return -1;
	}
	ccg = cg; // test object assignment
	count = 0;
	for(I i = ccg.begin() ; i != ccg.end() ; ++i){
		std::cout << "Element #" << count << ": " << *i << std::endl;
		++count;
	}
	std::cout << "Iterated over " << count << " elements." << std::endl;
	if(count != il.size()){
		std::cerr << "Expected " << il.size() << " elements." << std::endl;
		return -1;
	}
	return 0;
}

int main(void){
	const std::initializer_list<int> il = {0, 1, 2, 3, 4, 9, 8, 7, 6};

	std::cout << "Performing deque tests (problem 1)..." << std::endl;
	if(tester<casagrande<int>,casagrande<int>::const_iterator,int>(il)){
		std::cerr << "Error during deque tests!" << std::endl;
		return EXIT_FAILURE;
	}
	std::cout << "Performing queue tests (problem 2)..." << std::endl;
	if(tester<casaqueue<int>,casaqueue<int>::const_iterator,int>(il)){
		std::cerr << "Error during queue tests!" << std::endl;
		return EXIT_FAILURE;
	}
	std::cout << "Performing stack tests (problem 3)..." << std::endl;
	if(tester<casastack<int>,casastack<int>::const_iterator,int>(il)){
		std::cerr << "Error during stack tests!" << std::endl;
		return EXIT_FAILURE;
	}
	std::cout << "All tests succeeded!" << std::endl;
	return EXIT_SUCCESS;
}
