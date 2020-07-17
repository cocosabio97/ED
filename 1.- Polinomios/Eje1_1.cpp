/*
IGNACIO PALLÁS GOZÁLVEZ
FERNANDO HERMOSO CARA
*/

#include <iostream>
#include <cmath>
using namespace std;

const int GRADO_MAX = 5000;

class Polinomio
{
public:
	Polinomio();
	long evaluar(int valor);
	void anyadir_monomio(int coef, int exp);
private:
	int coeficientes[GRADO_MAX];
};

Polinomio::Polinomio() //O(GRADO_MAX)
{
	for (int i = 0; i < GRADO_MAX; ++i) {
		this->coeficientes[i] = 0;
	}
}

void Polinomio::anyadir_monomio(int coef, int exp) { //O(1)
	this->coeficientes[exp] += coef;
}

long Polinomio::evaluar(int valor) { //O(GRADO_MAX)
	long resultado = this->coeficientes[0];
	long potencia = 1;
	for (int i = 1; i < GRADO_MAX;++i) {
		potencia = potencia * valor;
		resultado += potencia * this->coeficientes[i];
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
	while (casoPrueba()) {}


	return 0;
}