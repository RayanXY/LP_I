#include <iostream>
#include <initializer_list>
#include "../include/vector.h"

int main(){
	
	std::cout << std::endl;
	{
		//std::cout << "\xe2\x99\xa5\n";
		std::cout << "Testing - Constructors, Push_Back(), Push_Front():\n";
		ls::vector<int> a;

		for(auto i(0); i < 10; i++){
			a.push_back((i+1)*1);
		}
		a.push_front(0);

		std::cout << ">>> A: ";
		a.print();
	}
	std::cout << std::endl;
	{
		std::cout << "Testing - Copy Constructors:\n";
		ls::vector<int> a;
		for(auto i(0); i < 10; i++){
			a.push_back((i+1)*2);
		}
		std::cout << ">>> A: ";
		a.print();

		/// Copying with vector(vector)
		ls::vector<int> b(a);
		std::cout << ">>> B: ";
		b.print();

		/// Copying with vector = vector
		ls::vector<int> c = a;
		std::cout << ">>> C: ";
		c.print();

		/// Copying with range (10, 43)
		ls::vector<int> d(10, 43);
		std::cout << ">>> D: ";
		d.print();

		/// Copying with range of D
		ls::vector<int> e(d.begin(), d.end());
		std::cout << ">>> E: ";
		e.print(); 
	}
	std::cout << std::endl;
	{
		std::cout << "Testing - Pop_Front(), Pop_Back(), Front(), Back():\n";
		
		ls::vector<int> a;
		for(auto i(0); i < 10; i++){
			a.push_back((i+1)*4);
		}

		std::cout << ">>> A: ";
		a.print();

		a.pop_front();
		a.pop_back();

		std::cout << ">>> A*: ";
		a.print();
		std::cout << ">>> Front: " << a.front() << "\n";
		std::cout << ">>> Back: " << a.back() << "\n";
	}
	std::cout << std::endl;
	{
		std::cout << "Testing - Clear():\n";
		ls::vector<int> a;
		for(auto i(0); i < 10; i++){
			a.push_back((i+1)*5);
		}
		a.clear();

		std::cout << ">>> A: ";
		a.print();
	}
	std::cout << std::endl;
	{
		std::cout << "Testing - Assign():\n";
		ls::vector<int> a;
		for(auto i(0); i < 10; i++){
			a.push_back((i+1)*6);
		}
		a.assign({8,9,10});

		std::cout << ">>> A: ";
		a.print();
	}
	std::cout << std::endl;
	{
		std::cout << "Testing - Operators == and !=:\n";
		ls::vector<int> a, b;
		for(auto i (0); i < 10; i++){
			a.push_back(i+1);
		}
		for(auto i (0); i < 10; i++){
			b.push_back(i+1);
		}
		if(a==b){
			std::cout << ">>> Equal\n";
		}else{
			std::cout << ">>> Different\n";
		}
	}
	std::cout << std::endl;
	{
		std::cout << "Testing - Erase():\n";
		ls::vector<int> a;
		for(auto i (0); i < 10; i++){
			a.push_back(i+1);

		}
		auto x = a.begin();
		auto y = a.begin();
		y++;y++;y++;y++;

		std::cout << "A: ";
		a.print();

		a.erase(x, y);

		std::cout << "A*: ";
		a.print();
	}
	std::cout << std::endl;
	{
		std::cout << "Testing - Insert():\n";
		ls::vector<int> a(1, 10);
		std::cout << "A: ";
		a.print();

		/// Insert range
		a.insert(a.begin(), 2, 15);
		std::cout << "A*: ";
		a.print();
		
		ls::vector<int> b(1, 5);
		std::cout << "B: ";
		b.print();

		/// Insert list
		b.insert(b.end(), {5, 6, 7});
		std::cout << "B*: ";
		b.print();

		ls::vector<int> c(1, 6);
		std::cout << "C: ";
		c.print();

		/// Insert element
		c.insert(c.begin(), 0);
		std::cout << "C*: ";
		c.print();

	}
	std::cout << std::endl;

}