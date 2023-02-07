//
// Created by manue on 30/10/2022.
//
#include <iostream>
#include "Slot.h"

using namespace std;


/*!Construtor sem parâmetros. Constrói um slot com dia da semana vazio, hora de início 0.0, hora de fim 0.0 e tipo vazio.
 * Complexidade: O(1)
 */
Slot::Slot() {
    startHour = 0.0;
    endHour = 0.0;
}

/*!Construtor com parâmetros. Constrói um slot com dia da semana (traduzido para português) weekday_, hora de início startHour_, hora de fim endHour_ e tipo type_.
 * Complexidade: O(1)
 * @param weekday_ dia da semana (traduzido para português)
 * @param startHour_ hora de início
 * @param endHour_ hora de fim
 * @param type_ tipo
 */
Slot::Slot(const string &weekday_, float startHour_, float endHour_, const string &type_) {
    if (weekday_ == "Monday") weekday = "Segunda-feira";
    else if (weekday_ == "Tuesday") weekday = "Terça-feira";
    else if (weekday_ == "Wednesday") weekday = "Quarta-feira";
    else if (weekday_ == "Thursday") weekday = "Quinta-feira";
    else if (weekday_ == "Friday") weekday = "Sexta-feira";
    startHour = startHour_;
    endHour = endHour_;
    type = type_;
}

/*!Retorna o dia da semana do slot.
 * Complexidade: O(1)
 * @return dia da semana do slot
 */
string Slot::getWeekday() const {
    return weekday;
}

/*!Retorna a hora de início do slot.
 * Complexidade: O(1)
 * @return hora de início do slot
 */
float Slot::getStartHour() const {
    return startHour;
}

/*!Retorna a hora de fim do slot.
 * Complexidade: O(1)
 * @return hora de fim do slot
 */
float Slot::getEndHour() const {
    return endHour;
}

/*!Retorna o tipo do slot.
 * Complexidade: O(1)
 * @return tipo do slot
 */
string Slot::getType() const {
    return type;
}

/*!Define o dia da semana do slot como weekday_.
 * Complexidade: O(1)
 * @param weekday_ novo dia da semana do slot
 */
void Slot::setWeekday(const string &weekday_) {
    weekday = weekday_;
}

/*!Define a hora de inicío do slot como startHour_.
 * Complexidade: O(1)
 * @param startHour_ nova hora de inicío do slot
 */
void Slot::setStartHour(float startHour_) {
    startHour = startHour_;
}

/*!Define a hora de fim do slot como endHour_.
 * Complexidade: O(1)
 * @param endHour_ nova hora de fim do slot
 */
void Slot::setEndHour(float endHour_) {
    endHour = endHour_;
}

/*!Define o tipo do slot como type_.
 * Complexidade: O(1)
 * @param type_ novo tipo do slot
 */
void Slot::setType(const string &type_) {
    type = type_;
}

/*!Indica se other se sobrepõe ao slot. Só se considera que um slot se sobrepõe efetivamente a outro se nenhum deles for do tipo T.
 * Complexidade: O(n), sendo n o maior tamanho entre weekday e type
 * @param other slot com o qual analisar sobreposição
 * @return true se other se sobrepõe ao slot, false caso contrário
 */
bool Slot::overlap(const Slot &other) const {
    return (type != "T" && other.type != "T" && weekday == other.weekday && ((startHour < other.startHour && other.startHour < endHour) || (startHour < other.endHour && other.endHour < endHour) || (other.startHour < startHour && startHour < other.endHour) || (other.startHour < endHour && endHour < other.endHour)));
}

/*!Compara o slot e other quanto à sua posição na semana.
 * Complexidade: O(n), sendo n o tamanho do maior dia da semana entre o slot e other
 * @param other slot com o qual comparar
 * @return true se a posição do slot na semana é anterior a other, false caso contrário
 */
bool Slot::operator<(const Slot &other) const {
    return ((weekdayToNumber() < other.weekdayToNumber()) || (weekdayToNumber() == other.weekdayToNumber() && startHour < other.startHour) || (weekdayToNumber() == other.weekdayToNumber() && startHour == other.startHour && endHour < other.endHour));
}

/*!Imprime o slot, campo por campo, indicando a que se refere cada campo.
 * Complexidade: O(1)
 */
void Slot::print() const {
    cout << "Dia da Semana: " << weekday << " | Hora de Início: " << startHour << " | Hora de Fim: " << endHour << " | Tipo: " << type << endl;
}

/*!Converte o dia da semana do slot para um número, referente à sua posição na semana.
 * Complexidade: O(n), sendo n o tamanho de weekday
 * @return o número correspondente à posição de weekday na semana
 */
unsigned Slot::weekdayToNumber() const {
    if (weekday == "Segunda-feira") return 1;
    if (weekday == "Terça-feira") return 2;
    if (weekday == "Quarta-feira") return 3;
    if (weekday == "Quinta-feira") return 4;
    if (weekday == "Sexta-feira") return 5;
    return 0;
}