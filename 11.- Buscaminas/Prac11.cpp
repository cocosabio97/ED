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
 * Estudiante 1: Fernando Hermoso Cara
 * Estudiante 2: Ignacio Pallás Gozálvez
 */


#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <unordered_map>


using namespace std;

using jugador = std::string;

class Buscaminas {
public:
    Buscaminas() {
        min_x = 0; 
        min_y = 0;
        max_x = 0;
        max_y = 0;
        numMinas = 0;
    }
    // O(log n) siendo n el nº de minas
    void anyadir_mina(int x, int y) {
        auto it = tablero.find(x);

        // no hay x
        if (it == tablero.end()) {
            if (!tablero.empty()) {

                if (x < min_x) {
                    min_x = x;
                }
                if (y < min_y) {
                    min_y = y;
                }
                if (x > max_x) {
                    max_x = x;
                }
                if (y > max_y) {
                    max_y = y;
                }             
            }
            else {
                min_x = x;
                min_y = y;
                max_x = x;
                max_y = y;
            }
            
                tablero[x].insert(y);
                tablero.insert({ x, tablero[x] });
                numMinas++;
   
        }
        else {// hay x
            // miramos si en esa posicion x hay una mina en la y
            if (tablero[x].count(y) == 0) {
                //si no hay esa y en la pos x la añadimos
                tablero[x].insert(y);
                tablero.insert({ x, tablero[x] });
                numMinas++;

                if (y < min_y) {
                    min_y = y;
                }
                if (y > max_y) {
                    max_y = y;
                }
            }
        }

    }
   
    //O(log n) siendo n el nº de jugadores
    void anyadir_jugador(jugador jug) {
        if (lista_jugadores.count(jug) == 1)
            throw invalid_argument("Jugador existente");
        else
            lista_jugadores.insert({ jug, 0 });
    }

    // O(log n) siendo n el nº de minas
    int explorar(jugador jug, int x, int y) {

        if (lista_jugadores.count(jug) == 0)
            throw invalid_argument("Jugador no existente");
        else {
            auto it = tablero.find(x);
            //hay mina en x
            if (it != tablero.end()) {
                //hay mina en y
                if (it->second.count(y) == 1) {
                    lista_jugadores.erase(jug);
                    return -1;
                }
                else {
                    return colindantes(x, y);
                }
            }
            else {
                // hay mina
                return colindantes(x, y);
            }
        }
    }

    // O(log n) siendo n el nº de minas
    bool bandera(jugador jug, int x, int y) {
        if (lista_jugadores.count(jug) == 0) {
            throw invalid_argument("Jugador no existente");
        }
        else {
            auto it = tablero.find(x);
            // no hay mina
            if (it == tablero.end()) {
                lista_jugadores[jug] -= 5;
                return false;
            }
            else {
                // hay mina
                lista_jugadores[jug] += 1;
                return true;
            }         
        }
    }
    // O(log n) siendo n el nº de jugadores
    int puntuacion(jugador jug) {
        if (lista_jugadores.count(jug) == 0)
            throw invalid_argument("Jugador no existente.");
        else
            return lista_jugadores[jug];
    }
    // O(1) 
    int num_minas() {
        return numMinas;
    }
    // O(1) 
    void bordes_tablero(int& minx, int& miny, int& maxx, int& maxy) {
        if (!tablero.empty()) {
            minx = min_x;
            miny = min_y;
            maxx = max_x;
            maxy = max_y;
        }
        else
            throw domain_error("Tablero vacio");
    }




private:
    unordered_map<jugador, int> lista_jugadores;

    map<int, set<int>> tablero;

    int min_x;
    int min_y ;
    int max_x;
    int max_y;
    int numMinas;

    // O(log n) siendo n el numero de minas
    int colindantes(int x, int y) {
        int cont = 0;

       
        
        // x = x
        auto it = tablero.find(x);
        if (it != tablero.end()) {
            if (it->second.count(y + 1) == 1) {
                cont++;
            }
            if (it->second.count(y - 1) == 1) {
                cont++;
            }
        }

      

        // x = x-1  
        auto it2 = tablero.find(x-1);
        if (it2 != tablero.end()) {

            if (it2->second.count(y) == 1) {
                cont++;
            }
            if ( it2->second.count(y + 1) == 1) {
                cont++;
            }
            if ( it2->second.count(y - 1) == 1) {
                cont++;
            }
        }
        // x = x+1
        auto it3 = tablero.find(x +1);
        if (it3 != tablero.end()) {

            if (it3->second.count(y) == 1) {
                cont++;
            }
            if (it3->second.count(y + 1) == 1) {
                cont++;
            }
            if (it3->second.count(y - 1) == 1) {
                cont++;
            }
        }

            return cont;
    }

       
};


bool tratar_caso() {
    // Implementar. Devolver false si al leer
    // se llega al fin del fichero, o true
    // en caso contrario.
    string dato;
    cin >> dato;

    if (!cin ) {
        return false;
    }
    else {
        Buscaminas buscaminas;
       
        while (dato != "FIN") {
            
            if (dato == "mina") {
                int x;
                int y;
                cin >> x;
                cin >> y;
                buscaminas.anyadir_mina(x, y);
                cout << buscaminas.num_minas()<<endl;
            }
            else if (dato == "jugador") {
                string nombre;
                cin >> nombre;
                try {
                    buscaminas.anyadir_jugador(nombre);
                }
                catch (exception& e) {
                    cout << e.what() << endl;
                }
               
            }
            else if (dato == "explorar") {
                string nombre;
                int x;
                int y;
                cin >> nombre;
                cin >> x;
                cin >> y;
                try {
                    int result = buscaminas.explorar(nombre, x, y);
                    if (result == -1) {
                        cout << "Has perdido" << endl;
                    }
                    else {
                        cout << result << endl;
                    }
                }
                catch (exception& e) {
                    cout << e.what() << endl;
                }
                
            }
            else if (dato == "bandera") {
                string nombre;
                int x;
                int y;
                cin >> nombre;
                cin >> x;
                cin >> y;
                try {
                    if (buscaminas.bandera(nombre, x, y)) {
                        cout << "Si" << " ";
                    }
                    else {
                        cout << "NO" << " ";
                    }
                    cout << buscaminas.puntuacion(nombre) << endl;
                }
                catch (exception& e) {
                    cout << e.what() << endl;
                }
               
            }
            else if (dato == "bordes") {
                try {
                    int min_x, min_y, max_x, max_y;
                    buscaminas.bordes_tablero(min_x, min_y, max_x, max_y);
                    cout << min_x << " " << min_y << " " << max_x << " " << max_y << endl;
                }
                catch (exception& e) {
                    cout << e.what() << endl;
                }
                
            }

            cin >> dato;
        }
        cout << "---" << endl;
        return true;
    }


 
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