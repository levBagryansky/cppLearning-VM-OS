/*
Люди стоят в очереди, но никогда не уходят из её начала, зато могут приходить в конец и уходить оттуда. Более того, иногда некоторые люди могут прекращать и начинать беспокоиться из-за того, что очередь не продвигается.

Будем считать, что люди в очереди нумеруются целыми числами, начиная с 0.

Реализуйте обработку следующих операций над очередью:

WORRY i: пометить i-го человека с начала очереди как беспокоящегося;
QUIET i: пометить i-го человека как успокоившегося;
COME k: добавить k спокойных человек в конец очереди;
COME -k: убрать k человек из конца очереди;
WORRY_COUNT: узнать количество беспокоящихся людей в очереди.
Изначально очередь пуста.
 */

#include <iostream>
#include <vector>
#define worry true
#define quiet false

using namespace std;

void printVector(const vector<bool>& v);
void worry_i(vector<bool>& v);
void quiet_i(vector<bool>& v);
void come_k(vector<bool>& v);
void come_min_k(vector<bool>& v);
int worry_count(const vector<bool>& v);

using namespace std;
int main() {
    vector<bool> v;
    //cout << "Enter the number of operations:";
    int q; // количество операций
    cin >> q;
    for (int i = 0; i < q; ++i) {
        //cout << "Command:";
        string command;
        cin >> command;

        if (command == "WORRY")
            worry_i(v);
        else if (command == "QUIET")
            quiet_i(v);
        else if (command == "COME")
            come_k(v);
        else if (command == "WORRY_COUNT")
            worry_count(v);
        else
        {
            i--;
            cout << "Try again";
        }

        //printVector(v);
    }
    return 0;
}

void printVector(const vector<bool>& v)
{
    cout << "Vector: ";
    for (auto elem: v) {
        if (elem == worry)
            cout << "worry ";
        else
            cout << "quit ";
    }
    cout << endl;
}

void worry_i(vector<bool>& v)
{
    int i;
    cin >> i;
    v[i] = worry;
}

void quiet_i(vector<bool>& v)
{
    int i;
    cin >> i;
    v[i] = quiet;
}

void come_k(vector<bool>& v) // добавить k спокойных человек в конец очереди
{
    int k;
    cin >> k;
    v.resize(v.size() + k);
}

void come_min_k(vector<bool>& v) // убрать к человек из конца очереди
{
    int k;
    cin >> k;
    v.resize(v.size() - k);
}

int worry_count(const vector<bool>& v) // узнать количество беспокоящихся людей
{
    int result = 0;
    for (auto elem: v)
    {
        if (elem == worry)
            result++;
    }
    cout << result << ' ';
    return result;
}

