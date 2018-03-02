#include <iostream>
#include <stdlib.h>

int gdc(int a, int b){

	if(b != 0){
		return gdc(b, a%b);
	}else{
		return a;
	}

}

int main (int argc, char *argv[]){
	
	int a, b, r;
	a = atoi(argv[1]);
	b = atoi(argv[2]);

	r = gdc(a, b);

	std::cout << "MDC de " << a << " e " << b << ": " << r;

}