#ifndef _LIST_H
#define _LIST_H
#include "Node.h"
#include <string>
#include <iostream>

template <class T>
class List
{
	/*
	Die Klasse List dient zur Verwaltung von Knoten (Node). Mit Hilfe der Klasse List
	kann ein Stapel oder Warteschlange realisiert werden.
	*/
private:
	struct form { std::string start = "<< "; std::string zwischen = ", "; std::string ende = " >>\n"; } _form;
	Node<T> * head, *tail;			// Zeiger auf Kopf- und End-Element
	int _size;						// Länge der Kette
	bool temp;						// normalerweise false; ist true, wenn es sich um eine temoräre Liste handelt
									// die innerhalb der überladenen Operatoren angelegt wird
public:
	List();
	~List();
	void InsertFront(T key);		// Einfügen eines Knotens am Anfang
	void InsertBack(T key);		// Einfügen eines Knotesn am Ende
	bool getFront(T & key);		// Entnehmen eines Knoten am Anfang
	bool getBack(T & key);		// Entnehmen eines Knoten am Ende
	bool del(T key);				// löschen eines Knotens [key]
	bool search(T key);			// Suchen eines Knoten
	bool swap(T key1, T key2);	// Knoten in der Liste vertauschen
	int size(void);					// Größe der Lise (Anzahl der Knoten)
	bool test(void);				// Überprüfen der Zeigerstruktur der Liste

	void format(const std::string & start, const std::string & zwischen, const std::string & ende);	// Mit der format-Methode kann die Ausgabe gesteuert werden: operator <<
	List<T> & operator = (const List<T> & _List);						// Zuweisungsoperator definieren
	List<T> & operator = (const List<T> * _List);						// Zuweisungsoperator definieren
	List<T> & operator + (const List<T> & List_Append);					// Listen zusammenfÃ¼hren zu einer Liste
	List<T> & operator + (const List<T> * List_Append);					// Listen zusammenfÃ¼hren zu einer Liste
	template <typename Tf>
	friend std::ostream & operator << (std::ostream & stream, const List<Tf> & Liste);		// Ausgabeoperator Ã¼berladen
	template <typename Tf>
	friend std::ostream & operator << (std::ostream & stream, const List<Tf> * Liste);		// Ausgabeoperator Ã¼berladen

};

template <class T>
List<T>::List()
{
	head = new Node<T>;
	tail = new Node<T>;
	_size = 0;
	temp = false;
	head->next = tail;
	tail->prev = head;
}
template <class T>
List<T>::~List()
{
	/*
	( ... löschen Sie alle noch vorhandenen Knoten Node dieser Instanz
	Denken Sie auch den die Knoten head und tail.)
	*/

	while (head->next != tail) {
		Node<T> *temp = head;
		head = head->next;
		delete temp;
	}
	//head ist das letzte Element
	_size = 0;
	delete head;
	delete tail;
}
template <class T>
void List<T>::InsertFront(T key)
{

	//	( ... Erweitern Sie die Methode so, dass ein neür Knoten Node vorne
	//		(hinter dem Knoten head) in die Liste eingefügt wird. )
	Node<T> *newNode = new Node<T>(key, head->next, head);
	if (head->next == tail) {
		//head next ist tail
		head->next = newNode;
		newNode->prev = head;
		newNode->next = tail;
		tail->prev = newNode;
	}
	/*	else if(head->next->next == tail){
	//head next next ist tail
	newNode->next = head->next;
	head->next->prev = newNode;
	head->next = newNode;

	}*/
	else {
		newNode->next = head->next;
		head->next->prev = newNode;
		head->next = newNode;
		newNode->prev = head;
	}
	_size++;
}
template <class T>
void List<T>::InsertBack(T key)
{
	//	( ... Erweitern Sie die Methode so, dass ein neür Knoten Node hinten
	//		(vor dem Knoten tail) in die Liste eingefügt wird. )
	Node<T> *newNode = new Node<T>(key, tail, tail->prev);
	tail->prev->next = newNode;
	tail->prev = newNode;
	_size++;
}
template <class T>
bool List<T>::getFront(T & key)
{
	//	( ... Erweitern Sie die Methode so, dass der erste Knoten der Liste
	//		(hinter head) zurückgegeben und dieser Knoten dann gelöscht wird.
	//		Im Erfolgsfall geben Sie true zurück, sonst false. )
	//	if (_size == 0) return false;
	if (_size == 0) {
		//std::cout << "BLABLA222222" << key;
		return false;
	}
	else {
		//Key zuruckgeben
		key = head->next->key;
		std::cout << "BLABLA" << key;
		//Knoten loeschen
		del(key);
		return true;
	}
}
template <class T>
bool List<T>::getBack(T & key)
{
	//	(... Erweitern Sie die Methode so, dass der letzte Knoten der Liste
	//		(vor tail) zurückgegeben und dieser Knoten dann gelöscht wird.
	//		Im Erfolgsfall geben Sie true zurück, sonst false. )
	if (_size == 0 || tail->prev == head) {
		//std::cout << "BLABLA222222" << key;
		return false;
	}
	else {
		//Key geben
		key = tail->prev->key;
		//		std::cout << "TEST..." << tail->prev->key<<std::endl;
		//Knoten loeschen
		if (del(key)) {
			//std::cout << "FEHLER beim loeschen...";
			return true;
		}

	}
}
template <class T>
bool List<T>::del(T key)
{
	//	(... Die Methode del sucht den Knoten mit dem Wert Key und löscht diesen
	//		im Erfolgsfall aus der Liste.
	//		Im Erfolgsfall geben Sie true zurück, sonst false. )
	if (_size == 0) return false;
	Node<T> *point = head->next;
	while (point != tail) {
		//Solange next nicht null oder tail gehe durch und suche

		if (point->key == key) {
			//loesche Knoten point
			point->prev->next = point->next;
			point->next->prev = point->prev;
			delete point;
			_size--;
			return true;
		}
		point = point->next;
	}
	//nicht gefunden
	return false;
}
template <class T>
bool List<T>::search(T key)
{
	//	(... Die Methode search sucht den Knoten mit dem Wert key
	//		Im Erfolgsfall geben Sie true zurück, sonst false. )
	Node<T> *point = head;
	while (point->next != NULL && point->next != tail) {
		//Solange next nicht null oder tail gehe durch und suche
		if (point->key == key) {
			return true;
		}
		point = point->next;
	}
	//nicht gefunden
	return false;
}
template <class T>
bool List<T>::swap(T key1, T key2)
{
	//	(... Die Methode swap sucht den Knoten mit dem Wert key1,
	//		dann den Knoten mit dem Wert key2. Diese Knoten werden dann
	//		getauscht, indem die Zeiger der Knoten entsprechend geändert
	//		werden. )

	//Teste ob die keys vorhanden sind
	if (search(key1) && search(key2)) {

		Node<T> *point1 = head;
		Node<T> *point2 = head;
		//Suche keys
		while (point1->next != NULL && point1->next != tail) {
			//Solange next nicht null oder tail gehe durch und suche
			if (point1->key == key1) {
				break;
			}
			point1 = point1->next;
		}
		while (point2->next != NULL && point2->next != tail) {
			//Solange next nicht null oder tail gehe durch und suche
			if (point2->key == key2) {
				break;
			}
			point2 = point2->next;
		}
		//Tausche Knoten
		Node<T> *temp = point1->prev;
		//[][][][P][X][][]
		if (point1->next != nullptr) point1->next->prev = point2;
		if (point2->next != nullptr) point2->next->prev = point1;
		//[][][X][P][][][]
		if (point1->prev != nullptr) point1->prev->next = point2;
		if (point2->prev != nullptr) point2->prev->next = point1;
		//[][][X][P][][][]
		//[][][Y][P][][][]
		if (point1->prev != nullptr && point2->prev != nullptr) {
			point1->prev = point2->prev;
			point2->prev = temp;
		}
		else if (point1->prev == nullptr && point2->prev != nullptr) point1->prev = point2->prev;
		else if (point1->prev != nullptr && point2->prev == nullptr) point2->prev = point1->prev;
		//[][][][P][X][][]
		//[][][][P][Y][][]
		temp = point1->next;
		if (point1->next != nullptr && point2->next != nullptr) {
			point1->next = point2->next;
			point2->next = temp;
		}
		else if (point1->next == nullptr && point2->next != nullptr) point1->next = point2->next;
		else if (point1->next != nullptr && point2->next == nullptr) point2->next = point1->next;



		//Alles fertig
		return true;
	}
	//nicht gefunden
	else return false;
}
template <class T>
int List<T>::size(void)
{
	//	(... Die Methode git den Wert von size (Anzahl der Knoten in der Liste) zurück. )
	Node<T> *temp_size = head;
	int count = 0;
	while (temp_size->next != NULL && temp_size->next != tail) {
		count++;
		temp_size = temp_size->next;
	}
	return count;
}
template <class T>
bool List<T>::test(void)
{
	//	(... Die Methode überprüft die Pointer der Liste. Gestartet wird mit head. Es werden alle 
	//		Knoten bis zum tail durchlaufen von dort aus dann die prev-Zeiger bis zum head.
	//		Bei Erfolg wird true zurück gegeben. )
	Node<T> *node_test = head;
	int count = 0;
	int list_size = size();

	while (node_test->next != tail && count < list_size) {
		node_test = node_test->next;
		count++;
	}
	if (count > list_size) return false;
	else count = 0;
	while (node_test->prev != head && count < list_size) {
		node_test = node_test->prev;
		count++;
	}
	if (count > list_size) return false;
	else return true;
}

//--------------Aus Praktikumsdatei
template <class T>
void List<T>::format(const std::string & start, const std::string & zwischen, const std::string & ende)
{
	_form.start = start;
	_form.zwischen = zwischen;
	_form.ende = ende;
}

template <class T>
List<T> & List<T>::operator = (const List<T> & _List)
{
	// in dem Objekt _List sind die Knoten enthalten, die Kopiert werden sollen.
	// Kopiert wird in das Objekt "this"
	if (this == &_List) return *this;	//  !! keine Aktion notwendig
	Node<T> * tmp_node;
	if (_size)
	{
		Node<T> * tmp_del;
		tmp_node = head->next;
		while (tmp_node != tail)		// Alle eventuell vorhandenen Knoten in this lÃ¶schen
		{
			tmp_del = tmp_node;
			tmp_node = tmp_node->next;
			delete tmp_del;
		}
		_size = 0;
		head->next = tail;
		tail->prev = head;
	}
	tmp_node = _List.head->next;
	while (tmp_node != _List.tail)
	{
		InsertBack(tmp_node->key);
		tmp_node = tmp_node->next;
	}
	if (_List.temp) delete & _List;		// ist die Ãœbergebene Liste eine temporÃ¤re Liste? -> aus Operator +
	return *this;
}

template <class T>
List<T> & List<T>::operator = (const List<T> * _List)
{
	// in dem Objekt _List sind die Knoten enthalten, die Kopiert werden sollen.
	// Kopiert wird in das Objekt "this"
	if (this == _List) return *this;	//  !! keine Aktion notwendig
	Node<T> * tmp_node;
	if (_size)
	{
		Node<T> * tmp_del;
		tmp_node = head->next;
		while (tmp_node != tail)		// Alle eventuell vorhandenen Knoten in this lÃ¶schen
		{
			tmp_del = tmp_node;
			tmp_node = tmp_node->next;
			delete tmp_del;
		}
		_size = 0;
		head->next = tail;
		tail->prev = head;
	}
	tmp_node = _List->head->next;
	while (tmp_node != _List->tail)
	{
		InsertBack(tmp_node->key);
		tmp_node = tmp_node->next;
	}
	if (_List->temp) delete _List;		// ist die Ãœbergebene Liste eine temporÃ¤re Liste? -> aus Operator +
	return *this;
}

template <class T>
List<T> & List<T>::operator + (List<T> const & List_Append)
{
	Node<T> * tmp_node;
	List * tmp;
	if (temp) {								// this ist eine temporÃ¤re Liste und kann verÃ¤ndert werden
		tmp = this;
	}
	else {
		tmp = new List<T>;					// this ist keine temporÃ¤re Liste -> Kopie erzeugen
		tmp->temp = true;					// Merker setzten, dass es sich um eine temporÃ¤re Liste handelt
		tmp_node = head->next;
		while (tmp_node != tail) {
			tmp->InsertBack(tmp_node->key);
			tmp_node = tmp_node->next;
		}
	}
	if (List_Append._size) {				// anhÃ¤ngen der Ã¼bergebenen Liste an tmp
		tmp_node = List_Append.head->next;
		while (tmp_node != List_Append.tail) {
			tmp->InsertBack(tmp_node->key);
			tmp_node = tmp_node->next;
		}
	}
	if (List_Append.temp) delete & List_Append;		// wurde eine temporÃ¤re Liste Ã¼bergeben, dann wird diese gelÃ¶scht							// 
	return *tmp;
}

template <class T>
List<T> & List<T>::operator + (List<T> const * List_Append)
{
	Node<T> * tmp_node;
	List * tmp;
	if (temp) {								// this ist eine temporÃ¤re Liste und kann verÃ¤ndert werden
		tmp = this;
	}
	else {
		tmp = new List<T>;					// this ist keine temporÃ¤re Liste -> Kopie erzeugen
		tmp->temp = true;					// Merker setzten, dass es sich um eine temporÃ¤re Liste handelt
		tmp_node = head->next;
		while (tmp_node != tail) {
			tmp->InsertBack(tmp_node->key);
			tmp_node = tmp_node->next;
		}
	}
	if (List_Append->_size) {				// anhÃ¤ngen der Ã¼bergebenen Liste an tmp
		tmp_node = List_Append->head->next;
		while (tmp_node != List_Append->tail) {
			tmp->InsertBack(tmp_node->key);
			tmp_node = tmp_node->next;
		}
	}
	if (List_Append->temp) delete List_Append;		// wurde eine temporÃ¤re Liste Ã¼bergeben, dann wird diese gelÃ¶scht							// 
	return *tmp;
}

template <class Tf>
std::ostream & operator << (std::ostream  & stream, const List<Tf> & Liste)
{
	stream << Liste._form.start;
	for (Node<Tf> * tmp = Liste.head->next; tmp != Liste.tail; tmp = tmp->next)
		stream << tmp->key << (tmp->next == Liste.tail ? Liste._form.ende : Liste._form.zwischen);
	if (Liste.temp) delete & Liste;			// wurde eine temporÃ¤re Liste Ã¼bergeben, dann wird diese gelÃ¶scht
	return stream;
}

template <class Tf>
std::ostream & operator << (std::ostream  & stream, const List<Tf> * Liste)
{
	stream << Liste->_form.start;
	for (Node<Tf> * tmp = Liste->head->next; tmp != Liste->tail; tmp = tmp->next)
		stream << tmp->key << (tmp->next == Liste->tail ? Liste->_form.ende : Liste->_form.zwischen);
	if (Liste->temp) delete Liste;			// wurde eine temporÃ¤re Liste Ã¼bergeben, dann wird diese gelÃ¶scht
	return stream;
}
#endif