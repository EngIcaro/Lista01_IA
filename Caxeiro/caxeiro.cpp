// RESUMO
// Algoritmo guarda apenas o estado atual e sua avaliação.
// cada busca é executada até que um número máximo de estipulações seja atingido.
// ou que os resultados encontardos não apresentam uma melhora interativa.
// INFORMAÇÕES:
// TENDO UM NÓ DE ORIGEM, EXISTEM 9! 362880 POSSIBILIDADES DE CAMINHOS
// RESTRIÇÕES:
// UMA CIDADE SÓ PODE SER VISITADA UMA VEZ
//
//
// PSEUDO-CÓDIGO
// 1. GERAR UM CAMINHO INICIAL.
// LOOP 1
// 2. ANALISAR SE ESSE CAMINHO ESTÁ LIGADO E SE A CIDADE FINAL ESTÁ CONECTADA CIDADE INICIAL
// 3. SE ESTIVER, ANALISO O CUSTO EM KM, PARA PECORRER TODOS OS VÉRTICES
// 4. SE ESSE CUSTO FOR O MENOR DE TODOS ANALISADOS, GUARDO ESSE CUSTO E O CAMINHO PERCORRIDO
// 5. GERO OS FILHOS DELES PERMUTANDO AS CIDADES A SEREM PERCORRIDAS
// 6. A BUSCA EM LARGURA NOS FILHOS DELES, PARA GERAR O PRÓXIMO A SER ANALISADO. SÃO ANALISADOS MÁXIMO DE 25 NÓS

// 7. FAÇO O REINÍCIO ALEATÓRIO. SÃO FEITOS 20 INTERAÇÕES
//
//FUNÇÃO vector
//.PUSH_BACK ACRESCENTA NO FINAL -- .SWAP TROCA AS INFORMAÇÕES DOS vector -- .FRONT PRIMEIRO ELEMENTO .BACK ULTIMO -- .AT

#include <iostream>
#include <vector>
using namespace std;


int main(){

	int distancia[10][10] = {{ 0, 30, 84, 56, -1, -1, -1, 75, -1, 80},
							 {30,  0, 65, -1, -1, -1, 70, -1, -1, 40},
							 {84, 65,  0, 74, 52, 55, -1, 60,143, 48},
							 {56, -1, 74,  0,135, -1, -1, 20, -1, -1},
							 {-1, -1, 52,135,  0, 70, -1,122, 98, 80},
							 {70, -1, 55, -1, 70,  0, 63, -1, 82, 35},
							 {-1, 70, -1, -1, -1, 63,  0, -1,120, 57},
							 {75, -1,135, 20,122, -1, -1,  0, -1, -1},
							 {-1, -1,143, -1, 98, 82,120, -1,  0, -1},
							 {80, 40, 48, -1, 80, 35, 57, -1, -1,  0}
							};



    //vector<vector<int> > atual;
	//atual.push_back(filhos);
	//std::cout << "vector tem tamanho: " <<atual.size() << "\n "<< atual[0].size() <<'\n';
	//vector<vector<int> > fila;
	//fila[][]
	int filhos[10] = {0,1,2,3,4,5,6,7,8,9};
	vector<int[10]> atual;
	atual.push_back(filhos);

	//fila.push_back(10);
	//fila[0].push_back(1);
	//fila[0].push_back(2);
	//vector<int> vetor[150]
	//cout << "0 0: " << fila[0][0]<<'\n';
	//cout << "0 1: " << fila[0][1]<<'\n';
	return 0;
}
