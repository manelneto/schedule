//
// Created by manue on 30/10/2022.
//

#ifndef SCHEDULE_MANAGEMENT_H
#define SCHEDULE_MANAGEMENT_H


#include <set>
#include <queue>
#include "ClassSchedule.h"
#include "Request.h"

class Management {
public:
    Management();
    Management(const std::list<UcClass> &classes_, const std::set<Student> &students_, const std::vector<ClassSchedule> &schedules_, const std::queue<Request> &requests_, unsigned cap_);
    std::list<UcClass> getClasses() const;
    std::set<Student> getStudents() const;
    std::vector<ClassSchedule> getSchedules() const;
    std::queue<Request> getRequests() const;
    unsigned getCap() const;
    void setClasses(const std::list<UcClass> &classes_);
    void setStudents(const std::set<Student> &students_);
    void setSchedules(const std::vector<ClassSchedule> &schedules);
    void setRequests(const std::queue<Request> &requests_);
    void setCap(unsigned cap_);
    void start();
    int menu();
    void end();
private:
    std::list<UcClass> classes;
    std::set<Student> students;
    std::vector<ClassSchedule> schedules;
    std::queue<Request> requests;
    unsigned cap;
    void readClassesFile();
    void readStudentsFile();
    void readSchedulesFile();
    void readRequestsFile();
    static bool isNumber(const std::string &str);
    static int validateOption(int option, const std::set<int> &options);
    bool isValidUcCode(const std::string &code) const;
    static std::string readString();
    static int readNumber();
    Student readStudent() const;
    std::string readUc() const;
    UcClass readUcClass() const;
    static bool sortByStudentsCount(const UcClass &left, const UcClass &right);
    static bool sortByName(const Student &left, const Student &right);
    static bool sortByUcsCount(const Student &left, const Student &right);
    static void chooseStudentsSort(std::list<Student> &toSort);
    static void printStudentsCount(const std::list<UcClass> &sorted);
    static void printStudents(const std::list<Student> &sorted);
    std::list<std::pair<Slot, UcClass>> getStudentSchedule(const Student &student) const;
    std::list<std::pair<Slot, UcClass>> getClassSchedule(const UcClass &ucClass) const;
    void listagens() const;
    void ocupacao() const;
    void ocupacaoTurmas() const;
    void ocupacaoTurmasTotal() const;
    void ocupacaoTurmasParcial() const;
    void ocupacaoTurmasAno() const;
    void ocupacaoTurmasUc() const;
    void ocupacaoTurma() const;
    void ocupacaoAno() const;
    void ocupacaoUc() const;
    void horarioEstudante() const;
    void estudantes() const;
    void estudantesTurma() const;
    void estudantesUc() const;
    void estudantesAno() const;
    void nUcs() const;
    void horarioTurma() const;
    void pedidos();
    void adicionarPedido();
    void removerTurma(Student &student);
    void adicionarTurma(Student &student);
    void alterarTurma(Student &student);
    void alterarTurmas(Student &student);
    void listarPedidos();
    bool temVaga(const UcClass &ucClass) const;
    bool desequilibra(const UcClass &origin, const UcClass &destination) const;
    bool sobrepoe(const UcClass &origin, const UcClass &destination, const Student &student) const;
    void processarPedidos();
    bool processarPedido(const Request &request);
    bool processarPedidoRemover(const Request &request);
    bool processarPedidoAdicionar(const Request &request);
    bool processarPedidoAlterar(const Request &request);
    void verPedido() const;
    void forcarPedido();
    void removerPedido();
    void removerPedidos();
    void writeStudentsFile() const;
    void writeRequestsFile();
};


#endif //SCHEDULE_MANAGEMENT_H
