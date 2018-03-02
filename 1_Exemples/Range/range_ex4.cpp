#include <iostream>
#include <iterator>

void scalar_multiplication(int *first, int *last, int scalar){

	for(/* Empty */; first != last; first++){
		*first *= scalar;
	}

}

int main(){

	int A[] = {1, 2, -3, -4, 5, -6};

	scalar_multiplication(std::begin(A), std::end(A), 3);

	for(int *i = std::begin(A); i != std::end(A); i++){
		std::cout << "|" << *i;
	}
	std::cout << "|\n";

}