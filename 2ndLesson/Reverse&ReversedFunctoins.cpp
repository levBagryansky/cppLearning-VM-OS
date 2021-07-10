#include <iostream>
#include <vector>

using namespace std;

void UpdateIfGreater(int first, int& second);

void MoveStrings(vector<string>& source, vector<string>& destination);

void Reverse(vector<int>& v);               // разворачивает вектор.

vector<int> Reversed(const vector<int>& v); // возвращает развернутый вектор, не меняя аргумент.

int main() {
    vector<int> numbers = {1, 5, 3, 4, 2};
    Reverse(numbers);
    return 0;
}

void UpdateIfGreater(int first, int& second)
{
    if (first > second)
        second = first;
}

void MoveStrings(vector<string>& source, vector<string>& destination)
{
    for (auto item: source) {
        destination.push_back(item);
    }

    source.clear();
}

void Reverse(vector<int>& v)
{
    vector<int> vClone = v;
    int vSize = v.size();
    v.clear();
    for (int i = --vSize; i >= 0; i--) {
        v.push_back(vClone[i]);
    }
}

vector<int> Reversed(const vector<int>& v)
{
    vector<int> result;
    for (int i = v.size() - 1; i >= 0 ; i--) {
        result.push_back(v[i]);
    }
    return result;
}