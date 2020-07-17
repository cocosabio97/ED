/*
IGNACIO PALLÁS GOZÁLVEZ
FERNANDO HERMOSO CARA
*/

#include <iostream>
#include <cmath>
using namespace std;

const int GRADO_MAX = 1000;

class Polinomio
{
public:
	Polinomio();
	long evaluar(int valor);
	void anyadir_monomio(int coef, int exp);
private:
	struct Monomio {
		int coeficiente;
		int exponente;
	};
	Monomio monomios[GRADO_MAX];
	int num_monomios;
};

Polinomio::Polinomio() //O(GRADO_MAX)
{
	for (int i = 0; i < GRADO_MAX; ++i) {
		this->monomios[i].coeficiente = 0;
		this->monomios[i].exponente = 0;
	}
	this->num_monomios = 0;
}

void Polinomio::anyadir_monomio(int coef, int exp) { //O(3n)donde n es el tamaño del array
	bool encontrado = false;
	int i = 0;
	//si meto uno que ya tengo 
	while (i < this->num_monomios && !encontrado) {
		if (this->monomios[i].exponente == exp) {
			this->monomios[i].coeficiente += coef;
			encontrado = true;
		}
		else {
			++i;
		}
	}
	//si meto uno nuevo
	if (!encontrado) {
		//busco donde puedo meterlo
		int j = 0;
		bool mayor = false;
		while (j < this->num_monomios && !mayor) {
			if (this->monomios[j].exponente > exp) {
				mayor = true;
			}
			else {
				++j;
			}
		}
		// insertamos al final si no hay exponente mayor en el array
		if (!mayor) {
			this->num_monomios++;
			this->monomios[j].coeficiente = coef;
			this->monomios[j].exponente = exp;
		}
		else {// desplazamos e insertamos 
			this->num_monomios++;
			for (int k = this->num_monomios; k > j; --k) {
				this->monomios[k] = this->monomios[k - 1];
			}
			this->monomios[j].coeficiente = coef;
			this->monomios[j].exponente = exp;
		}
		
		
	}
}

long Polinomio::evaluar(int valor) { //O(n^2)donde n es el tamaño del array

	long resultado = 0;
	for (int i = 0; i < this->num_monomios; ++i) {
		resultado += pow(valor,this->monomios[i].exponente)*this->monomios[i].coeficiente;
	}
	return resultado;
}

bool casoPrueba() {
	int n = 0;
	int v = 0;
	cin >> n >> v;
	if (n == 0 && v == 0) {
		return false;
	}
	else {
		Polinomio poli;
		int base = 0;
		int exp = 0;
		for (int i = 0; i < n; ++i) {
			cin >> base >> exp;
			poli.anyadir_monomio(base, exp);
		}

		cout << poli.evaluar(v) << endl;
		return true;
	}
}

int main() {
	while (casoPrueba()) {

	}


	return 0;
}