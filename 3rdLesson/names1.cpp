/*
Реализуйте класс для человека, поддерживающий историю изменений человеком своих фамилии и имени.

Считайте, что в каждый год может произойти не более одного изменения фамилии и не более одного
 изменения имени. При этом с течением времени могут открываться всё новые факты из прошлого
 человека, поэтому года́ в последовательных вызовах методов ChangeLastName и ChangeFirstName
 не обязаны возрастать.

Гарантируется, что все имена и фамилии непусты.

Строка, возвращаемая методом GetFullName, должна содержать разделённые одним пробелом имя и
 фамилию человека по состоянию на конец данного года.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#define first 0
#define second 1

using namespace std;

int find_i(const vector<int>& v, int x);

// Реализуйте класс для человека, поддерживающий историю изменений человеком своих фамилии и имени.
class Person {
public:
    void ChangeFirstName(int year, const string& new_first_name) {

        nameHystory[year][first] = new_first_name;
        changeFirstNameYears.push_back(year);

        // добавить факт изменения имени на first_name в год year
    }
    void ChangeLastName(int year, const string& new_last_name) {
        nameHystory[year][second] = new_last_name;
        changeSecondNameYears.push_back(year);
        ;
        // добавить факт изменения фамилии на last_name в год year
    }



    string GetFullName(int year) {
        string first_name = GetNumberName(year, changeFirstNameYears, first);
        string second_name = GetNumberName(year, changeSecondNameYears, second);

        if (first_name.empty() && second_name.empty())
            return "Incognito";
        if (second_name.empty())
            return first_name + " with unknown last name";
        if (first_name.empty())
            return second_name + " with unknown first name";
        return first_name + ' ' + second_name;
        // получить имя и фамилию по состоянию на конец года year
    }
private:
    map<int, string[2]> nameHystory;

    vector<int> changeFirstNameYears;  // года, хранящие изменения имен.
    vector<int> changeSecondNameYears; // года, хранящие изменения фамилий.

    string GetNumberName(int year, vector<int>& changeNameY, int nameNumber){
        if (changeNameY.empty())
            return "";
        sort(changeNameY.begin(), changeNameY.end());
        if (changeNameY.empty() || changeNameY[0] > year)
            return "";

        int i = 0;
        while ((i + 1) < changeNameY.size() && changeNameY[i + 1] <= year)  // в векторе с годами изменений имени
            i++;                                                           // ищем ближайший последний к year год

        return nameHystory[changeNameY[i]][nameNumber];
    }

    // приватные поля
};

int main() {
    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");

    for (int year : {1900, 1965, 1990}) {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }

    return 0;

}

