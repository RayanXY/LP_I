#include <iostream>
#include <stdlib.h>

int cannonball(int n){

	if(n > 1){
		return (n*n) + cannonball(n-1);
	}else{
		return 1;
	}

}

int main(int argc, char *argv[]){

	int height = atoi(argv[1]);
	int result;

	result = cannonball(height);

	std::cout << "Formada por: " << result << " bolas\n";

}