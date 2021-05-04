//
// Created by marco on 4/20/21.
//
#include <iostream>
#include "Memory.h"

Memory* Memory::instance = nullptr;

/// Singleton para la memoria
/// \return Memory*
Memory * Memory::get_instance() {
    if (instance == nullptr){
        instance = new Memory;
    }
    return instance;
}

///Se encarga de mostrar la lista de las posiciones que se pueden reciclar
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

/// Se encarga de reservar un espacio en el offset para la nueva variable
/// \param type std::string El tipo de la variable
/// \param i std::string Lo que la variable almacenara
/// \param name std::string El nombre de la variable
void Memory::Using_Memory(std::string type, std::string i,  std::string name) {

    if (i == ""){
        if (type == "int"){
            *reinterpret_cast<int *>(&this->head[this->counter]);
            this->InUse.add_node(&this->head[this->counter], "int", this->counter, name);
            this->counter+= 4;
        } else if (type=="char"){
            *reinterpret_cast<char *>(&this->head[this->counter]);
            this->InUse.add_node(&this->head[this->counter], "char", this->counter, name);
            this->counter+= 1;
        } else if (type=="long"){
            *reinterpret_cast<long *>(&this->head[this->counter]);
            this->InUse.add_node(&this->head[this->counter], "long", this->counter, name);
            this->counter+= 8;
        } else if (type=="double"){
            *reinterpret_cast<double *>(&this->head[this->counter]);
            this->InUse.add_node(&this->head[this->counter], "double", this->counter, name);
            this->counter+= 8;
        } else if (type=="float"){
            *reinterpret_cast<float *>(&this->head[this->counter]);
            this->InUse.add_node(&this->head[this->counter], "float", this->counter, name);
            this->counter+= 4;
        }
    }else {
        if (type == "int"){
            *reinterpret_cast<int *>(&this->head[this->counter]) = stoi(i);
            this->InUse.add_node(&this->head[this->counter], "int", this->counter, name);
            this->counter+= 4;
        } else if (type=="char"){
            *reinterpret_cast<char *>(&this->head[this->counter]) = i[0];
            this->InUse.add_node(&this->head[this->counter], "char", this->counter, name);
            this->counter+= 1;
        } else if (type=="long"){
            *reinterpret_cast<long *>(&this->head[this->counter]) = stol(i);
            this->InUse.add_node(&this->head[this->counter], "long", this->counter, name);
            this->counter+= 8;
        } else if (type=="double"){
            *reinterpret_cast<double *>(&this->head[this->counter]) = stod(i);
            this->InUse.add_node(&this->head[this->counter], "double", this->counter, name);
            this->counter+= 8;
        } else if (type=="float"){
            *reinterpret_cast<float *>(&this->head[this->counter]) = stof(i);
            this->InUse.add_node(&this->head[this->counter], "float", this->counter, name);
            this->counter+= 4;
        }
    }

}

/// Se encarga de reutilizar una posicion en el offset de memoria a ser posible
/// \param type std::string El tipo de la variable
/// \param i std::string Lo que la variable almacenara
/// \param position int Posicion la cual acapara la variabl en el offset
/// \param name std::string El nombre de la variable
void Memory::Reciclying_Memory(std::string type, std::string i, int position, std::string name)  {

    if (i == ""){
        if (type == "int"){
            *reinterpret_cast<int *>(&this->head[position]);
            this->InUse.add_node(&this->head[position], "int", position, name);
        } else if (type=="char"){
            *reinterpret_cast<char *>(&this->head[position]);
            this->InUse.add_node(&this->head[position], "char", position, name);
        } else if (type=="long"){
            *reinterpret_cast<long *>(&this->head[position]);
            this->InUse.add_node(&this->head[position], "long", position, name);
        } else if (type=="double"){
            *reinterpret_cast<double *>(&this->head[position]);
            this->InUse.add_node(&this->head[position], "double", position, name);
        } else if (type=="float"){
            *reinterpret_cast<float *>(&this->head[position]);
            this->InUse.add_node(&this->head[position], "float", position, name);
        }
    } else{
        if (type == "int"){
            *reinterpret_cast<int *>(&this->head[position]) = stoi(i);
            this->InUse.add_node(&this->head[position], "int", position, name);
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
    }

    //this->counter++;
}

/// Se encarga de sobreescribir una variable si esta ya existe
/// \param address void* Variable a sobreescribir
/// \param type std::string Tipo de la variable
/// \param value std::string Nuevo valor que la direccion almacenara
void Memory::Rewrite(void * address, std::string type, std::string value) {
    std::cout<<address<< ", "<< type << ", " << value<<std::endl;
    if (type == "int"){
        *reinterpret_cast<int *>(&address) = stoi(value);
    } else if (type=="char"){
        *reinterpret_cast<char *>(&address) = value[0];
    } else if (type=="long"){
        *reinterpret_cast<long *>(&address) = stol(value);
    } else if (type=="double"){
        *reinterpret_cast<double *>(&address) = stod(value);
    } else if (type=="float"){
        *reinterpret_cast<float *>(&address) = stof(value);
    }
}

/// Se encarga de liberar un espacio en memoria
/// \param name std::string Nombre de la variable a liberar
void Memory::Freeing_Memory(std::string name) {
    std::cout<<"Se liberó memoria:"<<name<<std::endl;
   int position = this->InUse.delete_node(name);
   if (position != -1){
       this->to_recicle.push_back(position);
   } else{
       std::cout<<"aqui pasa algo";
   }
}

/// Solicita memoria, lo que puede resultar en una sobreescritura, una nueva direccion o en el reciclaje de una variable que ya no esta en uso
/// \param type std::string Tipo de la variable
/// \param i std::string Valor a almacenar
/// \param name std::string Nombre de la variable
void Memory::Need_Memory(std::string type, std::string i, std::string name) {
    if (this->to_recicle.empty()){
        if (this->InUse.exists(name, Memory::InUse.GetHead())){
            this->Rewrite(this->InUse.returnAddress(name, Memory::InUse.GetHead()), this->InUse.returnType(name, Memory::InUse.GetHead()), i);

        }else if (!this->InUse.exists(name, Memory::InUse.GetHead())){
            this->Using_Memory(type, i, name);
            std::cout<<"aqui 1"<<std::endl;
        }
    } else{
        bool flag = false;
        for (std::vector<int>::iterator it = this->to_recicle.begin(); it != this->to_recicle.end(); ++it){
            int closest = this->InUse.return_listPostion(this->InUse.GetHead(), *it);
            std::cout << closest<< "--"<<std::endl;
            if (closest != NULL){
                std::cout<<type;
                if (type == "int" and closest >= 4){
                    this->Reciclying_Memory(type, i, closest-4, name);
                    this->to_recicle.erase(it);
                    flag = true;
                    break;
                } else if (type=="char" and closest >= 1){
                    this->Reciclying_Memory(type, i, closest-1, name);
                    this->to_recicle.erase(it);
                    flag = true;
                    break;
                } else if (type=="long" and closest >= 8){
                    this->Reciclying_Memory(type, i, closest-8, name);
                    this->to_recicle.erase(it);
                    flag = true;
                    break;
                } else if (type=="double" and closest >= 8){
                    this->Reciclying_Memory(type, i, closest-8, name);
                    this->to_recicle.erase(it);
                    flag = true;
                    break;
                } else if (type=="float" and closest >= 4){
                    this->Reciclying_Memory(type, i, closest-4, name);
                    this->to_recicle.erase(it);
                    flag = true;
                    break;
                }
            }
        }
        if (!flag){
            this->Using_Memory(type, i, name);

        }
    std::cout<<"\n\n"<< std::endl;

    }
}

/// Getter para la lista en la que se encuentran los espacios de memoria en uso
/// \return Linked_List
 Linked_List Memory::getInUse()  {
    return InUse;
}
/// Getter para la cabeza del offset
/// \return char*
char *Memory::getHead() const {
    return head;
}
