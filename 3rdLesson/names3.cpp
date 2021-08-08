// то же, что и names1, однако для Person теперь написан конструктор.

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
//#define first 0
//#define second 1

using namespace std;

int find_i(const vector<int>& v, int x);
string createStrOfElements (const vector<string>& v); // создает строку "(v[l-1], v[l-1], .. v[0])"
void deleteRepeats (vector<string>& v); // убирает повторяющиеся(подряд) жлементы массива и удаляет последний элемент



// Реализуйте класс для человека, поддерживающий историю изменений человеком своих фамилии и имени.
class Person {
public:
    Person(string first_name, string second_name, int year){
        birthyear = year;
        nameHystory[year][first] = first_name;
        nameHystory[year][second] = second_name;
        changeFirstNameYears.push_back(year);
        changeSecondNameYears.push_back(year);
    }

    void ChangeFirstName(int year, const string& new_first_name) {
        if (year > birthyear) {
            nameHystory[year][first] = new_first_name;
            changeFirstNameYears.push_back(year);
        }
        // добавить факт изменения имени на first_name в год year
    }
    void ChangeLastName(int year, const string& new_last_name) {
        if (year > birthyear) {
            nameHystory[year][second] = new_last_name;
            changeSecondNameYears.push_back(year);
        }
        // добавить факт изменения фамилии на last_name в год year
    }



    string GetFullName(int year) {
        string first_name = GetNumberName(year, changeFirstNameYears, first);
        string second_name = GetNumberName(year, changeSecondNameYears, second);

        if (first_name.empty() && second_name.empty())
            return "No person";
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
            return "No person";
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
    int birthyear;   // год рождения
    map<int, string[2]> nameHystory; // год - имя, фамилия

    vector<int> changeFirstNameYears;  // года, хранящие изменения имен.
    vector<int> changeSecondNameYears; // года, хранящие изменения фамилий.

    string GetNumberName(int year, vector<int>& changeNameY, int nameNumber) {
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
    Person person("Polina", "Sergeeva", 1960);
    for (int year : {1959, 1960}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1965, "Appolinaria");
    person.ChangeLastName(1967, "Ivanova");
    for (int year : {1965, 1967}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

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
