/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Manuel Montenegro Montes
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
 * Comienza poniendo el nombre de los/as componentes del grupo:
 *
 * Estudiante 1: Ignacio Pallás Gozálvez
 * Estudiante 2: Fernando Hermoso Cara
 */


#include <iostream>
#include <fstream>
#include <unordered_map>
#include <list>
#include <string>

using namespace std;

class Supermercado {
public:
    // O(1) ya que como mucho hay 16 cajas
    Supermercado(int num_cajas) {
        numCajas = num_cajas;
        for (int i = 0; i < num_cajas; ++i) {
            list<string> aux;
            cajas.insert({ i, aux });
        }
    }
    // O(1) 
    void nuevo_cliente(string cod_cliente, int num_cola) {
        if (num_cola > (numCajas - 1)) { // cte
            throw domain_error("Cola inexistente");
        }
        else {
            if (cliente_caja.count(cod_cliente) == 1) {//cte
                throw domain_error("Cliente duplicado");
            }
            cajas[num_cola].push_back(cod_cliente);//cte
            cliente_caja.insert({ cod_cliente, num_cola });//cte
        }
    }
    // o(n) siendo n el nuemro de personas en la cola
    void cambiar_cola(string cod_cliente, int num_cola) {
        if (num_cola > (numCajas - 1)) { // cte
            throw domain_error("Cola inexistente");
        }
        if (cliente_caja.count(cod_cliente) == 0) {//cte
            throw domain_error("Cliente inexistente");
        }
        int pos = cliente_caja[cod_cliente];// O(n)
        auto it = cajas[pos].begin();
        bool ok = false;
        while (it != cajas[pos].cend() && !ok) {// O(n) siendo n el numero de personas en la cola
            if (*it == cod_cliente) {
                ok = true;
            }
            else
                ++it;
        }
        if (pos != num_cola) {
            cajas[pos].erase(it);//cte
            cajas[num_cola].push_back(cod_cliente);//cte
            cliente_caja[cod_cliente] = num_cola;// O(n)
        }
    }
    // O(n) siendo n el numero de personas que hay en todas las colas
    int consultar_cliente(string cod_cliente) {
        if (cliente_caja.count(cod_cliente) == 0) {
            throw domain_error("Cliente inexistente");
        }
        return cliente_caja[cod_cliente];
    }
    // O(1)
    int cuantos_en_cola(int num_cola) {
        if (num_cola > numCajas - 1) {
            throw domain_error("Cola inexistente");
        }
        return cajas[num_cola].size();
    }
    //O(1) ya que como mucho tendremos 16 cajas
    list<string> clientes_en_cola(int num_cola) {
        if (num_cola > numCajas - 1) {
            throw domain_error("Cola inexistente");
        }
        return cajas[num_cola];
    }

private:
    int numCajas;
    unordered_map<int, list<string>> cajas;
    unordered_map<string, int> cliente_caja;

};


bool tratar_caso() {
    int dato1;
    string dato;
    cin >> dato1;
    if (!cin) {
        return false;
    }
    else {
        Supermercado super(dato1);
        cin >> dato;
        while (dato != "FIN") {
            if (dato == "nuevo_cliente") {
                string c;
                cin >> c;
                int caja;
                cin >> caja;
                try {
                    super.nuevo_cliente(c, caja);
                }
                catch (exception& e) {
                    cout << "ERROR: " << e.what() << endl;
                }

            }
            else if (dato == "cuantos_en_cola") {
                int d;
                cin >> d;
                try {
                    int a = super.cuantos_en_cola(d);
                    cout << "En la cola " << d << " hay " << a << " clientes\n";
                }
                catch (exception& e) {
                    cout << "ERROR: " << e.what() << endl;
                }
            }
            else if (dato == "clientes_en_cola") {
                int d;
                cin >> d;
                try {
                    list<string> lis = super.clientes_en_cola(d);
                    cout << "En la cola " << d << " estan: ";
                    for (auto it = lis.rbegin(); it != lis.rend(); ++it) {
                        cout << *it << " ";
                    }
                    cout << "\n";
                }
                catch (exception& e) {
                    cout << "ERROR: " << e.what() << endl;
                }
            }
            else if (dato == "cambiar_cola") {
                string a;
                int b;
                cin >> a;
                cin >> b;
                try {
                    super.cambiar_cola(a, b);
                }
                catch (exception& e) {
                    cout << "ERROR: " << e.what() << endl;
                }
            }
            else if (dato == "consultar_cliente") {
                string a;
                cin >> a;
                try {
                    int b = super.consultar_cliente(a);
                    cout << "El cliente " << a << " esta en la cola " << b << endl;
                }
                catch (exception& e) {
                    cout << "ERROR: " << e.what() << endl;
                }
            }
            cin >> dato;
        }
        cout << "---" << endl;
    }
    return true;
}



int main() {
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (tratar_caso()) {}

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar si se trabaja en Windows
     system("PAUSE");
#endif
    return 0;
}