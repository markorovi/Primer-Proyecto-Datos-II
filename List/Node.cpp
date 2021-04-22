//
// Created by marco on 4/20/21.
//

#include "Node.h"

using namespace std;

void Node::SetPosition(int value){ this->position = value;}
int Node::GetPosition(){return this->position;}
void Node::SetAddress(void* value){ this->address = value;}
void* Node::GetAddress(){return this->address;}
void Node::SetType(std::string type){this->type = type;}
string Node::GetType(){return this->type;}
void Node::SetName(std::string name) {this->name = name;}
string Node::GetName(){return this->name;}
Node* Node::GetNext() {return this->next;}
void Node::SetNext(Node *node) {this->next = node;}

