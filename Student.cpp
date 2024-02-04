//
// Created by manue on 30/10/2022.
//

#include <iostream>
#include "Student.h"

using namespace std;


/*!Construtor sem parâmetros. Constrói um estudante com código 0, nome vazio e em nenhuma turma.
 * Complexidade: O(1)
 */
Student::Student() {
    code = 0;
}

/*!Construtor com parâmetro. Constrói um estudante com código code_, nome vazio e em nenhuma turma.
 * Complexidade: O(1)
 * @param code_ código
 */
Student::Student(unsigned code_) {
    code = code_;
}

/*!Construtor com parâmetros. Constrói um estudante com código code_, nome name_ e em nenhuma turma.
 * Complexidade: O(1)
 * @param code_ código
 * @param name_ nome
 */
Student::Student(unsigned code_, const string &name_) {
    code = code_;
    name = name_;
}

/*!Construtor com parâmetros. Constrói um estudante com código code_, nome name_ e em turmas ucClasses_.
 * Complexidade: O(1)
 * @param code_ código
 * @param name_ nome
 * @param ucClasses_ turmas
 */
Student::Student(unsigned code_, const string &name_, const list<UcClass> &ucClasses_) {
    code = code_;
    name = name_;
    ucClasses = ucClasses_;
}

/*!Retorna o código do estudante.
 * Complexidade: O(1)
 * @return código do estudante
 */
unsigned Student::getCode() const {
    return code;
}

/*!Retorna o nome do estudante.
 * Complexidade: O(1)
 * @return nome do estudante
 */
string Student::getName() const {
    return name;
}

/*!Retorna as turmas do estudante.
 * Complexidade: O(1)
 * @return turmas do estudante
 */
list<UcClass> Student::getUcClasses() const {
    return ucClasses;
}

/*!Define o código do estudante como code_.
 * Complexidade: O(1)
 * @param code_ novo código do estudante
 */
void Student::setCode(unsigned code_) {
    code = code_;
}

/*!Define o nome do estudante como name_.
 * Complexidade: O(1)
 * @param name_ novo nome do estudante
 */
void Student::setName(const string &name_) {
    name = name_;
}

/*!Define as turmas do estudante como ucClasses_.
 * Complexidade: O(1)
 * @param ucClasses_ novas turmas do estudante
 */
void Student::setUcClasses(const list<UcClass> &ucClasses_) {
    ucClasses = ucClasses_;
}

/*!Adiciona ucClass às turmas do estudante.
 * Complexidade: O(1)
 * @param ucClass turma a adicionar às turmas do estudante
 */
void Student::addUcClass(const UcClass &ucClass) {
    ucClasses.push_back(ucClass);
}

/*!Remove ucClass das turmas do estudante.
 * Complexidade: O(n), sendo n o tamanho de ucClasses
 * @param ucClass turma a remover das turmas do estudante
 */
void Student::removeUcClass(const UcClass &ucClass) {
    ucClasses.remove(ucClass);
}

/*!Retorna um vector cujo índice do elemento correspondente ao (ano - 1) indica se o estudante frequenta esse ano (true) ou não (false).
 * Complexidade: O(n), sendo n o tamanho de ucClasses
 * @return vector cujo índice do elemento correspondente ao (ano - 1) indica se o estudante frequenta esse ano (true) ou não (false)
 */
vector<bool> Student::getYears() const {
    vector<bool> years = {false, false, false};
    for (const UcClass &ucClass : ucClasses)
        years[ucClass.getClassCode()[0] - '0' - 1] = true;
    return years;
}

/*!Indica se o estudante pertence a ucClass.
 * Complexidade: O(n), sendo n o tamanho de ucClasses
 * @param ucClass turma à qual analisar se o estudante pertence
 * @return true se o estudante pertence a ucClass, false caso contrário
 */
bool Student::inClass(const UcClass &ucClass) const {
    for (const UcClass &otherUcClass : ucClasses)
        if (ucClass == otherUcClass)
            return true;
    return false;
}

/*!Indica se o estudante frequenta a UC de ucClass.
 * Complexidade: O(n), sendo n o tamanho de ucClasses
 * @param ucClass turma cuja UC analisar se o estudante frequenta
 * @return true se o estudante frequenta a UC de ucClass, false caso contrário
 */
bool Student::inUc(const UcClass &ucClass) const {
    for (const UcClass &otherUcClass : ucClasses)
        if (ucClass.getUcCode() == otherUcClass.getUcCode())
            return true;
    return false;
}

/*!Compara o estudante e other quanto ao seu código.
 * Complexidade: O(1)
 * @param other estudante com o qual comparar
 * @return true se o código do estudante é inferior ao código de other, false caso contrário
 */
bool Student::operator<(const Student &other) const {
    return code < other.code;
}

/*!Imprime o código, nome e número de UCs do estudante.
 * Complexidade: O(1)
 */
void Student::printID() const {
    cout << "Estudante Nº " << code << " | Nome: " << name << " | Número de UCs: " << ucClasses.size() << endl ;
}

/*!Imprime o ID (código, nome e número de UCs) e as turmas do estudante.
 * Complexidade: O(n), sendo n o tamanho de ucClasses
 */
void Student::print() const {
    printID();
    for (const UcClass &ucClass : ucClasses)
        ucClass.print();
}