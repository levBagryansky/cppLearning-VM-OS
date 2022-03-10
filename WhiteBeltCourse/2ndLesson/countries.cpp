/*
 Словарт соответствий стран и столиц.
 Можно добавить новую страну, поменять названия,
 узнать всю информацию.

 CHANGE_CAPITAL country new_capital — изменение столицы страны country на new_capital,
 либо добавление такой страны с такой столицей, если раньше её не было.

 RENAME old_country_name new_country_name —
 переименование страны из old_country_name в new_country_name.

 ABOUT country — вывод столицы страны country.

 DUMP — вывод столиц всех стран.
 */

#include <iostream>
#include <map>

using namespace std;

void change_capital(map<string, string>& m);
void rename (map<string, string>& m);
void about(map<string, string>& m);
void dump(const map<string, string>& m);

int main()
{
    map<string, string> capitals;
    int q; cin >> q; //количество запросов
    for (int i = 0; i < q; ++i)
    {
        string command;
        //cout << "Enter command:";
        cin >> command;

        if (command == "CHANGE_CAPITAL")
            change_capital(capitals);
        else if (command == "RENAME")
            rename(capitals);
        else if (command == "ABOUT")
            about(capitals);
        else if (command == "DUMP")
            dump(capitals);

    }
    return 0;
}

void change_capital(map<string, string>& m)
{
    string country;
    cin >> country;
    string newCapital;
    cin >> newCapital;

    if (m.count(country) == 0)
        cout << "Introduce new country " << country <<" with capital "<< newCapital << endl;
    else if (m[country] == newCapital)
        cout << "Country " << country << " hasn't changed its capital" << endl;
    else
        cout << "Country " << country <<" has changed its capital from "<<
             m[country]<<" to " << newCapital <<endl;
    m[country] = newCapital;
}

void rename (map<string, string>& m) {
    string oldCountryName;
    cin >> oldCountryName;
    string newCountryName;
    cin >> newCountryName;

    if (oldCountryName == newCountryName ||
        m.count(oldCountryName) == 0 ||
        m.count(newCountryName) == 1)
        cout << "Incorrect rename, skip" << endl;
    else {
        cout << "Country " << oldCountryName << " with capital " <<
             m[oldCountryName] <<" has been renamed to " << newCountryName << endl;

        m[newCountryName] = m[oldCountryName];
        m.erase(oldCountryName);
    }
}

void about(map<string, string>& m)
{
    string country;
    cin >> country;

    if (m.count(country) == 0)
        cout << "Country " << country << " doesn't exist" << endl;
    else
        cout << "Country " << country << " has capital " << m[country] << endl;
}

void dump(const map<string, string>& m)
{
    if (m.empty())
        cout << "There are no countries in the world" << endl;
    else
    {
        for(auto item: m)
        {
            cout << item.first << '/' << item.second << ' ';
        }
        cout << endl;
    }
}
