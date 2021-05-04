//
// Created by marco on 4/20/21.
//

#include "Linked_List.h"
#include <iostream>

using namespace std;

///Inicia el valor de la cabeza de la lista como nulo.
Linked_List::Linked_List() {
    head = nullptr;
}

/// Se encarga de obtener la cabeza de la lista enlazada.
/// \return Node*
Node* Linked_List::GetHead() {return this->head;}

/// Se encarga de settear la cabeza de la lista enlazada.
/// \param head Node* El nodo que se deasea settear a cabeza.
void Linked_List::SetHead(Node *head) {this->head = head;}

/// Se encarga de obtener la longitud de la lista enlazada.
/// \return int
int Linked_List::lenght() {
    int i = 0;
    for (Node* curr = this->GetHead() ; curr; curr = curr->GetNext()){
        i++;
    }
    return i;
}

/// Se encarga de printear en consola la totalidad de la lista enlazada con cada uno de los parametros de los nodos
/// \param head Node* Es la cabeza de la lista que se desea printear
void Linked_List::print_list(Node *head) {
    cout << "Data in memory: ";
    for ( ; head; head = head->GetNext()){
        if (head->GetType() == "int"){
            cout << head->GetName() <<":" <<*(int*)head->GetAddress() <<  "("  << head->GetAddress()  << ")" << "[" << head->GetPosition() << "]" <<"->";
        } else if (head->GetType()=="char"){
            cout << head->GetName() <<":" <<*(char*)head->GetAddress() <<  "("  << head->GetAddress()  << ")"<< "[" << head->GetPosition() << "]"  <<"->";
        } else if (head->GetType()=="long"){
            cout << head->GetName() <<":" <<*(long*)head->GetAddress() <<  "("  << head->GetAddress()  << ")"<< "[" << head->GetPosition() << "]"  <<"->";
        } else if (head->GetType()=="double"){
            cout << head->GetName() <<":" <<*(double*)head->GetAddress() <<  "("  << head->GetAddress()  << ")"<< "[" << head->GetPosition() << "]"  <<"->";
        } else if (head->GetType()=="float"){
            cout << head->GetName() <<":" <<*(float*)head->GetAddress() <<  "("  << head->GetAddress()  << ")"<< "[" << head->GetPosition() << "]"  <<"->";
        }
    }
    cout << "\n\n";
}

/// Se encarga de verificar si una variable se encuentra almacenada en una lista enlazada
/// \param name std::string Variable a buscar
/// \param head Node* Cabeza de la lista a recorrer
/// \return bool
bool Linked_List::exists(std::string name, Node *head) {
    bool flag = false;
    if (this->lenght() > 0){
        for ( ; head; head = head->GetNext()){
            if (head->GetName() == name){
                flag = true;
            }
        }
    }
    return flag;
}

/// Se encarga de retornar la direccion de memoria almacenada en un nodo al que se accede por su nombre
/// \param name std::string Variable a buscar
/// \param head Node* Cabeza de la lista a recorrer
/// \return void*
void * Linked_List::returnAddress(std::string name, Node *head) {
    if (this->lenght() > 0){
        for ( ; head; head = head->GetNext()){
            if (head->GetName() == name){
                return head->GetAddress();
            }
        }
    }
}


int Linked_List::returnPostion(std::string name, Node *head) {
    if (this->lenght() > 0){
        for ( ; head; head = head->GetNext()){
            if (head->GetName() == name){
                return head->GetPosition();
            }
        }
    }
}

/// Se encarga de retornar el tipo de una variable almacenada en la lista enlazada
/// \param name std::string Variable a buscar
/// \param head Node* Cabeza de la lista que se desea recorrer
/// \return std::string
std::string Linked_List::returnType(std::string name, Node *head) {
    if (this->lenght() > 0){
        for ( ; head; head = head->GetNext()){
            if (head->GetName() == name){
                return head->GetType();
            }
        }
    }
}

/// Se encarga de retornar la posicion mas cercana a otra en una lista dada por el nodo que recibe
/// \param head Node* Nodo cabeza a recorrer
/// \param value int Posicion a comparar
/// \return int
int Linked_List::return_listPostion(Node *head, int value) {
    int closest = 104857600;
    if (this->lenght() > 0){
        if (this->lenght() == 1 and head->GetPosition() - value > 0) {
            closest = head->GetPosition();
        } else {
            for ( ; head; head = head->GetNext()){
                if (head->GetPosition() - value > 0 and head->GetPosition() - value < closest){
                    closest = head->GetPosition();
                }
            }
        }
    }

    return closest;
}

/// Se encarga de agregar un nodo a una lista
/// \param address void* Atributo address a agregar
/// \param type std::string Atributo type a agregar
/// \param position int Atributo position a agregar
/// \param name std::string Atributo name a agregar
void Linked_List::add_node(void* address, string type, int position, std::string name) {
    Node* tmp = new Node;
    tmp->SetAddress(address);
    tmp->SetType(type);
    tmp->SetPosition(position);
    tmp->SetName(name);
    tmp->SetNext(nullptr);

    if(head == nullptr){
        this->SetHead(tmp);
    }
    else{
        tmp->SetNext(this->GetHead());
        this->SetHead(tmp);
    }
}

/// Se encarga de eliminar un nodo de la lista en base al nombre de la variable que almacena
/// \param name std::string Variable a buscar
/// \return int
int Linked_List::delete_node(int position) {
    int to_return = -1;

    if (this->GetHead() == nullptr) {
        cout << "Not existing list or position our of range given when deleting a node" << "\n";
    } else if (this->GetHead()->GetPosition() == position) {
        to_return = this->GetHead()->GetPosition();

        Node *tmp = this->GetHead()->GetNext();

        delete this->GetHead();
        this->SetHead(tmp);
    } else {
        Node *tmp = this->GetHead();
        for (int i = 0; i < this->lenght(); i++) {
            if (tmp->GetNext()->GetPosition() == position) {
                to_return = tmp->GetNext()->GetPosition();
                Node *to_connect = tmp->GetNext()->GetNext();
                tmp->GetNext()->SetNext(nullptr);
                delete tmp->GetNext();
                tmp->SetNext(to_connect);
                break;
            } else {
                tmp = tmp->GetNext();
            }
        }
    }
    return to_return;
}
