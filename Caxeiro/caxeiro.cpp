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
#include <string.h>

using namespace std;

int myrandom (int i) { return std::rand()%10;}
vector<int> caminho;
vector<int> menorCaminho;
vector<vector<int> > fila;
int menorCusto = 100000;
int custo = 0;
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

bool existeCaminho(){
	bool flag = 0;
	custo = 0;
	for(int i=0; i<10; i++){
		if(i == 9){
			if(distancia[caminho.at(0)][caminho.at(9)] == -1){
				flag =1;
			}
			custo = custo + distancia[caminho.at(9)][caminho.at(0)];
		}
		else{

			if(distancia[caminho.at(i)][caminho.at(i+1)] == -1){
				flag = 1;
				break;
			}
			custo = custo + distancia[caminho.at(i)][caminho.at(i+1)];
		}
	}
	return flag;
}

void gerarFilhos(){
	// gerando filho 1 que é a metade trocada
	int swap;
	next_permutation(caminho.begin()+1, caminho.end());
	fila.push_back(caminho);
	swap = caminho[1];
	caminho[1] = caminho[9];
	caminho[9] = swap;
	next_permutation(caminho.begin()+1, caminho.end());
	fila.push_back(caminho);
}



int main(){
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand


	int inicial;
	cout << "Digite a cidade inicial";
	cin  >> inicial;
	inicial = inicial - 1;

	//caminho.push_back(inicial);
	int aux =0;
	int atual;
	int map[10];
	int cont;
	int flag = 0;
	menorCaminho.push_back(1000);
	memset(map, 0, 10);
	srand (time(NULL));

while (1) {
	/* code */
	caminho.clear();
	caminho.push_back(inicial);
	for(int i =0; i<10; i++){
		map[i] = 0;
	}
	map[inicial] = 1;
	// gerando o próximo caminho aleatório.

  	/* initialize random seed: */
	cont = 0;
	while(cont < 9){
 		atual = rand() % 10; // vai de 0 a 9
		if(map[atual] == 0){
			map[atual] = 1;
			caminho.push_back(atual);
			cont++;
		}

	}


	flag = existeCaminho();
//cacau loves you

	// vejo se o custo foi menor do que todos analisados até o momento
	if(!flag){
		if(custo < menorCusto){
			menorCusto = custo;
			menorCaminho.clear();
			for(int i=0; i<10; i++){
				menorCaminho.push_back(caminho[i]);
			}
		}
		fila.push_back(caminho);
		gerarFilhos();
		for(int i=0; i<fila.size()-1; i++){
			caminho.swap(fila[i+1]);
			flag = existeCaminho();
			if(!flag){
				if(custo < menorCusto){
					menorCusto = custo;
					menorCaminho.clear();
					for(int j=0; j<10; j++){
						menorCaminho.push_back(caminho[j]);
					}
				gerarFilhos();
				}
			}
		}
	}

	//fila.push_back(caminho);
	aux++;
	if(aux == 30000)
		break;
	}

	cout << "A cidade escolhida foi: " << inicial+1 << "\nO menor caminho para o caxeiro visitar todas as cidades, saíndo e chegando na própria cidade foi de:"
	     << menorCusto << "\n E o caminho foi esse:";
	for(int i =0; i<10; i++){
		cout << " " << menorCaminho[i]+1;
	}
	return 0;
}
