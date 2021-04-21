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
public:
    double *head = (double *) malloc(1310720);
    Linked_List InUse;
    static Memory *get_instance();
    void Using_Memory(std::string type, std::string i);
    void Reciclying_Memory(std::string type, std::string i, int position);
    void Freeing_Memory(void* to_free);
    void Show();
    void Need_Memory(std::string type, std::string i);

};


#endif //IDE_MEMORY_H
