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

    /*!
     * @brief Se encarga de settear la cabeza de la lista enlazada.
     * @param head El nodo que se deasea settear a cabeza.
     */
    void SetHead(Node *head);

    /*!
     * @brief Se encarga de obtener la cabeza de la lista enlazada.
     * @return Node*
     */
    Node* GetHead();

    /*!
     * @brief Inicia el valor de la cabeza de la lista como nulo.
     */
    Linked_List();

    /*!
     * @brief Se encarga de agregar un nodo a una lista
     * @param address Atributo address a agregar
     * @param type Atributo type a agregar
     * @param position Atributo position a agregar
     * @param name Atributo name a agregar
     */
    void add_node(void* address, std::string type, int position, std::string name);

    /*!
     * @brief Se encarga de eliminar un nodo de la lista en base al nombre de la variable que almacena
     * @param position Variable a buscar
     * @return int
     */
    int delete_node(int position);

    /*!
     * @brief Se encarga de printear en consola la totalidad de la lista enlazada con cada uno de los parametros de los nodos
     * @param head Es la cabeza de la lista que se desea printear
     */
    void print_list(Node* head);

    /*!
     * @brief Se encarga de retornar la posicion mas cercana a otra en una lista dada por el nodo que recibe
     * @param head Nodo cabeza a recorrer
     * @param value Posicion a comparar
     * @return
     */
    int return_listPostion(Node* head, int value);

    /*!
     * @brief Se encarga de obtener la longitud de la lista enlazada.
     * @return int
     */
    int lenght();

    /*!
     * @brief Se encarga de verificar si una variable se encuentra almacenada en una lista enlazada
     * @param name Variable a buscar
     * @param head Cabeza de la lista a recorrer
     * @return
     */
    bool exists(std::string name,  Node *head);

    /*!
     * @brief
     * @param name
     * @param head
     * @return
     */
    std::string returnType(std::string name, Node *head);

    /*!
     * @brief Se encarga de retornar el tipo de una variable almacenada en la lista enlazada
     * @param name Variable a buscar
     * @param head Cabeza de la lista que se desea recorrer
     * @return std::string
     */
    void * returnAddress(std::string name, Node *head);

    /*!
     * @brief Se encarga de retornar la posicion en la que se encuentra almacenado el nodo con respecto al offset
     * @param name Variable a buscar
     * @param head Cabeza de la lista a recorrer
     * @return
     */
    int returnPostion(std::string name, Node *head);

    /*!
     * @brief Se encarga de retornar el valor que contiene el nodo que se busca
     * @param name Nodo a buscar
     * @param head Cabeza de la lista a recorrer
     * @return std::string
     */
    std::string returnValue(std::string name, Node *head);

};

#endif //IDE_LINKED_LIST_H
