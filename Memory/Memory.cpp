//
// Created by marco on 4/20/21.
//

#include "Memory.h"

Memory* Memory::instance = nullptr;

Memory * Memory::get_instance() {
    if (instance == nullptr){
        instance = new Memory;
    }
    return instance;
}

void Memory::Show() {
    this->InUse.print_list(this->InUse.GetHead());
    std::cout << "Positions to recicle: ";
    if (this->to_recicle.size() != 0){
        for (int i = 0; i < this->to_recicle.size(); i++) {
            std::cout << this->to_recicle.at(i) << ' ';
        }
    }
    std::cout<<"\n\n";
}

void Memory::Using_Memory(std::string type, std::string i) {

    if (type == "int"){
        *reinterpret_cast<int *>(&this->head[this->counter]) = stoi(i);
        this->InUse.add_node(&this->head[this->counter], "int", this->counter);
    } else if (type=="char"){
        *reinterpret_cast<char *>(&this->head[this->counter]) = i[0];
        this->InUse.add_node(&this->head[this->counter], "char", this->counter);
    } else if (type=="long"){
        *reinterpret_cast<long *>(&this->head[this->counter]) = stol(i);
        this->InUse.add_node(&this->head[this->counter], "long", this->counter);
    } else if (type=="double"){
        *reinterpret_cast<double *>(&this->head[this->counter]) = stod(i);
        this->InUse.add_node(&this->head[this->counter], "double", this->counter);
    } else if (type=="float"){
        *reinterpret_cast<float *>(&this->head[this->counter]) = stof(i);
        this->InUse.add_node(&this->head[this->counter], "float", this->counter);
    }
    this->counter++;
}

void Memory::Reciclying_Memory(std::string type, std::string i, int position)  {

    if (type == "int"){
        *reinterpret_cast<int *>(&this->head[position]) = stoi(i);
        this->InUse.add_node(&this->head[this->counter], "int", position);
    } else if (type=="char"){
        *reinterpret_cast<char *>(&this->head[position]) = i[0];
        this->InUse.add_node(&this->head[position], "char", position);
    } else if (type=="long"){
        *reinterpret_cast<long *>(&this->head[position]) = stol(i);
        this->InUse.add_node(&this->head[position], "long", position);
    } else if (type=="double"){
        *reinterpret_cast<double *>(&this->head[position]) = stod(i);
        this->InUse.add_node(&this->head[position], "double", position);
    } else if (type=="float"){
        *reinterpret_cast<float *>(&this->head[position]) = stof(i);
        this->InUse.add_node(&this->head[position], "float", position);
    }
    this->counter++;
}

void Memory::Freeing_Memory(void * to_free) {
   int position = this->InUse.delete_node(to_free);
   if (position != -1){
       this->to_recicle.push_back(position);
   }
}

void Memory::Need_Memory(std::string type, std::string i) {
    if (this->to_recicle.empty()){
        this->Using_Memory(type, i);
    } else{
        this->Reciclying_Memory(type, i, this->to_recicle.back());
        this->to_recicle.pop_back();
    }
}