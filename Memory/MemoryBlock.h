//
// Created by marco on 4/19/21.
//
#include <iostream>
#include <vector>

#ifndef IDE_FIRST_ALLOCATION_H
#define IDE_FIRST_ALLOCATION_H



class MemoryBlock {
private:

public:
    std::vector<char> ToUse;
    MemoryBlock();
    void First_Resize();
    void Using_Memory(int to_use);
    void Freeing_Memory(int to_free);
    int Capacity();
};


#endif //IDE_FIRST_ALLOCATION_H
