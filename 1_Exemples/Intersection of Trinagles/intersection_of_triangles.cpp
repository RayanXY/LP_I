#include <iostream>

//Tipo para definir os pontos dos retângulos.
typedef struct Rectangle{
    
    int x, y, w, h;

}RECT;

/*!
*@brief A função irá verificar se o ponto v_ está entre o intervalo (projeção) do outro retângulo (min e max).
*@param v_ Valor do ponto
*@param min Valor min do ponto do outro retângulo.
*@param max Valor max do ponto do outro retângulo.
*
*@return 1 (True) se o ponto estiver no intervalo ou 0 (False) se não estiver
*/
bool range(int v_, int min, int max){
    return(
        v_ >= min and v_ <= max 
    );
}

/*!
*@brief A função irá verificar se há interseção entre os dois retângulos R e S.
*@param xIntersection Armazena o resultado da função 'range' no eixo x dos retângulos R e S.
*@param yIntersection Armazena o resultado da função 'range' no eixo y dos retângulos R e S.
*
*@return 1 (True) se os resultados das váriaveis xIntersection e yIntersection também forem 1 (True) 
*   ou 0 (False) se um ou os dois forem 0 (False).
*/
bool intersection(RECT R, RECT S){

    bool xIntersection = range(R.x, S.x, S.x + S.w) or range(S.x, R.x, R.x + R.w);
    bool yIntersection = range(R.y, S.y, S.y + S.h) or range(S.y, R.y, R.y + R.h);

    return xIntersection and yIntersection;

}
//Testando
int main(){
    RECT R, S, T;
// R
    R.x = 2;
    R.y = 3;
    R.w = 2;
    R.h = 2;
// S    
    S.x = 4;
    S.y = 2;
    S.w = 3;
    S.h = 2;     
// T    
    T.x = 6;
    T.y = 1;
    T.w = 3;
    T.h = 2;

    //R e S - Há interseção
    bool rR_S = intersection(R, S);

    if(rR_S == 1){

        std::cout << "R e S: Tem intersecao\n";

    }else{

        std::cout << "R e S: Nao tem intersecao\n";

    }

    //S e T - Há interseção
    bool rS_T = intersection(S, T);

    if(rS_T == 1){

        std::cout << "S e T: Tem intersecao\n";

    }else{

        std::cout << "S e T: Nao tem intersecao\n";

    }

    //R e T - Não há interseção
    bool rR_T = intersection(R, T);

    if(rR_T == 1){

        std::cout << "R e T: Tem intersecao\n";

    }else{

        std::cout << "R e T: Nao tem intersecao\n";

    }

}