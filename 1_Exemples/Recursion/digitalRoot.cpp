#include <iostream>
#include <stdlib.h>

int digitalRoot(int n){

	int r;

	r = (n%10) + (n/10);

	if(n < 10){
		return n;
	}else{
		digitalRoot(r);
	}

}

int main(int argc, char *argv[]){
	
	int n, r;
	n = atoi(argv[1]);

	r = digitalRoot(n);

	std::cout << "A Raiz Digital: " << r;

}