#include <iostream>
#include <string>
#include <cstring>

using byte = unsigned char;

void swap(void * a, void * b, size_t size){

	byte aux[size];

	std::memcpy(aux, a, size); //!< Equivalente -> aux = a
	std::memcpy(a,  b,  size); //!< Equivalente -> a = b
	std::memcpy(b, aux, size); //!< Equivalente -> b = aux

}

int main(void){

	int a(5), b(8);
	std::string c("Cinco"), d("Oito");

	/// Letras
	std::cout << "Original: c = " << c << " and d = " << d << "\n";
	swap(&c, &d, sizeof(c));
	std::cout << "Swap: c = " << c << " and d = " << d << "\n";

}