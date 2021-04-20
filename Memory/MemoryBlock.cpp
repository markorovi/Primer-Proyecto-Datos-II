//
// Created by marco on 4/19/21.
//

#include "MemoryBlock.h"


MemoryBlock::MemoryBlock(){
    this->First_Resize();
}

void MemoryBlock::First_Resize() {
    this->ToUse.resize(10485760); //10485760 chars = 10mb
}

int MemoryBlock::Capacity() {
    return this->ToUse.size(); //returns the remaining bytes available on the memory
}

void MemoryBlock::Using_Memory(int used) {
    int temp = this->ToUse.capacity();
    std::vector<char>().swap(this->ToUse);
    this->ToUse.resize(temp - used); //Consumes "used" bytes of the memory
}

void MemoryBlock::Freeing_Memory(int to_free) {
    int temp = this->ToUse.capacity();
    std::vector<char>().swap(this->ToUse);
    this->ToUse.resize(temp + to_free); //Frees "to_free" bytes of the memory
}