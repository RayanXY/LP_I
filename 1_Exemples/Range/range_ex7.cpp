#include <iostream>
#include <iterator>

int * copy(const int *first, const int *last, int *d_first){

	for(/* Empty */; first != last; first++){
		*d_first = *first;
		*d_first++;
	}

	return d_first;

}

int main(){

	int A[] = {1, 2, 3, 4, 5};
	int B[] = {0, 0, 0};
	int *i;

	auto b_last = copy(std::begin(A)+1, std::begin(A)+4, std::begin(B));

	for(i = std::begin(B); i != b_last; i++){
		std::cout << "|" << *i;
	}
	std::cout << "|\n";

}