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
#include<set>
#include<unordered_map>
#include<map>
//#include <algorithm>
//#include <vector>
//#include<set>
using namespace std;

void partidaBingo(unordered_map<int, set<string>> diccionario, map<string, int> &participantesCarton) {
    bool hayGanador = false;


    while (!hayGanador) {
        int bola;
        cin >> bola;

        // si la bola esta en el diccionario => hay que tachar a los jugadores asiociados a esa bola
        if (diccionario.count(bola) == 1) {

            for (auto it = diccionario[bola].begin(); it != diccionario[bola].end(); it++) {
                participantesCarton[*it] -= 1;
                if (participantesCarton[*it] == 0)
                    hayGanador = true;
            }
        }
    }
    return;
}
  



bool tratar_caso() {
    // Implementar. Devolver false si es el
    // caso de prueba que determina el fin de entrada,
    // o true en caso contrario.
    int numParticipantes;
    map<string, int> participantesCarton;

    unordered_map<int, set<string>> diccionario;


    cin >> numParticipantes;

    if (numParticipantes == 0)
        return false;
    else {

        for (int i = 0; i < numParticipantes; i++) {
            string participante;
            set<string> conjuntoNombres;

            cin >> participante;

            int numero;
            int cont = 0;
            cin >> numero;

            while (numero != 0) {
               
                //clave ya esta en diccionario
                if (diccionario.count(numero) == 1) {
                    diccionario.at(numero).insert(participante);
                }
                else {
                    conjuntoNombres.insert(participante);
                    diccionario.insert({ numero, conjuntoNombres });
                }
               cin >> numero;
               cont++;

            }
            participantesCarton.insert({ participante, cont });
        }

        partidaBingo(diccionario,participantesCarton);

        for (auto it = participantesCarton.cbegin(); it != participantesCarton.cend(); it++) {
            if (it->second == 0) {
                cout << it->first << " ";
            }
        }
        cout << endl;
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
