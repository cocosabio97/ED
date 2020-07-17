/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

 /*
  * MUY IMPORTANTE: Para realizar este ejercicio solo pod�is
  * modificar el c�digo contenido entre las etiquetas <answer>
  * y </answer>. Toda modificaci�n fuera de esas etiquetas est�
  * prohibida, pues no ser� corregida.
  *
  * Tampoco esta permitido modificar las l�neas que contienen
  * las etiquetas <answer> y </answer>, obviamente :-)
  */


  /*@ <answer> */

  /*
   * Comienza poniendo el nonmbre de los/as componentes del grupo:
   *
   * Estudiante 1: Fernando Hermoso Cara
   * Estudiante 2: Ignacio Pall�s Goz�lvez
   */

   /*@ </answer> */



#include <iostream>
#include <fstream>
#include <memory>
#include <cassert>


/*
  Implementaci�n de la clase BinTree para representar �rboles binarios.

  Para realizar este ejercicio no es necesario modificar la clase.
 */

template<class T>
class BinTree {
public:

    BinTree() : root_node(nullptr) { }

    BinTree(const T& elem) : root_node(std::make_shared<TreeNode>(nullptr, elem, nullptr)) { }

    BinTree(const BinTree& left, const T& elem, const BinTree& right)
        :root_node(std::make_shared<TreeNode>(left.root_node, elem, right.root_node)) { }


    bool empty() const {
        return root_node == nullptr;
    }

    const T& root() const {
        assert(root_node != nullptr);
        return root_node->elem;
    }

    BinTree left() const {
        assert(root_node != nullptr);
        BinTree result;
        result.root_node = root_node->left;
        return result;
    }

    BinTree right() const {
        assert(root_node != nullptr);
        BinTree result;
result.root_node = root_node->right;
return result;
    }

    void display(std::ostream& out) const {
        display_node(root_node, out);
    }

private:
    struct TreeNode;
    using NodePointer = std::shared_ptr<TreeNode>;

    struct TreeNode {
        TreeNode(const NodePointer& left, const T& elem, const NodePointer& right) : elem(elem), left(left), right(right) { }

        T elem;
        NodePointer left, right;
    };

    NodePointer root_node;

    static void display_node(const NodePointer& root, std::ostream& out) {
        if (root == nullptr) {
            out << ".";
        }
        else {
            out << "(";
            display_node(root->left, out);
            out << " " << root->elem << " ";
            display_node(root->right, out);
            out << ")";
        }
    }

};

/*
 * Operador << para mostrar un �rbol por pantalla. No es necesario mostrar �rboles
 * por pantalla en la pr�ctica, pero os lo dejo por si quer�is depurar.
 */
template<typename T>
std::ostream& operator<<(std::ostream& out, const BinTree<T>& tree) {
    tree.display(out);
    return out;
}


/*
 * Funci�n para leer un �rbol binario de la entrada. El formato es el siguiente:
 *
 *  �rbol vac�o: .
 *  �rbol no vac�o: (i x r)  donde i es la representaci�n del hijo izquierdo
 *                                 x es la ra�z
 *                                 r es la representaci�n del hijo derecho
 */
template<typename T>
BinTree<T> read_tree(std::istream& in) {
    char c;
    in >> c;
    if (c == '.') {
        return BinTree<T>();
    }
    else {
        assert(c == '(');
        BinTree<T> left = read_tree<T>(in);
        T elem;
        in >> elem;
        BinTree<T> right = read_tree<T>(in);
        in >> c;
        assert(c == ')');
        BinTree<T> result(left, elem, right);
        return result;
    }
}



/*@ <answer> */

/* Completa a continuaci�n la funci�n pedida. Puedes definir las funciones
   auxiliares que necesites, �pero siempre antes de la etiqueta </answer>! */

using namespace std;

// Pista: Este problema admite una soluci�n recursiva, como todos los
// que hemos visto sobre �rboles. No obstante, ten cuidado con el coste.
// 
// Es recomendable tener una funci�n auxiliar recursiva que devuelva el
// n�mero m�ximo de hitos visitables del �rbol junto con la informaci�n
// adicional que necesites para calcular este n�mero m�ximo.
//
// La funci�n max_hitos_visitados deber�a solamente realizar la llamada
// inicial a esta funci�n recursiva.


/*
Apartado 2: Si el �rbol es equilibrado el coste de la funci�n es de O(n), siendo n el n�mero de nodos del �rbol
Apartado 3: Si el �rbol degenerado el coste de la funci�n es de O(n^2), siendo n el n�meor de nodos del �rbol
*/

void max_hitos_visitados_aux(const BinTree<int>& montanya, int &altura, int &maximo) {
    if (montanya.empty()) {
        altura = 0;
        return;
    }
    else {
        int contIzq = 0;
        int contDer = 0;
        max_hitos_visitados_aux(montanya.left(), contIzq, maximo);
        max_hitos_visitados_aux(montanya.right(), contDer, maximo);

        if (contDer + contIzq + 1 > maximo) {
            maximo = contDer + contIzq + 1;
        }
        if (contIzq > contDer)
            altura = contIzq + 1;
        else
            altura = contDer + 1;

    }
}

int max_hitos_visitados(const BinTree<int>& montanya) {
    int max = 0;
    int altura = 0;
    max_hitos_visitados_aux(montanya, altura, max);
    return max;

}




/*@ </answer> */


bool tratar_caso() {
    BinTree<int> montanya = read_tree<int>(cin);
    if (montanya.empty()) return false;

    cout << max_hitos_visitados(montanya) << "\n";

    return true;
}



int main() {
/*#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif*/

    while (tratar_caso()) {}

/*#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar si se trabaja en Windows
    // system("PAUSE");
#endif*/
    return 0;
}