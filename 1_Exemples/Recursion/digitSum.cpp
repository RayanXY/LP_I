#include <iostream>
#include <stdlib.h>

int digitSum(int n){

	if(n < 10){
		return n;
	}else{
		return (n%10) + digitSum(n/10);
	}

}

int main(int argc, char *argv[]){
	
	int n, r;
	n = atoi(argv[1]);

	r = digitSum(n);

	std::cout << "A soma dos digitos de n: " << r;

}