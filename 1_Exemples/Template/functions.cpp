#include <iostream>	 //Cout
#include <iterator>	 //Begin, End
#include <algorithm> //Copy

template <typename T>
T myMax(T * first, T * last){

	T maior = *first++;

	while(first != last){

		if(*first > maior){
			maior = *first;
		}
		first++;
	}
	return maior;

}

T busca_bin(T * first, T * last, T value){

	auto size = std::distance(first, last);
	auto l(first);
	auto r(last-1);

	while(l < r){
		auto m = (l+r)/2;
		if(first [m] == value){
			return first;
		}else if(value , first[m]){ //!< Go left
			r = m-1;
		}else{						//!< Go right
			l = m+1;
		}
	}
	return last;

}

int main(){

	int A[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	std::string S[] = {"Um", "Dois", "Três", "Quatro"};
	
		std::cout << ">>> A: |";
			std::copy(std::begin(A), std::end(A), std::ostream_iterator<int>(std::cout, " "));
		std::cout << "|\n";
	
		std::cout << ">>> S: |";
		for(const auto & e : S){
			std::cout << "\"" << e << "\"";
		}
		std::cout << "|\n";
	
		std::cout << ">>> Maior de A é: " << myMax(std::begin(A), std::end(A)) << ".\n";
		std::cout << ">>> Maior de S é: " << myMax(std::begin(S), std::end(S)) << ".\n";

		auto target(8);
		std::cout << ">>> A: |";
			std::copy(std::begin(A), std::end(A), std::ostream_iterator<int>(std::cout, " "));
		std::cout << "|\n";

		std::cout << "Searching...";
		auto result = busca_bin(std::begin(A), std::begin(A), target);

		if(result == std::end(A)){
			std::cout << ">>> Element " << target << " not find in A";
		}else{
			std::cout << ">>> Element " << target << " find in A, position " << std::distance(std::begin(A), result) << ".\n";
		}

	return 0;
}