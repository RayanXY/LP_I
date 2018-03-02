#include <iostream>
#include <iterator>

int dot_product(const int *a_first, const int *a_last, const int *b_first){
	
	int result = 0;

	for(/* Empty */; *a_first != *a_last; *a_first++){
		result += (*a_first * *b_first);
		*b_first++;
	}
	
	return result;

}

int main(){

	int vet[] = {1, 3, -5, 4, -2, -1};

	auto result = dot_product(std::begin(vet), std::begin(vet)+3, std::begin(vet)+3);

	std::cout << "Result: " << result << "\n";

}