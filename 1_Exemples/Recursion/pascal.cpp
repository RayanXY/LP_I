#include <iostream>
#include <stdlib.h>

int pascalTriangle(int n, int k){

	if(k == 0 || k == n){
		return 1;
	}else{
		return pascalTriangle(n - 1, k - 1) + pascalTriangle(n - 1, k);
	}

}

int main(int argc, char *argv[]){

	int i, j, a, h, n, k;
	h = atoi(argv[1]);
	n = atoi(argv[2]);
	k = atoi(argv[3]);
	
	for (i = 0; i <= h; i++){

		a = 1;
		for(j = 0; j<=i; j++){
			std::cout << " " << a << " ";
			a = a*(i-j)/(j+1);
		}

		std::cout << "\n";

	}

	std::cout << "Posição c(" << n << ", " << k << ") é: " << pascalTriangle(n, k);

}