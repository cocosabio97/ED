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
*  Estudiante 1:
*  Estudiante 2:
*@ </answer> */

/*
* Implementa las operaciones pedidas en el ejercicio al final de
* este fichero, entre las etiquetas.
*/


#include <cassert>
#include <iostream>
#include <fstream>

class ListLinkedSingle {
private:
	struct Node {
		int value;
		Node *next;
	};

public:
	ListLinkedSingle() : head(nullptr) { }
	~ListLinkedSingle() {
		delete_list(head);
	}

	ListLinkedSingle(const ListLinkedSingle &other)
		: head(copy_nodes(other.head)) { }

	void push_front(const int &elem) {
		Node *new_node = new Node{ elem, head };
		head = new_node;
	}

	void push_back(const int &elem);

	void pop_front() {
		assert(head != nullptr);
		Node *old_head = head;
		head = head->next;
		delete old_head;
	}

	void pop_back();

	int size() const;

	bool empty() const {
		return head == nullptr;
	};

	const int & front() const {
		assert(head != nullptr);
		return head->value;
	}

	int & front() {
		assert(head != nullptr);
		return head->value;
	}

	const int & back() const {
		return last_node()->value;
	}

	int & back() {
		return last_node()->value;
	}

	const int & at(int index) const {
		Node *result_node = nth_node(index);
		assert(result_node != nullptr);
		return result_node->value;
	}

	int & at(int index) {
		Node *result_node = nth_node(index);
		assert(result_node != nullptr);
		return result_node->value;
	}

	void display(std::ostream &out) const;
	void display() const {
		display(std::cout);
	}

	void merge(ListLinkedSingle &other);

private:
	Node * head;

	void delete_list(Node *start_node);
	Node *last_node() const;
	Node *nth_node(int n) const;
	Node *copy_nodes(Node *start_node) const;

};

ListLinkedSingle::Node * ListLinkedSingle::copy_nodes(Node *start_node) const {
	if (start_node != nullptr) {
		Node *result = new Node{ start_node->value, copy_nodes(start_node->next) };
		return result;
	}
	else {
		return nullptr;
	}
}


void ListLinkedSingle::delete_list(Node *start_node) {
	if (start_node != nullptr) {
		delete_list(start_node->next);
		delete start_node;
	}
}

void ListLinkedSingle::push_back(const int &elem) {
	Node *new_node = new Node{ elem, nullptr };
	if (head == nullptr) {
		head = new_node;
	}
	else {
		last_node()->next = new_node;
	}
}

void ListLinkedSingle::pop_back() {
	assert(head != nullptr);
	if (head->next == nullptr) {
		delete head;
		head = nullptr;
	}
	else {
		Node *previous = head;
		Node *current = head->next;

		while (current->next != nullptr) {
			previous = current;
			current = current->next;
		}

		delete current;
		previous->next = nullptr;
	}
}

int ListLinkedSingle::size() const {
	int num_nodes = 0;

	Node *current = head;
	while (current != nullptr) {
		num_nodes++;
		current = current->next;
	}

	return num_nodes;
}


ListLinkedSingle::Node * ListLinkedSingle::last_node() const {
	assert(head != nullptr);
	Node *current = head;
	while (current->next != nullptr) {
		current = current->next;
	}
	return current;
}

ListLinkedSingle::Node * ListLinkedSingle::nth_node(int n) const {
	assert(0 <= n);
	int current_index = 0;
	Node *current = head;

	while (current_index < n && current != nullptr) {
		current_index++;
		current = current->next;
	}

	return current;
}

void ListLinkedSingle::display(std::ostream &out) const {
	out << "[";
	if (head != nullptr) {
		out << head->value;
		Node *current = head->next;
		while (current != nullptr) {
			out << ", " << current->value;
			current = current->next;
		}
	}
	out << "]";
}

/* ==============================================================================================
* Implementa aquí el método merge y la función merge_lists
* ==============================================================================================
*
*@ <answer>
*/

using namespace std;
// coste o(n + m) respecto al tamaño de las 2 listas


/*
IGNACIO PALLÁS GOZÁLVEZ
FERNANDO HERMOSO CARA
*/
void ListLinkedSingle::merge(ListLinkedSingle &other) {
	// ...
	Node* aux;
	Node* current = this->head;
	Node* current2 = other.head;

	if (current && current2) {
		if (current->value <= current2->value) {
			current = current->next;
			aux = this->head;
		}
		else {

			this->head = current2;
			current2 = current2->next;
			this->head->next = current;
			aux = this->head;
			other.head = current2;

		}
		while (current2 && current) {
			if (current->value <= current2->value) {
				aux->next = current;
				aux = current;
				current = aux->next;
			}
			else {
				aux->next = current2;
				aux = current2;
				current2 = aux->next;
			}
		}
		if (current2 == nullptr) {
			aux->next = current;
		}
		else if (current == nullptr) {
			aux->next = current2;
		}
		
	}
	else if (current == nullptr && current2 != nullptr) {
		this->head = other.head;
	}
	other.head = nullptr;
}


/*
ListLinkedSingle merge_lists(const ListLinkedSingle &l1, const ListLinkedSingle &l2) {
	// ...
}*/


void tratar_caso() {
	int dato;
	ListLinkedSingle l1;
	ListLinkedSingle l2;
	cin >> dato;
	while (dato != 0) {
		l1.push_back(dato);
		cin >> dato;
	}
	cin >> dato;
	while (dato != 0) {
		l2.push_back(dato);
		cin >> dato;
	}
	l1.merge(l2);
	l1.display();
	cout << endl  ;
}

int main() {
	int num_casos;
/*
#ifndef DOMJUDGE
	std::ifstream in("sample.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif*/

	cin >> num_casos;

	while (num_casos > 0) {
		tratar_caso();
		num_casos--;
	}

/*
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	// Descomentar si se trabaja en Visual Studio
		system("PAUSE");

#endif*/
	return 0;
}



