#include <iostream>
#include <stdlib.h>

int raiseToPower(int n, int k){

	if(k == 0){
		return 1;
	}else if(k == 1){
		return n;
	}else{
		return n*raiseToPower(n, k-1);
	}

}

int main(int argc, char *argv[]){
	
	int n, k, r;

	n = atoi(argv[1]);
	k = atoi(argv[2]);

	r = raiseToPower(n, k);

	std::cout << n << "^" << k << " = " << r;

}