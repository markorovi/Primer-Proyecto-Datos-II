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

void Memory::Using_Memory(std::string type, std::string i,  std::string name) {

    if (type == "int"){
        *reinterpret_cast<int *>(&this->head[this->counter]) = stoi(i);
        this->InUse.add_node(&this->head[this->counter], "int", this->counter, name);
    } else if (type=="char"){
        *reinterpret_cast<char *>(&this->head[this->counter]) = i[0];
        this->InUse.add_node(&this->head[this->counter], "char", this->counter, name);
    } else if (type=="long"){
        *reinterpret_cast<long *>(&this->head[this->counter]) = stol(i);
        this->InUse.add_node(&this->head[this->counter], "long", this->counter, name);
    } else if (type=="double"){
        *reinterpret_cast<double *>(&this->head[this->counter]) = stod(i);
        this->InUse.add_node(&this->head[this->counter], "double", this->counter, name);
    } else if (type=="float"){
        *reinterpret_cast<float *>(&this->head[this->counter]) = stof(i);
        this->InUse.add_node(&this->head[this->counter], "float", this->counter, name);
    }
    this->counter++;
}

void Memory::Reciclying_Memory(std::string type, std::string i, int position, std::string name)  {

    if (type == "int"){
        *reinterpret_cast<int *>(&this->head[position]) = stoi(i);
        this->InUse.add_node(&this->head[this->counter], "int", position, name);
    } else if (type=="char"){
        *reinterpret_cast<char *>(&this->head[position]) = i[0];
        this->InUse.add_node(&this->head[position], "char", position, name);
    } else if (type=="long"){
        *reinterpret_cast<long *>(&this->head[position]) = stol(i);
        this->InUse.add_node(&this->head[position], "long", position, name);
    } else if (type=="double"){
        *reinterpret_cast<double *>(&this->head[position]) = stod(i);
        this->InUse.add_node(&this->head[position], "double", position, name);
    } else if (type=="float"){
        *reinterpret_cast<float *>(&this->head[position]) = stof(i);
        this->InUse.add_node(&this->head[position], "float", position, name);
    }
    this->counter++;
}

void Memory::Freeing_Memory(std::string name) {
   int position = this->InUse.delete_node(name);
   if (position != -1){
       this->to_recicle.push_back(position);
   } else{
       std::cout<<"aqui pasa algo";
   }
}

void Memory::Need_Memory(std::string type, std::string i, std::string name) {
    if (this->to_recicle.empty()){
        this->Using_Memory(type, i, name);
    } else{
        this->Reciclying_Memory(type, i, this->to_recicle.back(), name);
        this->to_recicle.pop_back();
    }
}