#include <iostream>
#include <algorithm>

using byte = unsigned char;

void * selection_sort(const void * first, const void * last, size_t size){

	auto f = (byte *) first;
	auto l = (byte *) last;

	for(auto i(f); i != l; i += size){
		auto m(i);
		for(auto j(i+size); j != l; j+=size){
			if(*j < *m){
				m = j;
			}
		}
		std::swap(*i, *m);
	}

}

void * partition(const void * first, const void * last, size_t size){

	auto f = (byte *) first;
	auto l = (byte *) last;

	auto p(l-size);
	auto fast(f);
	auto slow(f);

	while(fast != l){
		if(*fast <= *p){
			std::swap(*fast, *slow);
			slow += size;
		}
		fast += size;
	}

	return slow;

}

void * quick_sort(const void * first, const void * last, size_t size){

	auto f = (byte *) first;
	auto l = (byte *) last;

	if(f == l) return 0;

	auto pivot = partition(f, l, sizeof(int));
	auto p = (byte *) pivot;

	quick_sort(f, p-size, sizeof(int));
	quick_sort(p, l, sizeof(int));

}

void * bubble_sort(const void * first, const void * last, size_t size){

	auto f = (byte *) first;
	auto l = (byte *) last;

	bool change = true;
	while(change){
		change = false;
		for(auto i(f); i != l-size; i += size){
			auto j(i+size);
			if((*i - *j) > 0){
				std::swap(*i, *j);
				change = true;
			}
		}
	}

}

void * insertion_sort(const void * first, const void * last, size_t size){

	auto f = (byte *) first;
	auto l = (byte *) last;

	for(auto i(f); i != l; i += size){
		auto k(i);
		auto j(i-size);
		while((*j >= 0)&&(*j > *k)){
			*(j+=size) = *j;
			j -= size;
		}
		*(j+size) = *k;
	}

}

int main(){
	
	int i; 
	int A1[] = {2, 5, 1, 4, 3, 8, 10, 6, 9, 7};
	int A2[] = {7, 10, 1, 3, 6, 8, 2, 9, 4, 5};
	int A3[] = {5, 6, 2, 3, 1, 7, 4, 8, 10, 9};
	int A4[] = {8, 4, 9, 3, 7, 5, 10, 6, 1, 2};

	/// Selection
	std::cout << ">>> Selection\nA1: ";
	for(i = 0; i < 10; i++){
		std::cout << "|" << A1[i];
	}
	std::cout << "|\n";
	selection_sort(std::begin(A1), std::end(A1), sizeof(int));
	std::cout << "S1: ";
	for(i = 0; i < 10; i++){
		std::cout << "|" << A1[i];
	}
	std::cout << "|\n";

	/// Quick
	std::cout << ">>> Quick\nA2: ";
	for(i = 0; i < 10; i++){
		std::cout << "|" << A2[i];
	}
	std::cout << "|\n";
	quick_sort(std::begin(A2), std::end(A2), sizeof(int));
	std::cout << "Q2: ";
	for(i = 0; i < 10; i++){
		std::cout << "|" << A2[i];
	}
	std::cout << "|\n";

	/// Bubble
	std::cout << ">>> Bubble\nA3: ";
	for(i = 0; i < 10; i++){
		std::cout << "|" << A3[i];
	}
	std::cout << "|\n";
	bubble_sort(std::begin(A3), std::end(A3), sizeof(int));
	std::cout << "B3: ";
	for(i = 0; i < 10; i++){
		std::cout << "|" << A3[i];
	}
	std::cout << "|\n";

	/// Insertion
	std::cout << ">>> Insertion\nA4: ";
	for(i = 0; i < 10; i++){
		std::cout << "|" << A4[i];
	}
	std::cout << "|\n";
	insertion_sort(std::begin(A4), std::end(A4), sizeof(int));
	
}