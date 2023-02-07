//
// Created by manue on 30/10/2022.
//

#include <iostream>
#include "UcClass.h"

using namespace std;


/*!Construtor sem parâmetros. Constrói uma turma de código vazio, de uma UC de código vazio e sem estudantes.
 * Complexidade: O(1)
 */
UcClass::UcClass() {
    studentsCount = 0;
}

/*!Construtor com parâmetros. Constrói uma turma de código classCode_, de uma UC de código ucCode_ e sem estudantes.
 * Complexidade: O(1)
 * @param ucCode_ código da UC
 * @param classCode_ código da turma
 */
UcClass::UcClass(const string &ucCode_, const string &classCode_) {
    ucCode = ucCode_;
    classCode = classCode_;
    studentsCount = 0;
}

/*!Construtor com parâmetros. Constrói uma turma de código classCode_, de uma UC de código ucCode_ e com número de estudantes studentsCount_.
 * Complexidade: O(1)
 * @param ucCode_ código da UC
 * @param classCode_ código da turma
 * @param studentsCount_ número de estudantes
 */
UcClass::UcClass(const string &ucCode_, const string &classCode_, unsigned studentsCount_) {
    ucCode = ucCode_;
    classCode = classCode_;
    studentsCount = studentsCount_;
}

/*!Retorna o código da UC.
 * Complexidade: O(1)
 * @return código da UC
 */
string UcClass::getUcCode() const {
    return ucCode;
}

/*!Retorna o código da turma.
 * Complexidade: O(1)
 * @return código da turma
 */
string UcClass::getClassCode() const {
    return classCode;
}

/*!Retorna o número de estudantes da turma.
 * Complexidade: O(1)
 * @return número de estudantes da turma
 */
unsigned UcClass::getStudentsCount() const {
    return studentsCount;
}

/*!Define o código da UC como ucCode_.
 * Complexidade: O(1)
 * @param ucCode_ novo código da UC
 */
void UcClass::setUcCode(const string &ucCode_) {
    ucCode = ucCode_;
}

/*!Define o código da turma como classCode_.
 * Complexidade: O(1)
 * @param classCode_ novo código da turma
 */
void UcClass::setClassCode(const string &classCode_) {
   classCode = classCode_;
}

/*!Define o número de estudantes da turma como studentsCount_.
 * Complexidade: O(1)
 * @param studentsCount_ novo número de estudantes da turma
 */
void UcClass::setStudentsCount(unsigned studentsCount_) {
    studentsCount = studentsCount_;
}

/*!Incrementa o número de estudantes da turma em 1.
 * Complexidade: O(1)
 */
void UcClass::addStudent() {
    studentsCount += 1;
}

/*!Decrementa o número de estudantes da turma em 1.
 * Complexidade: O(1)
 */
void UcClass::removeStudent() {
    studentsCount -= 1;
}

/*!Compara a turma e other, primeiro quanto ao código da UC e depois quanto ao código da turma, ambas as comparações por ordem lexicográfica.
 * Complexidade: O(n), sendo n o maior tamanho entre o código da UC e o código da turma, da turma e de other
 * @param other turma com a qual comparar
 * @return true se a turma é anterior a other, false caso contrário
 */
bool UcClass::operator<(const UcClass &other) const {
    return (ucCode < other.ucCode || (ucCode == other.ucCode && classCode < other.classCode));
}

/*!Compara a turma e other quanto ao código da UC e ao código da turma, ambas as comparações por ordem lexicográfica.
 * Complexidade: O(n), sendo n o maior tamanho entre o código da UC e o código da turma, da turma e de other
 * @param other turma com a qual a comparar
 * @return true se a turma e other têm igual código da UC e código da turma, false caso contrário
 */
bool UcClass::operator==(const UcClass &other) const {
    return (ucCode == other.ucCode && classCode == other.classCode);
}

/*!Imprime o código da UC e o código da turma.
 * Complexidade: O(1)
 */
void UcClass::print() const {
    cout << "UC: " << ucCode << " - Turma: " << classCode << endl;
}