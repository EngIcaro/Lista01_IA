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
    int max;                       // max = 1 quer o max
    int alfa;                       // alfa =  quer o
    int peso;
    int elemento;                  // elemeto = 1 é o X!
    int funcAvaliacao;
    int campo[3][3];
    CampoAtual *father;
    CampoAtual(int maxx, int elementoo, int pesoo,int campoo[3][3], CampoAtual *fatherr){
       elemento = elementoo;
       max = maxx;
       if(max)
          alfa = -1500;
       else
          alfa = 1500;
       for(int i =0; i< 3; i++){
           for(int j =0; j<3; j++){
               campo[i][j] = campoo[i][j];
           }
       }
       funcAvaliacao = 0;
       father = fatherr;
       peso = pesoo;
    }

    bool eFolha(){
        for(int i =0; i< 3; i++){
            if((campo[i][0] == campo[i][1]) && (campo[i][1] == campo[i][2]) && campo[i][2] != -1)
              return true;
        }
        for(int i =0; i< 3; i++){
            if((campo[0][i] == campo[1][i]) && (campo[1][i] == campo[2][i]) && campo[2][i] != -1)
              return true;
        }
        if((campo[0][0] == campo[1][1]) && (campo[1][1] == campo[2][2]) && campo[2][2] != -1){
              return true;
        }
        if((campo[2][0] == campo[1][1]) && (campo[1][1] == campo[0][2]) && campo[1][1] != -1){
              return true;
        }
        for(int i =0; i< 3; i++){
            for(int j =0; j<3; j++){
                  if(campo[i][j] == -1){
                    return false;
                  }
            }
        }
        return true;
    }
    void gerarAvaliacao(){
        int flag =0;
      for(int i =0; i< 3; i++){
          if((campo[i][0] == campo[i][1]) && (campo[i][1] == campo[i][2]) && (campo[i][2] == 1)){
            funcAvaliacao = 1 * peso;
            flag =1;
          }

      }
      for(int i =0; i< 3; i++){
          if((campo[0][i] == campo[1][i]) && (campo[1][i] == campo[2][i]) && campo[2][i] == 1){
            funcAvaliacao = 1 * peso;
            flag =1;
          }

      }
      if((campo[0][0] == campo[1][1]) && (campo[1][1] == campo[2][2]) && campo[2][2] == 1){
            funcAvaliacao = 1 * peso;
            flag = 1;

      }
      if((campo[2][0] == campo[1][1]) && (campo[1][1] == campo[0][2]) && campo[1][1] == 1){
            funcAvaliacao = 1 * peso;
            flag = 1;
      }
      for(int i =0; i< 3; i++){
          if((campo[i][0] == campo[i][1]) && (campo[i][1] == campo[i][2]) && campo[i][2] == 0){
            funcAvaliacao = -1 * peso;
            flag = 1;
          }
      }
      for(int i =0; i< 3; i++){
          if((campo[0][i] == campo[1][i]) && (campo[1][i] == campo[2][i]) && campo[2][i] == 0){
            funcAvaliacao = -1 * peso;
            flag =1;
          }

      }
      if((campo[0][0] == campo[1][1]) && (campo[1][1] == campo[2][2]) && campo[2][2] == 0){
            flag = 1;
            funcAvaliacao = -1 * peso;

      }
      if((campo[2][0] == campo[1][1]) && (campo[1][1] == campo[0][2]) && campo[1][1] == 0){
            funcAvaliacao = -1 * peso;
            flag = 1;

      }
      if(flag == 0){
            funcAvaliacao = 0;
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
    void escolherJogada(int raiz[3][3], int mi){
        pilhaDeCampo.clear();
        pilhaDeRetorno.clear();
        CampoAtual *campo = new CampoAtual(mi,1,200,raiz,0);
        pilhaDeCampo.push(campo);

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
                                if(campoAtual->max){
                                    campoAtual->campo[i][j] = 1;
                                   //  std::cout << "entrei 1";
                                    CampoAtual *novoCampo = new CampoAtual(0, 0, campoAtual->peso - 1,campoAtual->campo, campoAtual);
                                    pilhaDeCampo.push(novoCampo);
                                    campoAtual->campo[i][j] = -1;
                                }
                                else{
                                    campoAtual->campo[i][j] = 1;
                                  //  std::cout << "entrei 2";
                                    CampoAtual *novoCampo = new CampoAtual(1, 0, campoAtual->peso - 1,campoAtual->campo, campoAtual);
                                    pilhaDeCampo.push(novoCampo);
                                    campoAtual->campo[i][j] = -1;
                                }
                            }
                            else{
                                if(campoAtual->max){
                                 //   std::cout << "entrei 3";
                                    campoAtual->campo[i][j] = 0;
                                    CampoAtual *novoCampo = new CampoAtual(0, 1, campoAtual->peso - 1,campoAtual->campo, campoAtual);

                                    campoAtual->campo[i][j] = -1;
                                }
                                else{
                                   //  std::cout << "entrei 4";
                                     campoAtual->campo[i][j] = 0;
                                     CampoAtual *novoCampo = new CampoAtual(1, 1, campoAtual->peso - 1,campoAtual->campo, campoAtual);
                                     pilhaDeCampo.push(novoCampo);
                                     campoAtual->campo[i][j] = -1;
                                }
                            }
                        }
                    }
                }
            }
            //std::cout << pilhaDeCampo.size() <<" pilha de retorno: " <<pilhaDeRetorno.size() <<'\n';
        }
        //std::cout << "aquiiii" <<pilhaDeRetorno.size();
        while(pilhaDeRetorno.size()){
            //std::cout  << pilhaDeRetorno.size() << '\n';
            CampoAtual *campoAtual = pilhaDeRetorno.pop();
            if(campoAtual->father->max){
                if(campoAtual->alfa > campoAtual->father->alfa){
                    campoAtual->father->alfa = campoAtual->alfa;
                    if(campoAtual->father->father == 0){
                        //std::cout << "meu filho tem: " << campoAtual->alfa << " e meu atual: " << campoAtual->father->alfa;
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
                    if(campoAtual->father->father == 0){
                        for(int i=0; i<3; i++){
                            for(int j=0; j<3; j++){
                                campoFinal[i][j] = campoAtual->campo[i][j];
                            }
                        }
                    }
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
    std::cout << "OLÁ, EU SOU O PROFESSOR DUMBLEDORE, SOU CAMPEÃO MUNDIAL DO JOGO DA VELHA!\nX É REPRESENTADO PELO VALOR 1, O É "
                 "REPRESENTADO PELO VALOR 0, CAMPO VAZIO\nPELO VALOR -1\nVAMOS JOGAR UMA PARTIDA!?\n";
    //std::cout << "escolha linha e coluna respectivamente";
    //std::cin  >> linha >> coluna;
    //  matriz[linha][coluna] = 0;
    MiniMax *mini = new MiniMax();
  //  mini->escolherJogada(matriz, 1);
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            mini->campoFinal[i][j] = -1;
                std::cout << " "<<mini->campoFinal[i][j] << " | ";
        }
        std::cout << "\n";
    }
    for(int i=0; i<5; i++){
        std::cout << "\nESCOLHA UMA LINHA E COLUNA RESPECTIVAMENTE, APENAS VALORES ENTRE [0, 2] ";
        std::cin  >> linha >> coluna;
        mini->campoFinal[linha][coluna] = 0;
        CampoAtual *novoCampoo = new CampoAtual(1, 1,0,mini->campoFinal, 0);
        if(novoCampoo->eFolha()){
            std::cout << "DEU EMPATE\n";
            return 0;
        }
        mini->escolherJogada(mini->campoFinal, 1);
        CampoAtual *novoCampo = new CampoAtual(1, 1,0,mini->campoFinal, 0);
        if(novoCampo->eFolha()){
            std::cout << "EU GANHEI\n";
            return 0;
        }
    }
    return 0;
    return a.exec();
}
