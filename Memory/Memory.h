//
// Created by marco on 4/20/21.
//

#ifndef IDE_MEMORY_H
#define IDE_MEMORY_H
#include <iostream>
#include <vector>
#include "../List/Linked_List.h"

class Memory {
private:

    static Memory* instance;
    int counter = 0;
    std::vector<int> to_recicle;
    Linked_List InUse;
    char *head = (char *) malloc(10485760);
public:
    char *getHead() const;
    std::vector<int> getToRecicle();

public:
    Linked_List getInUse();
    static Memory *get_instance();
    void Using_Memory(std::string type, std::string i,  std::string name);
    void Reciclying_Memory(std::string type, std::string i, int position, std::string name);
    void Freeing_Memory(std::string name);
    void Show();
    void Rewrite(void * address, std::string type, std::string value);
    void Need_Memory(std::string type, std::string i,  std::string name);
    void FillingStruct(std::string type, std::string i,  std::string name);
    void GeneratingStruct(int size, std::string name);
};


#endif //IDE_MEMORY_H
