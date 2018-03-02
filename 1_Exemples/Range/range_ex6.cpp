#include <iostream>

int compact(int s, int v[]){
	int i, j, n_s = s;
	for(i = 0; i < n_s; /* Empty */){
		if(v[i] <= 0){
			for(j = i; j < n_s; j++){
				v[j] = v[j+1];
			}
			n_s--;
		}else{
			i++;
		}
	}
	return n_s;
}

int main(){
	
	/// Vetor
	int i, j, size_ = 10, vet[size_];

	std::cout << ">>> ENTER THE VALUES:\n";
	/// Lendo os números
	for(i = 0; i < size_; i++){
		std::cin >> vet[i];
	}

	/// Vetor passado
	std::cout << ">> A: ";
	for (i = 0; i < size_; i++){
		std::cout << "|" << vet[i];
	}
	std::cout << "|\n";

	std::cout << ">>> COMPACTING...\n";
	/// Compactando e atualizando o size_
	size_ = compact(size_, vet);

	/// Vetor Compactado
	std::cout << ">> A: ";
	for (i = 0; i < size_; i++){
		std::cout << "|" << vet[i];
	}
	std::cout << "|\n";

	std::cout << ">>> END";

}