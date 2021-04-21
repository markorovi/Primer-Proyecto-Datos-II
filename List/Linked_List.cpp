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
            cout << *(int*)head->GetAddress() <<  "("  << head->GetAddress()  << ")" << "[" << head->GetPosition() << "]" <<"->";
        } else if (head->GetType()=="char"){
            cout << *(char*)head->GetAddress() <<  "("  << head->GetAddress()  << ")"<< "[" << head->GetPosition() << "]"  <<"->";
        } else if (head->GetType()=="long"){
            cout << *(long*)head->GetAddress() <<  "("  << head->GetAddress()  << ")"<< "[" << head->GetPosition() << "]"  <<"->";
        } else if (head->GetType()=="double"){
            cout << *(double*)head->GetAddress() <<  "("  << head->GetAddress()  << ")"<< "[" << head->GetPosition() << "]"  <<"->";
        } else if (head->GetType()=="float"){
            cout << *(float*)head->GetAddress() <<  "("  << head->GetAddress()  << ")"<< "[" << head->GetPosition() << "]"  <<"->";
        }
    }
    cout << "\n\n";
}

void Linked_List::add_node(void* address, string type, int position) {
    Node* tmp = new Node;
    tmp->SetAddress(address);
    tmp->SetType(type);
    tmp->SetPosition(position);
    tmp->SetNext(nullptr);

    if(head == nullptr){
        this->SetHead(tmp);
    }
    else{
        tmp->SetNext(this->GetHead());
        this->SetHead(tmp);
    }
}

int Linked_List::delete_node(void* address) {
    int to_return = -1;

    if (this->GetHead() == nullptr) {
        cout << "Not existing list or position our of range given when deleting a node" << "\n";
    } else if (reinterpret_cast<int *>(this->GetHead()->GetAddress()) == reinterpret_cast<int *>(address)) {
        to_return = this->GetHead()->GetPosition();

        Node *tmp = this->GetHead()->GetNext();

        delete this->GetHead();
        this->SetHead(tmp);
    } else {
        Node *tmp = this->GetHead();
        for (int i = 0; i < this->lenght(); i++) {

            if (reinterpret_cast<int *>(tmp->GetAddress()) == reinterpret_cast<int *>(address)) {
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
