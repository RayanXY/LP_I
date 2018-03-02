#include <iostream>
#include <cassert>

//using namespace std;

/*!
*@brief Função que calcula a potência de n^k e retorna o seu valor.
*@param n_ Valor de base.
*@param k_ Espoente.
*
*@note Função assume expoentes positivos.
*
*@return 0 Valor de n^k.
*/

int raise_to_power(int n_, int k_){

	auto result(1);

	for(auto i(0); i < k_; i++){

		result *= n_;

	}

	return result;

}

int main(){
	
	auto limit(0);

	std::cout << ">> Este programa apresenta as potencias de 2.\n";

	std::cout << ">> Entre com o expoente (Maior que 0):\n";
	std::cin >> limit;


	for(auto j(0); j <= limit; j++){

		std::cout << ">>> 2^" << j << " = " << raise_to_power(2, j) << "\n";
 
	}

	/*	
	//std::cout << raise_to_power(2, limit) << "\n";
	assert(raise_to_power(2,3) == 8); Faz um teste se o valor é o correto
	std::cout << ">> Resultado:" << raise_to_power(2,3) << "\n";
	*/
	return 0; //Retona 0

}

//<< Contatena as coisas.
//Executando: g++ nome.cpp -o nome