#include <iostream>
#include <cstring>
#include <iterator>
#include <functional>

using byte = unsigned char;

void print(int * first, int * last){
	
	std::cout << "A: ";
	while(first != last){
		std::cout << "|" << *first;
		first++;
	}
	std::cout << "|\n";

}

void reverse(void * first, void * last, size_t size){

	byte *f = (byte *) first;
	byte *l = (byte *) last;

	auto n = (l - f)/size; //!< N elementos no vetor
	byte aux[size]; //!< Auxilixar para viabilizar trocas 

	int *t = (int*) f;
	auto offset(0u);
	for(auto i(0u); i < n/2; i += size){
		/// aux = V[i];
		std::memcpy(aux, f+(i*size), size);
		/// V[i] = V[n-i-1];
		std::memcpy(f+offset, f+(n-i-1)*size, size);
		/// V[n-i-1] = aux;
		std::memcpy(f+(n-i-1)*size, aux, size);
	}

}

bool maior_5(const void * e){
	const int * i = (const int *) e;
	return *i > 5;
}

void * find_if(const void * first, const void * last, size_t size, std::function < bool(const void *) > p){

	const byte *f = (const byte *) first;
	const byte *l = (const byte *) last;

	for(/* Empty */; f != l; f+= size){
		if(p(f)){
			return (void *) f;
		}
	}
	return (void *) f;

}

int main(void){
	int V[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	int * result = (int *) find_if(std::begin(V), std::end(V), sizeof(int), maior_5);
	std::cout << "Result: " << *result << "\n";
}