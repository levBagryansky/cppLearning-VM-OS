/*
У каждого из нас есть повторяющиеся ежемесячные дела,
 каждое из которых нужно выполнять в конкретный день каждого месяца:
 оплата счетов за электричество, абонентская плата за связь и пр.
 Вам нужно реализовать работу со списком таких дел на месяц, а именно,
 реализовать набор следующих операций:
*)ADD i s
Назначить дело с названием s на день i текущего месяца.

*)DUMP i
Вывести все дела, запланированные на день i текущего месяца.

*)NEXT
Перейти к списку дел на новый месяц. При выполнении данной команды
 вместо текущего (старого) списка дел на текущий месяц создаётся и
 становится активным (новый) список дел на следующий месяц: все дела
 со старого списка дел копируются в новый список. После выполнения
 данной команды новый список дел и следующий месяц становятся текущими,
 а работа со старым списком дел прекращается.  При переходе к новому
 месяцу необходимо обратить внимание на разное количество дней в месяцах:
если следующий месяц имеет больше дней, чем текущий, «дополнительные» дни
необходимо оставить пустыми (не содержащими дел);
если следующий месяц имеет меньше дней, чем текущий, дела со всех «лишних»
 дней необходимо переместить на последний день следующего месяца.
 */

#include <iostream>
#include <vector>

using namespace std;
vector<int> tableOfMonths = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

void add_i_s(vector<vector<string>>& todo);
void dump_i(const vector<vector<string>>& todo);
void next(vector<vector<string>>& todo, int& monthCounter);
void print_todo(const vector<vector<string>>& todo);

int main()
{
    vector<int> tableOfMonths = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    //сколько дней в каком месяце
    vector<vector<string>> todo(tableOfMonths[0]);
    int monthCounter = 0;
    cout << "Enter numbers of operations:";
    int q; cin >> q;
    for (int i = 0; i < q; ++i) {
        string command;
        cout << "Enter command:";
        cin >> command;

        if (command == "ADD")
            add_i_s(todo);
        else if (command == "DUMP")
            dump_i(todo);
        else if (command == "NEXT")
            next(todo, monthCounter);
        //print_todo(todo);
    }
    //print_todo(todo);

    return 0;
}

void add_i_s(vector<vector<string>>& todo)
{
    int i; cin >> i;
    string s; cin >> s;

    todo[i - 1].push_back(s);
    //cout << "/==========================================" << endl;
    //print_todo(todo);
    //cout << "/==========================================" << endl;
}
void dump_i(const vector<vector<string>>& todo)
{
    int i; cin >> i;
    cout << todo[i-1].size() << ' ';
    for (int j = 0; j < todo[i - 1].size(); ++j) {
        cout << todo[i - 1][j] << ' ';
    }
    cout << endl;
}
void next(vector<vector<string>>& todo, int& monthCounter)
{
    monthCounter++;
    monthCounter %= 12;
    if (tableOfMonths[monthCounter - 1] <= tableOfMonths[monthCounter])
        todo.resize(tableOfMonths[monthCounter]);
    else
    {
        for (int i = tableOfMonths[monthCounter]; i < tableOfMonths[monthCounter - 1]; ++i)
        {
            for (auto elem: todo[i])
            {
                todo[tableOfMonths[monthCounter] - 1].push_back(elem);
            }
        }
        todo.resize(tableOfMonths[monthCounter]);

    }
}
void print_todo(const vector<vector<string>>& todo)
{
    for (int i = 0; i < todo.size(); ++i) {
        cout << "Day number " << i + 1 <<':'<< endl;
        for (int j = 0; j < todo[i].size(); ++j) {
            cout << j + 1 << ' ' << todo[i][j] << endl;
        }
    }
}
