#include <iostream>
#include <iterator>

void reverse(int *first, int *last){

	int arrSz = last - first;
	for(int i = 0; i < arrSz/2; i++){
		std::swap(*(first+i),*(last-1-i));
	}
	
}

int main(){

	int *i, A[] = {1, 2, 3, 4, 5};

	reverse(std::begin(A), std::end(A));

	for(i = std::begin(A); i != std::end(A); i++){
		std::cout << "|" << *i;
	}
	std::cout << "|\n";

}