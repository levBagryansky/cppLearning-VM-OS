// Даётся n слов, найти сколько среди них уникальных

#include <iostream>
#include <set>

using namespace std;

int main()
{
    int n;
    cin >> n;
    set<string> s;
    string word;

    for (int i = 0; i < n; ++i) {
        cin >> word;
        s.insert(word);
    }

    cout << s.size();

    return 0;
}