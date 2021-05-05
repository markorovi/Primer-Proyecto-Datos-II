//
// Created by marco on 4/20/21.
//

#include "Node.h"

using namespace std;

/// Setter de la posicion del nodo
/// \param value int Valor a asignar
void Node::SetPosition(int value){ this->position = value;}

/// Getter de la posision del noto
/// \return int
int Node::GetPosition(){return this->position;}

/// Setter para el address del nodo
/// \param value
void Node::SetAddress(void* value){ this->address = value;}

/// Getter para el address del nodo
/// \return void*
void* Node::GetAddress(){return this->address;}

/// Setter para el type del nodo
/// \param type
void Node::SetType(std::string type){this->type = type;}

/// Getter para el type del nodo
/// \return std::string
string Node::GetType(){return this->type;}

/// Setter para el nombre del nodo
/// \param name
void Node::SetName(std::string name) {this->name = name;}

/// Getter para el nombre del nodo
/// \return std::string
string Node::GetName(){return this->name;}

/// Getter para el siguiente nodo
/// \return Node*
Node* Node::GetNext() {return this->next;}

/// Setter para el siguiente nodo
/// \param node
void Node::SetNext(Node *node) {this->next = node;}

/// Getter para tamano del nodo
/// \return int
int Node::GetSize() {return this->size;}

/// Setter para el tamano del nodo
/// \param node
void Node::SetSize(int size) {this->size = size;}

