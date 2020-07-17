/*
* ---------------------------------------------------
*                ESTRUCTURAS DE DATOS
* ---------------------------------------------------
*/

/*
* MUY IMPORTANTE: Para realizar este ejercicio solo podéis
* modificar el código contenido entre las etiquetas <answer>
* y </answer>. Toda modificación fuera de esas etiquetas está
* prohibida, pues no será corregida.
*
* Tampoco esta permitido modificar las líneas que contienen
* las etiquetas <answer> y </answer>, obviamente :-)
*/

/*@ <answer>
* Comienza poniendo el nonmbre de los/as componentes del grupo:
*
*  Estudiante 1: IGNACIO PALLÁS GOZÁLVEZ
*  Estudiante 2: FERNANDO HERMOSO CARA

*@ </answer> */

/*
* Implementa las operaciones pedidas en el ejercicio al final de
* este fichero, entre las etiquetas.
*/


#include <cassert>
#include <iostream>
#include <fstream>

class ListLinkedDouble {
private:
	struct Node {
		int value;
		Node* next;
		Node* prev;
	};

public:
	ListLinkedDouble() : num_elems(0) {
		head = new Node;
		head->next = head;
		head->prev = head;
	}

	ListLinkedDouble(const ListLinkedDouble& other) : ListLinkedDouble() {
		copy_nodes_from(other);
		num_elems = other.num_elems;
	}

	~ListLinkedDouble() {
		delete_nodes();
	}

	void push_front(const int& elem) {
		Node* new_node = new Node{ elem, head->next, head };
		head->next->prev = new_node;
		head->next = new_node;
		num_elems++;
	}

	void push_back(const int& elem) {
		Node* new_node = new Node{ elem, head, head->prev };
		head->prev->next = new_node;
		head->prev = new_node;
		num_elems++;
	}

	void pop_front() {
		assert(num_elems > 0);
		Node* target = head->next;
		head->next = target->next;
		target->next->prev = head;
		delete target;
		num_elems--;
	}

	void pop_back() {
		assert(num_elems > 0);
		Node* target = head->prev;
		target->prev->next = head;
		head->prev = target->prev;
		delete target;
		num_elems--;
	}

	int size() const {
		return num_elems;
	}

	bool empty() const {
		return num_elems == 0;
	};

	const int& front() const {
		assert(num_elems > 0);
		return head->next->value;
	}

	int& front() {
		assert(num_elems > 0);
		return head->next->value;
	}

	const int& back() const {
		assert(num_elems > 0);
		return head->prev->value;
	}

	int& back() {
		assert(num_elems > 0);
		return head->prev->value;
	}

	const int& operator[](int index) const {
		assert(0 <= index && index < num_elems);
		Node* result_node = nth_node(index);
		return result_node->value;
	}

	int& operator[](int index) {
		assert(0 <= index && index < num_elems);
		Node* result_node = nth_node(index);
		return result_node->value;
	}

	ListLinkedDouble& operator=(const ListLinkedDouble& other) {
		if (this != &other) {
			delete_nodes();
			head = new Node;
			head->next = head->prev = head;
			copy_nodes_from(other);
			num_elems = other.num_elems;
		}
		return *this;
	}

	void display(std::ostream& out) const;

	void display() const {
		display(std::cout);
	}

	void display_reverse(std::ostream& out) const;

	void display_reverse() const {
		display_reverse(std::cout);
	}


	void partition(int pivot);

private:
	Node* head;
	int num_elems;

	Node* nth_node(int n) const;
	void delete_nodes();
	void copy_nodes_from(const ListLinkedDouble& other);

	void detach(Node* node);
	void attach(Node* node, Node* position);
};



ListLinkedDouble::Node* ListLinkedDouble::nth_node(int n) const {
	int current_index = 0;
	Node* current = head->next;

	while (current_index < n && current != head) {
		current_index++;
		current = current->next;
	}

	return current;
}

void ListLinkedDouble::delete_nodes() {
	Node* current = head->next;
	while (current != head) {
		Node* target = current;
		current = current->next;
		delete target;
	}

	delete head;
}

void ListLinkedDouble::copy_nodes_from(const ListLinkedDouble& other) {
	Node* current_other = other.head->next;
	Node* last = head;

	while (current_other != other.head) {
		Node* new_node = new Node{ current_other->value, head, last };
		last->next = new_node;
		last = new_node;
		current_other = current_other->next;
	}
	head->prev = last;
}


void ListLinkedDouble::display(std::ostream& out) const {
	out << "[";
	if (head->next != head) {
		out << head->next->value;
		Node* current = head->next->next;
		while (current != head) {
			out << ", " << current->value;
			current = current->next;
		}
	}
	out << "]";
}


void ListLinkedDouble::display_reverse(std::ostream& out) const {
	out << "[";
	if (head->prev != head) {
		out << head->prev->value;
		Node* current = head->prev->prev;
		while (current != head) {
			out << ", " << current->value;
			current = current->prev;
		}
	}
	out << "]";
}

std::ostream& operator<<(std::ostream& out, const ListLinkedDouble& l) {
	l.display(out);
	return out;
}


/* ==============================================================================================
* Implementa aquí los métodos pedidos
* ==============================================================================================
*
*@ <answer>
*/

using namespace std;
//O(1)
void ListLinkedDouble::detach(Node* node) {
	
	node->prev->next = node->next;
	node->next->prev = node->prev;
}
// O(1)
void ListLinkedDouble::attach(Node* node, Node* position) {
	node->prev = position->prev;
	position->prev->next = node;
	node->next = position;
	position->prev = node;
	
}
// O(num_elems)
void ListLinkedDouble::partition(int pivot) {
	int cont = 0;
	Node* current = head->next;
	Node* aux = current;
	while (cont < num_elems) {
		if (current->value > pivot) {
			detach(current);
			aux = current;
			current = current->next;
			attach(aux, head);
		}
		else {

			current = current->next;
			aux = current;

		}
		cont++;
	}
}

void tratar_caso() {
	ListLinkedDouble l1;
	int lista;
	int pivote;
	cin >> lista;

	while (lista != 0) {
		l1.push_back(lista);
		cin >> lista;
	}
	cin >> pivote;
	l1.partition(pivote);
	l1.display();
	cout << "\n";
	l1.display_reverse();
	cout << "\n";
}

int main() {
	int num_casos;
#ifndef DOMJUDGE
	std::ifstream in("sample.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	cin >> num_casos;

	while (num_casos > 0) {
		tratar_caso();
		num_casos--;
	}


#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	// Comentar si no se trabaja en Visual Studio
	system("PAUSE");
#endif

	return 0;
}

/*@ </answer> */

