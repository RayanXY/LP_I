#include <iostream>
#include <iterator>

void negate(int *first, int *last){

	for( /* Empty */ ; first != last; first++){
		*first *= -1;
	}

}

int main(){
	
	int vet[] = {1, 2, -3, -4, 5, -6};

	std::cout << ">>> A:";
	for(auto i = std::begin(vet); i != std::end(vet); i++){
		std::cout << "|" << *i;
	}
	std::cout << "|\n";

	std::cout << ">>> A:";
	negate(std::begin(vet), std::end(vet)); //!< Nega todo vetor
	for(auto i = std::begin(vet); i != std::end(vet); i++){
		std::cout << "|" << *i;
	}
	std::cout << "|\n";

	std::cout << ">>> A:";
	negate(std::begin(vet), std::end(vet)); //!< Nega do 3º ao último
	for(auto i = std::begin(vet); i != std::end(vet); i++){
		std::cout << "|" << *i;
	}
	std::cout << "|\n";

	std::cout << ">>> A:";
	negate(std::begin(vet)+3, std::begin(vet)+4);
	for(auto i = std::begin(vet); i != std::end(vet); i++){
		std::cout << "|" << *i;
	}
	std::cout << "|\n";
	
}