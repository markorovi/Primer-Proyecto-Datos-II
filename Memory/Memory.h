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

    /*!
     * @brief Getter para la cabeza del offset
     * @return char*
     */
    char *getHead() const;

    /*!
     * @brief Getter para la lista de reciclaje
     * @return std::vector<int>
     */
    std::vector<int> getToRecicle();

public:

    /*!
     * @brief Getter para la lista en la que se encuentran los espacios de memoria en uso
     * @return Linked_List
     */
    Linked_List getInUse();

    /*!
     * @brief Singleton para la memoria
     * @return Memory*
     */
    static Memory *get_instance();

    /*!
     * @brief Se encarga de reservar un espacio en el offset para la nueva variable
     * @param type El tipo de la variable
     * @param i Lo que la variable almacenara
     * @param name El nombre de la variable
     */
    void Using_Memory(std::string type, std::string i,  std::string name);

    /*!
     * @brief Se encarga de reutilizar una posicion en el offset de memoria a ser posible
     * @param type El tipo de la variable
     * @param i Lo que la variable almacenara
     * @param position Posicion la cual acapara la variabl en el offset
     * @param name l nombre de la variable
     */
    void Reciclying_Memory(std::string type, std::string i, int position, std::string name);

    /*!
     * @brief Se encarga de liberar un espacio en memoria
     * @param name Nombre de la variable a liberar
     */
    void Freeing_Memory(std::string name);

    /*!
     * @brief Se encarga de mostrar la lista de las posiciones que se pueden reciclar
     */
    void Show();

    /*!
     * @brief Se encarga de sobreescribir una variable si esta ya existe
     * @param position Variable a sobreescribir
     * @param type Tipo de la variable
     * @param value Nuevo valor que la direccion almacenara
     */
    void Rewrite(int position, std::string type, std::string value);

    /*!
     * @brief Solicita memoria, lo que puede resultar en una sobreescritura, una nueva direccion o en el reciclaje de una variable que ya no esta en uso
     * @param type Tipo de la variable
     * @param i Valor a almacenar
     * @param name Nombre de la variable
     */
    void Need_Memory(std::string type, std::string i,  std::string name);

    /*!
     * @brief Se encarga de rellenar los espacios de memoria del struct que se esta generando con sus respectivos atributos
     * @param type Tipo de dato a guardar
     * @param i Valor a guardar
     * @param name Nombre con el cual se va a guardar
     */
    void FillingStruct(std::string type, std::string i,  std::string name);

    /*!
     * @brief Funcion que declara cuando se esta empezando a generar un struct
     * @param size Tamano del struct
     * @param name Nombre de la cabeza del struct
     */
    void GeneratingStruct(int size, std::string name);
};


#endif //IDE_MEMORY_H
