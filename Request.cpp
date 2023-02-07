//
// Created by manue on 30/10/2022.
//

#include <iostream>
#include "Request.h"

using namespace std;


/*!Construtor sem parâmetros. Constrói um pedido associado a um estudante vazio, de uma turma vazia para uma turma vazia e de tipo 0 (tipo por defeito).
 * Complexidade: O(1)
 */
Request::Request() {
    type = 0;
}

/*!Construtor com parâmetros. Constrói um pedido associado a um estudante student_, de uma turma origin_ para uma turma destination_ e de tipo type_.
 * Complexidade: O(1)
 * @param student_ estudante
 * @param origin_ turma de origem
 * @param destination_ turma de destino
 * @param type_ tipo do pedido
 */
Request::Request(const Student &student_, const UcClass &origin_, const UcClass &destination_, unsigned type_) {
    student = student_;
    origin = origin_;
    destination = destination_;
    type = type_;
}

/*!Retorna o estudante associado ao pedido.
 * Complexidade: O(1)
 * @return estudante associado ao pedido
 */
Student Request::getStudent() const {
    return student;
}

/*!Retorna a turma de origem do pedido.
 * Complexidade: O(1)
 * @return turma de origem do pedido
 */
UcClass Request::getOrigin() const {
    return origin;
}

/*!Retorna a turma de destino do pedido.
 * Complexidade: O(1)
 * @return turma de destino do pedido
 */
UcClass Request::getDestination() const {
    return destination;
}

/*!Retorna o tipo do pedido.
 * Complexidade: O(1)
 * @return tipo do pedido
 */
unsigned Request::getType() const {
    return type;
}

/*!Define o estudante associado ao pedido como student_.
 * Complexidade: O(1)
 * @param student_ novo estudante associado ao pedido
 */
void Request::setStudent(const Student &student_) {
    student = student_;
}

/*!Define a turma de origem do pedido como origin_.
 * Complexidade: O(1)
 * @param origin_ nova turma de origem do pedido
 */
void Request::setOrigin(const UcClass &origin_) {
    origin = origin_;
}

/*!Define a turma de destino do pedido como destination_.
 * Complexidade: O(1)
 * @param destination_ nova turma de destino do pedido
 */
void Request::setDestination(const UcClass &destination_) {
    destination = destination_;
}

/*!Define o tipo do pedido como type_.
 * Complexidade: O(1)
 * @param type_ novo tipo do pedido
 */
void Request::setType(unsigned type_) {
    type = type_;
}

/*!Imprime o ID do estudante associado ao pedido e uma descrição do pedido.
 * Complexidade: O(1)
 */
void Request::print() const {
    student.printID();
    switch (type) {
        case 1:
            cout << "Remover de ";
            origin.print();
            break;
        case 2:
            cout << "Adicionar a ";
            destination.print();
            break;
        case 3:
            cout << "Alterar de ";
            origin.print();
            cout << "para ";
            destination.print();
            break;
        default:
            return;
    }

}