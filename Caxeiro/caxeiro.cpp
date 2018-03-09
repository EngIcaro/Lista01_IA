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
#include <algorithm>
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand

using namespace std;


int main(){
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand

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

	int inicial, fim;
	//cout << "Digite a cidade inicial"
	//cin  >> inicial;
	//cout << "Digite a cidade de destino"
	//cin  >> fim;

	//caminho.push_back(inicial);
	vector<int> caminho;
	vector<int> menorCaminho;
	menorCaminho.push_back(1000);
 	caminho.push_back(1);
	caminho.push_back(2);
	caminho.push_back(3);
	caminho.push_back(4);
	caminho.push_back(5);
	caminho.push_back(6);
	caminho.push_back(7);
	caminho.push_back(8);
	caminho.push_back(9);
	caminho.push_back(10);
//	for(int i =0; i<caminho.size(); i++){
//		std::cout << caminho[i] << ' ';
//	}
int aux =0;
while (1) {
	/* code */

	// gerando o próximo caminho aleatório.
	srand ( unsigned ( std::time(0) ) );
	random_shuffle(caminho.begin()+1, caminho.end());
		for(int i =0; i<caminho.size(); i++){
			//cout << caminho[i] << ' ';
		}
	// Analisar se o caminho existe

	int flag =0;
	int menorCusto = 100000;
	int custo = 0;
	for(int i=0; i<10; i++){
		if(i == 9){
			if(distancia[caminho.at(0)-1][caminho.at(9)-1] == -1){
				flag =1;
			}
			custo = custo + distancia[i][i++];
		}
		else{
		//	std::cout << "blaaaa"<< caminho.at(i) << caminho.at(i+1)<< '\n';
			if(distancia[caminho.at(i)-1][caminho.at(i+1)-1] == -1){
				flag = 1;
				break;
			}
			custo = custo + distancia[i][i+1];
		}
	}
	// vejo se o custo foi menor do que todos analisados até o momento
	if(!flag){
		cout << "O caminho existe e teve custo: " << custo << " O menor custo tem: " << menorCusto;
		if(custo < menorCusto){
			menorCusto = custo;
			menorCaminho.swap(caminho);
		}
	}
	aux++;
	if(aux == 9000)
		break;
}

	/*int count =0;
	do{
		for(int i =0; i<caminho.size(); i++){
			std::cout << caminho[i] << ' ';
		}
		std::cout << '\n';
		count++;
		if(count ==10){
			break;
		}
	}
		while(std::next_permutation(caminho.begin(), caminho.end()));
*/


	vector<vector<int> > fila;
	fila.push_back(caminho);
	return 0;
}
