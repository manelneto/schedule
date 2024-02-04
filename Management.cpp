//
// Created by manue on 30/10/2022.
//

#include "Management.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;


/*!Construtor sem parâmetros. Constrói um objeto de gestão com capacidade das turmas 0 e com turmas, estudantes, horários e pedidos lidos de ficheiros.
 * Complexidade: O(n * m), sendo o par (n, m) o máximo entre n o número de linhas do ficheiro estudantes e m o tamanho de classes, ou n o número de linhas do ficheiro de horários e m o tamanho de schedules, ou n o número de linhas do ficheiro de pedidos e m o tamanho de classes
 */
Management::Management() {
    cap = 0;
    readClassesFile();
    readStudentsFile();
    readSchedulesFile();
    readRequestsFile();
}

/*!Construtor com parâmetros. Constrói um objeto de gestão com turmas classes_, estudantes students_, horários schedules_, pedidos requests_ e capacidade das turmas cap_.
 * Complexidade: O(1)
 * @param classes_ turmas
 * @param students_ estudantes
 * @param schedules_ horários
 * @param requests_ pedidos
 * @param cap_ capacidade das turmas
 */
Management::Management(const list<UcClass> &classes_, const set<Student> &students_, const vector<ClassSchedule> &schedules_, const queue<Request> &requests_, unsigned cap_) {
    classes = classes_;
    students = students_;
    schedules = schedules_;
    requests = requests_;
    cap = cap_;
}

/*!Retorna as turmas.
 * Complexidade: O(1)
 * @return turmas
 */
list<UcClass> Management::getClasses() const {
    return classes;
}

/*!Retorna os estudantes.
 * Complexidade: O(1)
 * @return estudantes
 */
set<Student> Management::getStudents() const {
    return students;
}

/*!Retorna os horários.
 * Complexidade: O(1)
 * @return horários
 */
vector<ClassSchedule> Management::getSchedules() const {
    return schedules;
}

/*!Retorna os pedidos.
 * Complexidade: O(1)
 * @return pedidos
 */
queue<Request> Management::getRequests() const {
    return requests;
}

/*!Retorna a capacidade das turmas.
 * Complexidade: O(1)
 * @return capacidade das turmas
 */
unsigned Management::getCap() const {
    return cap;
}

/*!Define as turmas como classes_.
 * Complexidade: O(1)
 * @param classes_ novas turmas
 */
void Management::setClasses(const list<UcClass> &classes_) {
    classes = classes_;
}

/*!Define os estudantes como students_.
 * Complexidade: O(1)
 * @param students_ novos estudantes
 */
void Management::setStudents(const set<Student> &students_) {
    students = students_;
}

/*!Define os horários como schedules_.
 * Complexidade: O(1)
 * @param schedules_ novos horários
 */
void Management::setSchedules(const vector<ClassSchedule> &schedules_) {
    schedules = schedules_;
}

/*!Define os pedidos como requests_.
 * Complexidade: O(1)
 * @param requests_ novos pedidos
 */
void Management::setRequests(const std::queue<Request> &requests_) {
    requests = requests_;
}

/*!Define a capacidade das turmas como cap_.
 * Complexidade: O(1)
 * @param cap_ nova capacidade das turmas
 */
void Management::setCap(unsigned cap_) {
    cap = cap_;
}

/*!Inicia a aplicação e lê o valor a atribuir à capacidade das turmas.
 * Complexidade: O(n), sendo n a posição do primeiro input válido introduzido pelo utilizador
 */
void Management::start() {
    cout << "\nAntes de iniciar o programa, indique o valor pretendido para a capacidade máxima de uma turma (Cap): ";
    cap = readNumber();
}

/*!Apresenta o menu principal. Permite selecionar a opção de listagens, de pedidos ou sair.
 * Complexidade: amplamente variável de acordo com o input
 * @return 0 se o utilizador pretender sair, 1 caso contrário
 */
int Management::menu() {
    cout << "\nMenu Principal:\n1 - Listagens\n2 - Pedidos\n0 - Sair\nSelecione a opção pretendida através do número correspondente." << endl;
    int option = readNumber();
    set<int> options = {1, 2, 0};
    option = validateOption(option, options);
    switch (option) {
        case 1:
            listagens();
            break;
        case 2:
            pedidos();
            break;
        default:
            return 0;
    }
    return 1;
}

/*!Termina a aplicação, processando os pedidos e atualizando os ficheiros de estudantes e de pedidos.
 * Complexidade: amplamente variável de acordo com o tipo de pedidos a processar
 */
void Management::end() {
    processarPedidos();
    writeStudentsFile();
    writeRequestsFile();
}

/*!Lê o ficheiro de turmas.
 * Complexidade: O(n), sendo n o número de linhas do ficheiro de turmas
 */
void Management::readClassesFile() {
    ifstream in("../Files/classes_per_uc.csv");
    if (!in.is_open()) {
        cout << "Erro ao abrir o ficheiro classes_per_uc.csv." << endl;
        cout << "Verifique se o ficheiro se encontra dentro do diretório Files." << endl;
        return;
    }
    string line;
    getline(in, line);
    while (getline(in, line)) {
        istringstream iss(line);
        string field;
        vector<string> fields(2);
        unsigned f = 0;
        while(getline(iss, field, ','))
            fields[f++] = field;
        string ucCode = fields[0];
        string classCode = fields[1];
        UcClass ucClass = UcClass(ucCode, classCode);
        classes.push_back(ucClass);
    }
    cout << "Leitura de ficheiro classes_per_uc.csv bem-sucedida." << endl;
}

/*!Lê o ficheiro de estudantes.
 * Complexidade: O(n * m), sendo n o número de linhas do ficheiro estudantes e m o tamanho de classes
 */
void Management::readStudentsFile() {
    ifstream in("../Files/students_classes.csv");
    if (!in.is_open()) {
        cout << "Erro ao abrir o ficheiro students_classes.csv." << endl;
        cout << "Verifique se o ficheiro se encontra dentro do diretório Files." << endl;
        return;
    }
    string line;
    getline(in, line);
    while (getline(in, line)) {
        istringstream iss(line);
        string field;
        vector<string> fields(4);
        unsigned f = 0;
        while(getline(iss, field, ','))
            fields[f++] = field;
        unsigned studentCode = stoi(fields[0]);
        string studentName = fields[1];
        string ucCode = fields[2];
        string classCode = fields[3];
        UcClass ucClass = UcClass(ucCode, classCode);
        find(classes.begin(), classes.end(), ucClass)->addStudent();
        Student student = Student(studentCode, studentName);
        auto it = students.find(student);
        if (it != students.end()) {
            Student temp = *it;
            students.erase(it);
            temp.addUcClass(ucClass);
            students.insert(temp);
        } else {
            student.addUcClass(ucClass);
            students.insert(student);
        }
    }
    cout << "Leitura de ficheiro students_classes.csv bem-sucedida." << endl;
}

/*!Lê o ficheiro de horários.
 * Complexidade: O(n * m), sendo n o número de linhas do ficheiro de horários e m o tamanho de schedules
 */
void Management::readSchedulesFile() {
    ifstream in("../Files/classes.csv");
    if (!in.is_open()) {
        cout << "Erro ao abrir o ficheiro classes.csv." << endl;
        cout << "Verifique se o ficheiro se encontra dentro do diretório Files." << endl;
        return;
    }
    string line;
    getline(in, line);
    while (getline(in, line)) {
        istringstream iss(line);
        string field;
        vector<string> fields(6);
        unsigned f = 0;
        while(getline(iss, field, ','))
            fields[f++] = field;
        string classCode = fields[0];
        string ucCode = fields[1];
        string weekday = fields[2];
        float startHour = stof(fields[3]);
        float duration = stof(fields[4]);
        float endHour = startHour + duration;
        string type = fields[5];
        UcClass ucClass = UcClass(ucCode, classCode);
        Slot slot = Slot(weekday, startHour, endHour, type);
        ClassSchedule classSchedule = ClassSchedule(ucClass);
        auto it = find(schedules.begin(), schedules.end(), classSchedule);
        if (it != schedules.end())
            it->addSlot(slot);
        else {
            classSchedule.addSlot(slot);
            schedules.push_back(classSchedule);
        }
    }
    cout << "Leitura de ficheiro classes.csv bem-sucedida." << endl;
}

/*!Lê o ficheiro de pedidos.
 * Complexidade: O(n * m), sendo n o número de linhas do ficheiro de pedidos e m o tamanho de classes
 */
void Management::readRequestsFile() {
    ifstream in("../Files/requests.csv");
    if (!in.is_open())
        return;
    string line;
    getline(in, line);
    while (getline(in, line)) {
        istringstream iss(line);
        string field;
        vector<string> fields(6);
        unsigned f = 0;
        while (getline(iss, field, ','))
            fields[f++] = field;
        unsigned studentCode = stoi(fields[0]);
        string originUcCode = fields[1];
        string originClassCode = fields[2];
        string destinationUcCode = fields[3];
        string destinationClassCode = fields[4];
        unsigned type = stoi(fields[5]);
        Student student = Student(studentCode);
        auto it = students.find(student);
        if (it == students.end())
            continue;
        auto origin = find(classes.begin(), classes.end(), UcClass(originUcCode, originClassCode));
        auto destination = find(classes.begin(), classes.end(),UcClass(destinationUcCode, destinationClassCode));
        Request request;
        switch (type) {
            case 1: {
                request = Request(*it, *origin, UcClass(), type);
                break;
            }
            case 2: {
                request = Request(*it, UcClass(), *destination, type);
                break;
            }
            default:
                request = Request(*it, *origin, *destination, type);
        }
        requests.push(request);
    }
    cout << "Leitura de ficheiro requests.csv bem-sucedida." << endl;
}

/*!Verifica se str é um número.
 * Complexidade: O(n), sendo n o tamanho de str
 * @param str string a verificar se é um número
 * @return true se str é um número, false caso contrário
 */
bool Management::isNumber(const std::string &str) {
    for (const char &ch : str)
        if (isalpha(ch))
            return false;
    return true;
}

/*!Valida uma opção, isto é, verifica se option pertence ao conjunto de opções válidas options. Enquanto a opção for inválida, tenta ler uma opção válida.
 * Complexidade: O(n), sendo n a posição do primeiro input válido introduzido pelo utilizador
 * @param option opção a validar
 * @param options opções válidas
 * @return opção válida introduzida pelo utilizador
 */
int Management::validateOption(int option, const set<int> &options) {
    while (options.find(option) == options.end()) {
        cout << "O número inserido não é uma opção válida. Tente novamente." << endl;
        option = readNumber();
    }
    return option;
}

/*!Verifica se code é um código de uma UC.
 * Complexidade: O(n), sendo n o tamanho de classes
 * @param code string a verificar se é um código de uma UC
 * @return true se code é um código de uma UC, false caso contrário
 */
bool Management::isValidUcCode(const std::string &code) const {
    for (const UcClass &ucClass : classes)
        if (ucClass.getUcCode() == code)
            return true;
    return false;
}

/*!Lê uma string do utilizador.
 * Complexidade: O(1)
 * @return string introduzida pelo utilizador
 */
string Management::readString() {
    string s;
    cin >> s;
    cout << endl;
    return s;
}

/*!Lê um número do utilizador, forçando a que seja um número não negativo.
 * Complexidade: O(n), sendo n a posição do primeiro input válido introduzido pelo utilizador
 * @return número não negativo introduzido pelo utilizador
 */
int Management::readNumber() {
    string s = readString();
    while (!isNumber(s)) {
        cout << "Deve inserir um número. Tente novamente." << endl;
        s = readString();
    }
    int n = stoi(s);
    while (n < 0) {
        cout << "O número não pode ser negativo. Tente novamente." << endl;
        n = readNumber();
    }
    return n;
}

/*!Lê um estudante através do seu código, forçando a que ele exista.
 * Complexidade: O(n * log m), sendo n a posição do primeiro input válido introduzido pelo utilizador e m o tamanho de students
 * @return estudante existente introduzido pelo utilizador
 */
Student Management::readStudent() const {
    cout << "Número do Estudante: ";
    int code = readNumber();
    Student student = Student(code);
    while (students.find(student) == students.end()) {
        cout << "Estudante não encontrado. Tente novamente." << endl;
        student = readStudent();
    }
    student = *students.find(student);
    return student;
}

/*!Lê uma UC através do seu código, forçando a que ela exista.
 * Complexidade: O(n * m), sendo n a posição do primeiro input válido introduzido pelo utilizador e m o tamanho de classes
 * @return UC existente introduzida pelo utilizador
 */
std::string Management::readUc() const {
    cout << "Código da UC: ";
    string ucCode = readString();
    while (!isValidUcCode(ucCode)) {
        cout << "UC não encontrada. Tente novamente." << endl;
        ucCode = readUc();
    }
    return ucCode;
}

/*!Lê uma turma através do seu código e do código da UC a que pertence, forçando que ela exista.
 * Complexidade: O(n * m), sendo n a posição do primeiro input válido introduzido pelo utilizador e m o tamanho de classes
 * @return turma existente introduzida pelo utilizador
 */
UcClass Management::readUcClass() const {
    string ucCode = readUc();
    cout << "Código da Turma: ";
    string classCode = readString();
    UcClass ucClass = UcClass(ucCode, classCode);
    while (find(classes.begin(), classes.end(), ucClass) == classes.end()) {
        cout << "Turma não encontada. Tente novamente." << endl;
        ucClass = readUcClass();
    }
    return ucClass;
}

/*!Compara o número de estudantes de left com o número de estudantes de right.
 * Complexidade: O(1)
 * @param left turma com a qual comparar número de estudantes de right
 * @param right turma com a qual comparar número de estudantes de left
 * @return true se o número de estudantes de left for menor do que o número de estudantes de right, false caso contrário
 */
bool Management::sortByStudentsCount(const UcClass &left, const UcClass &right) {
    return left.getStudentsCount() < right.getStudentsCount();
}

/*!Compara lexicograficamente o nome de left com o nome de right.
 * Complexidade: O(1)
 * @param left estudante com o qual comparar o nome de right
 * @param right estudante com o qual comparar o nome de left
 * @return true se o nome de left for lexicograficamente anterior ao nome de right, false caso contrário
 */
bool Management::sortByName(const Student &left, const Student &right) {
    return left.getName() < right.getName();
}

/*!Compara o número de UCs de left com o número de UCs de right.
 * Complexidade: O(1)
 * @param left estudante com o qual comparar o número de UCs de right
 * @param right estudante com o qual comparar o número de UCs de left
 * @return true se o número de UCs de left for inferior ao número de UCs de right, false caso contrário
 */
bool Management::sortByUcsCount(const Student &left, const Student &right) {
    return left.getUcClasses().size() < right.getUcClasses().size();
}

/*!Lê do utilizador a ordenação pretendida para os estudantes a listar (por código, nome ou número de UCs) e ordena os estudantes como pretendido.
 * Complexidade: O(n * log n), sendo n o tamanho de toSort
 * @param toSort lista de estudantes a ordenar
 */
void Management::chooseStudentsSort(std::list<Student> &toSort) {
    cout << "\nOrdenação:\n1 - Número do Estudante\n2 - Nome do Estudante\n3 - Número de UCs\nSelecione a opção pretendida através do número correspondente." << endl;
    int option = readNumber();
    set<int> options = {1, 2, 3};
    option = validateOption(option, options);
    switch (option) {
        case 2:
            toSort.sort(sortByName);
            break;
        case 3:
            toSort.sort(sortByUcsCount);
            break;
        default:
            toSort.sort();
            return;
    }
}

/*!Lê do utilizador a ordenação pretendida para as UCs a listar por ocupação (crescente ou decrescente) e imprime-as, com o respetivo número de estudantes, pela ordem pretendida.
 * Complexidade: O(n), sendo n o tamanho de sorted
 * @param sorted lista de UCs a imprimir
 */
void Management::printStudentsCount(const std::list<UcClass> &sorted) {
    cout << "\nOrdenação:\n1 - Crescente\n2 - Decrescente\n0 - Sair\nSelecione a opção pretendida através do número correspondente." << endl;
    int option = readNumber();
    set<int> options = {1, 2, 0};
    option = validateOption(option, options);
    switch (option) {
        case 1:
            for (const UcClass &ucClass : sorted) {
                ucClass.print();
                cout << ucClass.getStudentsCount() << " alunos" << endl;
                cout << endl;
            }
            break;
        case 2:
            for (auto it = sorted.rbegin(); it != sorted.rend(); it++) {
                (*it).print();
                cout << (*it).getStudentsCount() << " alunos" << endl;
                cout << endl;
            }
            break;
        default:
            return;
    }
}

/*!Lê do utilizador a ordenação pretendida para os estudantes a listar (crescente ou decrescente) e imprime o ID de cada um, pela ordem pretendida.
 * Complexidade: O(n), sendo n o tamanho de sorted
 * @param sorted lista de estudantes a imprimir
 */
void Management::printStudents(const std::list<Student> &sorted) {
    cout << "\nOrdenação:\n1 - Crescente\n2 - Decrescente\n0 - Sair\nSelecione a opção pretendida através do número correspondente." << endl;
    int option = readNumber();
    set<int> options = {1, 2, 0};
    option = validateOption(option, options);
    switch (option) {
        case 1:
            for (const Student &student : sorted)
                student.printID();
            break;
        case 2:
            for (auto it = sorted.rbegin(); it != sorted.rend(); it++)
                (*it).printID();
            break;
        default:
            return;
    }
}

/*!Retorna o horário ordenado de um estudante.
 * Complexidade: O(n * m), sendo n tamanho de ucClasses do estudante e m o máximo entre o tamanho de schedules e o tamanho de slots do horário
 * @param student estudante
 * @return horário ordenado do estudante
 */
list<pair<Slot, UcClass>> Management::getStudentSchedule(const Student &student) const {
    list<pair<Slot, UcClass>> schedule;
    for (const UcClass &ucClass : student.getUcClasses())
        for (const Slot &slot : find(schedules.begin(), schedules.end(), ClassSchedule(ucClass))->getSlots())
            schedule.emplace_back(slot, ucClass);
    schedule.sort();
    return schedule;
}

/*!Retorna o horário ordenado de uma turma.
 * Complexidade: O(n), sendo n o tamanho de schedules
 * @param ucClass turma
 * @return horário ordenado da turma
 */
std::list<std::pair<Slot, UcClass>> Management::getClassSchedule(const UcClass &ucClass) const {
    list<pair<Slot, UcClass>> schedule;
    for (const Slot &slot : find(schedules.begin(), schedules.end(), ClassSchedule(ucClass))->getSlots())
        schedule.emplace_back(slot, ucClass);
    schedule.sort();
    return schedule;
}

/*!Apresenta o menu de listagens. Permite selecionar a opção de listagens pretendida (ocupação de turmas/ano/UC, horário de determinado estudante, esudantes em determinada turma/UC/ano, estudantes com mais de n UCs ou horário de determinada turma) ou sair.
 * Complexidade: amplamente variável de acordo com o input
 */
void Management::listagens() const {
    cout << "\nMenu de Listagens:\n1 - Ocupação de turmas/ano/UC\n2 - Horário de determinado estudante\n3 - Esudantes em determinada turma/UC/ano\n4 - Estudantes com mais de n UCs\n5 - Horário de determinada turma\n0 - Sair\nSelecione a opção pretendida através do número correspondente." << endl;
    int option = readNumber();
    set<int> options = {1, 2, 3, 4, 5, 0};
    option = validateOption(option, options);
    switch (option) {
        case 1:
            ocupacao();
            break;
        case 2:
            horarioEstudante();
            break;
        case 3:
            estudantes();
            break;
        case 4:
            nUcs();
            break;
        case 5:
            horarioTurma();
            break;
        default:
            return;
    }
}

/*!Permite selcionar a consulta de ocupação pretendida (turmas, ano ou UC) ou sair.
 * Complexidade: amplamente variável de acordo com o input
 */
void Management::ocupacao() const {
    cout << "\nConsulta de Ocupação:\n1 - Turmas\n2 - Ano\n3 - UC\n0 - Sair\nSelecione a opção pretendida através do número correspondente." << endl;
    int option = readNumber();
    set<int> options = {1, 2, 3, 0};
    option = validateOption(option, options);
    switch (option) {
        case 1:
            ocupacaoTurmas();
            break;
        case 2:
            ocupacaoAno();
            break;
        case 3:
            ocupacaoUc();
            break;
        default:
            return;
    }
}

/*!Permite selcionar a consulta de ocupação de turmas pretendida (total ou parcial) ou sair.
 * Complexidade: amplamente variável de acordo com o input
 */
void Management::ocupacaoTurmas() const {
    cout << "\nConsulta de Ocupação de Turmas:\n1 - Total\n2 - Parcial\n0 - Sair\nSelecione a opção pretendida através do número correspondente." << endl;
    int option = readNumber();
    set<int> options = {1, 2, 0};
    option = validateOption(option, options);
    switch (option) {
        case 1:
            ocupacaoTurmasTotal();
            break;
        case 2:
            ocupacaoTurmasParcial();
            break;
        default:
            return;
    }
}

/*!Apresenta o menu de consulta de ocupação de turmas total e lê do utilizador a opção pretendida (ordenação por UC, ordenação por ocupação ou sair).
 * Complexidade: O(n * log n), sendo n o tamanho de classes
 */
void Management::ocupacaoTurmasTotal() const {
    cout << "\nOrdenação:\n1 - Por UC\n2 - Por Ocupação\n0 - Sair\nSelecione a opção pretendida através do número correspondente." << endl;
    int option = readNumber();
    set<int> options = {1, 2, 0};
    option = validateOption(option, options);
    list<UcClass> sorted;
    for (const UcClass &ucClass : classes)
        sorted.push_back(ucClass);
    switch (option) {
        case 1:
            break;
        case 2:
            sorted.sort(sortByStudentsCount);
            break;
        default:
            return;
    }
    printStudentsCount(sorted);
}

/*!Apresenta o menu de consulta de ocupação de turmas parcial e lê do utilizador a opção pretendida (todas as turmas de um ano, todas as turmas de uma UC, uma turma de uma UC ou sair).
 * Complexidade: amplamente variável de acordo com o input
 */
void Management::ocupacaoTurmasParcial() const {
    cout << "\nConsulta de Ocupação de Turmas Parcial:\n1 - Todas as turmas de um ano\n2 - Todas as turmas de uma UC\n3 - Uma turma de uma UC\n0 - Sair\nSelecione a opção pretendida através do número correspondente." << endl;
    int option = readNumber();
    set<int> options = {1, 2, 3, 0};
    switch (option) {
        case 1:
            ocupacaoTurmasAno();
            break;
        case 2:
            ocupacaoTurmasUc();
            break;
        case 3:
            ocupacaoTurma();
            break;
        default:
            return;
    }
}

/*!Imprime a ocupação (número de estudantes) de todas as turmas de um ano.
 * Complexidade: O(n), sendo n o tamanho de classes
 */
void Management::ocupacaoTurmasAno() const {
    cout << "\nIndique o ano (1, 2 ou 3)" << endl;
    int option = readNumber();
    set<int> options = {1, 2, 3};
    option = validateOption(option, options);
    for (const UcClass &ucClass : classes)
        if (ucClass.getClassCode()[0] - '0' == option) {
            ucClass.print();
            cout << ucClass.getStudentsCount() << " alunos" << endl;
            cout << endl;
        }
}

/*!Imprime a ocupação (número de estudantes) de todas as turmas de uma UC.
 * Complexidade: O(n), sendo n o tamanho de classes
 */
void Management::ocupacaoTurmasUc() const {
    string ucCode = readUc();
    for (const UcClass &ucClass : classes)
        if (ucClass.getUcCode() == ucCode)
            cout << ucClass.getClassCode() << ": " << ucClass.getStudentsCount()  << " alunos" << endl;
}

/*!Imprime a ocupação (número de estudantes) de uma determinada turma de uma UC.
 * Complexidade: O(n), sendo n o tamanho de students
 */
void Management::ocupacaoTurma() const {
    UcClass ucClass = readUcClass();
    unsigned res = 0;
    for (const Student &student : students)
        if (student.inClass(ucClass))
            res += 1;
    cout << res << " alunos" << endl;
}

/*!Imprime a ocupação (número de estudantes) de um determinado ano.
 * Complexidade: O(n), sendo n o tamanho de students
 */
void Management::ocupacaoAno() const {
    cout << "\nIndique o ano (1, 2 ou 3)" << endl;
    int option = readNumber();
    set<int> options = {1, 2, 3};
    option = validateOption(option, options);
    unsigned res = 0;
    for (const Student &student : students)
        if (student.getYears()[option - 1])
            res += 1;
    cout << res << " alunos" << endl;
}

/*!Imprime a ocupação (número de estudantes) de uma determinada UC.
 * Complexidade: O(n), sendo n o tamanho de classes
 */
void Management::ocupacaoUc() const {
    string ucCode = readUc();
    unsigned res = 0;
    for (const UcClass &ucClass : classes)
        if (ucClass.getUcCode() == ucCode)
            res += ucClass.getStudentsCount();
    cout << res << " alunos" << endl;
}

/*!Imprime o horário de um determinado estudante.
 * Complexidade: O(n * m), sendo n o tamanho de ucClasses do estudante e m o máximo entre o tamanho de schedules e o tamanho de slots do horário
 */
void Management::horarioEstudante() const {
    Student student = readStudent();
    student.print();
    cout << endl;
    list<pair<Slot, UcClass>> schedule = getStudentSchedule(student);
    for (const pair<Slot, UcClass> &pair : schedule) {
        pair.first.print();
        pair.second.print();
        cout << endl;
    }
}

/*!Apresenta o menu de consulta de estudantes e lê do utilizador a opção pretendida (por turma, por UC, por ano ou sair).
 * Complexidade: amplamente variável de acordo com o input
 */
void Management::estudantes() const {
    cout << "\nConsulta de Estudantes:\n1 - Turma\n2 - UC\n3 - Ano\n0 - Sair\nSelecione a opção pretendida através do número correspondente." << endl;
    int option = readNumber();
    set<int> options = {1, 2, 3, 0};
    option = validateOption(option, options);
    switch (option) {
        case 1:
            estudantesTurma();
            break;
        case 2:
            estudantesUc();
            break;
        case 3:
            estudantesAno();
            break;
        default:
            return;
    }
}

/*!Imprime os estudantes de uma determinada turma de uma UC.
 * Complexidade: O(n * log n), sendo n o tamanho de students
 */
void Management::estudantesTurma() const {
    UcClass ucClass = readUcClass();
    list<Student> sorted;
    for (const Student &student : students)
        if (student.inClass(ucClass))
            sorted.push_back(student);
    chooseStudentsSort(sorted);
    printStudents(sorted);
}

/*!Imprime os estudantes de uma determinada UC.
 * Complexidade: O(n * m), sendo n o tamanho de students e m o tamanho de ucClasses do estudante
 */
void Management::estudantesUc() const {
    string ucCode = readUc();
    list<Student> sorted;
    for (const Student &student : students)
        for (const UcClass &ucClass : student.getUcClasses())
            if (ucClass.getUcCode() == ucCode)
                sorted.push_back(student);
    chooseStudentsSort(sorted);
    printStudents(sorted);
}

/*!Imprime os estudantes de um determinado ano.
 * Complexidade: O(n * log n), sendo n o tamanho de students
 */
void Management::estudantesAno() const {
    cout << "\nIndique o ano (1, 2 ou 3)" << endl;
    int option = readNumber();
    set<int> options = {1, 2, 3};
    option = validateOption(option, options);
    list<Student> sorted;
    for (const Student &student : students)
        if (student.getYears()[option - 1])
            sorted.push_back(student);
    chooseStudentsSort(sorted);
    printStudents(sorted);
}

/*!Imprime os estudantes com mais de n UCs pela ordem pretendida.
 * Complexidade: O(n * log n), sendo n o tamanho de students
 */
void Management::nUcs() const {
    cout << "\nIntroduza o valor de n" << endl;
    int n = readNumber();
    list<Student> sorted;
    for (const Student &student: students)
        if (student.getUcClasses().size() > n)
            sorted.push_back(student);
    chooseStudentsSort(sorted);
    printStudents(sorted);
}

/*!Imprime o horário de uma determinada turma de uma UC.
 * Complexidade: O(n), sendo n o tamanho de schedules
 */
void Management::horarioTurma() const {
    UcClass ucClass = readUcClass();
    list<pair<Slot, UcClass>> schedule = getClassSchedule(ucClass);
    for (const pair<Slot, UcClass> &pair : schedule) {
        pair.first.print();
        pair.second.print();
        cout << endl;
    }
}

/*!Apresenta o menu de pedidos e lê do utilizador a opção pretendida (adicionar pedido, listar pedidos, processar todos os pedidos, ver próximo pedido a processar, processar próximo pedido, remover próximo pedido a processar, remover todos os pedidos ou sair).
 * Complexidade: amplamente variável de acordo com o input
 */
void Management::pedidos() {
    cout << "\nMenu de Pedidos:\n1 - Adicionar pedido\n2 - Listar pedidos\n3 - Processar todos os pedidos\n4 - Ver próximo pedido a processar\n5 - Processar próximo pedido\n6 - Remover próximo pedido a processar\n7 - Remover todos os pedidos\n0 - Sair\nSelecione a opção pretendida através do número correspondente." << endl;
    int option = readNumber();
    set<int> options = {1, 2, 3, 4, 5, 6, 7, 0};
    option = validateOption(option, options);
    switch (option) {
        case 1:
            adicionarPedido();
            break;
        case 2:
            listarPedidos();
            break;
        case 3:
            processarPedidos();
            break;
        case 4:
            verPedido();
            break;
        case 5:
            forcarPedido();
            break;
        case 6:
            removerPedido();
            break;
        case 7:
            removerPedidos();
            break;
        default:
            return;
    }
}

/*!Apresenta o menu de adição de pedidos e lê do utilizador a opção pretendida (remover estudante de turma/UC, adicionar estudante a uma turma/UC, alterar a turma/UC de um estudante, alterar um conjunto de turmas/UCs de um estudante ou sair).
 * Complexidade: amplamente variável de acordo com o input
 */
void Management::adicionarPedido() {
    cout << "\nTipo do Pedido a Adicionar:\n1 - Remover estudante de turma/UC\n2 - Adicionar estudante a uma turma/UC\n3 - Alterar a turma/UC de um estudante\n4 - Alterar um conjunto de turmas/UCs de um estudante\n0 - Sair\nSelecione a opção pretendida através do número correspondente." << endl;
    int option = readNumber();
    set<int> options = {1, 2, 3, 4, 0};
    option = validateOption(option, options);
    switch (option) {
        case 1: {
            Student student = readStudent();
            removerTurma(student);
            break;
        }
        case 2: {
            Student student = readStudent();
            adicionarTurma(student);
            break;
        }
        case 3: {
            Student student = readStudent();
            alterarTurma(student);
            break;
        }
        case 4: {
            Student student = readStudent();
            alterarTurmas(student);
            break;
        }
        default:
            return;
    }
}

/*!Lê do utilizador um pedido de remoção de um estudante a uma turma.
 * Complexidade: O(n), sendo n o tamanho de classes
 * @param student estudante a tentar remover de turma
 */
void Management::removerTurma(Student &student) {
    UcClass origin = readUcClass();
    UcClass destination = UcClass();
    if (!student.inClass(origin)) {
        cout << "\nO estudante indicado já não frequenta essa turma." << endl;
        return;
    }
    Request request = Request(student, origin, destination, 1);
    requests.push(request);
    cout << "\nPedido adicionado à fila de pedidos." << endl;
}

/*!Lê do utilizador um pedido de adição de um estudante a uma turma.
 * Complexidade: O(n), sendo n o tamanho de classes
 * @param student estudante a tentar adiconar a turma
 */
void Management::adicionarTurma(Student &student) {
    UcClass origin = UcClass();
    UcClass destination = readUcClass();
    if (student.inClass(destination)) {
        cout << "\nO estudante indicado já frequenta essa turma." << endl;
        return;
    }
    if (student.inUc(destination)) {
        cout << "\nO estudante indicado já frequenta essa UC. Um estudante não pode frquentar duas turmas da mesma UC." << endl << "Caso pretenda mudar de turma dentro da mesma UC, deve solicitar um pedido de alteração de turma." << endl;
        return;
    }
    Request request = Request(student, origin, destination, 2);
    requests.push(request);
    cout << "\nPedido adicionado à fila de pedidos." << endl;
}

/*!Lê do utilizador um pedido de alteração de turma de um estudante.
 * Complexidade: O(n), sendo n o tamanho de classes
 * @param student estudante a tentar alterar turma
 */
void Management::alterarTurma(Student &student) {
    cout << "\nTurma de Origem" << endl;
    UcClass origin = readUcClass();
    while (!student.inClass(origin)) {
        cout << "O estudante indicado não frequenta essa turma. Tente novamente." << endl;
        origin = readUcClass();
    }
    cout << "\nTurma de Destino" << endl;
    UcClass destination = readUcClass();
    while (origin.getUcCode() != destination.getUcCode()) {
        cout << "A UC de destino deve coincidir com a UC de origem. Um estudante só pode mudar de turma dentro da mesma UC. Tente novamente." << endl;
        cout << "\nTurma de Destino" << endl;
        destination = readUcClass();
    }
    Request request = Request(student, origin, destination, 3);
    requests.push(request);
    cout << "\nPedido adicionado à fila de pedidos." << endl;
}

/*!Lê do utilizador um pedido de alteração de um conjunto de turmas de um estudante.
 * Complexidade: O(n * m), sendo n o input do utilizador (número de turmas a alterar) e m o tamanho de classes
 * @param student estudante a tentar alterar turmas
 */
void Management::alterarTurmas(Student &student) {
    cout << "\nIndique o número de UCs a alterar." << endl;
    int n = readNumber();
    for (int i = 1; i <= n; i++) {
        cout << "\nAteração Nº " << i << endl;
        alterarTurma(student);
    }
}

/*!Lista, por ordem, todos os pedidos na fila de pedidos.
 * Complexidade: O(n), sendo n o tamanaho da fila de pedidos.
 */
void Management::listarPedidos() {
    if (requests.empty()) {
        cout << "\nA fila de pedidos está vazia." << endl;
        return;
    }
    queue<Request> requestsCopy = requests;
    unsigned i = 1;
    while (!requestsCopy.empty()) {
        cout << i++ << ". ";
        requestsCopy.front().print();
        cout << endl;
        requestsCopy.pop();
    }
}

/*!Indica se uma turma tem vaga, de acordo com a capacidade máxima das turmas.
 * Complexidade: O(1)
 * @param ucClass turma a analisar se tem vaga
 * @return true se a turma tem vaga, false caso contrário
 */
bool Management::temVaga(const UcClass &ucClass) const {
    return ucClass.getStudentsCount() < cap;
}

/*!Indica se a mudança de um estudante de uma turma para outra provoca desequilíbrio nas turmas dessa UC (ou se já existia desequilíbrio).
 * Complexidade: O(n), sendo n o tamanho de classes
 * @param origin turma de origem
 * @param destination turma de destino
 * @return true se a mudança de um estudante de uma turma para outra provoca desquilíbrio nas turmas dessa UC (ou se já existia desequilíbrio), false caso contrário
 */
bool Management::desequilibra(const UcClass &origin, const UcClass &destination) const {
    unsigned max = 0;
    unsigned min = UINT_MAX;
    for (const UcClass &ucClass : classes)
        if (ucClass.getUcCode() == origin.getUcCode())  {
            if (ucClass.getStudentsCount() > max) {
                max = ucClass.getStudentsCount();
                if (ucClass.getClassCode() == origin.getClassCode())
                    max -= 1;
                if (ucClass.getClassCode() == destination.getClassCode())
                    max += 1;
            }
            if (ucClass.getStudentsCount() < min) {
                min = ucClass.getStudentsCount();
                if (ucClass.getClassCode() == origin.getClassCode())
                    min -= 1;
                if (ucClass.getClassCode() == destination.getClassCode())
                    min += 1;
            }
        }
    unsigned dif = max - min;
    return dif >= 4;
}

/*!Indica se o horário de um estudante, retirando-lhe a turma da qual pretende sair, se sobrepõe com o horário da turma para a qual pretende mudar.
 * Complexidade: O(n * m), sendo n tamanho de ucClasses do estudante e m o máximo entre o tamanho de schedules e o tamanho de slots do horário
 * @param origin turma da qual o estudante pretende sair
 * @param destination turma para a qual o estudante pretende mudar
 * @param student estudante
 * @return true se o horário do estudante se sobrepõe com o horário da turma para a qual pretende mudar, false caso contrário
 */
bool Management::sobrepoe(const UcClass &origin, const UcClass &destination, const Student &student) const {
    Student temp = student;
    temp.removeUcClass(origin);
    ClassSchedule destinationSchedule = *find(schedules.begin(), schedules.end(), ClassSchedule(destination));
    for (const pair<Slot, UcClass> &p : getStudentSchedule(temp))
        if (destinationSchedule.overlap(p.first))
            return true;
    return false;
}

/*!Processa todos os pedidos em fila.
 * Complexidade: amplamente variável de acordo com o tipo de pedidos a processar
 */
void Management::processarPedidos() {
    queue<Request> updatedRequests;
    while (!requests.empty()) {
        Request request = requests.front();
        if (!processarPedido(request))
            updatedRequests.push(request);
        requests.pop();
    }
    requests = updatedRequests;
}

/*!Processa um pedido de acordo com o seu tipo.
 * Complexidade: amplamente variável de acordo com o tipo de pedido
 * @param request pedido a processar
 * @return true se o pedido foi aceite (ou tornado inválido), false caso contrário
 */
bool Management::processarPedido(const Request &request) {
    switch (request.getType()) {
        case 1:
            return processarPedidoRemover(request);
        case 2:
            return processarPedidoAdicionar(request);
        case 3:
            return processarPedidoAlterar(request);
        default:
            break;
    }
    return false;
}

/*!Processa (de acordo com as regras) um pedido de remoção de turma, imprimindo o resultado do processamento e o motivo.
 * Complexidade: O(n), sendo n o tamanho de classes
 * @param request pedido a processar
 * @return true (um pedido de remoção é sempre aceite ou inválido)
 */
bool Management::processarPedidoRemover(const Request &request) {
    auto ucClass = find(classes.begin(), classes.end(), request.getOrigin());
    auto student = students.find(request.getStudent());
    if (student->inClass(*ucClass)) {
        cout << "\nPedido aceite:" << endl;
        request.print();
        ucClass->removeStudent();
        Student temp = *student;
        students.erase(student);
        temp.removeUcClass(*ucClass);
        students.insert(temp);
    }
    else {
        cout << "\nPedido tornou-se inválido e será removido porque o estudante já não se encontra na turma:" << endl;
        request.print();
    }
    return true;
}

/*!Processa (de acordo com as regras) um pedido de adição de turma, imprimindo o resultado do processamento e o motivo.
 * Complexidade: O(n * m), sendo n tamanho de ucClasses do estudante e m o máximo entre o tamanho de schedules e o tamanho de slots do horário
 * @param request pedido a processar
 * @return true se o pedido foi aceite (ou tornado inválido), false caso contrário
 */
bool Management::processarPedidoAdicionar(const Request &request) {
    UcClass origin = request.getOrigin();
    auto destination = find(classes.begin(), classes.end(), request.getDestination());
    auto student = students.find(request.getStudent());
    if (!student->inClass(*destination) && !student->inUc(*destination) && temVaga(*destination) && !desequilibra(origin, *destination) && !sobrepoe(origin, *destination, *student)) {
        cout << "\nPedido aceite:" << endl;
        request.print();
        destination->addStudent();
        Student temp = *student;
        students.erase(student);
        temp.addUcClass(*destination);
        students.insert(temp);
        return true;
    }
    if (student->inClass(*destination)) {
        cout << "\nPedido tornou-se inválido e será removido porque o estudante já se encontra na turma:" << endl;
        request.print();
        return true;
    }
    if (student->inUc(*destination)) {
        cout << "\nPedido tornou-se inválido e será removido porque o estudante já frequenta essa UC e não pode frequentar duas turmas da mesma UC:" << endl;
        request.print();
        return true;
    }
    cout << "\nPedido rejeitado:" << endl;
    request.print();
    if (!temVaga(*destination))
        cout << "Motivo: a turma de destino não possui vaga." << endl;
    if (desequilibra(origin, *destination))
        cout << "Motivo: provoca desquilíbrio nas turmas dessa UC." << endl;
    if (sobrepoe(origin, *destination, *student))
        cout << "Motivo: provoca sobreposição de horários." << endl;
    return false;
}

/*!Processa (de acordo com as regras) um pedido de alteração de turma, imprimindo o resultado do processamento e o motivo.
 * Complexidade: O(n * m), sendo n tamanho de ucClasses do estudante e m o máximo entre o tamanho de schedules e o tamanho de slots do horário
 * @param request pedido a processar
 * @return true se o pedido foi aceite (ou tornado inválido), false caso contrário
 */
bool Management::processarPedidoAlterar(const Request &request) {
    auto origin = find(classes.begin(), classes.end(), request.getOrigin());
    auto destination = find(classes.begin(), classes.end(), request.getDestination());
    auto student = students.find(request.getStudent());
    if (student->inClass(*origin) && !student->inClass(*destination) && temVaga(*destination) && !desequilibra(*origin, *destination) && !sobrepoe(*origin, *destination, *student)) {
        cout << "\nPedido aceite:" << endl;
        request.print();
        origin->removeStudent();
        destination->addStudent();
        Student temp = *student;
        students.erase(student);
        temp.removeUcClass(*origin);
        temp.addUcClass(*destination);
        students.insert(temp);
        return true;
    }
    if (!student->inClass(*origin)) {
        cout << "\nPedido tornou-se inválido e será removido porque o estudante já não se encontra na turma de origem:" << endl;
        request.print();
        return true;
    }
    if (student->inClass(*destination)) {
        cout << "\nPedido tornou-se inválido e será removido porque o estudante já se encontra na turma de destino:" << endl;
        request.print();
        return true;
    }
    cout << "\nPedido rejeitado:" << endl;
    request.print();
    if (!temVaga(*destination))
        cout << "Motivo: a turma de destino não possui vaga." << endl;
    if (desequilibra(*origin, *destination))
        cout << "Motivo: provoca desquilíbrio nas turmas dessa UC." << endl;
    if (sobrepoe(*origin, *destination, *student))
        cout << "Motivo: provoca sobreposição de horários." << endl;
    return false;
}

/*!Imprime o próximo pedido da fila de pedidos.
 * Complexidade: O(1)
 */
void Management::verPedido() const {
    if (!requests.empty())
        requests.front().print();
    else
        cout << "\nA fila de pedidos está vazia." << endl;
}

/*!Processa (de acordo com as regras) o próximo pedido da fila de pedidos.
 * Complexidade: amplamente variável de acordo com o tipo de pedido
 */
void Management::forcarPedido() {
    if (!requests.empty()) {
        Request request = requests.front();
        if (processarPedido(request))
            requests.pop();
        cout << endl;
    }
    else
        cout << "\nA fila de pedidos está vazia." << endl;
}

/*!Remove o próximo pedido a processar da fila de pedidos.
 * Complexidade: O(1)
 */
void Management::removerPedido() {
    if (!requests.empty()) {
        cout << "\nPedido removido: " << endl;
        requests.front().print();
        requests.pop();
        cout << endl;
    }
    else
        cout << "\nA fila de pedidos está vazia." << endl;
}

/*!Remove todos os pedidos da fila de pedidos.
 * Complexidade: O(n), sendo n o tamanho de requests
 */
void Management::removerPedidos() {
    while (!requests.empty())
        removerPedido();
    cout << "\nA fila de pedidos está vazia." << endl;
}

/*!Atualiza o ficheiro de estudantes com os novos dados dos estudantes.
 * Complexidade: O(n * m), sendo n o tamanho de students e m o maior tamanho de ucClasses de um estudante
 */
void Management::writeStudentsFile() const {
    ofstream out;
    out.open("../Files/students_classes.csv");
    out << "StudentCode,StudentName,UcCode,ClassCode" << endl;
    for (const Student &student : students)
        for (const UcClass &ucClass : student.getUcClasses())
            out << student.getCode() << "," << student.getName() << "," << ucClass.getUcCode() << "," << ucClass.getClassCode() << endl;
    out.close();
}

/*!Atualiza o ficheiro de pedidos com os pedidos em fila.
 * Complexidade: O(n), sendo n o tamanho de requests
 */
void Management::writeRequestsFile() {
    ofstream out("../Files/requests.csv");
    out << "StudentCode,OriginUcCode,OriginClassCode,DestinationUcCode,DestinationClassCode,Type" << endl;
    while (!requests.empty()) {
        Request request = requests.front();
        out << request.getStudent().getCode() << "," <<
             request.getOrigin().getUcCode() << "," << request.getOrigin().getClassCode() << "," <<
             request.getDestination().getUcCode() << "," << request.getDestination().getClassCode() << "," <<
             request.getType() << endl;
        requests.pop();
    }
    out.close();
}