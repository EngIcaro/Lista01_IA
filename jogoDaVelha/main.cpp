#include <QCoreApplication>
#include <iostream>
#include <QDebug>
#include <QStack>
// 1º VOU GERAR O CAMPO VAZIO
// 2º

// ATRIBUTOS:
// NÓ VAI CONTER UM BOOL PARA SABER SE É MAX OU MINI, PONTEIRO PARA O PAI, UM ALFA E BETA,
// UMA MATRIZ DA POSIÇÃO ATUAL DO JOGO DA VELHA, FUNÇÃO DE AVALIAÇÃO
// MÉTODOS:
// É SOLUÇÃO? GERAR FUNÇÃO DA AVALIAÇÃO

class CampoAtual
{
public:
    bool max;                       // max = 1 quer o max
    int alfa;                       // alfa =  quer o
    bool elemento;                  // elemeto = 1 é o X!
    int funcAvaliacao;
    int campo[3][3];
    CampoAtual *father;
    CampoAtual(bool maxx,bool elementoo ,int campoo[3][3], CampoAtual *fatherr){
       elemento = elementoo;
       max = maxx;
       if(max)
          alfa = -150;
       else
          alfa = 150;
       for(int i =0; i< 3; i++){
           for(int j =0; j<3; j++){
               campo[i][j] = campoo[i][j];
           }
       }
       funcAvaliacao = 0;
       father = fatherr;
    }

    bool eFolha(){
        for(int i =0; i< 3; i++){
            for(int j =0; j<3; j++){
                if(campo[i][j] == -1)
                    return false;
            }
        }
        return true;
    }
    void gerarAvaliacao(){
        // Percorrer todas as linhas
        for(int i =0; i< 3; i++){
            for(int j =0; j<3; j++){
                if(campo[i][j] == 1)
                    funcAvaliacao++;
                else if(campo[i][j] == 0)
                    funcAvaliacao--;
            }
        }
        // Percorrer todas as colunas
        for(int i =0; i< 3; i++){
            for(int j =0; j<3; j++){
                if(campo[j][i] == 1)
                    funcAvaliacao++;
                else if(campo[j][i] == 0)
                    funcAvaliacao--;
            }
        }
        // Percorrer todas as colunas
        for(int i =0; i< 3; i++){
                if(campo[i][i] == 1)
                    funcAvaliacao++;
                else if(campo[i][i] == 0)
                    funcAvaliacao--;
        }

    }
};

// ATRIBUTOS:
// LISTA DE CAMPOS, ALFA, FUNÇÃO DE AVALIAÇÃO
class MiniMax
{

public:
    int campoFinal[3][3];
    int funcAvaliacao;
    QStack<CampoAtual*> pilhaDeCampo;
    QStack<CampoAtual*> pilhaDeRetorno;
    MiniMax(){
        pilhaDeCampo.clear();
        pilhaDeRetorno.clear();
    }
    void escolherJogada(int raiz[3][3]){
        pilhaDeCampo.clear();
        pilhaDeRetorno.clear();
        CampoAtual *campo = new CampoAtual(1,1,raiz,0);
        pilhaDeCampo.push(campo);
        std::cout << pilhaDeCampo.size() << '\n';
        while(pilhaDeCampo.size()){
            CampoAtual *campoAtual = pilhaDeCampo.pop();
            //std::cout << campoAtual->alfa;
            if(campoAtual->eFolha()){
               // std::cout << "cheguei em uma folha";
                campoAtual->gerarAvaliacao();
                // precisa saber se o pai quer o máximo ou o mínimo dos filhos.
                if(campoAtual->father->max){
                    if(campoAtual->father->father != 0){
                        if(campoAtual->funcAvaliacao > campoAtual->father->alfa){
                            campoAtual->father->alfa = campoAtual->funcAvaliacao;
                        }
                    }
                    else{
                        if(campoAtual->funcAvaliacao > campoAtual->father->alfa){
                            campoAtual->father->alfa = campoAtual->funcAvaliacao;
                            for(int i=0; i<3; i++){
                                for(int j=0; j<3; j++){
                                    campoFinal[i][j] = campoAtual->campo[i][j];
                                }
                            }
                        }
                    }
                }
                else{
                    if(campoAtual->funcAvaliacao < campoAtual->father->alfa){
                        campoAtual->father->alfa = campoAtual->funcAvaliacao;
                    }
                }
            }
            // se não for folha, eu vou gerar todos os filhos
            else{
                //std::cout << "entro aqui";
                if(campoAtual->father != 0)
                    pilhaDeRetorno.push(campoAtual);
                // gerar todos os filhos, loops para percorrer o campo, e se for == -1
                // é preciso saber se vai marcar como bola ou x
                for(int i=0; i<3; i++){
                    for(int j=0; j<3; j++){
                        if(campoAtual->campo[i][j] == -1){
                            if(campoAtual->elemento){
                                campoAtual->campo[i][j] = 1;
                                CampoAtual *novoCampo = new CampoAtual(!(campoAtual->max), !(campoAtual->elemento),campoAtual->campo, campoAtual);
                                pilhaDeCampo.push(novoCampo);
                                campoAtual->campo[i][j] = -1;
                            }
                            else{
                                campoAtual->campo[i][j] = 0;
                                CampoAtual *novoCampo = new CampoAtual(!(campoAtual->max), !(campoAtual->elemento),campoAtual->campo, campoAtual);
                                pilhaDeCampo.push(novoCampo);
                                campoAtual->campo[i][j] = -1;
                            }
                        }
                    }
                }
            }
            std::cout << pilhaDeCampo.size() <<" pilha de retorno: " <<pilhaDeRetorno.size() <<'\n';
        }
        //std::cout << "aquiiii" <<pilhaDeRetorno.size();
        while(pilhaDeRetorno.size()){
            std::cout  << pilhaDeRetorno.size() << '\n';
            CampoAtual *campoAtual = pilhaDeRetorno.pop();
            if(campoAtual->father->max){
                if(campoAtual->alfa > campoAtual->father->alfa){
                    campoAtual->father->alfa = campoAtual->alfa;
                    if(campoAtual->father->father == 0){
                        for(int i=0; i<3; i++){
                            for(int j=0; j<3; j++){
                                campoFinal[i][j] = campoAtual->campo[i][j];
                            }
                        }
                    }
                }
            }
            else{
                if(campoAtual->alfa < campoAtual->father->alfa){
                    campoAtual->father->alfa = campoAtual->alfa;
                }
            }
        }
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                if(campoFinal[i][j] !=-1){
                    std::cout << " "<<campoFinal[i][j] << " | ";
                }
                else{
                    std::cout << campoFinal[i][j] << " | ";
                }
            }
                std::cout << "\n";
        }
    }
};


int main(int argc, char *argv[])
{
    int linha, coluna;
    QCoreApplication a(argc, argv);
    int matriz[3][3];
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            matriz[i][j] = -1;
        }
    }
    //std::cout << "escolha linha e coluna respectivamente";
    //std::cin  >> linha >> coluna;
    //  matriz[linha][coluna] = 0;
    MiniMax *mini = new MiniMax();
    mini->escolherJogada(matriz);
    for(int i=0; i<5; i++){
        std::cout << "escolha linha e coluna respectivamente";
        std::cin  >> linha >> coluna;
        mini->campoFinal[linha][coluna] = 0;
        mini->escolherJogada(mini->campoFinal);
    }
    return 0;
    return a.exec();
}
