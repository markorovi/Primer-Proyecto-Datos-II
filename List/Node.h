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
    std::string name;
    int size;
public:

    /*!
     * @briefSetter de la posicion del nodo
     * @param value Valor a asignar
     */
    void SetPosition(int value);

    /*!
     * @brief Getter de la posision del noto
     * @return int
     */
    int GetPosition();

    /*!
     * @brief Setter para el tamano del nodo
     * @param size node
     */
    void SetSize(int size);

    /*!
     * @brief Getter para tamano del nodo
     * @return int
     */
    int GetSize();

    /*!
     * @brief Setter para el address del nodo
     * @param value Valor a settear
     */
    void SetAddress(void* value);

    /*!
     * @brief Getter para la direccion del nodo
     * @return void*
     */
    void* GetAddress();

    /*!
     * @brief Setter para el tipo del nodo
     * @param type Tipo a settear
     */
    void SetType(std::string type);

    /*!
     * @brief Getter para el tipo del nodo
     * @return std::string
     */
    std::string GetType();

    /*!
     * @brief Setter para el nombre del nodo
     * @param name Nombre a settear
     */
    void SetName(std::string name);

    /*!
     * @brief Getter para el nombre del nodo
     * @return std::string
     */
    std::string GetName();

    /*!
     * @brief Setter para el siguiente nodo
     * @param node Nodo a settear
     */
    void SetNext(Node* node);

    /*!
     * @brief Getter para el siguiente nodo
     * @return Node*
     */
    Node* GetNext();
};



#endif //IDE_NODE_H
