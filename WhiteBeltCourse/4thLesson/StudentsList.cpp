/*
 Определите структуру «Студент» со следующими полями: имя, фамилия,
 день, месяц и год рождения. Создайте вектор из таких структур,
 заполните его из входных данных и затем по запросам выведите
 нужные поля. Чтение и запись данных в этой задаче производится
 с использованием стандартных потоков.
 */

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>

using namespace std;

struct Student{
    string first_name;
    string last_name;
    int birthday;
    int birthmonth;
    int birthyear;
};

vector<Student> readStudents();
void doCommand(const vector<Student>& students, string command, int k);

int main() {
    vector<Student> students = readStudents();
    int n_commands; //количество команд
    cin >> n_commands;


    for (int i = 0; i < n_commands; ++i) {
        string command;
        cin >> command;
        int k;
        cin >> k;
        k--;

        doCommand(students, command, k);
    }
    return 0;
}

vector<Student> readStudents(){
    int size;
    cin >> size;
    vector<Student> result(size);
    for (int i = 0; i < size; ++i) {
        cin >> result[i].first_name
            >> result[i].last_name
            >> result[i].birthday
            >> result[i].birthmonth
            >> result[i].birthyear;
    }
    return result;
}

void doCommand(const vector<Student>& students, string command, int k){
    if (k > students.size())
        cout << "bad request" << endl;

    else if (command == "name")
        cout << students[k].first_name << ' '
             << students[k].last_name << endl;

    else if (command == "date")
        cout << students[k].birthday   << '.'
             << students[k].birthmonth << '.'
             << students[k].birthyear << endl;

    else
        cout << "bad request" << endl;
}
