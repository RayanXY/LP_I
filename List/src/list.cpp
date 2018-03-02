#include <iostream>
#include <iterator>
#include <cassert>
#include "../include/list.h"

/// Prints out the list.
template<typename T> 
void print(ls::list<T> & v){

	if(v.empty()){
		std::cout << "Empty list!\n";
		return;
	}
	auto b = v.begin();
	auto e = v.end();

	for(/* */; b != e; b++){
		std::cout << " " << *b;
	}
	std::cout << "\n";

}

int main(){
	
	std::cout << std::endl;
		std::cout << ">>> Test - Insert, Erase, Clear e Empty: \n";
			/// Default constructor
			ls::list<int> a;
			/// Insert
			a.insert(a.cbegin(), {1,2, 3, 4});
			a.insert(a.cbegin(), 0);
			std::cout << "A: ";	
			print(a);
			/// Erase element
			a.erase(a.cbegin());
			std::cout << "A*: ";
			print(a);
			/// Erase range
			a.erase(a.cbegin(), a.cend());
			std::cout << "A**: ";
			assert(a.empty() == true);	
			print(a);
			/// New list to clear
			ls::list<int> b = {77, 88, 99};
			std::cout << "B: ";
			print(b);
			/// Clear
			b.clear();
			assert(b.empty() == true);
			std::cout << "B*: ";
			print(b);

	std::cout << std::endl;
		std::cout << ">>> Test - Constructors, Pop Back:\n";
			/// Initializer list =
			ls::list<int> c = {1, 2, 3, 4};
			std::cout << "C: ";
			print(c);
			c.pop_back();
			/// Range constructor
			ls::list<int> d(c.begin(), c.end());
			std::cout << "D: ";
			print(d);
			d.pop_back();
			/// Equal constructor
			ls::list<int> e = d;
			std::cout << "E: ";
			print(e);
			/// Initializer List contructor
			ls::list<int> f({1});
			std::cout << "F: ";
			print(d);
	
	std::cout << std::endl;
		std::cout << ">>> Test = Assing:\n";
			/// New list
			ls::list<int> g = {1, 2, 3, 4, 5};
			std::cout << "G: ";
			print(g);
			/// Assign default
			g.assign(0);
			std::cout << "G*: ";
			print(g);
			/// Assign list =
			ls::list<int> h = {1,2};
			g.assign(h.begin(), h.end());
			std::cout << "G**: ";
			print(g);
			/// Assign initializer list
			g.assign({3,4});
			std::cout << "G***: ";
			print(g);

	std::cout << std::endl;
		std::cout << ">>> Test - Push Front & Back e Pop Front:\n";
			/// New list
			ls::list<int> i;
			/// Push Back & Push Front
			i.push_back(1);
			i.push_front(2);
			/// Printing
			std::cout << "I: ";
			print(i);
			/// Pop Front
			i.pop_front();
			/// Priting
			std::cout << "I*: ";
			print(i);

	std::cout << std::endl;
		std::cout << ">>> Test - Front e Back:\n";
			/// New list
			ls::list<int> j = {1000, 2520, 3789};
			/// Front & Back
			std::cout << "J - Front: " << j.front() << "\n";
			std::cout << "J - Back: " << j.back() << "\n";

	std::cout << std::endl;
		std::cout << ">> Test - Find:\n";
			int find_1 = 2520;
			int find_2 = 500;
			auto result_1 = j.find(find_1);
			auto result_2 = j.find(find_2);

			if(*result_1 == find_1){
				std::cout << "The number " << find_1 << " was found!\n";
			}else{
				std::cout << "The number " << find_1 << " was not found!\n";
			}

			if(*result_2 == find_2){
				std::cout << "The number " << find_2 << " was found!\n";
			}else{
				std::cout << "The number " << find_2 << " was not found!\n";
			}

	std::cout << std::endl;

}