#include <iostream>
#include <iterator>

int * min(const int *first, const int *last){

	int * minor;
	*minor = *first;
	for(/* Empty */; first != last; first++){
		if(*first < *minor){
			*minor = *first;
		}
	}
	return minor;
	
}

int main(){
	
	int A[] = {1, 2, -3, -4, 5, -6};

	/// Minor: -6
	auto result = min(std::cbegin(A), std::cend(A));
	std::cout << "Minor: " << *result << std::endl;

	/// Minor: -4
	result = min(std::cbegin(A)+1, std::cbegin(A)+5);
	std::cout << "Minor: " << *result << std::endl;

}

int compact(std::vector<int> &V, std::size_t size){
    int i, j = 0;
    for(i = 0; i < size; i++){
        if(V[i] > 0){
            V[j] = V[j+1];
            j++;
        }
    }
}
