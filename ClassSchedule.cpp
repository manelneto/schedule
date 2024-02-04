//
// Created by manue on 30/10/2022.
//

#include "ClassSchedule.h"

using namespace std;


/*!Construtor sem parâmetros. Constrói um horário de uma turma vazia sem nenhum slot.
 * Complexidade: O(1)
 */
ClassSchedule::ClassSchedule() {
}

/*!Construtor com parâmetro. Constrói um horário de uma turma ucClass_ sem nenhum slot.
 * Complexidade: O(1)
 * @param ucClass_ turma
 */
ClassSchedule::ClassSchedule(const UcClass &ucClass_) {
    ucClass = ucClass_;
}

/*!Construtor com parâmetros. Constrói um horário de uma turma ucClass_ com slots slots_.
 * Complexidade: O(1)
 * @param ucClass_ turma
 * @param slots_ slots
 */
ClassSchedule::ClassSchedule(const UcClass &ucClass_, const list<Slot> &slots_) {
    ucClass = ucClass_;
    slots = slots_;
}

/*!Retorna a turma do horário.
 * Complexidade: O(1)
 * @return turma do horário
 */
UcClass ClassSchedule::getUcClass() const {
    return ucClass;
}

/*!Retorna os slots do horário.
 * Complexidade: O(1)
 * @return slots do horário
 */
list<Slot> ClassSchedule::getSlots() const {
    return slots;
}

/*!Define a turma do horário como ucClass_.
 * Complexidade: O(1)
 * @param ucClass_ nova turma do horário
 */
void ClassSchedule::setUcClass(const UcClass &ucClass_) {
    ucClass = ucClass_;
}

/*!Define os slots do horário como slots_.
 * Complexidade: O(1)
 * @param slots_ novos slots do horário
 */
void ClassSchedule::setSlots(const list<Slot> &slots_) {
    slots = slots_;
}

/*!Adiciona slot aos slots do horário.
 * Complexidade: O(1)
 * @param slot slot a adicionar aos slots do horário
 */
void ClassSchedule::addSlot(const Slot &slot) {
    slots.push_back(slot);
}

/*!Indica se other se sobrepõe a algum dos slots do horário.
 * Complexidade: O(n), sendo n o tamanho de slots
 * @param other slot com o qual analisar sobreposição
 * @return true se other se sobrepõe a algum dos slots do horário, false caso contrário
 */
bool ClassSchedule::overlap(const Slot &other) const {
    for (const Slot &slot : slots)
        if (slot.overlap(other))
            return true;
    return false;
}

/*!Indica se other é da mesma turma do horário.
 * Complexidade: O(1)
 * @param other horário com o qual comparar turma
 * @return true se other é da mesma turma do horário, false caso contrário
 */
bool ClassSchedule::operator==(const ClassSchedule &other) const {
    return ucClass == other.ucClass;
}

/*!Imprime a turma do horário e os slots do horário.
 * Complexidade: O(n), sendo n o tamanho de slots
 */
void ClassSchedule::print() const {
    ucClass.print();
    for (const Slot &slot : slots)
        slot.print();
}