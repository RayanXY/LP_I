#include <iostream>
#include <stdlib.h>
#include <iterator>

bool find(int *k, int *first, int *last){

	for(/* Empty */; first != last; first++){
		if(*first == *k){
			return true;
		}else{
			return false;
		}
	}

}

int * unique(int *first, int *last){
	
	int *j;
	*j = 0;
	for(/* Empty */; first != last; first++){
		if(find(first, first, last)){
			*first = *first + *j;
			*j++;
		}
	}

	return last;

}

int main(int argc, char *argv[]){

	int *i;
	
	int A[] = {1, 5, 8, 1, 5, 2, 3, 3};

	auto r = unique(std::begin(A), std::end(A));

	std::cout << "A: ";
	for(i = 0; i < r; i++){
		std::cout << "|" << A[*i];
	}
	std::cout << "|\n";

}