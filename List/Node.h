//
// Created by marco on 4/20/21.
//

#ifndef IDE_NODE_H
#define IDE_NODE_H
#include<iostream>
#include<stdlib.h>

class Node {
private:
    void* address;
    std::string type;
    Node* next;
    int position;
public:
    void SetPosition(int value);
    int GetPosition();
    void SetAddress(void* value);
    void* GetAddress();
    void SetType(std::string type);
    std::string GetType();
    void SetNext(Node* node);
    Node* GetNext();
};



#endif //IDE_NODE_H
