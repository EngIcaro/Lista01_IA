#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>    // std::sort
using namespace std;
/* O NÓ DO MEU GRAFO VAI CONTER:
1: UM  VECTOR DE VECTOR, IDENTIFICANDO OS  REGISTRO DO NÓ
   [0] = age [1] = spectacle [2] = astigmatic [3]  = tear
   [4] = class
2: ARRAY  DE  4 POSIÇÕES CORRESPONDESTES AOS  RESPECTIVOS
   ATRIBUTOS, ONDE 0 NÃO FOI AVALIADO E 1 JÁ FOI AVALIADO
3: INTEIRO DIZENDO QUAL O ATRIBUTO ATUAL ANALISADO DE 0 A
  3
4: UM INTEIRO DIZENDO SE ESSE NÓ É CLASSE OU CONJUNTO  DE
   REGISTROS
5: UM ARRAY REFERENTE AS DECISÕES  DO  ATRIBUTO ANALISADO
*/

class nodeGraph{
public:
    int attribute[4];
    int atualAttribute;
    int isClass;
    int taxaErro;
    //int decision[3];
    vector<vector<int> > instance;

    nodeGraph(int attri[], int atual, vector<vector<int> > inst){
        attribute[0] = attri[0]; attribute[1] = attri[1];
        attribute[2] = attri[2]; attribute[3] = attri[3];
        atualAttribute = atual;
        isClass = 0;
        taxaErro = 0;
        for(int i =0; i< inst.size(); i++){
            instance.push_back(inst[i]);
        }
      //cout << "saí desse loop" << '\n';
      //for(int i =0; i< instance.size(); i++){
      //}
    }
    // METODO PARA SABER SE EXISTE APENAS UMA CLASSE NA TABELA
    bool oneClass(){
        if(instance.size() != 0){
            int atual = instance[0][4];
            for(int i=1; i < instance.size(); i++){
                //cout << "comparando " << atual << "com " << instance[i][4] ;
                if(atual != instance[i][4]){
                    //cout << "existe mais de uma classe";
                    return false;
                }
            }
        //cout << "existe apenas uma classe";
        return true;
        }
        return true;
    }
    // METODO PARA SABER SE TODOS OS ATRIBUTOS INDEPENDENTES JÁ FORAM ANALISADOS
    bool haveAttribute(){
        for(int i=0; i<4; i++){
        //    cout << attribute[i] << '\n';
            if(attribute[i] == 0){
        //        cout << "ainda resta atributo \n";
                return true;
            }
        }
    //    cout << "todos atributos já foram analisados \n";
        return false;
    }

    /*void setDecision(){
        if(atualAttribute = 1){
            decision[0] = 1;
            decision[1] = 2;
            decision[2] = 3;
        }
        else if(atualAttribute = 2){
            decision[0] = 1;
            decision[1] = 2;
        }
        else if(atualAttribute = 3){
            decision[0] = 1;
            decision[1] = 2;
        }
        else{
            decision[0] = 1;
            decision[1] = 2;
        }
    }*/
    double getEntropy(){
        double total = instance.size();
        double classA = 0; double classB=0; double classC = 0;
        double entropy = 0;
        for(int i=0; i<instance.size(); i++){
            if(instance[i][4] == 1){
                classA++;
            }
            else if(instance[i][4] == 2){
                classB++;
            }
            else{
                classC++;
            }
        }
        if(classC != 0 && classA != 0 && classB != 0){
            entropy = (-((classA/total)*log2(classA/total)) - ((classB/total)*log2(classB/total)) - ((classC/total)*log2(classC/total)));
        }
        else if(classC !=0 && classA !=0 && classB == 0){
            entropy = (-((classA/total)*log2(classA/total)) - ((classC/total)*log2(classC/total)));
        }
        else if(classC !=0 && classA ==0 && classB != 0){
            entropy = ( - ((classB/total)*log2(classB/total)) - ((classC/total)*log2(classC/total)));
        }
        else if(classC !=0 && classA ==0 && classB == 0){
            entropy = (- ((classC/total)*log2(classC/total)));
        }
        else if(classC ==0 && classA !=0 && classB != 0){
            entropy = (-((classA/total)*log2(classA/total)) - ((classB/total)*log2(classB/total)));
        }
        else if(classC ==0 && classA !=0 && classB == 0){
            entropy = (-(classA/total)*log2(classA/total));
        }
        else if(classC ==0 && classA ==0 && classB != 0){
            entropy = (((classB/total)*log2(classB/total)));
        }
        else if(classC ==0 && classA ==0 && classB == 0){
            entropy = 0;
        }
    }
};

/*  ATRIBUTOS DA MINHA CLASSE GRAFO:
    1: VECTOR DE NODEGRAPH NA ORDEM DE UMA BUSCA EM LARGURA
    2: VECTOR DE NODEGRAPH DA PROFUNDIDADE QUE  SE ENCONTRA
*/
class graph{
public:
    vector<nodeGraph*> tree;
    vector<nodeGraph*> depth;
    graph(vector<vector<int> > inst){
        int attri[4] = {0,0,0,0};
        nodeGraph *root = new nodeGraph(attri, -1, inst);
        tree.push_back(root);
    //    cout << "tudo ok no contrutor" << '\n';
    }

    void creatTree(){
        int attr;
        vector<vector<int> > sonA;
        vector<vector<int> > sonB;
        vector<vector<int> > sonC;
        int auxx[4];
        int arrayAux[3] = {0,0,0};
        for(int i=0; i < tree.size(); i++){
            //std::cout << "mais um loop da contrução da árvore " << tree.size() <<'\n';
            nodeGraph *atualNode = tree[i];
            if(tree.size() > 50){
                break;
            }
        //    cout << "aqui1?" << '\n';
            if(atualNode->oneClass()){
                if(atualNode->instance.size() != 0){
                    atualNode->isClass = atualNode->instance[0][4];
                }
            }
            else{
                if(atualNode->haveAttribute()){
                    attr = chooseAttri(atualNode);
                    if(attr == 0){
                        for(int i=0; i< atualNode->instance.size(); i++){
                            if(atualNode->instance[i][0] == 1){
                                sonA.push_back(atualNode->instance[i]);
                            }
                            else if(atualNode->instance[i][0] == 2){
                                sonB.push_back(atualNode->instance[i]);
                            }
                            else if(atualNode->instance[i][0] == 3){
                                sonC.push_back(atualNode->instance[i]);
                            }
                        }
                    //    std::cout << "ATRIIIIIIII 000" << '\n';
                        auxx[0] = 1;
                        auxx[1] = atualNode->attribute[1];
                        auxx[2] = atualNode->attribute[2];
                        auxx[3] = atualNode->attribute[3];
                        nodeGraph *A  = new nodeGraph(auxx, 0, sonA);
                        tree.push_back(A);
                        nodeGraph *B  = new nodeGraph(auxx, 0, sonB);
                        tree.push_back(B);
                        nodeGraph *C  = new nodeGraph(auxx, 0, sonC);
                        tree.push_back(C);
                        sonA.clear();
                        sonB.clear();
                        sonC.clear();
                    }
                    else if(attr == 1){
                        for(int i=0; i< atualNode->instance.size(); i++){
                            if(atualNode->instance[i][1] == 1){
                                sonA.push_back(atualNode->instance[i]);
                            }
                            else if(atualNode->instance[i][1] == 2){
                                sonB.push_back(atualNode->instance[i]);
                            }
                        }
                    //    std::cout << "ATRIIIIIIII 11111" << '\n';
                        auxx[0] = atualNode->attribute[0];
                        auxx[1] = 1;
                        auxx[2] = atualNode->attribute[2];
                        auxx[3] = atualNode->attribute[3];
                        nodeGraph *A  = new nodeGraph(auxx, 1, sonA);
                        tree.push_back(A);
                        nodeGraph *B  = new nodeGraph(auxx, 1, sonB);
                        tree.push_back(B);
                        sonA.clear();
                        sonB.clear();
                    }
                    else if(attr == 2){
                        for(int i=0; i< atualNode->instance.size(); i++){
                            if(atualNode->instance[i][2] == 1){
                                sonA.push_back(atualNode->instance[i]);
                            }
                            else if(atualNode->instance[i][2] == 2){
                                sonB.push_back(atualNode->instance[i]);
                            }
                        }
                        //std::cout << "ATRIIIIIIII 2222222222222222" << '\n';
                        auxx[0] = atualNode->attribute[0];
                        auxx[1] = atualNode->attribute[1];
                        auxx[2] = 1;
                        auxx[3] = atualNode->attribute[3];
                        nodeGraph *A  = new nodeGraph(auxx, 2, sonA);
                        tree.push_back(A);
                        nodeGraph *B  = new nodeGraph(auxx, 2, sonB);
                        tree.push_back(B);
                        sonA.clear();
                        sonB.clear();
                    }
                    else if(attr == 3){
                        int flaga = 0;
                        int flagb = 0;
                        for(int i=0; i< atualNode->instance.size(); i++){
                            if(atualNode->instance[i][3] == 1){
                                sonA.push_back(atualNode->instance[i]);
                            //    cout << sonA[flaga][0] << " "; cout << sonA[flaga][1] << " "; cout << sonA[flaga][2] << " ";
                            //    cout << sonA[flaga][3] << " "; cout << sonA[flaga][4] << "\n";
                                flaga ++;
                            }
                            else if(atualNode->instance[i][3] == 2){
                                sonB.push_back(atualNode->instance[i]);
                            //    cout << sonB[flagb][0] << " "; cout << sonB[flagb][1] << " "; cout << sonB[flagb][2]<< " ";
                            //    cout << sonB[flagb][3]<< " "; cout << sonB[flagb][4]<< " \n\n";
                                flagb++;
                            }
                        }
                        //std::cout << "ATRIIIIIIII333333 == 1 " << sonA.size() << " == 2 "<< sonB.size() <<'\n';
                        auxx[0] = atualNode->attribute[0];
                        auxx[1] = atualNode->attribute[1];
                        auxx[2] = atualNode->attribute[2];
                        auxx[3] = 1;
                        nodeGraph *A  = new nodeGraph(auxx, 3, sonA);
                        tree.push_back(A);
                        nodeGraph *B  = new nodeGraph(auxx, 3, sonB);
                        tree.push_back(B);
                        sonA.clear();
                        sonB.clear();
                    }
                }
                else{
                    //std::cout << "ENTREIIIIIIIIIII AQUIII" << '\n';
                    for(int i=0; i<atualNode->instance.size(); i++){
                        if(atualNode->instance[i][4] == 1){
                            arrayAux[0]++;
                        }
                        else if(atualNode->instance[i][4] == 2){
                            arrayAux[1]++;
                        }
                        else{
                            arrayAux[2]++;
                        }
                        if(arrayAux[0] > arrayAux[1] && arrayAux[0] > arrayAux[2]){
                            atualNode->isClass = 1;
                        }
                        else if(arrayAux[1] > arrayAux[0] && arrayAux[1] > arrayAux[2]){
                            atualNode->isClass = 2;
                        }
                        else{
                            atualNode->isClass = 3;
                        }
                        sort(arrayAux, arrayAux+3);
                        atualNode->taxaErro = 1 - (arrayAux[2]/(arrayAux[0]+arrayAux[1]+arrayAux[2]));
                    }
                }
            }
            //std::cout << "PASSEI NA CONTRUÇÃO DA ÁRVORE" << '\n';
        }
    }
    int chooseAttri(nodeGraph *node){
        double ES = node->getEntropy();
        double ESV = 0;                 // ENTROPIA PARA DOS FILHOS
        double gain = -1;                // GANHO
        int bestAttribute = 0;          // GUARDAR O MELHOR ATRIBUTO
        double A; double AV;
        double BV;
        double CV;
        vector<vector<int> > diviA;
        vector<vector<int> > diviB;
        vector<vector<int> > diviC;
        //std::cout << "ENTREI NA ESCOLHA DO ATRIBUTO" << '\n';
        //percorrer todos os atributos não utilizados na árvore até o momento
        // para saber qual o melhor atributo a ser analisado a partir desse nó

        //dividindo para age
        if(node->attribute[0] == 0){
            for(int i=0; i< node->instance.size(); i++){
                if(node->instance[i][0] == 1){
                    diviA.push_back(node->instance[i]);
                }
                else if(node->instance[i][0] == 2){
                    diviB.push_back(node->instance[i]);
                }
                else if(node->instance[i][0] == 3){
                    diviC.push_back(node->instance[i]);
                }
            }
            int aux[4] = {0,0,0,0};
            nodeGraph *nodeA = new nodeGraph(aux, 0, diviA);
            nodeGraph *nodeB = new nodeGraph(aux, 0, diviB);
            nodeGraph *nodeC = new nodeGraph(aux, 0, diviC);
            A= node->instance.size(); AV= nodeA->instance.size();
            BV= nodeB->instance.size();
            CV= nodeC->instance.size();
            ESV = (((AV/A) * nodeA->getEntropy()) +
                   ((BV/A) * nodeB->getEntropy()) +
                   ((CV/A) * nodeC->getEntropy()));
        //    std::cout <<"ENTROPIA: "<< ES << "ENTROPIA DIVIDINDO PELO ATRIBUTO O: " << ESV <<'\n';
            if(gain < (ES - ESV)){
                gain = ES - ESV;
                bestAttribute = 0;
            }
            diviA.clear();
            diviB.clear();
            diviC.clear();
        }
        // dividindo para spectacle
        if(node->attribute[1] == 0){
            for(int i=0; i< node->instance.size(); i++){
                if(node->instance[i][1] == 1){
                    diviA.push_back(node->instance[i]);
                }
                else if(node->instance[i][1] == 2){
                    diviB.push_back(node->instance[i]);
                }
            }
            int aux[4] = {0,0,0,0};
            nodeGraph *nodeA = new nodeGraph(aux, 0, diviA);
            nodeGraph *nodeB = new nodeGraph(aux, 0, diviB);
            A= node->instance.size(); AV= nodeA->instance.size();
            BV= nodeB->instance.size();
            ESV = (((AV/A) * nodeA->getEntropy()) +
                   ((BV/A) * nodeB->getEntropy()));
        //    std::cout <<"ENTROPIA: "<< ES << "ENTROPIA DIVIDINDO PELO ATRIBUTO 1: " << ESV <<'\n';
            if(gain < (ES - ESV)){
                gain = ES - ESV;
                bestAttribute = 1;
            }
            diviA.clear();
            diviB.clear();
            diviC.clear();
        }
        if(node->attribute[2] == 0){
            for(int i=0; i< node->instance.size(); i++){
                if(node->instance[i][2] == 1){
                    diviA.push_back(node->instance[i]);
                }
                else if(node->instance[i][2] == 2){
                    diviB.push_back(node->instance[i]);
                }
            }
            int aux[4] = {0,0,0,0};
            nodeGraph *nodeA = new nodeGraph(aux, 0, diviA);
            nodeGraph *nodeB = new nodeGraph(aux, 0, diviB);
            A= node->instance.size(); AV= nodeA->instance.size();
            BV= nodeB->instance.size();
            ESV = (((AV/A) * nodeA->getEntropy()) +
                   ((BV/A) * nodeB->getEntropy()));
        //           std::cout <<"ENTROPIA: "<< ES << "ENTROPIA DIVIDINDO PELO ATRIBUTO 2: " << ESV <<'\n';
            if(gain < (ES - ESV)){
                gain = ES - ESV;
                bestAttribute = 2;
            }
            diviA.clear();
            diviB.clear();
            diviC.clear();
        }
        if(node->attribute[3] == 0){
            for(int i=0; i< node->instance.size(); i++){
                if(node->instance[i][3] == 1){
                    diviA.push_back(node->instance[i]);
                }
                else if(node->instance[i][3] == 2){
                    diviB.push_back(node->instance[i]);
                }
            }
            int aux[4] = {0,0,0,0};
            nodeGraph *nodeA = new nodeGraph(aux, 0, diviA);
            nodeGraph *nodeB = new nodeGraph(aux, 0, diviB);
            A= node->instance.size(); AV= nodeA->instance.size();
            BV= nodeB->instance.size();
            ESV = (((AV/A) * nodeA->getEntropy()) +
                   ((BV/A) * nodeB->getEntropy()));
        //           std::cout <<"ENTROPIA: "<< ES << "ENTROPIA DIVIDINDO PELO ATRIBUTO 3: " << ESV <<'\n';
            if(gain < (ES - ESV)){
                gain = ES - ESV;
                bestAttribute = 3;
            }
            diviA.clear();
            diviB.clear();
            diviC.clear();
        }
    //    std::cout << "PASSEI NA ESCOLHA DO ATRIBUTO E O MELHOR FOI:" << bestAttribute<< '\n';
    return bestAttribute;
    }
    //tree.push_back()

};

int main(){
    int att[4] = {0,0,0,0};
    vector<vector<int> > input;
    int id;
    int aux;
    vector<int> array;
   for(int i=0; i<24; i++){
       cin >> id;
       cin >> aux; array.push_back(aux);
       cin >> aux; array.push_back(aux);
       cin >> aux; array.push_back(aux);
       cin >> aux; array.push_back(aux);
       cin >> aux; array.push_back(aux);
       input.push_back(array);
       //cout << input[i][0] << ' ';cout << input[i][1] << ' ';
       //cout << input[i][2] << ' '; cout << input[i][3] << ' ';
       //cout << input[i][4] << '\n';
       array.clear();
    }
    graph *id3 = new graph(input);
    id3->creatTree();
    cout << "A SEGUIR TEMOS UM PRINT DA ÁRVORE ID3, PRINT SEGUE A ORDEM DA BUSCA EM LARGURA \n";
    for(int i=0; i< id3->tree.size(); i++){
        cout << "Nó: " << i << " Atributo usado para criar esse nó foi: "<< id3->tree[i]->atualAttribute
             << " Meu Nó contem: " << id3->tree[i]->instance.size() << " instâncias";
             if(id3->tree[i]->isClass == 1){
                cout << " é uma folha do tipo: (1) com taxa de erro: " << id3->tree[i]->taxaErro ;
             }
             else if(id3->tree[i]->isClass == 2){
                cout << " é uma folha do do tipo (2) com taxa de erro: " << id3->tree[i]->taxaErro;
             }
             else if(id3->tree[i]->isClass == 3){
                cout << " é uma folha do do tipo (3) com taxa de erro: " << id3->tree[i]->taxaErro;
             }
             else{
                 cout << " não é considerado uma folha";
             }
             cout << '\n';
    }

}
