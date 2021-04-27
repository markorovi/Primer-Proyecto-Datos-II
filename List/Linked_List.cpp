//
// Created by marco on 4/20/21.
//

#include "Linked_List.h"
#include <iostream>

using namespace std;

Linked_List::Linked_List() {
    head = nullptr;
}

Node* Linked_List::GetHead() {return this->head;}
void Linked_List::SetHead(Node *head) {this->head = head;}

int Linked_List::lenght() {
    int i = 0;
    for (Node* curr = this->GetHead() ; curr; curr = curr->GetNext()){
        i++;
    }
    return i;
}

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

int Linked_List::delete_node(std::string name) {
    int to_return = -1;

    if (this->GetHead() == nullptr) {
        cout << "Not existing list or position our of range given when deleting a node" << "\n";
    } else if (this->GetHead()->GetName() == name) {
        to_return = this->GetHead()->GetPosition();

        Node *tmp = this->GetHead()->GetNext();

        delete this->GetHead();
        this->SetHead(tmp);
    } else {
        Node *tmp = this->GetHead();
        for (int i = 0; i < this->lenght(); i++) {
            if (tmp->GetNext()->GetName() == name) {
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
