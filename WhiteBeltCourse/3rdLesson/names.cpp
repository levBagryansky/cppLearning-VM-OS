/*
Реализуйте класс для человека, поддерживающий историю изменений человеком своих фамилии и имени.
Считайте, что в каждый год может произойти не более одного изменения фамилии и не более одного
 изменения имени. При этом с течением времени могут открываться всё новые факты из прошлого
 человека, поэтому года́ в последовательных вызовах методов ChangeLastName и ChangeFirstName
 не обязаны возрастать.
Гарантируется, что все имена и фамилии непусты.
Строка, возвращаемая методом GetFullName, должна содержать разделённые одним пробелом имя и
 фамилию человека по состоянию на конец данного года.

 В отличие от метода GetFullName, метод GetFullNameWithHistory должен вернуть не только последние
 имя и фамилию к концу данного года, но ещё и все предыдущие имена и фамилии в обратном
 хронологическом порядке. Если текущие факты говорят о том, что человек два раза подряд изменил
 фамилию или имя на одно и то же, второе изменение при формировании истории нужно игнорировать.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#define first 0
#define second 1

using namespace std;

string createStrOfElements (const vector<string>& v); // создает строку "(v[l-1], v[l-1], .. v[0])"
void deleteRepeats (vector<string>& v); // убирает повторяющиеся(подряд) жлементы массива и удаляет последний элемент


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

    string GetFullNameWithHistory (int year)  // получить все имена и фамилии по состоянию на конец года year
    {
        string first_name = GetNumberName(year, changeFirstNameYears, first);
        vector<string> first_names;
        int i = 0;
        while (i < changeFirstNameYears.size() && year >= changeFirstNameYears[i]) {
            first_names.push_back(nameHystory[changeFirstNameYears[i]][first]);
            i++;
        }
        deleteRepeats(first_names);

        string second_name = GetNumberName(year, changeSecondNameYears, second);
        vector<string> second_names;
        i = 0;
        while (i < changeSecondNameYears.size() && year >= changeSecondNameYears[i]) {
            second_names.push_back(nameHystory[changeSecondNameYears[i]][second]);
            i++;
        }
        deleteRepeats(second_names);

        if (first_name.empty() && second_name.empty())
            return "Incognito";
        if (second_name.empty())
            return first_name + ' ' + createStrOfElements(first_names) + "with unknown last name";
        if (first_name.empty())
            return second_name + ' ' + createStrOfElements(second_names) + "with unknown first name";
        string result = first_name + ' ' + createStrOfElements(first_names) +
                        second_name + ' ' + createStrOfElements(second_names);
        result.resize(result.size() - 1);
        return result;

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

int main(){
    Person person;

    person.ChangeFirstName(1900, "Eugene");
    person.ChangeLastName(1900, "Sokolov");
    person.ChangeLastName(1910, "Sokolov");
    person.ChangeFirstName(1920, "Evgeny");
    person.ChangeLastName(1930, "Sokolov");
    cout << person.GetFullNameWithHistory(1940) << endl;

    return 0;

}

string createStrOfElements (const vector<string>& v)
{

    if (v.empty())
        return "";

    string result = "(";
    for (int i = v.size() - 1; i > 0; --i) {
        result += (v[i] + ", ");

    }
    result += (v[0] + ") ");
    return result;
}

void deleteRepeats (vector<string>& v)
{
    if (v.size() == 1)
        v.clear();
    else if (v.size() >= 2)
    {
        vector<string> new_v;
        new_v.push_back(v[0]);
        for (int i = 1; i < v.size(); ++i) {
            if (v[i] != new_v.back())
                new_v.push_back(v[i]);
        }
        new_v.resize(new_v.size() - 1);
        v = new_v;
    }

}

