#include <iostream>
#include <vector>
#include <math.h>
#include <set>
#include <map>

using namespace std;

class iris{
public:
    string classe;
    double sepalLen, sepalWidht, petalLen, petalWidht;
    iris(double sepalLen, double sepalWidht, double petalLen, double petalWidht, string classe){
        this->sepalLen = sepalLen;
        this->sepalWidht = sepalWidht;
        this->petalLen = petalLen;
        this->petalWidht = petalWidht;
        this->classe = classe;

    }
};

double obterDistEuclidiana(iris ind1, iris ind2)
{


	double soma = pow((ind1.sepalLen - ind2.sepalLen), 2) +
				  pow((ind1.sepalWidht - ind2.sepalWidht), 2) +
				  pow((ind1.petalLen - ind2.petalLen), 2) +
				  pow((ind1.petalWidht - ind2.petalWidht), 2);

	return sqrt(soma);
}



string classificarAmostra(vector<iris>& allIris,
						  iris novo_exemplo, int K)
{

	if(K % 2 == 0)
	{
		K--;
		if(K <= 0)
			K = 1;
	}


	int tam_vet = allIris.size();


	set<pair<double, int> > dist_iris;


	for(int i = 0; i < tam_vet; i++)
	{
		double dist = obterDistEuclidiana(allIris[i], novo_exemplo);
		dist_iris.insert(make_pair(dist, i));
	}

    set<pair<double, int> >::iterator it;

	vector<int> cont_classes(3);

	int contK = 0;

	for(it = dist_iris.begin(); it != dist_iris.end(); it++)
	{
		if(contK == K) break;

		string classe = allIris[it->second].classe;

		if(classe == "Iris-setosa")
			cont_classes[0]++;
		else if(classe == "Iris-versicolor")
			cont_classes[1]++;
		else
			cont_classes[2]++;

		contK++;
	}

	string classe_classificacao;

	if(cont_classes[0] >= cont_classes[1] && cont_classes[0] >= cont_classes[2])
		classe_classificacao = "Iris-setosa";
	else if(cont_classes[1] >= cont_classes[0] && cont_classes[1] >= cont_classes[2])
		classe_classificacao = "Iris-versicolor";
	else
		classe_classificacao = "Iris-virginica";

	return classe_classificacao;
}



int main(){

    vector<iris> allIris;

    int k = 3;

    int tam_treinamento = 125;

    string classe;
    double a, b, c, d;
    char g;
    for(int i = 0; i < tam_treinamento; i++)
	{
		cin >> a;
        g = cin.get();
        cin >> b;
        g = cin.get();
        cin >> c;
        g = cin.get();
        cin >> d;
        g = cin.get();
        cin >> classe;
		allIris.push_back(iris(a, b, c, d, classe));
    }

    int acertos = 0;

	int tam_testes = 150 - tam_treinamento;

    for(int i = 0; i < tam_testes; i++)
	{

        cin >> a;
        g = cin.get();
        cin >> b;
        g = cin.get();
        cin >> c;
        g = cin.get();
        cin >> d;
        g = cin.get();
        cin >> classe;
		iris iri(a, b, c, d, classe);

		string classe_obtida = classificarAmostra(allIris, iri, k);

		cout << "Classe esperada: " << classe << "\n";
		cout << "Classe obtida: " << classe_obtida << "\n\n";

		if(classe == classe_obtida)
			acertos++;
	}

	cout << acertos << " acertos de um total de " << tam_testes << " testes.\n";

    return 0;
}
