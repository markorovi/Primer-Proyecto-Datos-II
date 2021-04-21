//
// Created by marco on 4/20/21.
//

#ifndef IDE_LINKED_LIST_H
#define IDE_LINKED_LIST_H


#include "Node.h"

class Linked_List {
private:
    Node *head;
public:
    void SetHead(Node *head);
    Node* GetHead();
    Linked_List();
    void add_node(void* address, std::string type, int position);
    int delete_node(void* address);
    void print_list(Node* head);
    int lenght();
    void add_espace(Node *p);
};

#endif //IDE_LINKED_LIST_H
