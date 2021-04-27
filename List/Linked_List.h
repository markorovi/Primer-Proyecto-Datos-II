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
    void add_node(void* address, std::string type, int position, std::string name);
    int delete_node(std::string name);
    void print_list(Node* head);
    int return_listPostion(Node* head, int value);
    int lenght();
    bool exists(std::string name,  Node *head);
    std::string returnType(std::string name, Node *head);
    void * returnAddress(std::string name, Node *head);
    void add_espace(Node *p);
};

#endif //IDE_LINKED_LIST_H
